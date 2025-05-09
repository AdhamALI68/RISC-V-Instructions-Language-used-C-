#include <stdio.h>

int difference_between_squares(int a, int b) {
    return (a * a) - (b * b);
}

int main() {
    int result = difference_between_squares(8, 7);
    printf("Difference between the squares: %d\n", result);
    
    return 0;
}
