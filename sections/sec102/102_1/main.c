#include <stdio.h>
#include "power.h"

int main(int argc, char const *argv[]) {
    
    //102_1
    // int answer;
    // answer = add(2, 2);
    // printf("%d\n", answer);

    // answer = power(5, 2);
    // printf("%d\n", answer);

    //102_3 & 102_4
    char* test_arr[15] = {
                            "1. diceRoll",
                            "2. CircleArea",
                            "3. CubeVol",
                            "4. Power", 
                            "5. Exit"
                            };    

    printString(test_arr, 5);

    char str[10];
    getUserInput(str, 10);
    

    return 0;
}


