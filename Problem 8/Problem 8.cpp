#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <chrono>

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

class InsertionSorter : public Sorter{
    public :
        void Sort(vector<int> &arr , int size){
            for(int i = 1, j; i < size; i++){
                int temp = arr[i];
                for (j = i-1 ; (j >=0 && arr[j] > temp ); j--){
                    arr[j+1] = arr[j];
                }
                arr[j+1] = temp ;
            }
        }
};

class ModifiedInsertionSorter : public Sorter{
    public :
        void Sort(vector<int> &arr , int size){
            for(int i = 1; i < size; i++){
                int item = arr[i];
                int pos = BinarySearch(arr , arr[i] , i );
                for(int j = i ; j > pos ; --j){
                    arr[j] = arr[j - 1];
                }
                arr[pos] = item;
            }
        }

        int BinarySearch(vector<int>& arr, int item , int end){
            int s = 0 , e = end - 1;
            while(s <= e){
                int mid = (s + e)/2;
                if(arr[mid] > item){
                    e = mid - 1;
                }
                else{
                    s = mid + 1;
                }
            }
            return s;
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
            sort(listOfRandomIntegers.begin(), listOfRandomIntegers.end());
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
    Sorter* insertion = new InsertionSorter;
    Sorter* modifiedInsertion = new ModifiedInsertionSorter;

    cout << "Insertion Sort on Random Ordered Data " << endl;
    test.RunExperiement(insertion, 0, 10000, 100000, 1000, 100000, 200, 5000);

    cout << endl << endl << "Insertion Sort on reversed Ordered Data " << endl;
    test.RunExperiement(insertion, 1, 10000, 100000, 1000, 100000, 200, 5000);

    cout  << endl << endl << "Modified insertion Sort on reversed Ordered Data " << endl;
    test.RunExperiement(modifiedInsertion, 1, 1, 100, 1000, 100000, 200, 5000);

    cout << endl << endl << "Modified insertion Sort on Random Ordered Data " << endl;
    test.RunExperiement(modifiedInsertion, 0, 10000, 100000, 1000, 100000, 200, 5000);
}
