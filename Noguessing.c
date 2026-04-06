#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int main() {
    int random, guess;
    int no_of_guess = 0;
    srand(time(NULL));
    random = rand() % 100+1; // Generating between 0 to 100

    do
    {
        printf("Enter your Guess between(1 to 100): ");
        scanf("%d", &guess);
        no_of_guess++;

        if (guess < random) {
            printf("Guess a larger no.\n");
        }
        else if (guess > random) {
            printf("Guess a smaller no.\n");
        }
        else {
            printf("Congratulations!! You have guessed the correct no. in %d attempts", no_of_guess);
        }
        
    } while (guess != random);
    
    printf("\n\nBye Bye, Thanks for Playing.");
    printf("\n\nDeveloped By ALOK.");
    return 0;
}