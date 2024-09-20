#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <ostream>
#include <stdexcept>

// Forward declaration of the class template ArrayList<T>.
// At this point the compiler knows there is something called ArrayList<T>
// A class template called ArrayList
// The compiler does not need to know exactly what ArrayList is at this point
// It just needs to know that there is something  like that.
// We need to do this because of the function template definition below,
// which needs to take in an argument of type ArrayList<T>. That's why 
// we had to pre-declare it here.
template <class T>
class ArrayList;


// This needs to be declared before the class ArrayList, so that it
// can be used inside the class to specify that we want it as a friend
// It takes in the class template ArrayList as a parameter,
// so it needs to be defined after the class declaration.
template <class T>
std::ostream& operator<<(std::ostream& os, const ArrayList<T>& container);


// Array list is a class template, allowing us to store data of any type
template <class T>
class ArrayList{
protected:
    // Helper function to check if we are out of capacity,
    // in which case it doubles the capacity while preserving the data

    T* data;
    int count;
    int capacity;

    // Helper function double our capacity while preserving the data
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

    void deflate() {
        capacity /= 2;
        T* temp = new T[capacity];

        // Copy the existing elements to the new array
        for (int i = 0; i < count; i++) {
            temp[i] = data[i];
        }

        T* old = data;
        data = temp;

        delete[] old;
    }

public:
    // Default constructor. Starts with capacity of 1. Will be increased if necessary.
    ArrayList(){
        count = 0;
        capacity = 1;
        data = new T[capacity];  
    }

    // Copy constructor. Needed because we store data on the heap
    ArrayList(const ArrayList& other){
        count = other.count;
        capacity = other.capacity;

        // data = other.data;
        data = new T[capacity];

        for (int i = 0; i < count; i++){
            data[i] = other.data[i];
        }
    }

    // Overloaded assignment operator. Needed because we store data on the heap
    ArrayList& operator=(const ArrayList& other){
        if (capacity == other.capacity){
            // capacities match
            count = other.count;
            for (int i = 0; i < count; i++){
                data[i] = other.data[i];
            }
        }
        else{
            // capacities are different
            delete[] data;
            capacity = other.capacity;
            count = other.count;

            data = new T[capacity];

            for (int i = 0; i < count; i++){
                data[i] = other.data[i];
            }
        }

        return *this;
    }

    // Appends a value (to the end of the list)
    // We guarantee that there is always space to add one more
    // But after we have added that one, we may have run out of space
    // The inflate() function increases the capacity if necessary
    void append(T x){
        data[count] = x;
        count++;

        if (count == capacity){
            inflate();
        }
    }

    void prepend(T value){
        // Your code here...
        // Shift all elements to the right to make space at the start
        for (int i = count; i > 0; i--) {
            data[i] = data[i - 1];
        }
        data[0] = value; // Insert the new element at the beginning
        count++;

        if (count == capacity) {
            inflate(); // Double the capacity if necessary
        }
    }

    T removeFirst() {
        // Your code here
        if (count == 0) {
            throw std::out_of_range("List is empty");
        }

        // Store the first element to return it later
        T firstElement = data[0];

        // Shift all elements to the left
        for (int i = 1; i < count; i++) {
            data[i - 1] = data[i];
        }

        // Decrease the count
        count--;

        // Deflate if we are using less than half the capacity
        if (count > 0 && count < capacity / 2) {
            deflate();
        }

        return firstElement;
    }

    T removeLast() {
        // Your code here
        if (count == 0) {
            throw std::out_of_range("List is empty");
        }

        // Store the last element to return it
        T lastElement = data[count - 1];

        // Decrease the element count
        count--;

        // Deflate if we are using less than half the capacity
        if (count > 0 && count < capacity / 2) {
            deflate();
        }
        return lastElement;
    }

    // This is so we are able to access and manipulate (read and write) any element in a valid position in the list
    T& operator[](int index){
        return data[index];
    }

    // Returns the number of elements in the list (not the current capacity)
    int size() const {
        return count;
    }

    // Returns the currently available capacity of the list
    int getCapacity() const {
        return capacity;
    }

    // Destructor, responsible for releasing the memory used on the heap
    ~ArrayList(){
        delete[] data;
    }

    // Some friendship declarations here, for the overloaded operator<< 
    // and for Unit Testing purposes. We want the test program to have access to everything
    friend std::ostream& operator<< <>(std::ostream& os, const ArrayList<T>& container);
    friend struct TestArrayList;

};


// This is for being able to cout our ArrayList
// It is a function template because we wish to be able to pass a class template as a parameter
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

#endif
