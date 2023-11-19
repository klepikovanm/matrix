#include <iostream>
#include <fstream> //для файлов
#include <string> //для строк

using namespace std;

class Matrix{
private: //спецификатор доступа, в котором лежат переменные - элементы данных, доступ к которым есть только у методов класса
    int lines,columns;
    int** matrix;
public: //спецификатор доступа, который позволяет вызывать другим функциям методы класса

    //Конструктор: k_lines - количество строк, k_columns - количество столбцов
    Matrix(int k_lines, int k_columns) {
        lines = k_lines;
        columns = k_columns;
        //создание двуменого массива для матриц - [номер строки][номер столбца]
        matrix = (int**) new int* [lines];
        for (int i=0; i<lines; i++) {
             matrix[i] = (int*) new int [columns];
        };
        //заполнение массива нулями
        for (int i=0; i<lines; i++){
            for (int j=0; j<columns; j++) {
                matrix[i][j]=0;
            }
        }
    }

    //set-функции инициализируют элементы данных
    //n_lines - номер строки, n_columns - номер столбца, number - число
    void setMatrix(int n_lines, int n_columns, int number) {
        matrix[n_lines][n_columns] = number;
    }

    //get-функции позволяют посмотреть значения элементов данных
    void getMatrix(const char* name) {
        cout << "Введенная матрица " << name << ":" << endl;
        for (int i=0; i<lines; i++) {
            for (int j=0; j<columns; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    //Деструктор: нужен, чтобы освободить память, которая была выделена для двумерного массива
    ~Matrix() {
        for (int i=0; i<lines; i++) {
            delete [] matrix[i];
        }
    }


};
int main() {    
    //Ввод матрицы А вручную:
    int lines_A,columns_A;
    int number_A;
    cout << "Введите количество строк матрицы А: ";
    cin >> lines_A;
    cout << "Введите количество столбцов матрицы А: ";
    cin >> columns_A;
    Matrix A(lines_A, columns_A); //объявление объекта - матрица А
    for (int i=0; i<lines_A; i++) {
        for (int j=0; j<columns_A; j++) {
            cout << "Введите число: строка - " << i+1 << "; столбец - " << j+1 << ": ";
            cin >> number_A;
            A.setMatrix(i, j, number_A);//инициализация матрицы
        }
    }
    A.getMatrix("A");

    //Ввод матрицы В с использованием файла
    
    ifstream file("matrix_B.txt"); //файловый поток
    if (file.is_open()) {//если файл открыт, считаем элементы, пока не дойдем до конца
        int k_B=0;
        int number;
        while (!file.eof()) {
            file >> number; //считываем текущий символ 
            k_B++;
        }

        file.clear();//возвращаем файл в рабочее состояние
        file.seekg(0, ios::beg); //сброс указателя на начало (перемещаем на 0 относительно начала) 

        //считаем количество строк
        int lines_B=0;
        string line;
        while(getline(file,line)) {
            file >> line;
            lines_B++;
        }
        //считаем количество столбцов
        int columns_B;
        columns_B = k_B / lines_B;

        file.clear();
        file.seekg(0, ios::beg);

        //считываем матрицу 
        Matrix B(lines_B, columns_B);
        for (int i=0; i<lines_B; i++) {
            for (int j=0; j<columns_B; j++) {
                int number_B;
                file >>  number_B;
                cout << number_B << " ";
                B.setMatrix(i, j, number_B);//инициализация матрицы
            }
        }
        B.getMatrix("B");
        cout << lines_B << columns_B;
    }
    file.close();

    return 0;
}