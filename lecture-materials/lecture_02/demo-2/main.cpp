#include <iostream>

using namespace std;

template <class T>
class Triple{
public:
    T first;
    T second;
    T third;

    // Triple(){
    //     first = 0;
    //     second = 0;
    //     third = 0;
    // }

    Triple(T one, T two, T three){
        first = one;
        second = two;
        third = three;
    }
};

template <class T>
ostream& operator<<(ostream& os, const Triple<T>& triple){
    os << triple.first << ", " << triple.second << ", " << triple.third;
    return os;
}

Triple<int> getScores(){
    return Triple<int>(108, 94, 57);
}

Triple<string> getCountries(){
    return Triple<string>("USA", "China", "Japan");
}



int main(){

    Triple<int> result = getScores();

    Triple<string> countries = getCountries();

    result.second = 99;

    // cout << result.first << ", " << result.second << ", " << result.third << endl;
    cout << result << endl;
    cout << countries << endl;

    return 0;
}
