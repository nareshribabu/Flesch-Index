/*****************************babuNareshriA2.c*********************************
Student Name: Nareshri Babu                      Email Id: nbabu@uoguelph.ca
Date: Febuary 12, 2019                           Course Name: CIS 2500
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]){

    /*Variables*/
    int i;
    int c;

    /*Counters*/
    int countSentence = 0;
    int countWords = 0;
    int countSyl = 0;
    int wordVowel = 0;
    float index;

    /*Other variables*/
    char endOfWord;
    char vowels;
    char previousChar;
    char numbers;
    char otherSymbols;
    char nextChar;
    char endOfSentence;

    /*storing array*/
    char *storeArray;
    int size = 250;
    int memoryUsed = 0;

    /*Check if there are two arguments in the command line*/
    if (argc != 2) {
        printf("Not enough command line arguments, please enter a file name.\n");
        return(-1);
    }


    /*Declare a file variable and open the file*/
    FILE *user_file = fopen(argv[1], "r");

    /*check if the file opened properly*/
    if (user_file == NULL) {
        printf("Error opening the file\n");
        return(-1);
    }

    /*store all the characters in an array*/
    storeArray = malloc(sizeof(char) * size);

    while ((c = fgetc(user_file)) != EOF) {

        /*realloc memory*/
        if (memoryUsed >= size - 1) {
            size += 100;
            storeArray = realloc(storeArray, size);
        }

        storeArray[memoryUsed] = c;

        memoryUsed++;
    }

    /*close file*/
    fclose(user_file);

    storeArray[memoryUsed] = '\0';

    /*Use the array to find the information*/
    for (i = 0; i < memoryUsed; i++){

        /*Definitions based on the assignment*/
        endOfSentence = ((storeArray[i] == '.') || (storeArray[i] == ';') || (storeArray[i] == ':') || (storeArray[i] == '?') || (storeArray[i] == '!'));

        vowels = ((storeArray[i] == 'a') || (storeArray[i] == 'e') || (storeArray[i] == 'i') || (storeArray[i] == 'o') || (storeArray[i] == 'u') || (storeArray[i] == 'y') ||
                  (storeArray[i] == 'A') || (storeArray[i] == 'E') || (storeArray[i] == 'I') || (storeArray[i] == 'O') || (storeArray[i] == 'U') || (storeArray[i] == 'Y'));

        endOfWord = ((storeArray[i] == ' ') || (storeArray[i] == '\n') || (storeArray[i] == '\t'));

        otherSymbols = ((storeArray[i] == ',') || (storeArray[i] == ')'));

        numbers = ((storeArray[i] >= '0') && (storeArray[i] <= '9'));

        previousChar = storeArray[i - 1];

        nextChar = storeArray[i + 1];

        /*Counting Words*/
        if (endOfWord || endOfSentence || otherSymbols) {
            if ((previousChar >= 'a' && previousChar <= 'z') || (previousChar >= 'A' && previousChar <= 'Z') || (previousChar >= '0' && previousChar <= '9')) {

                ++countWords;
                wordVowel = 0;
            }
        }

        /*Counting Sentences*/
        if (endOfSentence) {
            if ((previousChar >= 'a' && previousChar <= 'z') || (previousChar >= 'A' && previousChar <= 'Z') || (previousChar >= '0' && previousChar <= '9') ||
                (previousChar == ' ') || (previousChar == '\n') || (previousChar == '\t')) {

                countSentence++;
            }
        }

        /*Counting syllables*/
        if (vowels || numbers) {

            /*If two vowels are togeather it counts as 1 syllable*/
            if ((!(numbers)) && ((previousChar != 'a') && (previousChar != 'e') && (previousChar != 'i') && (previousChar != 'o') && (previousChar != 'u') &&
                (previousChar != 'y') && (previousChar != 'A') && (previousChar != 'E') && (previousChar != 'I') && (previousChar != 'O') && (previousChar != 'U') &&
                (previousChar != 'Y'))) {

                countSyl++;
                wordVowel++;
            }

            /*If two numbers are togeather it counts as 1 syllables but if a vowel and a number is next to each other it counts as 2 syllables*/
            if (numbers && (((previousChar >= 'a') && (previousChar <= 'z')) || ((previousChar >= 'A') && (previousChar <= 'Z')) || (!((previousChar >= '0') &&
                (previousChar <= '9'))))) {

                countSyl++;
                wordVowel++;
            }

            /*If the last letter of a word is a vowel and its an "e" then it doesn't count as a syllable*/
            if (((storeArray[i] == 'e') || (storeArray[i] == 'E')) && ((nextChar == ' ') || (nextChar == '\n') || (nextChar == '.') || (nextChar == ';') || (nextChar == ':') ||
                (nextChar == '?') || (nextChar == '!') || (nextChar == ')') || (nextChar == ','))) {

                countSyl--;
                wordVowel--;
            }

        }


        /*If a word doesn't have any syllables, then the word  has 1 syllable*/
        if((wordVowel == 0) && ((nextChar == ' ') || (nextChar == '\n') || (nextChar == '\t') || (nextChar == '.') || (nextChar == ';') || (nextChar == ':') ||
            (nextChar == '?') || (nextChar == '!') || (nextChar == ',') || (nextChar == ')'))) {

            if ((((storeArray[i] >= 'a') && (storeArray[i] <= 'z'))) || ((storeArray[i] >= 'A') && (storeArray[i] <= 'Z')) || ((storeArray[i] >= '0') && (storeArray[i] <= '9'))) {
                countSyl = countSyl + 1;
            }
        }
    }

    /*Check if the calculation below is going have a division by 0*/
    if ((countWords == 0) || (countSentence == 0)) {
        printf("Error: There is a division by 0\n");
        return(-1);
    }



    /*Index calculations and output*/
    index = 206.835 - 84.6 * (countSyl / countWords) - 1.015 * (countWords / countSentence);
    index = round(index);

    printf("Flesch Index = %.0f\n", index);
    printf("Syllable Count = %d\n", countSyl);
    printf("Word Count = %d\n", countWords);
    printf("Sentence Count = %d\n", countSentence);

    /*Free memory*/
    free(storeArray);

    return 0;
}
