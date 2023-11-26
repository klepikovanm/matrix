#include <iostream>
#include <fstream> //для файлов
#include <string> //для строк

using namespace std;

class Matrix{
private: //спецификатор доступа, в котором лежат переменные - элементы данных, доступ к которым есть только у методов класса
    int lines,columns;
    double** matrix;
    void clear(){
         for (int i=0; i<lines; i++) {
            delete [] matrix[i];
        }
        delete matrix;
    }
public: //спецификатор доступа, который позволяет вызывать другим функциям методы класса

    //Конструктор: k_lines - количество строк, k_columns - количество столбцов
    Matrix(int k_lines, int k_columns) {
        lines = k_lines;
        columns = k_columns;
        //создание двуменого массива для матриц - [номер строки][номер столбца]
        matrix = (double**) new double* [lines];
        for (int i=0; i<lines; i++) {
             matrix[i] = (double*) new double [columns];
        }
    }
    //Конструктор копирования
    Matrix(const Matrix & M) {
        lines = M.lines;
        columns = M.columns;
        matrix = (double**) new double* [lines];
        double** mx = matrix;
        for (int i=0; i<lines; i++) {
             matrix[i] = (double*) new double [columns];
        }
        //заполнение массива нулями
        for (int i=0; i<lines; i++){
            for (int j=0; j<columns; j++) {
                mx[i][j]=M.matrix[i][j];
            }
        }

    }
    //set-функции инициализируют элементы данных
    //n_lines - номер строки, n_columns - номер столбца
    void setMatrix(int n_lines, int n_columns) {
        for (int i=0; i<lines; i++) {
            for (int j=0; j<columns; j++) {
                double number;
                cout << "Введите число: строка - " << i+1 << "; столбец - " << j+1 << ":";
                cin >> number;
                matrix[i][j] = number;
            }
        }
    }
    //функция для считывания матрицы из файла
    void setMatrix_file(const char* file_name) {
        ifstream file(file_name);//открываем файл для чтения
        for (int i=0; i<lines; i++) {
            for (int j=0; j<columns; j++) {
                double number;
                file >> number;
                matrix[i][j] = number;
            }
        }
        file.close();
    }

    //get-функции позволяют посмотреть значения элементов данных
    void getMatrix(const char* name) {
        cout << "Матрица " << name << endl;
        for (int i=0; i<lines; i++) {
            for (int j=0; j<columns; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    //функция для вывода матрицы в файл
    void getMatrix_file(const char* file_name) {
        ofstream file(file_name);//открываем файл для записи
        for (int i=0; i<lines; i++) {
            for (int j=0; j<columns; j++) {
                file << matrix[i][j] << " ";
            }
            file << endl;
        }
        file.close();
    }

    //Деструктор: нужен, чтобы освободить память, которая была выделена для двумерного массива
    ~Matrix() {
        clear();
    }
    //перегрузка оператора * для умножения матриц
    //в качестве параметра передаем второй объект, с которым нужно умножить первый
    //передаем константный параметр, чтобы случайно его не изменить; принимаем по ссылке
    Matrix operator *(const Matrix & second) {
        if (this->columns == second.lines) {//через this обращаемся к текущему объекту класса, в котором находимся 
            cout << "Матрица произведения:" << endl;
            Matrix T(lines,second.columns); //если количество столбцов первой матрицы равно количеству строк второй матрицы, умножаем матрицы
            for (int i=0; i<lines; i++) {
                for (int j=0; j<second.columns; j++) {
                    T.matrix[i][j] = 0;
                    for (int k=0; k<lines; k++) {
                        T.matrix[i][j] += this->matrix[i][k] * second.matrix[k][j];
                    }
                }
            }
            return T;
        } else { //если нет, то матрицы невозможно умножить
            cout << "Матрицы нельзя умножить!" << endl;
            Matrix T(lines,second.columns);
            for (int i=0; i<lines; i++) {
                for (int j=0; j<second.columns; j++) {
                    T.matrix[i][j] = 0;
                }
            }
            return T;
        } 
    } 
    //перегрузка оператора * для умножения матрицы на скаляр
    Matrix operator *(double scalar) {
        Matrix T(lines,columns);
        for (int i=0; i<lines; i++) {
            for (int j=0; j<columns; j++) {
                T.matrix[i][j] = this->matrix[i][j] * scalar;
            }
        }
        return T;
    }
    //перегрузка операторов + и -
    Matrix operator +(const Matrix & second) {
        Matrix T(lines,columns); //временная переменная
        if (this->lines == second.lines && this->columns == second.columns) { //если размерности матриц одинаковые, складываем
            cout << "Матрица сложения:" << endl;
            for (int i=0; i<lines; i++) {
                for (int j=0; j<columns; j++) {
                    T.matrix[i][j] = this->matrix[i][j] + second.matrix[i][j];
                }
            }
            return T;
        } else { //иначе сложить нельзя
            cout << "Матрицы разного порядка, сложить нельзя!" << endl;
            Matrix T(lines,columns); 
            for (int i=0; i<lines; i++) {
                for (int j=0; j<columns; j++) {
                    T.matrix[i][j] = 0;
                }
            }
            return T;
        }  
    }
    Matrix operator -(const Matrix & second) {
        Matrix T(lines,columns); //временная переменная
        if (this->lines == second.lines && this->columns == second.columns) {
            cout << "Матрица вычитания:" << endl;
            for (int i=0; i<lines; i++) {
                for (int j=0; j<columns; j++) {
                    T.matrix[i][j] = this->matrix[i][j] - second.matrix[i][j];
                }
            }
            return T;
        } else {
            cout << "Матрицы разного порядка, вычесть нельзя!" << endl;
            Matrix T(lines,columns);
            for (int i=0; i<lines; i++) {
                for (int j=0; j<columns; j++) {
                    T.matrix[i][j] = 0;
                }
            }
            return T;
        } 
    }
    //перегрузка операторов == и != для сравнения матриц
    bool operator ==(const Matrix & second){
        if (this->lines == second.lines && this->columns == second.columns) { //если размерности матриц совпадают
            for (int i=0; i<lines; i++) {
                for (int j=0; j<columns; j++) {
                    if (this->matrix[i][j] != second.matrix[i][j]) {//проверяем элементы на равенство
                        cout << "Матрицы не равны" << endl;;
                        return false;//при нахождении первого несовпадения false
                    }
                } 
            }
            cout <<  "Матрицы равны" << endl;
            return true; //все совпало true
        } else {
            cout << "Матрицы не равны" << endl;
            return false;//при сравнении матриц их размерность не совпала
        }
    }
    bool operator !=(const Matrix & second){
        return !(*this == second); //разыменовали this, при проверке на неравенство ссылаемся на равенство
    }
    //перегрузка операторов == и != для сравнения матрицы и скаляра 
    bool operator ==(double scalar) {
        for (int i=0; i<lines; i++) {
            for(int j=0; j<columns; j++) {
                if (i!=j && matrix[i][j] != 0) {//если элемент вне главной диагонали не ноль false
                    cout << "Матрица не равна скаляру" << endl;
                    return false;
                } 
                if (i==j && matrix[i][j] != scalar) {//если  элемент на главной диагонали не равен скаляру false
                    cout << "Матрица не равна скаляру" << endl;
                    return false;
                }
            }
        }
        cout << "Матрица равна скаляру" << endl;
        return true;//равенства выполняются true
    }

    bool operator !=(double scalar) {
        return !(*this == scalar);
    }
    //функция для сложения строк или столбцов
    //если thing = 0 - строка, если thing = 1 - столбец
    void plus(int thing, int one, int two, double L) {
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
    void minus(int thing, int one, int two, double L) {
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
    void multiply(int thing, int one, double L) {
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
    
    //функция для нахождения детерминанта
    double determinant() {
        double det=0;
        int one;
        double ** M = this->matrix;
        if (this->lines != this->columns) {//матрица не квадратная, определителя нет
            cout <<  "Невозможно найти определитель!" << endl;
            return 0;
        } else {
            if (lines == 1) { //если порядок матрицы 1 - выводим определитель
                return matrix[0][0];
            } else if (lines == 2) { //порядок матрицы 2 - выводим определитель по формуле
                return (matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0]);
            } else {//если порядок больше - будем искать через матрицы все меньшего порядка
                det = 0;
                for (int i=0; i<lines; i++) {
                    Matrix temp(lines-1,columns-1);
                    for (int j=1; j<lines; j++) {
                        int t = 0;
                        for (int k=0; k<lines; k++) {
                            if (k == i) { //если столбец равен тому, который должен быть вычеркнут, пропускаем его
                                continue;
                            }
                            temp.matrix[j-1][t] = matrix[j][k];
                            t++;
                        }
                    }
                    //знак каждого слагаемого для определителя
                    //i+1 - столбец, +1 - первая строка
                    if ((i+1+1)%2==0) {
                        one = 1;
                    } else {
                        one = -1;
                    }
                    //формула - det += pow(-1,i+1+1)*matrix[0][i]*temp.determinant()
                    //matrix[0][i] - элемент из первой строки
                    det += one*matrix[0][i]*temp.determinant();
                }
            }
        }
        return det;
    }
    //функция для нахождения дополнений
    double addition(int stroka, int stolb) {
        Matrix temp(lines-1,columns-1); //матрица на порядок меньше исходной
        int m_l,m_c; //строки и столбцы исходной матрицы
        m_l=0;
        for (int t_l=0; t_l<lines-1; t_l++) {
            if (t_l==stroka-1) {
                m_l=1;
            }
            m_c=0;
            for (int t_c=0; t_c<lines-1; t_c++) {
                if (t_c == stolb-1) {
                    m_c = 1;
                }
                temp.matrix[t_l][t_c] = matrix[t_l+m_l][t_c+m_c];//заполняем элементами, кроме вычеркнутых строки и столбца
            }
        }
        //знак каждого дополнения
        int one;
        if ((stroka+stolb)%2==0) {
            one = 1;
        } else {
            one = -1;
        }
        return one*temp.determinant();
    }

    //функция для нахождения присоединенной матрицы - A*
    Matrix join() {
        double ** M = this->matrix;
        Matrix temp(lines,columns);//передаем во временную матрицу исходную
        for (int i=0; i<lines; i++) {
                for (int j=0; j<columns; j++){
                    temp.matrix[i][j] = matrix[i][j]; 
                }
        }
        Matrix T(lines,columns);//создаем конечную матрицу
        if (lines != columns) {
            cout << "Присоединенной матрицы нет! Обратите внимание, что исходная не квадратная: ";
            return temp;
        } else {
            for (int i=0; i<lines; i++) {
                for (int j=0; j<columns; j++){
                    T.matrix[i][j] = temp.addition(i+1,j+1); //заполняем элементы конечной матрицы дополнениями, найденными из исходной
                }
            }
        } 
        return T;
    }
    //функция для транспонирования матрицы
    void transposed() {
        Matrix temp(lines,columns);
        for (int i=0; i<lines; i++) {
            for (int j=0; j<lines; j++) {
                temp.matrix[i][j] = matrix[i][j];
            }
        }
        for (int i=0; i<lines; i++) {
            for (int j=0; j<lines; j++) {
                matrix[i][j] = temp.matrix[j][i];
            }
        }
    }
    //перегрузка оператра ! для вычисления обраной матрицы
    Matrix operator !() {
        Matrix temp(lines,columns);//передаем во временную матрицу исходную
        for (int i=0; i<lines; i++) {
            for (int j=0; j<lines; j++) {
                temp.matrix[i][j] = matrix[i][j];
            }
        }
        double det = temp.determinant();
        if (det == 0) {
            cout << "Обратной матрицы не существует! ";
            Matrix zero(lines,columns);
            for (int i=0; i<lines; i++) {
                for (int j=0; j<lines; j++) {
                    zero.matrix[i][j] = 0;
                }
            }
            return zero;
        } else {
            Matrix temp_2 = temp.join();//во вторую временную матрицу передаем присоединенную для исходной
            temp_2.transposed();
            Matrix temp_3 = temp_2 * (1/det);//третья временная матрица - обратная
            cout << "Обратная матрица для заданной ";
            return temp_3;
        }
    }

    Matrix operator =(const Matrix & second) {
        
        clear();
        //4x4 5x5 
        lines = second.lines;
        columns=second.columns;
        matrix = new double * [lines];
        for (int i=0; i<lines; i++) {
            matrix[i] = new double [columns];
            for (int j=0; j<columns; j++) {
                matrix[i][j] = second.matrix[i][j];
            }
        }

    }

};

int main() {    
    //Ввод матрицы А вручную:
    int lines_A,columns_A;
    cout << "Введите количество строк матрицы А: ";
    cin >> lines_A;
    cout << "Введите количество столбцов матрицы А: ";
    cin >> columns_A;
    Matrix A(lines_A, columns_A); //объявление объекта - матрица А
    A.setMatrix(lines_A, columns_A);//инициализация матрицы
    A.getMatrix("A");

    //Ввод матрицы В с использованием файла
    ifstream file("matrix_B.txt"); //файловый поток
    //считаем элементы, пока не дойдем до конца
    int k_B=0;
    double number;
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
    file.close();

    //считываем матрицу 
    Matrix B(lines_B, columns_B);
    B.setMatrix_file("matrix_B.txt");
    B.getMatrix("B");
    
    
    
    Matrix C = A * B;
    C.getMatrix("C");

    double s;
    cout << "Введите скаляр: ";
    cin >> s;
    Matrix D = A * s;
    D.getMatrix("D - матрица, умноженная на скаляр: ");

   Matrix E = A + B;
    E.getMatrix("E");
    Matrix F = A - B;
    F.getMatrix("F");

    bool equal = A==B;
    bool not_equal = A!=B;

    double r;
    cout << "Введите скаляр: ";
    cin >> r;
    bool equal_scalar = A==r;
    bool not_equal_scalar = A!=r;
    
   /* 
   //Элементарные преобразования
    A.plus(0,1,2,3);
    A.getMatrix("A - к первой строке прибавили вторую, умноженную на 3");
    A.minus(0,2,1,2);
    A.getMatrix("A - из второй строки вычли первую, умноженную на 2");
    A.multiply(1,2,6);
    A.getMatrix("А - второй столбец умножаем на 6");
    A.change(1,1,2);
    A.getMatrix("A - первый столбец меняем со вторым");
    A.getMatrix_file("matrix_B.txt");
    */

    cout << "Определитель матрицы A: " << A.determinant() << endl;

    Matrix G = !A;
    G.getMatrix("A^(-1) обратная для A: ");

}