#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <ostream>
#include <stdexcept>

template <typename T>
struct Link {
    T data;
    Link* next;

    Link() {
        data = T();
        next = nullptr;
    }

    Link(T data) {
        this->data = data;
        next = nullptr;
    }
};

template <typename T>
class LinkedList {
    Link<T>* front;
    Link<T>* back;
    int size;

public:
    LinkedList() {
        front = nullptr;
        back = nullptr;
        size = 0;
    }

    // Append a new value to the end of the list
    void append(T value) {
        if (front == nullptr) {
            // Appending to an empty list
            front = new Link<T>(value);
            back = front;
        }
        else {
            // Appending to list with elements
            Link<T>* temp = new Link<T>(value);
            back->next = temp;
            back = temp;
        }
        size++;
    }

    // Prepend a new value to the front of the list
    void prepend(T value) {
        if (front == nullptr){
            // Prepending to an empty list
            front = new Link<T>(value);
            back = front;
        }
        else {
            // Prepending to a list with elements
            Link<T>* temp = new Link<T>(value);
            temp->next = front;
            front = temp;
        }
        size++;
    }

    // Remove and return the first element
    T removeFirst() {
        if (front == nullptr) {
            throw std::logic_error("Cannot remove from an empty list");
        }

        T value = front->data;
        Link<T>* temp = front;
        front = front->next;
        delete temp;
        size--;

        // If the list becomes empty after removing, update back pointer
        if (front == nullptr) {
            back = nullptr;
        }

        return value;
    }

    // Remove and return the last element
    T removeLast() {
        if (front == nullptr) {
            throw std::logic_error("Cannot remove from an empty list");
        }

        if (front == back) {
            // Only one element in the list
            T value = front->data;
            delete front;
            front = nullptr;
            back = nullptr;
            size--;
            return value;
        }

        // More than one element in the list
        Link<T>* temp = front;
        while (temp->next != back) {
            temp = temp->next;
        }

        T value = back->data;
        delete back;
        back = temp;
        back->next = nullptr;
        size--;

        return value;
    }

    // Access element by index
    T& operator[](int index) {
        if (index < 0 || index >= size){
            throw std::logic_error("Index out of bounds");
        }
        Link<T>* temp = front;
        for (int i = 0; i < index; i++){
            temp = temp->next;
        }
        return temp->data;
    }

    // Get the size of the list
    int getSize() const {
        return size;
    }

    // Friend function for printing the list
    friend std::ostream& operator<<(std::ostream& os, const LinkedList& list) {
        Link<T>* curr = list.front;
        while (curr != nullptr) {
            os << curr->data;
            if (curr->next != nullptr) os << ", ";
            curr = curr->next;
        }
        return os;
    }
    
    // The following 2 friend declarations must be present so the unit tests can run
    friend struct TestTemplates;
    friend struct TestRemoveMethods;

};

// Overloaded << operator for printing the LinkedList
// inline std::ostream& operator<<(std::ostream& os, const LinkedList& list){
//     Link* curr = list.front;
//     while (curr != nullptr){
//         os << curr->data;
//         if (curr->next != nullptr) os << ", ";
//         curr = curr->next;
//     }

//     return os;
// }


#endif