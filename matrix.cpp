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
        cout << "Матрица " << name << ":" << endl;
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
    //перегрузка оператора *
    //в качестве параметра передаем второй объект, с которым нужно умножить первый
    //передаем константный параметр, чтобы случайно его не изменить; принимаем по ссылке
    Matrix operator *(const Matrix & second) {
        if (this->columns == second.lines) {//через this обращаемся к текущему объекту класса, в котором находимся 
            Matrix T(lines,second.columns);
            for (int i=0; i<lines; i++) {
                for (int j=0; j<second.columns; j++) {
                    T.matrix[i][j] = 0;
                    for (int k=0; k<lines; k++) {
                        T.matrix[i][j] += this->matrix[i][k] * second.matrix[k][j];
                    }
                }
            }
            return T;
        } else if (second.lines == 1 && second.columns == 1) {
            Matrix T(lines,columns);
            for (int i=0; i<lines; i++) {
                for (int j=0; j<columns; j++) {
                    T.matrix[i][j] = this->matrix[i][j] * second.matrix[0][0];
                }
            }
            return T;
        } else {
            Matrix T(lines,second.columns);
            for (int i=0; i<lines; i++) {
                for (int j=0; j<second.columns; j++) {
                    T.matrix[i][j] = 0;
                }
            } 
            return T;
        } 
    } 
    //перегрузка операторов + и -
    Matrix operator +(const Matrix & second) {
        Matrix T(lines,columns); //временная переменная
        if (this->lines == second.lines && this->columns == second.columns) {
            for (int i=0; i<lines; i++) {
                for (int j=0; j<columns; j++) {
                    T.matrix[i][j] = this->matrix[i][j] + second.matrix[i][j];
                }
            }
        } else {
            for (int i=0; i<lines; i++) {
                for (int j=0; j<columns; j++) {
                    T.matrix[i][j] = 0;
                }
            }
        }
        return T;   
    }
    Matrix operator -(const Matrix & second) {
        Matrix T(lines,columns); //временная переменная
        if (this->lines == second.lines && this->columns == second.columns) {
            for (int i=0; i<lines; i++) {
                for (int j=0; j<columns; j++) {
                    T.matrix[i][j] = this->matrix[i][j] - second.matrix[i][j];
                }
            }
        } else {
            for (int i=0; i<lines; i++) {
                for (int j=0; j<columns; j++) {
                    T.matrix[i][j] = 0;
                }
            }
        }
        return T;   
    }
    //перегрузка операторов == и !=
    bool operator ==(const Matrix & second){
        if (this->lines == second.lines && this->columns == second.columns) {
            for (int i=0; i<lines; i++) {
                for (int j=0; j<columns; j++) {
                    if (this->matrix[i][j] != second.matrix[i][j]) {
                        return false;
                    }
                } 
            }
            return true;
        } else {
            return false;
        }
    }
    bool operator !=(const Matrix & second){
        return !(*this == second); //разыменовали this, при проверке на неравенство ссылаемся на равенство
    }
    //функция для сложения строк или столбцов
    //если thing = 0 - строка, если thing = 1 - столбец
    void plus(int thing, int one, int two, int L) {
        if (thing == 0) {
            for (int i=0; i<columns; i++) {
                matrix[one-1][i] += matrix[two-1][i] * L;
            }
        } else {
            for (int i=0; i<lines; i++) {
                matrix[i][one-1] += matrix[i][two-1] * L;
            }
        }
    }    
    //функция для вычитания строк или столбцов
    void minus(int thing, int one, int two, int L) {
        if (thing == 0) {
            for (int i=0; i<columns; i++) {
                matrix[one-1][i] -= matrix[two-1][i] * L;
            }
        } else {
            for (int i=0; i<lines; i++) {
                matrix[i][one-1] -= matrix[i][two-1] * L;
            }
        }
    }
    //функция для преобразования отдельной строки или столбца
    void multiply(int thing, int one, int L) {
        if (thing == 0) {
            for (int i=0; i<columns; i++) {
                matrix[one-1][i] *= L;
            }
        } else {
            for (int i=0; i<lines; i++) {
                matrix[i][one-1] *= L;
            }
        }
    }
    //функция для перестановки строки или столбца
    void change(int thing, int one, int two) {
       int temp;
       if (thing == 0) {
            for (int i=0; i<columns; i++) {
                temp = matrix[one-1][i];
                matrix[one-1][i] = matrix[two-1][i];
                matrix[two-1][i] = temp;
            }
        } else {
            for (int i=0; i<lines; i++) {
                temp = matrix[i][one-1];
                matrix[i][one-1] = matrix[i][two-1];
                matrix[i][two-1] = temp;
            }
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
    //считаем элементы, пока не дойдем до конца
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
            B.setMatrix(i, j, number_B);//инициализация матрицы
        }
    }
    B.getMatrix("B");
    
    file.close();
    
    Matrix C = A * B;
    C.getMatrix("C - умножение матриц");
    int m;
    cout << "Введите число, на которое хотите умножить матрицу А: ";
    cin >> m;
    Matrix Scalar(1,1);
    Scalar.setMatrix(0,0,m);
    Matrix D = A * Scalar;
    D.getMatrix("D - умножение на скаляр");

    Matrix E = A + B;
    E.getMatrix("E - сложение");
    Matrix F = A - B;
    F.getMatrix("F - вычитание");

    bool equal = A==B;
    bool not_equal = A!=B;
    cout << "A и В равны? - " << equal << endl;
    cout << "А и В не равны? - " << not_equal << endl;

    A.plus(0,1,2,3);
    A.getMatrix("A - к первой строке прибавили вторую, умноженную на 3");
    A.minus(0,2,1,2);
    A.getMatrix("A - из второй строки вычли первую, умноженную на 2");
    A.multiply(1,2,6);
    A.getMatrix("А - второй столбец умножаем на 6");
    A.change(1,1,2);
    A.getMatrix("A - первый столбец меняем со вторым");
    return 0;
}