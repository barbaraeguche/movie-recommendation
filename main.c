#include <stdio.h>
#include "movieRecommendations.h"

/**
 * @brief Main function of the movie recommendation system.
 * This function serves as the entry point for the movie recommendation system.
 * It displays a menu to the user and performs various actions based on the user's choice.
 * @return 0 upon successful execution
 */
int main() {
    int userChoice;

    do {
        displayMenu();
        scanf("%d", &userChoice);

        switch(userChoice) {
            case 1: registerUser();
                printf("\n--------------------------------------- NEXT RUN --------------------------------------\n");
                break;
            case 2: displayMovies();
                printf("\n--------------------------------------- NEXT RUN --------------------------------------\n");
                break;
            case 3: rateMovie();
                printf("\n--------------------------------------- NEXT RUN --------------------------------------\n");
                break;
            case 4: movieRecommended();
                printf("\n--------------------------------------- NEXT RUN --------------------------------------\n");
                break;
            case 0: freeAllMemory();
                break;
            default: printf("Code not valid, try again...\n");
                printf("\n--------------------------------------- NEXT RUN --------------------------------------\n");
        }
    } while(userChoice != 0);

    printf("Terminating Movie Recommendation System...\n");
    return 0;
}