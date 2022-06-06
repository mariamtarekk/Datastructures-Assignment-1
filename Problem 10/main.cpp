#include<iostream>
using namespace std;

template<class type>
class Node{
private :
    type _data;
    Node<type>* _next;
    Node<type>* _pre;
public :
    Node(type data = 0, Node<type>* next = NULL, Node<type>* pre = NULL){
        _data = data;
        _next = next;
        _pre = pre;
    }

    void setNext(Node<type>* next){
        _next = next;
    }

    void setPrevious(Node<type>* pre){
        _pre = pre;
    }

    void setData(type data){
        _data = data;
    }

    type& getData(){
        return _data;
    }

    Node<type>* getNext(){
        return _next;
    }

    Node<type>* getPrevious(){
        return _pre;
    }
};

template<class type>
class MyList{
private :
    Node<type>* _head;
    Node<type>* _tail;
    Node<type>* _dummy;
    int _size;
public :
    
    MyList(){
        _head = NULL;
        _tail = NULL;
        _dummy = new Node<type>;
        _size = 0;
    }

    MyList(type data , int size){
        _size = size;
        for(int i = 0 ; i < _size ; ++i){
            Node<type>* newNode = new Node<type>;
            if(i == 0){
                _head = newNode;
                _tail = newNode;
                _tail->setNext(_dummy);
            }
            else if(i == 1){
                _head->setNext(newNode);   
                newNode->setPrevious(_head);
                _tail = newNode;
                _tail->setNext(_dummy);
            }else{
                newNode->setPrevious(_tail->getPrevious());
                _tail->getPrevious()->setNext(newNode);
                _tail = newNode;
                _tail->setNext(_dummy);
            }
            newNode->setData(data);
        }
    }
class iterator{
        
        private:
            Node<type>* _node = NULL;
        public:
            friend class MyList; 
            iterator(Node<type>* node){
                _node = node;
            }
            iterator(){
                _node = NULL;
            }
            void operator++(int){
                if(_node->getNext() == NULL){
                    throw "Out of bounds";
                }
                _node = _node->getNext();
            }
            void operator++(){
                if(_node->getNext() == NULL){
                    throw "Out of bounds";
                }
                _node = _node->getNext();
            }
            void operator--(){
                if(_node->getPrevious() == NULL){
                    throw "Out of bounds";
                }
                _node = _node->getPrevious();
            }

            bool operator==(const iterator& it){
                return (_node == it._node);
            }
            type& operator *(){
                return (_node->getData());
            }
    };
    void push_back(type data){
        Node<type>* newNode = new Node<type>;
        newNode->setData(data);
        if(_head == NULL){
            _head = newNode;
            _tail = newNode;
            _tail->setNext(_dummy);
        }
        else{
            _tail->setNext(newNode);
            newNode->setPrevious(_tail);
            _tail = newNode;
            _tail->setNext(_dummy);
        }
        _size++;
      
    }

    void push_front(type data){
        Node<type>* newNode = new Node<type>;
        newNode->setData(data);
        if(_head == NULL){
            _head = newNode;
            _tail = newNode;
            _tail->setNext(_dummy);
        }
        else{
            _head->setPrevious(newNode);
            newNode->setNext(_head);
            _head = newNode;
        }
        _size++;
    }

    void pop_back(){
        _tail = _tail->getPrevious();
        Node<type>* tmp = _tail->getNext();
        _tail->setNext(_dummy);
        _size--;
        delete tmp;
    }

    void pop_front(){
        Node<type>* tmp = _head;
        _head = _head->getNext();
        _head->setPrevious(NULL);
        _size--;
        delete tmp;
    }

    MyList<type>& operator = (const MyList<type>& oldList){
        Node<type>* move = oldList._tail;
        for(int i = 0; i < oldList._size; ++i){
            this->push_front(move->getData());
            move = move->getPrevious();
        }
        return *this;
    }

    void print(){
        Node<type>* tmp = _head;
        while(tmp != _dummy){
            cout << tmp->getData() << endl;
            tmp = tmp->getNext();
        }
        delete tmp;
    }
    int size(){
        return size;
    }
    MyList<type>::iterator begin(){
        return iterator(_head);
    }
    MyList<type>::iterator end(){
        return iterator(_dummy);
    }
    void insert(type value, MyList<type>::iterator position){
        Node<type>* newNode = new Node<type>;
        newNode->setData(value);
        if(position._node == _head){
            push_front(value);
        }else if(position._node == _dummy){
            push_back(value);
        }else{
            newNode->setPrevious(position._node->getPrevious());
            position._node->getPrevious()->setNext(newNode);
            position._node->setPrevious(newNode);
            newNode->setNext(position._node);
        }
        _size++;
    }

    MyList<type>::iterator erase(MyList<type>::iterator position){
        if(position._node == _dummy){
            throw "Out of bounds";
        }
        if(position._node != _head){
            position._node->getPrevious()->setNext(position._node->getNext());
        }
        position._node->getNext()->setPrevious(position._node->getPrevious());
        if(position._node == _head){
            _head = position._node->getNext();
        }
        delete position._node;
        
        position++;
        _size--;
        return position;
    }
    ~MyList(){
        while(_size--){
            Node<type>* tmp = _head;
            _head = _head->getNext();
            delete tmp;
        }
    }

    
};



int main(){
    MyList<int> myList;
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);
    MyList<int>::iterator it = myList.begin();
    it++;
    cout<< *it;

    

}