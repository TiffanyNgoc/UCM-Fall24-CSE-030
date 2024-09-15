#include <iostream>
#include <ostream>

using namespace std;

template <class T>
class ArrayList;

template <class T>
std::ostream& operator<<(std::ostream& os, const ArrayList<T>& container);


template <class T>
class ArrayList{

    T* data;
    int count;

public:
    ArrayList(){
        data = new T[10];
        count = 0;
    }

    void append(T x){
        data[count] = x;
        count++;
    }

    T& operator[](int index){
        return data[index];
    }

    ~ArrayList(){
        delete[] data;
    }

    // friend std::ostream& operator<<(std::ostream& os, const ArrayList& list);
    friend std::ostream& operator<< <>(std::ostream& os, const ArrayList<T>& container);

};

template <class T>
std::ostream& operator<<(std::ostream& os, const ArrayList<T>& list){
    for (int i = 0; i < list.count; i++){
        os << list.data[i];
        if (i < list.count - 1){
            os << ", ";
        }
    }
    return os;
}

int main(){

    ArrayList<int> numbers;

    numbers.append(6);
    numbers.append(7);
    numbers.append(2);

    numbers[0] = 99;

    cout << numbers << endl;

    ArrayList<string> names;
    names.append("Steve");
    names.append("Tim");
    names.append("Bill");

    cout << names << endl;


    return 0;

}
