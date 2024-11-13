#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "movies.h"

//----------------------------------------------------------------//
#define MAX_USERS 20
#define MAX_NAME_LENGTH 15
#define MAX_MOVIE_LENGTH 90
#define MAX_RATING_LENGTH 60
//----------------------------------------------------------------//
FILE *fptr;
char **userDatabase, **movieDatabase;
float movieRating, **ratingsDatabase;
int userCount = 0, movieCount = 0, movieNumber;
bool moviesWereRead = false, ratingsWereRead = false;
//----------------------------------------------------------------//

/**
 * This function prints the main menu options to the console.
 */
void displayMenu() {
    printf("\n***** Movie Recommendation System *****\n");
    printf("1. Register User\n");
    printf("2. Display Movies\n");
    printf("3. Rate a Movie\n");
    printf("4. Get Movie Recommendations\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

/**
 * This function reads user data from a file and populates the userDatabase array. If the file does not exist, it prints an error message and returns.
 */
void readUsersFromFile() {
    fptr = fopen("/Users/barbara/courseHub/COMP 348/A1/text_files/user_data.txt", "r");
    char nameAndNumber[MAX_NAME_LENGTH];

    if(fptr == NULL) { //the file does not exist
        printf("\'user_data.txt\' not found.\n\n");
        return;
    }

    //free previously allocated memory for userDatabase
    if(userCount != 0) {
        freeCharMemory(userDatabase, MAX_USERS);
    }

    //dynamically allocate memory for userDatabase
    userDatabase = (char **)malloc(MAX_USERS * sizeof(char *));
    for(int i = 0; i < MAX_USERS; i++) {
        userDatabase[i] = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
    }

    userCount = 0;
    while(fgets(nameAndNumber, sizeof(nameAndNumber), fptr)) {
        //tokenize the original string
        char *nameOnly = strtok(nameAndNumber, " "); //split the string to record only the name and not the number

        //read users into the database, remove the newline at the end of the string, and update the number of users
        strcpy(userDatabase[userCount], nameOnly);
        userDatabase[userCount][strcspn(userDatabase[userCount], "\n")] = '\0';
        userCount++;
    }
    fclose(fptr);
}
/**
 * This function writes user data from the userDatabase array to a file. If the file does not exist, it creates a new one.
 */
void writeUsersToFile() {
    fptr = fopen("/Users/barbara/courseHub/COMP 348/A1/text_files/user_data.txt", "wt");
    for(int i = 0; i < userCount; i++) {
        if(i != (userCount - 1)) { //if not at the last user, add a newline after writing to the file and continue
            fprintf(fptr, "%s %d\n", userDatabase[i], (i + 1));
            continue;
        }
        fprintf(fptr, "%s %d", userDatabase[i], (i + 1));
    }
    fclose(fptr);
}

/**
 * This function checks if a user with the given username is registered in the userDatabase.
 * @param username the username to search for
 * @return true if the user is registered, false otherwise
 */
bool isUserRegistered(const char *username) {
    for(int i = 0; i < userCount; i++) {
        if(strcasecmp(username, userDatabase[i]) == 0) { //making the search case-insensitive
            return true;
        }
    }
    return false;
}
/**
 * This function prompts the user to enter a new username for registration. It checks if the username is already registered.
 * If not, adds it to the user database and writes to file.
 */
void registerUser() {
    char newUser[MAX_NAME_LENGTH];
    bool found;

    readUsersFromFile();
    do {
        printf("Enter username for registration: ");
        scanf("%14s", newUser);

        found = isUserRegistered(newUser);
        if(found) {
            printf("User already exists. Please choose a different name.\n");
        } else {
            //add new user to the database, remove the newline at the end of the string, and update the number of users
            strcpy(userDatabase[userCount], newUser);
            userDatabase[userCount][strcspn(userDatabase[userCount], "\n")] = '\0';
            userCount++;
            printf("User %s is successfully registered.\n", newUser);
        }
    } while(found);
    writeUsersToFile();
}

/**
 * This function reads movie data from a file and populates the movieDatabase array. If the file does not exist, it prints an error message and returns.
 */
void readMoviesFromFile() {
    fptr = fopen("/Users/barbara/courseHub/COMP 348/A1/text_files/movie_database.txt", "r");
    char display[MAX_MOVIE_LENGTH];

    if(fptr == NULL) { //the file does not exist
        printf("\'movie_database.txt\' not found.\n\n");
        return;
    }

    //free previously allocated memory for movieDatabase
    if(movieCount != 0) {
        freeCharMemory(movieDatabase, 10);
    }

    //dynamically allocate memory for movieDatabase
    movieDatabase = (char**)malloc(10 * sizeof(char*));
    for(int i = 0; i < 10; i++) {
        movieDatabase[i] = (char *)malloc(MAX_MOVIE_LENGTH * sizeof(char));
    }

    moviesWereRead = true;
    movieCount = 0;
    while(fgets(display, sizeof(display), fptr)) {
        //split the string by the space
        char *title = strtok(display, " ");
        char *genre = strtok(NULL, " ");
        char *rating = strtok(NULL, " ");

        //replace underscores in the title with spaces
        for(int i = 0; title[i] != '\0'; i++) {
            if(title[i] == '_') {
                title[i] = ' ';
            }
        }

        //format the components into the desired string
        char formattedString[MAX_MOVIE_LENGTH];
        sprintf(formattedString, "%s (%s) - %s", title, genre, rating);

        //add formatted string to movie database, remove the newline at the end of the string, and update the number of movies
        strcpy(movieDatabase[movieCount], formattedString);
        movieDatabase[movieCount][strcspn(movieDatabase[movieCount], "\n")] = '\0';
        movieCount++;
    }
    fclose(fptr);
}
/**
 * This function reads movie data from file and displays it to the console. If the file does not exist, it prints an error message and returns.
 */
void displayMovies() {

    readMoviesFromFile();
    if(moviesWereRead) { //if the file was opened and read successfully
        printf("\n***** Movie Database *****\n");
        for(int i = 0; i < movieCount; i++) {
            printf("%d. %s\n", (i + 1), movieDatabase[i]);
        }
    }
}

/**
 * This function reads user ratings data from a file and populates the ratingsDatabase array. If the file does not exist, it prints an error message and returns.
 */
void readRatingsFromFile() {
    fptr = fopen("/Users/barbara/courseHub/COMP 348/A1/text_files/user_ratings.txt", "r");
    char ratings[MAX_RATING_LENGTH], *token;
    int userIndex = 0, movieIndex = 0;

    if(fptr == NULL) { //the file does not exist
        printf("\'user_ratings.txt\' not found.\n\n");
        return;
    }

    //free previously allocated memory for ratingsDatabase
    if(ratingsWereRead) {
        freeFloatMemory(ratingsDatabase, userCount);
    }

    //dynamically allocate memory for ratingsDatabase
    ratingsDatabase = (float **)malloc(userCount * sizeof(float *));
    for(int i = 0; i < MAX_USERS; i++) {
        ratingsDatabase[i] = (float *)malloc(movieCount * sizeof(float));
    }

    ratingsWereRead = true;
    fgets(ratings, sizeof(ratings), fptr);
    while(fgets(ratings, sizeof(ratings), fptr) != NULL) {
        token = strtok(ratings, " ");

        while(token != NULL) { //keep splitting by the space till the end of the string
            ratingsDatabase[userIndex][movieIndex] = atof(token);
            movieIndex++;
            token = strtok(NULL, " ");
        }
        movieIndex = 0;
        userIndex++;
    }
    fclose(fptr);

    //new users may have been registered, so set their ratings to the default(0.0)
    for(int i = userIndex; i < userCount; i++) {
        for(int j = 0; j < movieCount; j++) {
            ratingsDatabase[i][j] = 0.0;
        }
    }
}
/**
 * This function writes user ratings data from the ratingsDatabase array to a file. If the file does not exist, it creates a new one.
 */
void writeRatingsToFile() {
    fptr = fopen("/Users/barbara/courseHub/COMP 348/A1/text_files/user_ratings.txt", "wt");

    fprintf(fptr, "%d %d\n", userCount, movieCount);
    for(int i = 0; i < userCount; i++) {
        for(int j = 0; j < movieCount; j++) {
            if(j != movieCount - 1) { //if not at the last movie rating of a user, add a space after writing the movie rating to the file and continue
                fprintf(fptr, "%.1f ", ratingsDatabase[i][j]);
                continue;
            }
            if(i != userCount - 1) { //if not at the last user, add a newline after writing the last rating of all movies to the file and continue
                fprintf(fptr, "%.1f\n", ratingsDatabase[i][j]);
                continue;
            }
            fprintf(fptr, "%.1f", ratingsDatabase[i][j]); //if at the last movie and user, add neither a newline nor a space
        }
    }
    fclose(fptr);
}

/**
 * This function validates a user-entered movie number & rating to ensure it falls within the specified range.
 * @param string the prompt instruction to display
 * @param maxRating the upper bound digit allowed
 * @return the validated input
 */
float validateNumber(const char *string, int maxRating) {
    float exactRating;

    do {
        printf("%s", string); //print the prompt instruction
        scanf("%f", &exactRating);

        if(exactRating < 1 || exactRating > maxRating) {
            printf("Invalid rating. Please enter a rating between 1 and %d.\n", maxRating);
        }
    } while(exactRating < 1 || exactRating > maxRating);

    return exactRating;
}
/**
 * This function finds the index of a user in the userDatabase array based on the username.
 * @param username the username to search for
 * @return the index of the user if found, otherwise -1.
 */
int userRatingIndex(const char *username) {
    for(int i = 0; i < userCount; i++) {
        if(strcasecmp(username, userDatabase[i]) == 0) { //making the search case-insensitive
            return i;
        }
    }
    return -1;
}

/**
 * This function allows a user to rate a movie. It prompts the user to enter their username, then displays the list of movies for rating.
 * After the user selects a movie and provides a rating, the rating is recorded and written to file.
 * If the user is not found or if the movie number or rating provided is invalid, appropriate messages are displayed.
 */
void rateMovie() {
    char validateUser[MAX_NAME_LENGTH];

    readUsersFromFile();
    printf("Enter your username: ");
    scanf("%14s", validateUser);

    bool found = isUserRegistered(validateUser);
    if(!found) {
        printf("User not found. Please register first.\n");
        return;
    }

    displayMovies();
    int userIndex = userRatingIndex(validateUser);

    //prompt the user to enter the movie number and rating
    movieNumber = validateNumber("Enter the number of the movie you want to rate: ", movieCount);
    movieRating = validateNumber("Enter your rating (1-5): ", 5);

    readRatingsFromFile();
    ratingsDatabase[userIndex][movieNumber - 1] = movieRating;  //update the movie rating

    writeRatingsToFile();
    printf("Rating recorded successfully.\n");
}
/**
 * This function generates movie recommendations for a user based on the ratings of other users. It prompts the user to enter their username, then checks if the user is registered.
 * If the user is found, recommendations are generated by calculating the average rating of movies that the user has not seen yet, based on ratings from other users.
 */
void movieRecommended() {
    char validateUser[MAX_NAME_LENGTH], *nameAndGenre, recommendation[MAX_MOVIE_LENGTH];
    int countedRatings = 0, movieCounter = 1;
    float sumRating = 0;

    readUsersFromFile();
    printf("Enter your username: ");
    scanf("%14s", validateUser);

    bool found = isUserRegistered(validateUser);
    if(!found) {
        printf("User not found. Please register first.\n");
        return;
    }

    int userIndex = userRatingIndex(validateUser);
    readMoviesFromFile();
    readRatingsFromFile();

    printf("\n***** Recommended Movies *****\n");
    for(int i = 0; i < movieCount; i++) { //for each movie
        for(int j = 0; j < userCount; j++) { //for each user
            if(ratingsDatabase[userIndex][i] == 0.0) { //if the user hasn't seen the movie(movie rating is 0.0 by default)
                if(ratingsDatabase[j][i] != 0.0) { //if the other users have seen the movie(movie rating is not 0.0)
                   sumRating += ratingsDatabase[j][i]; //update the total rating of the other users
                   countedRatings++; //count the number of users that have seen the movie
               }
           }
        }

        if(countedRatings != 0) {
            nameAndGenre = strtok(movieDatabase[i], "-"); //split the string by the hyphen
            float predictedRating = sumRating / countedRatings; //calculate the average rating of other users

            //format the components into the desired string
            sprintf(recommendation, "%d. %s- Predicted Rating: %.1f\n", movieCounter, nameAndGenre, predictedRating);
            printf("%s", recommendation);
            movieCounter++;
        }
        sumRating = 0;
        countedRatings = 0;
    }
}

/**
 * This function deallocates memory that was dynamically allocated for an array of strings.
 * @param database pointer to the array of strings to be deallocated
 * @param arrayLength length of the array
 */
void freeCharMemory(char **database, int arrayLength) {
    for(int i = 0; i < arrayLength; i++) { //iterate through each string in the array and free its memory
        free(database[i]);
    }
    free(database); //free the memory allocated for the array itself
}
/**
 * This function deallocates memory that was dynamically allocated for a 2D array of floats.
 * @param database pointer to the 2D array of floats to be deallocated
 * @param arrayLength length of the outer array (number of rows)
 */
void freeFloatMemory(float **database, int arrayLength) {
    for(int i = 0; i < arrayLength; i++) { //iterate through each string in the array and free its memory
        free(database[i]);
    }
    free(database); //free the memory allocated for the array itself
}
/**
 * This function deallocates memory that was dynamically allocated for all databases: userDatabase, movieDatabase, and ratingsDatabase.
 * It checks if each database pointer is not NULL before attempting to free its memory.
 */
void freeAllMemory() {
    if(userDatabase != NULL) { //free memory for userDatabase
        for(int i = 0; i < MAX_USERS; i++) { //iterate through each string in the array and free its memory
            free(userDatabase[i]);
        }
        free(userDatabase); //free the memory allocated for the array itself
    }
    if(movieDatabase != NULL) { //free memory for movieDatabase
        for(int i = 0; i < movieCount; i++) { //iterate through each string in the array and free its memory
            free(movieDatabase[i]);
        }
        free(movieDatabase); //free the memory allocated for the array itself
    }
    if(ratingsDatabase != NULL) { //free memory for ratingsDatabase
        for(int i = 0; i < userCount; i++) { //iterate through each string in the array and free its memory
            free(ratingsDatabase[i]);
        }
        free(ratingsDatabase); //free the memory allocated for the array itself
    }
}