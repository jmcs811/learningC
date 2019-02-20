#include <stdio.h>
#include "power.h"

int main(int argc, char const *argv[]) {
    

    int answer;
    answer = add(2, 2);
    printf("%d\n", answer);

    answer = power(5, 2);
    printf("%d\n", answer);
    return 0;
}


