#include <stdio.h>
#include <stdlib.h>  // For rand() and srand()
#include <time.h>    // For time()

void main(){
    int num1, num2, i;

    // Generate a random number between 1 and 50
    srand(time(0));            // Seed the random number generator
    num1 = (rand() % 50) + 1;  // Random number between 1 and 50

    printf("\nHi! Welcome to the Guessing Game!!!!\n");
    printf("You have 5 Chances to guess the Number!!\n");
    printf("The number is in between 1 to 50\n");

    for(i = 1; i <= 5; i++){
        printf("\nChance %d - Enter your Number: ", i);
        scanf("%d", &num2);

        if(num2 == num1){
            printf("Your Entered Number %d is Right!!! You guessed it in %d attempt(s)!\n", num2, i);
            return;  // End the program after a correct guess
        }
        else if(num2 > num1){
            printf("It's a lower number than this.");
        }
        else{
            printf("It's a higher number than this.");
        }
    }

    printf("\n\nSorry!!! Your Chances are Over!!! The correct number was: %d\n", num1);
}
