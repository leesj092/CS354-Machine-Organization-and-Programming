/* Seungju Lee
 * slee887
*/

/* This function takes a string as input and removes 
 * leading and trailing whitespace including spaces
 * tabs and newlines. It also removes multiple internal
 * spaces in a row. Arrays are passed by reference.
 */

#include <stdio.h>
#include <stdlib.h>
#include "student_functions.h"

// Go backwards and find first character, and replace last with new null terminal (ignore everything else)
// Clear initial whitespace. Copy entire string earlier into the string or into a new string
// Removing double spaces: Find double space and copy everything earlier
void Clean_Whitespace(char str[]) {
    int i = 0;
    char cleanStr[1024];
    // int j is for indexing cleanStr
    int j = 0;

    // Move i until first character
    while (str[i])
    {
        if (str[i] == 32 || str[i] == '\n' || str[i] == '\t')
        {
            // Skip all spaces, newlines, and tabs
            i++;
            continue;
        }
        break;
    }

    // Copy everything else beyond current i
    while (str[i]) {
        cleanStr[j] = str[i];
        i++;
        j++;
    }

    //Clear rest of cleanStr
    while (cleanStr[j]) {
        cleanStr[j] = '\0';
        j++;
    }

    // create integer to record index of last character
    int lastChar = 0;

    // reset i and j
    i = 0;
    j = 0;
    while (cleanStr[i])
    {
        if (cleanStr[i] != 32 && cleanStr[i] != '\n' && cleanStr[i] != '\t')
        {
            lastChar = i;
        }
        i++;
    }

    // reset i and j
    i = 0;
    j = 0;

    // remove trailing white space while replacing multiplie internal spaces with one space
    char finalStr[1024];
    while (cleanStr[i])
    {
        if (i != lastChar + 1)
        {
            // if we reach two consecutive spaces, dont copy the first one
            if (cleanStr[i] == ' ' && cleanStr[i+1] == ' '){
                i++;
                continue;
            }
            // Copy all valid characters until last character
            finalStr[j] = cleanStr[i];
            i++;
            j++;
            continue;
        }
        // Put null character after last character and skip the rest
        finalStr[j] = '\0';
        break;
    }

    // Change contents of initial array using finalStr
    sprintf(str, "%s", finalStr);

    // Clear finalStr
    for (int i = 0; finalStr[i]; i++) {
        finalStr[i] = '\0';
    }
    return;
}

/* This function takes a string and makes the first
 * letter of every word upper case and the rest of the
 * letters lower case
 */ 
void Fix_Case(char str[]) {
    int i = 0;
    int start = 1;

    // Repeat until null character
    while (str[i]) {
        // if current character is a space (between words) repeat from start of loop
        if (str[i] == ' ') {
            i++;
            start = 1;
            continue;
        }
        // Proceed if character is alphabet
        if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122)) {
            // If it is the first character, change to upper. Else change to lower
            if (start) {
                // If first character not upper case, change to upper case
                if (str[i] > 90) {
                    str[i] -= 'a' - 'A';
                    i++;
                    start = 0;
                } else {
                    i++;
                    start = 0;
                }
            } else {
                // If letters in middle of word are not lower-case, change to lower-case
                if (str[i] < 97) {
                    str[i] += 'a' - 'A';
                    i++;
                } else {
                    i++;
                }
            }     
        }
    }
    return;
}

/* this function takes a string and returns the 
 * integer equivalent
 */
int String_To_Year(char str[]) {
    int year = atoi(str);
    return year;
}


/* this function takes the name of a 
 * director as a string and removes all but
 * the last name.  Example:
 * "Bucky Badger" -> "Badger"
 */
void Director_Last_Name(char str[]) {
    int lastSpace = 0;
    int i = 0;

    // Record last space index
    while (str[i]) {
        if (str[i] == ' ') {
            lastSpace = i;
        }
        i++;
    }

    char lastName[1024];
    int j = 0;

    // Move back i to next index of index for last space
    if (lastSpace != 0) {
        i = lastSpace + 1;
    } else {
        i = 0;
    }

    // Copy last name
    while (str[i]) {
        lastName[j] = str[i];
        i++;
        j++;
    }

    lastName[j] = '\0';
    sprintf(str, "%s", lastName);

    // CLear lastName
    i = 0;
    while (lastName[i]) {
        lastName[i] = '\0';
    }

    return;
}


/* this function takes the a string and returns
 * the floating point equivalent
 */
float String_To_Rating(char str[]) {
    float rating = atof(str);
    return rating;
}


/* this function takes a string representing
 * the revenue of a movie and returns the decimal
 * equivlaent. The suffix M or m represents millions,
 * K or k represents thousands.
* example: "123M" -> 123000000 
*/
long long String_To_Dollars(char str[])  {
    // Move i to last index for number while checking whether next character is M(m) or K(k)
    int i = 0;
    int j = 0;
    char numStr[1024];

    while (str[i] != 'M' && str[i] != 'm' && str[i] != 'K' && str[i] != 'k' && str[i] != '\0') {
        numStr[j] = str[i];
        i++;
        j++;
    }

    long long dollars = atoll(numStr);

    if (str[i] == 'M' || str[i] == 'm') {
        dollars *= 1000000;
    } else if (str[i] == 'K' || str[i] == 'k') {
        dollars *= 1000;
    }

    // Clear numStr
    i = 0;
    while (numStr[i]) {
        numStr[i] = '\0';
        i++;
    }

    // Clear str
    i = 0;
    while (str[i]) {
        str[i] = '\0';
        i++;
    }

    return dollars;
}


/* This function takes the array of strings representing 
 * the csv movie data and divides it into the individual
 * components for each movie.
 * Use the above helper functions.
 */
void Split(char csv[10][1024], int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {
    
    int csvLine = 0;
    int i = 0;
    int j = 0;

    // Repeat for all movies
    for (int movieNum = 0; movieNum < num_movies; movieNum++) {
        // Move to next line when end of line is reached
        if (csv[csvLine][i] == '\0') {
            csvLine++;
            i = 0;
            j = 0;
        }

        // Copy title
        while (csv[csvLine][i] != ',') {
            titles[csvLine][j] = csv[csvLine][i];
            i++;
            j++;
        }

        // add null character at end of title
        titles[csvLine][j] = '\0';
        Clean_Whitespace(titles[csvLine]);
        Fix_Case(titles[csvLine]);
        
        // Reset j and move i to next area (year)
        j = 0;
        i++;

        char strYear[1024];
        while (csv[csvLine][i] != ',') {
            strYear[j] = csv[csvLine][i];
            i++;
            j++;
        }

        strYear[j] = '\0';
        Clean_Whitespace(strYear);        
        years[csvLine] = String_To_Year(strYear);

        // Reset j and move i to next field (skip time)
        j = 0;
        i++;

        // Skip time field
        while (csv[csvLine][i] != ',') {
            i++;
        }

        // Copy directors
        i++;
        while (csv[csvLine][i] != ',') {
            directors[csvLine][j] = csv[csvLine][i];
            i++;
            j++;
        }

        directors[csvLine][j] = '\0';
        Clean_Whitespace(directors[csvLine]);
        Director_Last_Name(directors[csvLine]);
        Fix_Case(directors[csvLine]);


        // Reset j and move i to next field (rating)
        j = 0;
        i++;

        char strRating[1024];
        while (csv[csvLine][i] != ',') {
            strRating[j] = csv[csvLine][i];
            i++;
            j++;
        }

        strRating[j] = '\0';
        Clean_Whitespace(strRating);

        ratings[csvLine] = String_To_Rating(strRating);

        // Reset j and move i to next field (dollars)
        j = 0;
        i++;

        char strDollars[1024];
        while (csv[csvLine][i] != '\0') {
            strDollars[j] = csv[csvLine][i];
            i++;
            j++;
        }

        strDollars[j] = '\0';
        Clean_Whitespace(strDollars);
        dollars[csvLine] = String_To_Dollars(strDollars);
    }

    return;
}



/* This function prints a well formatted table of
 * the movie data 
 * Row 1: Header - use name and field width as below
 * Column 1: Id, field width = 3, left justified
 * Column 2: Title, field width = lenth of longest movie + 2 or 7 which ever is larger, left justified, first letter of each word upper case, remaining letters lower case, one space between words
 * Column 3: Year, field with = 6, left justified
 * Column 4: Director, field width = length of longest director last name + 2 or 10 (which ever is longer), left justified, only last name, first letter upper case, remaining letters lower case
 * column 5: Rating, field width = 6, precision 1 decimal place (e.g. 8.9, or 10.0), right justified
 * column 6: Revenue, field width = 11, right justified
 */
void Print_Table(int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {
    // Get data for longest title, director, and revenue
    // Longest Title
    int longestTitle = 0;
    int i = 0;
    for (int movieNum = 0; movieNum < num_movies; movieNum++) {
        while (titles[movieNum][i]) {
            i++;
        }

        if (i > longestTitle) {
            longestTitle = i;
        }
        i = 0;
    }

    // Longest Director
    int longestDirector = 0;
    for (int movieNum = 0; movieNum < num_movies; movieNum++) {
        while (directors[movieNum][i]) {
            i++;
        }

        if (i > longestDirector) {
            longestDirector = i;
        }
        i = 0;
    }

    // Print row 1:
    printf("%-*s", 3, "Id");

    if (longestTitle + 2 > 7) {
        printf("%-*s", longestTitle + 2, "Title");
    } else {
        printf("%-*s", 7, "Title");
    }

    printf("%-*s", 6, "Year");

    if (longestDirector + 2 > 10) {
        printf("%-*s", longestDirector + 2, "Director");
    } else {
        printf("%-*s", 10, "Director");
    }

    printf("%*s", 6, "Rating");
    printf("%*s", 11, "Revenue");
    printf("\n");

    // Print movie data
    for (int movieNum = 0; movieNum < num_movies; movieNum++) {
        printf("%-*d", 3, movieNum + 1);

        if (longestTitle + 2 > 7) {
            printf("%-*s", longestTitle + 2, titles[movieNum]);
        } else {
            printf("%-*s", 7, titles[movieNum]);
        }

        printf("%-*d", 6, years[movieNum]);

        if (longestDirector + 2 > 10) {
            printf("%-*s", longestDirector + 2, directors[movieNum]);
        } else {
            printf("%-*s", 10, directors[movieNum]);
        }

        printf("%*.1f", 6, ratings[movieNum]);
        printf("%*lld\n", 11, dollars[movieNum]);
                
    }
    return;
}


