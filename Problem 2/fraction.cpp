#include <iostream>
#include "fraction.h"
using namespace std;

int gcd(int a, int b){
    if(b == 0) return a;
    return gcd(b, a%b);
}

int lcm(int a , int b){
    return (a * b)/gcd(a , b);
}


Fraction Fraction::operator+(Fraction anotherFrac){
    Fraction result;
    result.numerator = (this->numerator * anotherFrac.denominator) + (anotherFrac.numerator * this->denominator);
    result.denominator = this->denominator * anotherFrac.denominator;
    result.reduce();
    return result;
}

Fraction Fraction::operator-(Fraction anotherFrac){
    Fraction result;
    result.numerator = (this->numerator * anotherFrac.denominator) + ((anotherFrac.numerator*-1) * this->denominator);
    result.denominator = this->denominator * anotherFrac.denominator;
    result.reduce();
    return result;
}

bool Fraction::operator<(Fraction anotherFrac){
    bool result = false;

    if(this->denominator == anotherFrac.denominator){
        return this->numerator < anotherFrac.numerator;
    }
    int tmpDenominator = this->denominator;
    this->numerator *= anotherFrac.denominator;
    this->denominator *= anotherFrac.denominator;
    anotherFrac.denominator *= tmpDenominator;
    anotherFrac.numerator *= tmpDenominator;
    if(this->numerator < anotherFrac.numerator) result = true;
    this->reduce();
    anotherFrac.reduce();
    return result;
}

bool Fraction::operator<=(Fraction anotherFrac){
    bool result = false;

    if(this->denominator == anotherFrac.denominator){
        return this->numerator <= anotherFrac.numerator;
    }
    int tmpDenominator = this->denominator;
    this->numerator *= anotherFrac.denominator;
    this->denominator *= anotherFrac.denominator;
    anotherFrac.denominator *= tmpDenominator;
    anotherFrac.numerator *= tmpDenominator;
    if(this->numerator <= anotherFrac.numerator) result = true;
    this->reduce();
    anotherFrac.reduce();
    return result;
}

bool Fraction::operator>(Fraction anotherFrac){
    bool result = false;

    if(this->denominator == anotherFrac.denominator){
        return this->numerator > anotherFrac.numerator;
    }
    int tmpDenominator = this->denominator;
    this->numerator *= anotherFrac.denominator;
    this->denominator *= anotherFrac.denominator;
    anotherFrac.denominator *= tmpDenominator;
    anotherFrac.numerator *= tmpDenominator;

    if(this->numerator > anotherFrac.numerator) result = true;
    this->reduce();
    anotherFrac.reduce();
    return result;
}

bool Fraction::operator==(Fraction anotherFrac){
    this->reduce();
    anotherFrac.reduce();
    if(this->numerator == anotherFrac.numerator && this->denominator == anotherFrac.denominator){
        return true;
    }
    return false;
}



bool Fraction::operator>=(Fraction anotherFrac){
    bool result = false;

    if(this->denominator == anotherFrac.denominator){
        return this->numerator >= anotherFrac.numerator;
    }
    int tmpDenominator = this->denominator;
    this->numerator *= anotherFrac.denominator;
    this->denominator *= anotherFrac.denominator;
    anotherFrac.denominator *= tmpDenominator;
    anotherFrac.numerator *= tmpDenominator;
    if(this->numerator >= anotherFrac.numerator)result = true;
    this->reduce();
    anotherFrac.reduce();
    return result;
}



Fraction Fraction::operator/(Fraction anotherFrac){
    Fraction result;
    result.numerator = this->numerator * anotherFrac.denominator;
    result.denominator = this->denominator * anotherFrac.numerator;
    result.reduce();
    return result;
}


Fraction Fraction::operator*(Fraction anotherFrac){
    Fraction result;
    result.numerator = this->numerator * anotherFrac.numerator;
    result.denominator = this->denominator * anotherFrac.denominator;
    result.reduce();
    return result;
}



void Fraction::reduce(){
    int gcdRes = gcd(this->numerator , this->denominator);
    this->numerator /= gcdRes;
    this->denominator /= gcdRes;
}

istream& operator >> (istream& input, Fraction& fraction){
    cout << "Enter numerator : " ;
    input >> fraction.numerator ;
    cout << "Enter denominator : ";
    input >> fraction.denominator;

    fraction.reduce();

    while(fraction.denominator == 0){
        cout << "Enter a valid denominator." << endl;
        cout << "Enter again the fraction denominator: ";
        input >> fraction.denominator;
    }

    return input;
}

ostream& operator<<(ostream& output, Fraction fraction){
    output << fraction.numerator << '/' << fraction.denominator;
    return output;
}


