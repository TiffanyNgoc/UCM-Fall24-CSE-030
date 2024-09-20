#include <iostream>
#include "ArrayList.h"
#include "RandomSupport.h"
#include "TimeSupport.h"

using namespace std;

int main(){

    const int N = 1000000;

    ArrayList<int> numbers;

    RNG rng(1, N*100);

    for (int i = 0; i < N; i++){
        numbers.append(i);
    }



    Timestamp start;

    for (int i = 0; i < N; i++){
        numbers.binary_search(-1);
    }

    

    Timestamp end;

    int duration = end - start;

    cout << "Took " << duration << " ms." << endl;

    return 0;

}
