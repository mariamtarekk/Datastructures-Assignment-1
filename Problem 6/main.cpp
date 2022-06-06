#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Entry{
    private:
        string firstName_;
        string lastName_;
        string phoneNumber_;
    public:
        Entry(){}
        Entry(string firstName , string lastName , string phoneNumber){
            firstName_ = firstName;
            lastName_ = lastName;
            phoneNumber_ = phoneNumber;
        }
        string getFirstName() const{
            return firstName_;
        }
        string getLastName() const{
            return lastName_;
        }
        string getPhoneNumber()const{
            return phoneNumber_;
        }

        void setFirstName(string firstName){
            firstName_ = firstName;
        }

        void setLastName(string lastName){
            lastName_ = lastName;
        }
        void setPhoneNumber(string phoneNumber){
            phoneNumber_ = phoneNumber;
        }

        friend istream& operator>>(istream& input, Entry& entry){
            cout << "Please enter entry first name: ";
            input >> entry.firstName_;
            cout << "Please enter entry second name: ";
            input >> entry.lastName_; 
            cout << "Please enter entry phone number: ";
            input >> entry.phoneNumber_;

            return input;
        }

        friend ostream& operator<<(ostream& output, Entry entry){
            if(entry.firstName_ == ""){
                output << "Entry not found" << endl;
            }else{  
                output << "First name: " << entry.firstName_ << endl;
                output << "Second name: " << entry.lastName_ << endl;
                output << "Phone number: " << entry.phoneNumber_ << endl;
            }
            

            return output;
        }
};

class PhoneDirectory{
    private:
        vector<Entry>data_;
        bool checkSorted;
    public:
        PhoneDirectory(PhoneDirectory& phone){
            for(unsigned int i = 0; i < phone.data_.size(); ++i){
                this->data_.push_back(phone.data_[i]);
            }
            this->checkSorted = phone.checkSorted;
        }
    private:
        void SelectionSort(vector<Entry>& data ){
            checkSorted = true;
            for(int i = 0 ,  size = data_.size() ; i < size -1  ; ++i){
                int idx = i;
                for(int j = i + 1 ; j < size ; ++j){
                    string compare = data[i].getFirstName();
                    if(compare > data[i].getFirstName()){
                        idx = j ;
                        compare = data[j].getFirstName();
                    }
                }
                swap(data[i] , data[idx]);
            }
        }

        void InsertionSort(vector<Entry>& data){
            checkSorted = true;
            for(int i = 1 , j , size = data.size() ; i < size ; ++i){
                Entry compare = data[i];
                for( j = i ; j > 0 && compare.getFirstName() < data[j - 1].getFirstName() ; --j){
                    data[j] = data[j - 1];
                }
                data[j] = compare;
            }
        }

        void BuubleSort(vector<Entry>& data ){
            checkSorted = true; 
            for(int i = 0 , size = data.size() ; i < size ; ++i){
                bool swapped = false;
                for(int j = size -1 ; j > i ; --j){
                    if(data[j].getFirstName() < data[j -1].getFirstName()){
                        swap(data[j] , data[j - 1]);
                        swapped = true;
                    }
                }
                if(!swapped) break;
            }
        }

        // searching for specific first name  and return it's all data
        Entry BinarySearchForFirstName(vector<Entry>& data , const string& firstName){
            int l = 0 , r = data.size() - 1;
            while(l <= r){
                int mid =(l + r)/2;
                if(data[mid].getFirstName() == firstName) return data[mid];
                else if(data[mid].getFirstName() > firstName){
                    r = mid -1 ;
                }
                else{
                    l = mid + 1;
                }
            }
            return Entry("" , "" , "");  
        }

        // searching for specific first name and return it position
        int BinarySearchForIndex(vector<Entry>& data , string firstName){
            int l = 0 , r = data.size() - 1;
            while(l <= r){
                int mid = (l + r) / 2;
                if(data[mid].getFirstName() == firstName){
                    return mid;
                }
                else if(data[mid].getFirstName() > firstName){
                    r = mid - 1;
                }
                else{
                    l = mid + 1;
                }
            }
            return -1;
        }

        void DeleteIndex(vector<Entry>&data , int index){
            if(index == -1 ){
                cout << "Not Found." << endl;
            }
            data.erase(data.begin() + index);
        }

    public:
        PhoneDirectory(){
            checkSorted = false;
        }

        void addEntry(Entry& newEntry){
            checkSorted = false;
            data_.push_back(newEntry);
        }

        void listAllEntries(){
            for(int i = 0, size = data_.size(); i < size; ++i){
                cout << data_[i] << endl;
            }
        }

        Entry phoneNumberLookup(string phoneNumber){
            for(int i = 0 , size = data_.size() ; i < size ; ++i){
                if(phoneNumber == data_[i].getPhoneNumber()){
                    return data_[i];
                }
            }
            return Entry("","","");
        }

        Entry lookupByFirstName(string firstName){
            if(checkSorted){
                Entry tmp = BinarySearchForFirstName(data_ , firstName);
                return tmp;
            }
            else{
                for(int i = 0 , size = data_.size() ; i < size ; ++i){
                   if(firstName == data_[i].getFirstName())return data_[i];
                }
                return Entry("" , "" , "");
            }
        }

        void sortUsingSelectionSort(){
            SelectionSort(data_);
        }

        void sortUsingInsertionSort(){
            InsertionSort(data_);
        }

        void sortUsingBubbleSort(){
            BuubleSort(data_);
        }

        void deleteByFirstNameUsingSelectioSort(string firstName){
            SelectionSort(data_);
            int indexNeedToDelete = BinarySearchForIndex(data_,firstName);
            DeleteIndex(data_ , indexNeedToDelete);
        }

        void deleteByFirstNameUsingBubbleSort(string firstName){
            BuubleSort(data_);
            int indexNeedToDelete = BinarySearchForIndex(data_,firstName);
            DeleteIndex(data_ , indexNeedToDelete);
        }

        void deleteByFirstNameUsingInsertionSort(string firstName){
            InsertionSort(data_);
            int indexNeedToDelete = BinarySearchForIndex(data_,firstName);
            DeleteIndex(data_ , indexNeedToDelete);
        }
};

int main(){
    PhoneDirectory phone;
    while(true){
        short choice;
        cout << "Enter Your choice " << endl;
        cout <<     "1. Add an entry to the directory " << endl
                    << "2. Look up a phone number "<< endl
                    << "3. Look up by first name" << endl
                    << "4. Delete an entry from the directory"  << endl
                    << "5. List All entries in phone directory " << endl
                    << "6. Exit form this program " << endl;
        cin >> choice;
        switch(choice){
            case 1:{
                Entry data;
                cin >> data;
                phone.addEntry(data);
                break;
            }
            case 2:{
                string phoneNumber;
                cout << "Enter the phone number you look up for : ";
                cin >> phoneNumber;
                Entry result = phone.phoneNumberLookup(phoneNumber);
                cout << result << endl;
                break;
            }
            case 3:{
                string firstName;
                cout << "Enter the First Name you search for : ";
                cin >> firstName;
                Entry result = phone.lookupByFirstName(firstName);
                cout << result << endl;
                break;
            }
            case 4:{
                string firstName;
                cout << "Enter the entry you want to delete : ";
                cin >> firstName ;
                PhoneDirectory tmp = phone;
                auto start1 = steady_clock::now();
                tmp.deleteByFirstNameUsingBubbleSort(firstName);
                auto end1 = steady_clock::now();
                auto start2 = steady_clock::now();
                tmp = phone;
                tmp.deleteByFirstNameUsingInsertionSort(firstName);
                auto end2 = steady_clock::now();
                auto start3 = steady_clock::now();
                tmp = phone;
                tmp.deleteByFirstNameUsingSelectioSort(firstName);
                auto end3 = steady_clock::now();

                auto duration1 = duration_cast<nanoseconds>(end1 - start1);
                auto duration2 = duration_cast<nanoseconds>(end2 - start2);
                auto duration3 = duration_cast<nanoseconds>(end3 - start3);

                cout << "Time Analysis" << endl;
                cout << "Bubble Sort has finished in " << duration1.count() << "nano seconds" << endl;
                cout << "Insertion Sort has finished in " << duration2.count() << "nano seconds" << endl;
                cout << "Selection Sort has finished in " << duration3.count() << "nano seconds" << endl;
                phone.deleteByFirstNameUsingBubbleSort(firstName);
                break;
            }
            case 5:{
                PhoneDirectory tmp = phone;
                auto start1 = steady_clock::now();
                tmp.sortUsingBubbleSort();
                auto end1 = steady_clock::now();
                auto start2 = steady_clock::now();
                tmp = phone;
                tmp.sortUsingInsertionSort();
                auto end2 = steady_clock::now();
                auto start3 = steady_clock::now();
                tmp = phone;
                tmp.sortUsingSelectionSort();
                auto end3 = steady_clock::now();

                auto duration1 = duration_cast<nanoseconds>(end1 - start1);
                auto duration2 = duration_cast<nanoseconds>(end2 - start2);
                auto duration3 = duration_cast<nanoseconds>(end3 - start3);

                phone.sortUsingBubbleSort();
                phone.listAllEntries();
                cout << "Time Analysis" << endl;
                cout << "Bubble Sort has finished in " << duration1.count() << "nano seconds" << endl;
                cout << "Insertion Sort has finished in " << duration2.count() << "nano seconds" << endl;
                cout << "Selection Sort has finished in " << duration3.count() << "nano seconds" << endl;
                break;
            }
            case 6:{
                exit(0);
                break;
            }
        }
        
    }
}