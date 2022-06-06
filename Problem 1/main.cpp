#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class BigInt{
    public:
        vector<int> digits;
        bool isNegative = false;
    private:
        vector<int> performAddition(vector<int> firstBigInt, vector<int> secondBigInt){
            vector<int> result;
            bool carry = false;
            int sum = 0;
            for(int i = 0; i < min(firstBigInt.size(), secondBigInt.size()); ++i){
                sum = firstBigInt[i] + secondBigInt[i] + carry;
                (sum > 9) ? carry = true : carry = false;
                result.push_back(sum%10);
            }
            if(firstBigInt.size() < secondBigInt.size()){
                for(int i = firstBigInt.size(); i < secondBigInt.size(); ++i){
                    sum = secondBigInt[i] + 0 + carry;
                    (sum > 9) ? carry = true : carry = false;
                    result.push_back(sum%10);
                }
            }else if(firstBigInt.size() > secondBigInt.size()){
                for(int i = secondBigInt.size(); i < firstBigInt.size(); ++i){
                    sum = firstBigInt[i] + 0 + carry;
                    (sum > 9) ? carry = true : carry = false;
                    result.push_back(sum%10);
                }
            }

            if(carry)result.push_back(1);
            return result;
        }

        vector<int> performSubtraction(vector<int> firstBigInt, vector<int> secondBigInt, bool& resultIsNegative){
            vector<int> result;
            bool carry = false;
            int sum = 0;
            for(int i = 0; i < secondBigInt.size(); ++i){
                secondBigInt[i] = abs(secondBigInt[i] - 9);
            }
            for(int i = 0; i < min(firstBigInt.size(), secondBigInt.size()); ++i){
                sum = firstBigInt[i] + secondBigInt[i] + carry;
                (sum > 9) ? carry = true : carry = false;
                result.push_back(sum%10);
            }
            if(firstBigInt.size() < secondBigInt.size()){
                for(int i = firstBigInt.size(); i < secondBigInt.size(); ++i){
                    sum = secondBigInt[i] + 0 + carry;
                    (sum > 9) ? carry = true : carry = false;
                    result.push_back(sum%10);
                }
            }else if(firstBigInt.size() > secondBigInt.size()){
                for(int i = secondBigInt.size(); i < firstBigInt.size(); ++i){
                    sum = firstBigInt[i] + 9 + carry;
                    (sum > 9) ? carry = true : carry = false;
                    result.push_back(sum%10);
                }
            }

            if(carry){
                for(int i = 0; i < result.size() && carry; ++i){
                    sum = result[i] + 1;
                    (sum > 9) ? carry = 1 : carry = 0;
                    result[i] = sum%10;
                }
                
            }else{
                resultIsNegative = true;
                for(int i = 0; i < result.size(); ++i){
                    result[i] = abs(result[i] - 9);
                }
            }
            return result;
            
        }
    public:
        BigInt(string decStr){
            //Check for wrong position for negative sign or multiple ones e.g. (--12398123) or (123123-1248)
            bool wrongNegativeSignPosition = false;
            for(int i = 0; i < decStr.size(); ++i){
                if(decStr[i] == '-' && i > 0){
                    wrongNegativeSignPosition = true;
                    break;
                }
            }
            if(wrongNegativeSignPosition){
                throw "Bad input (found multiple negative signs or one negative sign in wrong position)";
            }


            //Check for any + signs in the number (not allowed) e.g. (+12389912)
            bool foundPlusSign = false;
            for(int i = 0; i < decStr.size(); ++i){
                if(decStr[i] == '+'){
                    foundPlusSign = true;
                    break;
                }
            }
            if(foundPlusSign){
                throw "Bad input (plus sign is not allowed in the integer)";
            }


            //Check if number is negative
            if(decStr[0] == '-')isNegative = true;


            //Check if there is any trailing zeroes e.g. (00012371238)
            bool zeroBeforeAnyDigit = false;
            bool foundDigit = false;
            for(int i = 0 + isNegative; i < decStr.size(); ++i){
                if(decStr[i] == '0' && !foundDigit){
                    zeroBeforeAnyDigit = true;
                }else if(decStr[i] != '0'){
                    foundDigit = true;
                }
                digits.push_back(decStr[i] - '0');
            }
            if(decStr.size() - isNegative > 1 && zeroBeforeAnyDigit){
                throw "Bad input (found zero before any digit in integer bigger than one digit)";
            }

            //Check if there is alphabets in the integer e.g. (asdad12389)
            bool foundAlphabet = false;
            for(int i = 0 + isNegative; i < decStr.size(); ++i){
                if(isalpha(decStr[i])){
                    foundAlphabet = true;
                    break;
                }
            }
            if(foundAlphabet){
                throw "Bad input (found alphabets in the integer)";
            }

            reverse(digits.begin(), digits.end());
        }
        BigInt(int decInt){
            if(decInt == 0){
                digits.push_back(0);
            }else if(decInt == -0){
                digits.push_back(0);
                isNegative = true;
            }else{
                if(decInt < 0){
                    decInt *= -1;
                    isNegative = true;
                }
                while(decInt > 0){
                    digits.push_back(decInt%10);
                    decInt /= 10;
                }
            }
        }

        BigInt operator+(BigInt anotherDec){
            string tmp = "";
            vector<int> result;
            bool isResultNegative = false;
            if(this->isNegative == anotherDec.isNegative){
                if(this->isNegative)isResultNegative = true;
                result = performAddition(this->digits, anotherDec.digits);
            }else{
                if(this->isNegative){
                    result = performSubtraction(anotherDec.digits, this->digits, isResultNegative);
                }else{
                    result = performSubtraction(this->digits, anotherDec.digits, isResultNegative);
                }
            }
            for(int i = result.size() - 1; i >= 0; --i){
                tmp += (result[i] + '0');
            }
            bool foundDigit = false;
            int lengthToRemove = 0;
            for(int i = 0; i < result.size(); ++i){
                if(tmp[i] > '0'){
                    foundDigit = true;
                }
                if(!foundDigit){
                    lengthToRemove++;
                }
            }
            tmp.erase(0, lengthToRemove);
            if(isResultNegative){
                return BigInt('-' + tmp);
            }
            return BigInt(tmp);
        }

        BigInt operator-(BigInt anotherDec){
            anotherDec.isNegative ^= true;
            return *this + anotherDec;
        }
        BigInt operator=(BigInt anotherDec){
            this->digits = anotherDec.digits;
            this->isNegative = anotherDec.isNegative;

            return *this;
        }
        friend ostream& operator<<(ostream& out, BigInt b){
            if(b.isNegative)cout << '-';
            for(int i = b.size() - 1; i >= 0; --i){
                out << b.digits[i];
            }
            return out;
        }

        int size() const{
            return digits.size();
        }
};



int main(){
    //Exception handling for construction errors
    /*
        try{
            BigInt num1("----931123");
            BigInt num2("9asd967");
            BigInt num3("+++1293192");
            BigInt num4("12837182-12378");
        }catch(char const* message){
            cout << message << endl;
        }
    */

    //Test Cases for performing operations on BigInts

    //Test Case #1
    cout << "Test Case #1" << endl;
    BigInt num1_t1("123456789012345678901234567890");
    BigInt num2_t1("113456789011345678901134567890");
    BigInt num3_t1 = num2_t1 + num1_t1;
    cout << "num1 = " << num1_t1 << endl;
    cout << "num2 = " << num2_t1 << endl;
    //236913578023691357802369135780
    cout << "num2 + num1 = " << num3_t1 << endl;
    cout << endl;
    //Test Case #2
    cout << "Test Case #2" << endl;
    BigInt num1_t2("-123456789012345678901234567890");
    BigInt num2_t2("113456789011345678901134567890");
    BigInt num3_t2 = num2_t2 + num1_t2;
    cout << "num1 = " << num1_t2 << endl;
    cout << "num2 = " << num2_t2 << endl;
    //-10000000001000000000100000000
    cout << "num2 + num1 = " << num3_t2 << endl;
    cout << endl;

    //Test Case #3
    cout << "Test Case #3" << endl;
    BigInt num1_t3("12345678123128901234567890");
    BigInt num2_t3("113456789011111118901134567890");
    BigInt num3_t3 = num2_t3 - num1_t3;
    cout << "num1 = " << num1_t3 << endl;
    cout << "num2 = " << num2_t3 << endl;
    //113444443332987989999900000000
    cout << "num2 - num1 = " << num3_t3 << endl;
    cout << endl;

    //Test Case #4
    cout << "Test Case #4" << endl;
    BigInt num1_t4("-12345678123128901234567890");
    BigInt num2_t4("113456789011111118901134567890");
    BigInt num3_t4 = num2_t4 - num1_t4;
    cout << "num1 = " << num1_t4 << endl;
    cout << "num2 = " << num2_t4 << endl;
    //113469134689234247802369135780
    cout << "num2 - num1 = " << num3_t4 << endl;
    cout << endl;

    //Test Case #5
    cout << "Test Case #5" << endl;
    BigInt num1_t5("-12345678123128901234567890");
    BigInt num2_t5("-113456789011111118901111167890");
    BigInt num3_t5 = num2_t5 + num1_t5;
    cout << "num1 = " << num1_t5 << endl;
    cout << "num2 = " << num2_t5 << endl;
    //-113469134689234247802345735780
    cout << "num2 + num1 = " << num3_t5 << endl;
    cout << endl;
    return 0;
}