#include <iostream>

using namespace std;


int main(){

    // const int N = 5;

    int cap = 5;
    int* arr = new int[cap]; 

    int x;
    int curr = 0;
    while (cin >> x){
        arr[curr] = x;
        curr++;

        if (curr == cap){   // We have run out of space
            cout << "Resizing from " << cap;
            cap *= 2;       // Double the capacity variable
            cout << " to " << cap << endl;
            int* temp = new int[cap];

            for(int i = 0; i < curr; i++){
                temp[i] = arr[i];
            }

            int* old = arr;
            arr = temp;
            delete[] old;
        }
    }

    cout << "You entered" << endl;
    for (int i = 0; i < curr; i++){
        cout << arr[i] << " ";
    }
    cout << endl;


    delete[] arr; 

    cout << "Done..." << endl;

    return 0;
}
