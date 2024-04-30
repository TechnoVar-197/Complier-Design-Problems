#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nonTerminal;
    char** productions;
    int numProductions;
} Production;

void leftFactoring(Production* p) {
    int i, j;
    char commonPrefix[10];
    int commonPrefixLength = 0;

    // Find the longest common prefix among productions
    for (i = 0; i < p->numProductions - 1; ++i) {
        for (j = i + 1; j < p->numProductions; ++j) {
            int k = 0;
            while (p->productions[i][k] == p->productions[j][k] && k < 10) {
                commonPrefix[k] = p->productions[i][k];
                ++k;
            }
            if (k > commonPrefixLength) {
                commonPrefixLength = k;
                commonPrefix[k] = '\0'; // Null-terminate the common prefix string
            }
        }
    }

    if (commonPrefixLength > 0) {
        printf("%c -> %s%c'\n", p->nonTerminal, commonPrefix, p->nonTerminal);
        for (i = 0; i < p->numProductions; ++i) {
            if (strncmp(p->productions[i], commonPrefix, commonPrefixLength) == 0) {
                if (strlen(p->productions[i]) == commonPrefixLength) {
                    printf("%c' -> ε\n", p->nonTerminal); // ε represents an empty string
                } else {
                    printf("%c' -> %s\n", p->nonTerminal, p->productions[i] + commonPrefixLength);
                }
            }
        }
    } else {
        for (i = 0; i < p->numProductions; ++i) {
            printf("%c -> %s\n", p->nonTerminal, p->productions[i]);
        }
    }
}

int main() {
    Production p;
    char buffer[100];
    int numProductions, i;

    printf("Enter the non-terminal: ");
    scanf(" %c", &p.nonTerminal);

    printf("Enter the number of productions: ");
    scanf("%d", &numProductions);
    p.numProductions = numProductions;
    p.productions = (char**)malloc(numProductions * sizeof(char*));

    for (i = 0; i < numProductions; i++) {
        printf("Enter production %d: ", i + 1);
        scanf("%s", buffer);
        p.productions[i] = strdup(buffer);
    }

    leftFactoring(&p);

    // Free allocated memory
    for (i = 0; i < numProductions; i++) {
        free(p.productions[i]);
    }
    free(p.productions);
    getch();
    return 0;
}
