#include <iostream>
#include <vector>

using namespace std;

class StudentName{
    private:
        string _name;
    public:
        StudentName(string name){
            vector<string> tmp;
            string word = "";
            for(int i = 0; i < name.size(); ++i){
                if(name[i] != ' '){
                    word += name[i];
                }
                if(name[i] == ' ' || i == name.size() - 1){
                    tmp.push_back(word);
                    word = "";
                }
            }

            if(tmp.size() == 1){
                tmp.push_back(tmp[0]);
                tmp.push_back(tmp[0]);
            }else if(tmp.size() == 2){
                tmp.push_back(tmp[1]);
            }

            for(int i = 0; i < tmp.size(); ++i){
                if(i < tmp.size() - 1){
                    _name += tmp[i] + ' ';
                }else{
                    _name += tmp[i];
                }
            }
        }

        void print(){
            int cnt = 1;
            cout << cnt << ')' << ' ';
            for(int i = 0; i < _name.size(); ++i){
                if(_name[i] != ' '){
                    cout << _name[i];
                }else{
                    cnt++;
                    cout << endl;
                    cout << cnt << ')' << ' ';
                }
            }
            cout << endl;
        }

        bool replace(int i, int j){
            i--;
            j--;
            vector<string> tmp;
            string word = "";
            for(int i = 0; i < _name.size(); ++i){
                if(_name[i] != ' '){
                    word += _name[i];
                }
                if(_name[i] == ' ' || i == _name.size() - 1){
                    tmp.push_back(word);
                    word = "";
                }
            }
            if(i < 0 || j < 0 || i > tmp.size() - 1 || j > tmp.size() - 1){
                return false;
            }else{
                swap(tmp[i],tmp[j]);
                _name = "";
                for(int i = 0; i < tmp.size(); ++i){
                    if(i < tmp.size() - 1){
                        _name += tmp[i] + ' ';
                    }else{
                        _name += tmp[i];
                    }
                }
            }
            return true;
        }
};
int main(){
    StudentName name1("ahmed Mohamed sayed");
    StudentName name2("sara ahmed");
    StudentName name3("Khaled");
    StudentName name4("aya ali ahmed sayed");
    StudentName name5("bemwa malak gerges");

    if(name1.replace(1,2)){
        cout << "Replacement operation succeded" << endl;
    }else{
        cout << "Replacement operation failed" << endl;
    }
    name1.print();

    if(name2.replace(4,2)){
        cout << "Replacement operation succeded" << endl;
    }else{
        cout << "Replacement operation failed" << endl;
    }
    name2.print();

    if(name3.replace(3,2)){
        cout << "Replacement operation succeded" << endl;
    }else{
        cout << "Replacement operation failed" << endl;
    }
    name3.print();

    if(name4.replace(1,200)){
        cout << "Replacement operation succeded" << endl;
    }else{
        cout << "Replacement operation failed" << endl;
    }
    name4.print();


    if(name5.replace(1,1)){
        cout << "Replacement operation succeded" << endl;
    }else{
        cout << "Replacement operation failed" << endl;
    }
    name5.print();






    return 0;
}