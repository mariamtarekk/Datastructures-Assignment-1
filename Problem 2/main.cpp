#include <iostream>
#include "fraction.h"
using namespace std;

class FractionCalculator{
    private:
        Fraction fraction;
        void addAnotherFraction(){
            Fraction anotherFrac;
            cin >> anotherFrac ;
            fraction = fraction + anotherFrac;
            cout << fraction << endl;
        }
        
        void enterFraction(){
            cin >> fraction;
        }
        
        void subtractAnotherFraction(){
            Fraction anotherFrac;
            cin >> anotherFrac ;
            fraction = fraction - anotherFrac;
            cout << fraction << endl;

        }

        void multiplyByAnotherFraction(){
            Fraction anotherFrac;
            cin >> anotherFrac ;
            fraction = fraction * anotherFrac;
            cout << fraction << endl;

        }
        
        void divideByAnotherFraction(){
            Fraction anotherFrac;
            cin >> anotherFrac ;
            fraction = fraction / anotherFrac;
            cout << fraction << endl;

        }

        void compareWithAnotherFraction(short choice){
            Fraction anotherFrac;
            cin >> anotherFrac;
            switch(choice){
                case 6:
                    if(fraction == anotherFrac){
                        cout << fraction << " Is equal to " << anotherFrac << endl;
                    }else{
                        cout << fraction << " Is not equal to " << anotherFrac << endl;
                    }
                    break;
                case 7:
                    if(fraction < anotherFrac){
                        cout << fraction << " Is less than " << anotherFrac << endl;
                    }else{
                        cout << fraction << " Is not less than " << anotherFrac << endl;
                    }
                    break;
                case 8:
                    if(fraction > anotherFrac){
                        cout << fraction << " Is greater than " << anotherFrac << endl;
                    }else{
                        cout << fraction << " Is not greater than " << anotherFrac << endl;
                    }
                    break;

                case 9:
                    if(fraction <= anotherFrac){
                        cout << fraction << " Is less than or equal to " << anotherFrac << endl;
                    }
                    else {
                        cout << fraction << " Is not less than or equal to " << anotherFrac << endl;
                    }
                    break;

                case 10 :
                    if(fraction >= anotherFrac){
                        cout << fraction << " Is greater than or equal to " << anotherFrac << endl;
                    }else{
                        cout << fraction << " Is not greater than or equal to " << anotherFrac << endl;
                    }
                    break;
            }
        }
    public:
        void showMenu(){
            cout << endl << endl;
            cout << "Please choose your prefered operation: " << endl;
            cout << "1- Enter a fraction" << endl;
            cout << "2- Add another fraction" << endl;
            cout << "3- Subtract a fraction" << endl;
            cout << "4- Multiply by a fraction" << endl;
            cout << "5- Divide by a fraction" << endl;
            cout << "6- Compare with a fraction (==)" << endl;
            cout << "7- Compare with a fraction (<)" << endl;
            cout << "8- Compare with a fraction (>)" << endl;
            cout << "9- Compare with a fraction (<=)" << endl;
            cout << "10- Compare with a fraction (>=)" << endl;
            cout << "11- Exit" << endl;

            short choice;
            cin >> choice;
            switch(choice){
                case 1:
                    enterFraction();
                    break;
                case 2:
                    addAnotherFraction();
                    break;
                case 3:
                    subtractAnotherFraction();
                    break;
                case 4:
                    multiplyByAnotherFraction();
                    break;
                case 5:
                    divideByAnotherFraction();
                    break;
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                    compareWithAnotherFraction(choice);
                    break;
                case 11:
                    exit(0);
                    break;
                default: cout << "Invalid option." << endl;
            }
        }
};


int main(){
    
    FractionCalculator calculator;

    while(true){
        calculator.showMenu();
    }
}