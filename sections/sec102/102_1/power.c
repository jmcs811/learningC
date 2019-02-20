#include <stdlib.h>

int power(int base, int exponet) {
    if (exponet == 0) {
        return 1;
    } else {
        return base * power(base, exponet - 1);
    }
}

int add(int a, int b) {
    return a + b;
}