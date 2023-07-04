//Code by Sayan Mandal (Reg No.- 1004) and Anushtup Ganguly (Reg No.-978)
//The given code is a C program that reads keywords from two files and generates statistics about the frequency of those keywords. It uses a hash table for efficient keyword search and storage.
#include <stdio.h>   //Header files,I/O
#include <stdlib.h>  //Memory Allocation
#include <string.h>  //String Manipulation

#define MAX_KEYWORDS 1000  //Maximum number of keywords
#define MAX_WORD_LENGTH 50  //Maximum length of a keyword

typedef struct {            //Storing the word and its Count
    char word[MAX_WORD_LENGTH];
    int count;
} Keyword;

typedef struct {          //Hash table of keywords containing an array of keyword pointers and the number of keywords
    Keyword* keywords[MAX_KEYWORDS];
    int numKeywords;
} KeywordTable;

// Function to check if a word is a keyword
int isKeyword(KeywordTable* table, const char* word) {

    //This function iterates through the keywords in the table and compares each keyword with the given word using `strcmp`.
    //If a match is found, it returns the index of the keyword; otherwise, it returns -1.

    for (int i = 0; i < table->numKeywords; i++) {
        if (strcmp(table->keywords[i]->word, word) == 0) {
            return i;
        }
    }
    return -1;
}

// Function to insert a new keyword into the hash table

void insertKeyword(KeywordTable* table, const char* word) {
    
    //This function checks if the table has reached its maximum capacity, and if so, it prints an error message and returns.
    if (table->numKeywords >= MAX_KEYWORDS) {
        printf("Keyword table is full. Cannot insert more keywords.\n");
        return;
    }

    //It allocates memory for a new keyword, copies the given word into it using `strcpy`, sets the count to 0, and adds it to the table.
    Keyword* keyword = (Keyword*)malloc(sizeof(Keyword));
    strcpy(keyword->word, word);
    keyword->count = 0;
    table->keywords[table->numKeywords++] = keyword;
}

// Function to update (increment) the count of a keyword
//This function takes the keyword table and the index of the keyword to update.
// It increments the count of the keyword in the table.

void updateKeywordCount(KeywordTable* table, int index) {
    table->keywords[index]->count++;
}

// Function to print the keyword statistics
void printKeywordStatistics(KeywordTable* table) {

    //This function prints the header for the statistics table.

    printf("Keyword\t\tCount\n");
    printf("------------------------\n");

    //It then iterates through the keywords in the table and prints each keyword along with its count.

    for (int i = 0; i < table->numKeywords; i++) {
        printf("%s\t\t%d\n", table->keywords[i]->word, table->keywords[i]->count);
    }
}

int main() {
    FILE* keywordFile = fopen("keywords.txt", "r");     //Opens a text file in Read mode
    
    //If the file fails to open, it prints an error message and returns with an error code.

    if (keywordFile == NULL) {
        printf("Failed to open keywords file.\n");
        return 1;
    }
     
    //initializes the `KeywordTable` structure, setting the number of keywords to 0.

    KeywordTable keywordTable;
    keywordTable.numKeywords = 0;

    // Read keywords from the file and build the hash table
    char word[MAX_WORD_LENGTH];
    
    //It reads each word from the keyword file using `fscanf` and inserts it into the keyword table using the `insertKeyword` function.
    
    while (fscanf(keywordFile, "%s", word) != EOF) {
        insertKeyword(&keywordTable, word);
    }
    //After reading all the keywords, the keyword file is closed.

    fclose(keywordFile);
    
    //Opening the 'text.txt' file to search for the keywords
    FILE* textFile = fopen("text.txt", "r");
    if (textFile == NULL) {
        printf("Failed to open text file.\n");
        return 1;
    }

    // Read the contents of the text file and search for keywords

    //it reads each word from the text file using `fscanf` and checks if it is a keyword using the `isKeyword` function.

    while (fscanf(textFile, "%s", word) != EOF) {
        int index = isKeyword(&keywordTable, word);
        if (index != -1) {

            //If a keyword is found, it updates its count using the `updateKeywordCount` function.

            updateKeywordCount(&keywordTable, index);
        }
    }
    //After reading all the words in the text file, it closes the text file.

    fclose(textFile);

    // Print the keyword statistics
    printKeywordStatistics(&keywordTable);

    // Cleanup - free allocated memory for each keyword in the keyword table
    for (int i = 0; i < keywordTable.numKeywords; i++) {
        free(keywordTable.keywords[i]);
    }

    return 0;
}
