#include <iostream>
using namespace std;

int factorial(int x){
    int k = 1;
        
    for(int i = 1; i <= x; i++)
    {
        k = k * i;
    }
    return k;
}

int main() {
    
    int x = 5;
    int k = factorial(x);
    
   return 0;
}