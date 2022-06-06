#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>
using namespace std;
using namespace std::chrono;

class Sorter{
    public:
        virtual void Sort(vector<int>& arr , int size ){}
        void Print(vector<int> & v , int size){
            for(int i = 0 ; i < size ; ++i){
                cout << v[i] << " ";
            }
            cout << endl;
        }
};


class SelectionSorter : public Sorter{
    public :
        void Sort(vector<int> &arr , int size){
            for(int i = 0 ; i < size ; ++i){
                int idx_mn = i ;
                for(int j = i + 1 ; j < size ; ++j){
                    if(arr[j] < arr[idx_mn]){
                        idx_mn  = j ;
                    }
                }
                swap(arr[idx_mn] , arr[i]);
            }
        }
};

class QuickSorter : public Sorter{
    public:
        void Sort(vector<int>&arr , int size){
            quickSort(arr , 0 , size - 1);
        }  

        int Partition(vector<int>& arr, int left , int right){
            int idx_first = left;
            int j = left;
            for(int i = left + 1 ; i <= right ; ++i){
                if( arr[i] < arr[idx_first] ){
                    j++;
                    swap(arr[i] , arr[j] );
                }
            }
            swap(arr[idx_first] , arr[j]);
            return j;
        }
        
        void quickSort(vector<int>& arr ,int left , int right ){
            if(left >= right)return;
            int middle = Partition(arr, left , right);
            quickSort( arr, left , middle - 1 );
            quickSort(arr, middle + 1 , right);
        }
          
};

class Testbed{
    public:
        vector<int> GenerateRandomList(int min, int max, int size){
            vector<int>listOfRandomIntegers(size);
            for(int i = 0; i < size; i++){
                listOfRandomIntegers[i] = (rand()%(max-min)+min);
            }
            return listOfRandomIntegers;
        }

        vector<int> GenerateReverseOrderedList(int min, int max, int size){
            vector<int>listOfRandomIntegers(size);
            for(int i = 0; i < size; i++){
                listOfRandomIntegers[i] = (rand()%(max-min)+min);
            }
            QuickSorter sorter;
            sorter.Sort(listOfRandomIntegers, size);
            reverse(listOfRandomIntegers.begin(), listOfRandomIntegers.end());
            return listOfRandomIntegers;
        }
        

        double RunOnce(Sorter* sorter, vector<int> data, int size){
            auto start = steady_clock::now();
            sorter->Sort(data, size);
            auto stop = steady_clock::now();
        
            auto duration = duration_cast<milliseconds>(stop - start);
            return duration.count();
        }
        long double RunAndAverage(Sorter* sorter, bool type, int min, int max, int size, int sets_num){ //type is sorted = 0, or reversed = 1
            long double sum = 0;
            vector<int>dataSet;
            if(type == 0){
                for(int i = 0; i < sets_num; i++){
                    dataSet = GenerateRandomList(min, max, size);
                    sum += RunOnce(sorter, dataSet, size);
                }   
            }else{
                for(int i = 0; i < sets_num; i++){
                    dataSet = GenerateReverseOrderedList(min, max, size);
                    sum += RunOnce(sorter, dataSet, size);
                }   
            }
            return sum/sets_num;
        } 
        void RunExperiement(Sorter* sorter, bool type, int min, int max, int min_val, int max_val, int sets_num, int step){
            cout << "Set Size\t\t\t\t\t" << setw(10) << "Average Time(MilliSeconds)" << endl;
            long double average;
            for(int i = min_val; i <= max_val; i += step){
                average = RunAndAverage(sorter, type, min, max, i, sets_num);
                cout << i << "\t\t\t | \t\t\t" << setw(10) << average << endl;
                cout << "___________________________________________________________________________" << endl;
            }
        }   
};
int main(){
    Testbed test;
    Sorter* quick = new QuickSorter;
    Sorter* selection = new SelectionSorter;


    cout << "Quick Sort on Random Ordered Data " << endl;
    test.RunExperiement(quick, 0, 10000, 100000, 1000, 100000, 200, 5000);

    cout << endl << endl << "Quick Sort on reversed Ordered Data " << endl;
    test.RunExperiement(quick, 1, 10000, 100000, 1000, 100000, 200, 5000);

    cout  << endl << endl << "Selection Sort on reversed Ordered Data " << endl;
    test.RunExperiement(selection, 1, 1, 100, 1000, 100000, 200, 5000);

    cout << endl << endl << "Selection Sort on Random Ordered Data " << endl;
    test.RunExperiement(selection, 0, 10000, 100000, 1000, 100000, 200, 5000);


}