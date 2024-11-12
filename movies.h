#include <stdbool.h>

#ifndef MOVIES_H
#define MOVIES_H
//----------------------------------------------------------------//
void displayMenu();
void readUsersFromFile();
void registerUser();
void writeUsersToFile();
bool isUserRegistered(const char *);
void readMoviesFromFile();
void displayMovies();
void readRatingsFromFile();
int userRatingIndex(const char *);
float validateNumber(const char *, int);
void rateMovie();
void writeRatingsToFile();
void movieRecommended();
void freeCharMemory(char **, int);
void freeFloatMemory(float **, int);
void freeAllMemory();
//----------------------------------------------------------------//
#endif