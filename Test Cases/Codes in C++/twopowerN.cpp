#include <iostream>
using namespace std;

int two(int y) {
    
    int x = 2 << (y - 1);
    return x;
}

int main() {
    int x = 9;
    
    int y = two(x);
    
    cout<<y;

    return 0;
}