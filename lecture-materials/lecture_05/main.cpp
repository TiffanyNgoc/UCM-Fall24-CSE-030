#include <iostream>
#include "ArrayList.h"
#include "RandomSupport.h"
#include "TimeSupport.h"

using namespace std;

int main(){

    const int N = 100000;

    ArrayList<int> numbers;

    RNG rng(1, N*100);

    for (int i = 0; i < N; i++){
        numbers.append(rng.get());
    }

    // cout << numbers << endl;

    Timestamp start;

    for (int i = 0; i < N; i++){
        numbers.findMax();
    }

    Timestamp end;

    int duration = end - start;

    cout << "Took " << duration << " ms." << endl;

    return 0;

}
