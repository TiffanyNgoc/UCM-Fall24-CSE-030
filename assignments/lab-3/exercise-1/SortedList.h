#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include "ArrayList.h"

template <typename T>
class SortedList : public ArrayList<T> {
public:
    void append(T value){
        // Your code here
        int currentSize = this->size();
        
        if (currentSize == 0) {
            ArrayList<T>::append(value);
            return;
        }

        int insertIndex = std::lower_bound(this->arr, this->arr + currentSize, value) - this->arr;

        ArrayList<T>::append(this->arr[currentSize - 1]);

        for (int i = currentSize; i > insertIndex; i--) {
            this->arr[i] = this->arr[i - 1];
        }

        this->arr[insertIndex] = value;
    }

    // Binary search method for faster search in a sorted list
    bool search(T value) const {
        // Your code here
        int low = 0;
        int high = this->size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (this->arr[mid] == value) {
                return true;
            } else if (this->arr[mid] < value) { 
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return false;
    }

    // This needs to be here because of the unit tests
    friend struct TestSortedList;

};

#endif
