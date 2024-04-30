#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nonTerminal;
    char** productions;
    int numProductions;
} Production;

char getValidNewNonTerminal(const Production* p) {
    char candidate;
    for (candidate = 'Z'; candidate >= 'A'; --candidate) {
        if (candidate != p->nonTerminal) {
            return candidate;
        }
    }
    return '\0'; 
}

void eliminateLeftRecursion(Production* p) {
    int i,hasLeftRecursion = 0;
    char newNonTerminal = getValidNewNonTerminal(p);
    if (newNonTerminal == '\0') {
        printf("Error: Unable to find a valid new non-terminal.\n");
        return;
    }

    
    for (i = 0; i < p->numProductions; i++) {
        if (p->productions[i][0] == p->nonTerminal) {
            hasLeftRecursion = 1;
            break;
        }
    }

    if (!hasLeftRecursion) {
        printf("No left recursion found in productions.\n");
        return;
    }

    for (i = 0; i < p->numProductions; i++) {
        if (p->productions[i][0] == p->nonTerminal) {
            printf("%c -> %s%c\n", newNonTerminal, p->productions[i] + 1, newNonTerminal);
            free(p->productions[i]);
            p->productions[i] = NULL; // Mark for removal
        }
    }

    for (i = 0; i < p->numProductions; i++) {
        if (p->productions[i]) {
            printf("%c -> %s%c\n", p->nonTerminal, p->productions[i], newNonTerminal);
        }
    }

    printf("%c -> ε\n", newNonTerminal); // Add epsilon production for the new non-terminal
}

int main() {
    Production p;
    char buffer[1024]; // Increased buffer size for longer productions
    int numProductions,i,j;

    printf("Enter the non-terminal: ");
    if (scanf(" %c", &p.nonTerminal) != 1) {
        printf("Invalid input for non-terminal.\n");
        return 1;
    }

    printf("Enter the number of productions: ");
    if (scanf("%d", &numProductions) != 1 || numProductions <= 0) {
        printf("Invalid number of productions.\n");
        return 1;
    }

    p.numProductions = numProductions;
    p.productions = (char**)malloc(numProductions * sizeof(char*));
    if (!p.productions) {
        perror("Failed to allocate memory for productions");
        return 1;
    }

    for (i = 0; i < numProductions; i++) {
        printf("Enter production %d: ", i + 1);
        scanf("%s", buffer);
        p.productions[i] = strdup(buffer);
        if (!p.productions[i]) {
            perror("Failed to duplicate production string");
            // Free previously allocated memory before exiting
            for (j = 0; j < i; j++) {
                free(p.productions[j]);
            }
            free(p.productions);
            return 1;
        }
    }

    eliminateLeftRecursion(&p);

    // Free allocated memory
    for (i = 0; i < numProductions; i++) {
        if (p.productions[i]) {
            free(p.productions[i]);
        }
    }
    free(p.productions);
    getch();
    return 0;
}
