


#include <iostream>
#include "Thunder.h"

using namespace std; using namespace Thunder;


int main(){

    cout << "Hello, I am the storm..." << endl;


    Cybernetic cyber;
    cyber.value = 9999;
    cyber.reduceErrorToThreshold(0.000001, 5, 0.9);

    return 0;
}













