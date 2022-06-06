#include<iostream>
using namespace std;

template<class type>
class Matrix{
private :
    type** matrix;
    int _rows;
    int _columns;

protected :
    void allocateMemory(int rows , int columns){
        _rows = rows;
        _columns = columns;
        this->matrix = new type* [_rows];
        for(int i = 0 ; i < rows ; ++i){
            this->matrix[i] = new type [_columns];
        }
    }

public :
    Matrix(){
        _rows = 0 ;
        _columns = 0;
        matrix = nullptr;
    }

    Matrix(int rows , int columns){
        _rows = rows;
        _columns = columns;
        allocateMemory(_rows , _columns);
    }

    Matrix(Matrix& oldMatrix){
        _rows = oldMatrix._rows;
        _columns = oldMatrix._columns;
        // allocate for the new matrix
        allocateMemory(_rows , _columns);
        // copy elements
        for(int i = 0 ; i < _rows; ++i){
            for(int j = 0 ; j < _columns ; ++j){
                matrix[i][j] = oldMatrix.matrix[i][j];
            }
        }
    }

    int getRows(){
        return _rows;
    }

    int getColunms(){
        return _columns;
    }


    Matrix<type> operator + (Matrix& addMatrix){
        Matrix<type> result(addMatrix._rows , addMatrix._columns);
        for(int i = 0 ; i < _rows ; ++i){
            for(int j = 0 ; j < _columns ; ++j){
                result.matrix[i][j] = this->matrix[i][j] + addMatrix.matrix[i][j];
            }
        }
        return result;
    }

    Matrix<type> operator -(Matrix& subMatrix){
        Matrix<type> result(subMatrix._rows , subMatrix._columns);
        for(int i = 0 ; i < _rows ;++i){
            for(int j = 0 ; j < _columns ; ++j){
                result.matrix[i][j] = this->matrix[i][j] - subMatrix.matrix[i][j];
            }
        }
        return result;
    }

    Matrix<type> operator *(Matrix& mulMatrix){
        Matrix<type> result(this->_rows , mulMatrix._columns);
        for(int i = 0 ; i < this->_rows ; ++i){
            for(int j = 0 ; j < mulMatrix._columns ; ++j){
                long long sum = 0;
                for(int k = 0 ; k < this->_columns; ++k){
                    sum += this->matrix[i][k] * mulMatrix.matrix[k][j];
                }
                result.matrix[i][j] = sum;
            }
        }
        return result;
    }

    void operator = (const Matrix& oldMatrix){
        this->_rows = oldMatrix._rows;
        this->_columns = oldMatrix._columns;
        allocateMemory(this->_rows , this->_columns);
        for(int i = 0 ; i < this->_rows ; ++i){
            for(int j = 0 ; j < this->_columns ;++j){
                this->matrix[i][j] = oldMatrix.matrix[i][j];
            }
        }
    }

    friend istream& operator >> (istream& input , Matrix& newMatrix){
        bool validate = false;
        while(newMatrix._rows == 0 || newMatrix._columns == 0){
            validate = true;
            cout << "Enter the dimensions of the matrix : ";
            input >> newMatrix._rows >> newMatrix._columns;
        }

        while(newMatrix._rows < 0 || newMatrix._columns < 0){
            validate = true;
            cout << "Enter a valid dimensions : ";
            input >> newMatrix._rows >> newMatrix._columns;
        }

        if(validate) newMatrix.allocateMemory(newMatrix._rows , newMatrix._columns);

        cout << "Enter the Elements of the matrix : " << endl;
        for(int i = 0 ; i < newMatrix._rows ; ++i){
            for(int j = 0 ; j < newMatrix._columns ; ++j){
                input >> newMatrix.matrix[i][j];
            }
        }
        return input ;
    }

    friend ostream& operator << (ostream& output , const Matrix& matrix){
        cout << "The Matrix is : " << endl ;
        for(int i = 0 ; i < matrix._rows ; ++i){
            for(int j = 0 ; j < matrix._columns ; ++j){
                output << matrix.matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        return output ;
    }

    void transpose(){
        Matrix<type>tmp(_rows , _columns);
        for(int i = 0 ; i < _rows ; ++i){
            for(int j = 0 ; j < _columns ; ++j){
                tmp.matrix[i][j] = this->matrix[i][j] ;
            }
        }

        for(int i = 0 ; i < _rows ; ++i){
            delete [] matrix[i];
        }
        delete matrix;

        allocateMemory(this->_columns , this->_rows);

        for(int i = 0 ; i < this->_rows ; ++i){
            for(int j = 0 ; j < this->_columns ; ++j){
                matrix[i][j] = tmp.matrix[j][i];
            }
        }
    }

    ~Matrix(){
        for(int i = 0 ; i < _rows ; ++i){
            delete [] matrix[i];
        }
        delete matrix;
    }
};