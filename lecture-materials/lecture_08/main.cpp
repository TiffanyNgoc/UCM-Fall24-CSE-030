#include <cstddef>
#include <iostream>
#include "ArrayList.h"
#include "TimeSupport.h"
#include "RandomSupport.h"

using namespace std;

struct Link{
    int data;
    Link* next;

    Link(){
        data = 0;
        next = nullptr;
    }

    Link(int data){
        this->data = data;
        next = nullptr;
    }
};


class LinkedList{
    Link* front;
public:
    LinkedList(){
        front = nullptr;
    }

    void append(int value){
        if (front == nullptr){
            front = new Link(value);
        }
        else{
            Link* temp = front;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            // At this point temp is the last element
            temp->next = new Link(value);
        }
    }

    void prepend(int value){
        Link* temp = new Link(value);
        temp->next = front;

        front = temp;
    }

    friend ostream& operator<<(ostream& os, const LinkedList& list);
};

ostream& operator<<(ostream& os, const LinkedList& list){
    Link* temp = list.front;

    while (temp != nullptr){
        os << temp->data << " ";
        temp = temp->next;
    }
    return os;
}

int main(int argc, char* argv[]){

    LinkedList list;

    list.append(5);
    list.append(7);
    list.append(3);

    list.prepend(99);

    cout << list << endl;


    // Link* head = new Link(5);

    // head->next = new Link(7);

    // head->next->next = new Link(3);

    // cout << head->data << endl;

    // ArrayList<int> numbers;
    // const int N = 10;

    // RNG rng(1, N*100);

    // // Storing the requests
    // for (int i = 0; i < N; i++){
    //     numbers.append(rng.get());
    // }

    // cout << numbers << endl;

    // Timestamp start;

    // // Processing the requests
    // while (numbers.size() > 0){
    //     int x = numbers.removeFirst();
    //     // Processing request x
    //     cout << "Processing " << x << endl;
    // }

    // Timestamp end;

    // int duration = end - start;

    // cout << "Done in " << duration << " ms." << endl;

    return 0;
}
