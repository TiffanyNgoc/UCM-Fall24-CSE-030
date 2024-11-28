#include <iostream>
#include "ArrayList.h"
#include "LinkedList.h"
#include "TimeSupport.h"
#include "RandomSupport.h"

using namespace std;


class HashTable{
    int k;
    ArrayList<LinkedList<int>> data;

    HashTable(){}

    int f(int x) {
        return x % k;
    }

public:
    HashTable(int k){
        this->k = k; 
        for (int i = 0; i < k; i++){
            data.append(LinkedList<int>());
        } 
    }

    void append(int x){
        int index = f(x);

        data[index].append(x);
    }

    bool search(int x){
        int index = f(x);

        return data[index].search(x);
    }

    friend ostream& operator<<(ostream& os, const HashTable& table);
};

ostream& operator<<(ostream& os, const HashTable& table){
    // So we can cout the table

    for (int i = 0; i < table.k; i++){
        os<< i << ": " << table.data[i] << std::endl;
    }
    
    return os;
}


int main(int argc, char* argv[]){

    HashTable ht(10);

    ht.append(5);
    ht.append(4);
    ht.append(7);
    ht.append(15);

    cout << ht << endl;

    // const int N = 100000;

    // HashTable collection(1000);
    // RNG rng(1, N * 100);

    // Timestamp start;

    // for (int i = 0; i < N; i++){
    //     int x = rng.get();

    //     collection.append(x);

    //     collection.search(-1);
    // }

    // Timestamp end;

    // int duration = end - start;

    // cout << "Done in " << duration << " ms." << endl;

    return 0;
}
