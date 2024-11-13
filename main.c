#include <stdio.h>
#include "movies.h"

/**
 * this function serves as the entry point for the movie recommendation system.
 * @return 0 upon successful execution.
 */
int main() {
    int prompt;
    // printf("\n--------------------------------------- NEXT RUN --------------------------------------\n");

    do {
        displayMenu();
        scanf("%d", &prompt);

        switch(prompt) {
            case 1: 
                registerUser();
                printf("\n\n");
                break;
            case 2: 
                displayMovies();
                printf("\n\n");
                break;
            case 3: 
                rateMovie();
                printf("\n\n");
                break;
            case 4: 
                recommendMovies();
                printf("\n\n");
                break;
            case 0: 
                freeAllMemory();
                break;
            default: 
                printf("Code not valid, try again...\n");
                printf("\n\n");
        }
    } while(prompt != 0);

    printf("Terminating the recommendation system...");
    return 0;
}