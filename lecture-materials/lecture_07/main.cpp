#include <iostream>
#include "ArrayList.h"
#include "RandomSupport.h"
#include "TimeSupport.h"

using namespace std;

// O(n)
int findMinPos(const ArrayList<int>& list, int start){
    int min = list[start];
    int minPos = start;
    for (int i = start; i < list.size(); i++){
        if (list[i] < min){
            min = list[i];
            minPos = i;
        }
    }

    return minPos;
}

// O(n^2)
void selectionSort(ArrayList<int>& list){
    for (int i = 0; i < list.size(); i++){  // O(n)
        int p = findMinPos(list, i);        // O(n)
        int temp = list[i];
        list[i] = list[p];
        list[p] = temp;
    }
}

// Best case: O(n), worst case: O(n^2)
void insertionSort(ArrayList<int>& list){
    for (int i = 1; i < list.size(); i++){
        
        int key = list[i];
        int j = i - 1;
        while (j >= 0 && list[j] > key){
            list[j + 1] = list[j];
            j--;
        }

        list[j + 1] = key;
    }
}

// QuickSort
int partition(ArrayList<int>& list, int start, int end){
 
    int pivot = list[start];
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (list[i] <= pivot)
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    int temp = list[pivotIndex];
    list[pivotIndex] = list[start];
    list[start] = temp;
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (list[i] <= pivot) {
            i++;
        }
 
        while (list[j] > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            int temp = list[i];
            list[i] = list[j];
            list[j] = temp;
            i++;
            j--;
        }
    }
 
    return pivotIndex;
}
 
void q_sort(ArrayList<int>& list, int start, int end){
 
    // base case
    if (start >= end)
        return;
 
    // partitioning the array
    int p = partition(list, start, end);
 
    // Sorting the left part
    q_sort(list, start, p - 1);
 
    // Sorting the right part
    q_sort(list, p + 1, end);
}

void quickSort(ArrayList<int>& list){
    q_sort(list, 0, list.size() - 1);
}

int main(){

    // Code goes here

    ArrayList<int> numbers;
    RNG rng(1, 1000000);

    for (int i = 0; i < 100000; i++){
        numbers.append(rng.get());
    }

    // cout << numbers << endl;

    Timestamp start;

    quickSort(numbers);

    Timestamp end;

    int duration = end - start;

    cout << "Took " << duration << " ms." << endl;

    // cout << numbers << endl;

    return 0;

}
