#include <stdbool.h>

#ifndef MOVIES_H
#define MOVIES_H

void displayMenu();
void readUsersFromDb();
void registerUser();
void writeUsersToDb();
bool isUserRegistered(const char *);
void readMovies();
void displayMovies();
void readRatingsFromDb();
int findUserIndex(const char *);
float validateInput(const char *, int);
void rateMovie();
void writeRatingsToDb();
void recommendMovies();
void freeCharMemory(char **, int);
void freeFloatMemory(float **, int);
void freeAllMemory();

#endif