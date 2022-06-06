#include <iostream>
using namespace std;
class Fraction{
    public:
        int numerator;
        int denominator;
    public:
        Fraction operator+(Fraction);
        Fraction operator-(Fraction);
        bool operator<(Fraction);
        bool operator<=(Fraction);
        bool operator>(Fraction);
        bool operator>=(Fraction);
        Fraction operator/(Fraction);
        Fraction operator*(Fraction);
        bool operator==(Fraction );
        void reduce();
        friend istream& operator >>(istream&, Fraction&);
        friend ostream& operator <<(ostream&, Fraction) ;
};