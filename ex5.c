#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTIONS 100
#define MAX_RULES 10
#define BUFFER_SIZE 100

typedef struct {
    char nonTerminal;
    char productions[MAX_RULES][BUFFER_SIZE];
    int productionCount;
} Grammar;

Grammar grammars[MAX_PRODUCTIONS];
int grammarCount = 0;

// Function to check if a symbol is non-terminal
int isNonTerminal(char symbol) {
    return isupper(symbol);
}

// Function to add a grammar production
void addGrammar(char nonTerminal, char* production) {
    int i,found = 0;
    for (i = 0; i < grammarCount; ++i) {
        if (grammars[i].nonTerminal == nonTerminal) {
            strcpy(grammars[i].productions[grammars[i].productionCount++], production);
            found = 1;
            break;
        }
    }
    if (!found) {
        grammars[grammarCount].nonTerminal = nonTerminal;
        strcpy(grammars[grammarCount].productions[0], production);
        grammars[grammarCount++].productionCount = 1;
    }
}

// Function to compute FIRST set for a given non-terminal
void computeFirst(char nonTerminal, char* firstSet) {
    int i,j;
    char symbol;
    for (i = 0; i < grammarCount; ++i) {
        if (grammars[i].nonTerminal == nonTerminal) {
            for (j = 0; j < grammars[i].productionCount; ++j) {
                symbol = grammars[i].productions[j][0];
                if (!isNonTerminal(symbol)) {
                    // If the first symbol is terminal, add it to FIRST set
                    strncat(firstSet, &symbol, 1);
                } else {
                    // Recursively find FIRST set for the non-terminal
                    computeFirst(symbol, firstSet);
                }
            }
            break;
        }
    }
}

// Function to compute FOLLOW set for a given non-terminal
void computeFollow(char nonTerminal, char* followSet) {
    int i,j;
    char* pos;char nextSymbol;
    if (nonTerminal == grammars[0].nonTerminal) {
        strcat(followSet, "$"); // Add $ to FOLLOW of start symbol
    }

    for (i = 0; i < grammarCount; ++i) {
        for (j = 0; j < grammars[i].productionCount; ++j) {
            pos = strchr(grammars[i].productions[j], nonTerminal);
            if (pos) {
                nextSymbol = *(pos + 1);
                if (nextSymbol == '\0') {
                    // If non-terminal is at the end, compute FOLLOW of the left-hand non-terminal
                    if (grammars[i].nonTerminal != nonTerminal) {
                        computeFollow(grammars[i].nonTerminal, followSet);
                    }
                } else if (!isNonTerminal(nextSymbol)) {
                    // If the next symbol is terminal, add it to FOLLOW set
                    strncat(followSet, &nextSymbol, 1);
                } else {
                    // Compute FIRST of the next symbol and add to FOLLOW set
                    char tempFirstSet[BUFFER_SIZE] = "";
                    computeFirst(nextSymbol, tempFirstSet);
                    strcat(followSet, tempFirstSet);
                }
            }
        }
    }
}

int main() {
    char input[BUFFER_SIZE];
    int i,n;
    char nonTerminal;char* production;
    printf("Enter the number of productions: ");
    
    scanf("%d", &n);
    getchar(); // Consume newline

    for (i = 0; i < n; ++i) {
        printf("Enter production %d: ", i + 1);
        fgets(input, BUFFER_SIZE, stdin);
        input[strcspn(input, "\n")] = 0; // Remove newline

        nonTerminal = input[0];
        production = strchr(input, '>') + 1;
        addGrammar(nonTerminal, production);
    }

    for (i = 0; i < grammarCount; ++i) {
        char firstSet[BUFFER_SIZE] = "";
        char followSet[BUFFER_SIZE] = "";

        computeFirst(grammars[i].nonTerminal, firstSet);
        computeFollow(grammars[i].nonTerminal, followSet);

        printf("FIRST(%c): {%s}\n", grammars[i].nonTerminal, firstSet);
        printf("FOLLOW(%c): {%s}\n", grammars[i].nonTerminal, followSet);
    }
    getch();
    return 0;
}
