#include <iostream>
#include <cstring>
using namespace std ;

void BiasedSort( string songs[] , int size ){
    for ( int i = 1 , j , s ; i < size ; i++ , s++ ){
        string tmp = songs[i] ;        
        for ( j = i , s = 0; j > 0 && tmp < songs[j-1] ; j-- ){
            songs[j] = songs[j - 1] ;
            if (songs[j] == "Untitled"){
                songs[s] = songs[j] ;  
            }
        }
        songs[j] = tmp ;
    }
}

int main(){
    int n ;
    cin >> n ;
    string song[n] ;
    for ( int i = 0 ; i < n ; i++ ){
        cin >> song[i] ;
    }
    BiasedSort( song , n );
    for ( int i = 0 ; i < n ; i++ ){
        cout << song[i] <<" ";
    }

}