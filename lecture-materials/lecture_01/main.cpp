#include <iostream>
#include "RandomSupport.h"
#include "TimeSupport.h"

using namespace std;

int linear_search(int value, int numbers[], int size){
    for (int i = 0; i < size; i++){
        if (numbers[i] == value){
            return i;
        }
    }

    return -1;
}

int binary_search(int value, int numbers[], int size){
    int left = 0;
    int right = size - 1;

    while (left <= right){
        int mid = (left + right) / 2;

        if (numbers[mid] == value){
            return mid;
        }
        else{
            if (numbers[mid] > value){
                right = mid - 1;
            }
            else {
                // numbers[mid] < value
                left = mid + 1;
            }
        }
    }
    return -1;
}
void insertion_sort(int arr[], int size)
{
    int i, key, j;
    for (i = 1; i < size; i++)
    {
        key = arr[i];
        j = i - 1;
 
        // Move elements of arr[0..i-1], 
        // that are greater than key, to one
        // position ahead of their
        // current position
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

template <class T>
struct Node {
    T data;
    Node* next;

    Node(T x){
        data = x;
        next = nullptr;
    }
};

template <class T>
class Queue{
    Node<T>* first;
    Node<T>* last;

public:
    Queue(){
        first = nullptr;
        last = nullptr;
    }

    void push(int x){
        Node<T>* temp = new Node<T>(x);

        if (last == nullptr){
            first = temp;
            last = first;
        }
        else{
            last->next = temp;
            last = last->next;
        }
    }

    T pop(){
        if (first != nullptr){
            T value = first->data;

            Node<T>* temp = first;
            first = first->next;
            delete temp;
            return value;
        }
        else{
            throw std::logic_error("Can not pop from an empty queue.");
        }
    }

    bool search(int x){
        Node<T>* temp = first;
        while (temp != nullptr){
            if (temp->data == x){
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
    
    ~Queue(){
        while (first != nullptr){
            pop();
        }
    }
};

class HashTable {
private:
    Queue<int>* data;
    int K;

    int f(int x){
        return x % K >= 0 ? x % K: (x % K) + K;
    }

public:
    HashTable(int K){
        this->K = K;
        data = new Queue<int>[K];
    }

    void insert(int x){
        int i = f(x);
        data[i].push(x);
    }

    bool search(int x){
        int i = f(x);
        return data[i].search(x);
    }

    ~HashTable(){
        delete[] data;
    }

};

int main(int argc, char* argv[]){
    
    const int N = 1000000;

    int* arr = new int[N];

    HashTable ht(N/10);

    RNG rng(1, N * 100);

    

    Timestamp start;

    for (int i = 0; i < N; i++){
        // arr[i] = rng.get();
        // insertion_sort(arr, i+1);
        // binary_search(-1, arr, i+1);
        ht.insert(rng.get());
        ht.search(-1);
    }
    

    Timestamp end;

    int duration = end - start;

    cout << "Took: " << duration << " ms." << endl;

    delete[] arr;

    return 0;
}
