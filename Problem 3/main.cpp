#include<iostream>
#include "Matrix.h"

using namespace std;

class MatrixCalculator{
    private :
           void description(){
            cout << " Welcome to Matrix Calculator. " << endl;
            cout << " _____________________________________" << endl;
            cout << " 1- Perform Matrix Addition" << endl
                  << " 2- Perform Matrix Subtraction" << endl
                  << " 3- Perform Matrix Multiplication" << endl
                  <<" 4- Matrix Transpose" << endl;
            }   
    public : 
        void menu(){
            description();
            short choice ;
            cout << "Enter your choice : " ;
            cin >> choice ;
            switch (choice){
                case 1 :{
                    Matrix<int>firstMatrix;
                    cin >> firstMatrix ;
                    Matrix<int> secondMatrix ,  result ;
                    cin >> secondMatrix;
                    if(firstMatrix.getRows() == secondMatrix.getRows()  && firstMatrix.getColunms() == secondMatrix.getColunms() ){
                        result = firstMatrix + secondMatrix;
                        cout << result;
                    }
                    else {
                        cout << "invalid operation with these dimensions ." << endl; 
                    }
                    break;
                    
                }
                case 2 :{
                    Matrix<int>firstMatrix;
                    cin >> firstMatrix ;
                    Matrix<int> secondMatrix ,  result ;
                    cin >> secondMatrix;
                    if(firstMatrix.getRows() == secondMatrix.getRows()  && firstMatrix.getColunms() == secondMatrix.getColunms() ){
                        result = firstMatrix + secondMatrix;
                        cout << result;
                    }
                    else{
                        cout << "invalid operation with these dimensions ." << endl; 
                    }
                    break;
                }
                case 3 :{
                    Matrix<int>firstMatrix;
                    cout << "Please enter the first matrix: " << endl;
                    cin >> firstMatrix ;
                    Matrix<int> secondMatrix ,  result ;
                    cout << "Please enter the second matrix: " << endl;
                    cin >> secondMatrix;
                    if(firstMatrix.getColunms() == secondMatrix.getRows() ){
                        result = firstMatrix * secondMatrix;
                        cout << result;
                    }
                    else{
                        cout << "invalid operation with these dimensions ." << endl; 
                    }
                    break;
                }
                case 4 :{
                    Matrix<int>firstMatrix;
                    cin >> firstMatrix ;
                    firstMatrix.transpose();
                    cout << firstMatrix;
                    break;
                }
                default : {
                    cout << "Enter a valid choice ." << endl;
                    break;
                }
            }
        }
};


int main(){
    MatrixCalculator test;
    while(true){
        test.menu();
    }


}