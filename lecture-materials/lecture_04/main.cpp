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
    int capacity;

    void inflate(){
        capacity *= 2;

        T* temp = new T[capacity];

        for (int i = 0; i < count; i++){
            temp[i] = data[i];
        }

        T* old = data;
        data = temp;

        delete[] old;
    }

public:
    ArrayList(){
        count = 0;
        capacity = 1;
        data = new T[capacity];  
    }

    ArrayList(const ArrayList& other){
        count = other.count;
        capacity = other.capacity;

        // data = other.data;
        data = new T[capacity];

        for (int i = 0; i < count; i++){
            data[i] = other.data[i];
        }

    }

    int size() const {
        return count;
    }

    int getCapacity() const {
        return capacity;
    }

    void append(T x){
        data[count] = x;
        count++;

        if (count == capacity){
            inflate();
        }
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
    os << "[";
    for (int i = 0; i < list.count; i++){
        
        os << list.data[i];
        if (i < list.count - 1){
            os << ", ";
        }
    }
    os << "]";
    return os;
}

int main(){
    ArrayList<int> numbers;

    numbers.append(5);
    numbers.append(7);
    numbers.append(3);

    cout << "Numbers: " << numbers << endl;

    ArrayList<int> backup = numbers;

    cout << "Backup:  " << backup << endl;

    numbers[0] = 99;

    cout << "=========== AFTER CHANGE ===========" << endl;

    cout << "Numbers: " << numbers << endl;
    cout << "Backup:  " << backup << endl;

    return 0;
}
