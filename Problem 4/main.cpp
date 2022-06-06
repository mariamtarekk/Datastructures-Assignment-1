#include <iostream>
#include <set>
using namespace std;
 
void RecPermute(string soFar, string rest , set<string> &checked){
    if (rest == ""){ // No more characters
        if((checked.find(soFar)) != checked.end()){ // Check if the word is already printed
            return;
        }else{
            checked.insert(soFar);
            cout << soFar << endl;  // Print the word
        }
    }
    else // Still more chars
    // For each remaining char
    for (int i = 0; i < rest.length(); i++) {
        string next = soFar + rest[i]; // Glue next char
        string remaining = rest.substr(0, i) + rest.substr(i+1);
        RecPermute(next, remaining, checked);
    }
}

// "wrapper" function
void ListPermutations(string s) {
    set<string> checked;
    RecPermute("", s, checked);
}

 
int main(){
    ListPermutations("Makka");

}