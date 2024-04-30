#include <stdio.h>
#include <string.h>

#define MAX_VARS 10
#define MAX_TERMS 10
#define MAX_PROD 20

int vars, terms;
char var[MAX_VARS], term[MAX_TERMS], lead[MAX_VARS][MAX_TERMS] = {0}, trail[MAX_VARS][MAX_TERMS] = {0};

struct grammar {
    int prodno;
    char lhs;
    char rhs[MAX_PROD][MAX_PROD];
} gram[50];

void get() {
    int i,j;
    printf("\nLEADING AND TRAILING\n");
    printf("\nEnter the number of variables: ");
    scanf("%d", &vars);
    printf("\nEnter the variables:\n");
    for (i = 0; i < vars; i++) {
        scanf(" %c", &gram[i].lhs);
        var[i] = gram[i].lhs;
    }
    printf("\nEnter the number of terminals: ");
    scanf("%d", &terms);
    printf("\nEnter the terminals: ");
    for (j = 0; j < terms; j++)
        scanf(" %c", &term[j]);
    printf("\nPRODUCTION DETAILS\n");
    for (i = 0; i < vars; i++) {
        printf("\nEnter the number of productions for %c: ", gram[i].lhs);
        scanf("%d", &gram[i].prodno);
        for (j = 0; j < gram[i].prodno; j++) {
            printf("%c->", gram[i].lhs);
            scanf("%s", gram[i].rhs[j]);
        }
    }
}

void leading() {
    int i,j,k,m,count,rep,temp=-1;
    for (i = 0; i < vars; i++) {
        for (j = 0; j < gram[i].prodno; j++) {
            for (k = 0; k < terms; k++) {
                if (gram[i].rhs[j][0] == term[k]) {
                    lead[i][k] = 1;
                } else if (gram[i].rhs[j][1] == term[k]) {
                    lead[i][k] = 1;
                }
            }
        }
    }

    for (rep = 0; rep < vars; rep++) {
        for (i = 0; i < vars; i++) {
            for (j = 0; j < gram[i].prodno; j++) {
                temp = -1;
                for (m = 0; m < vars; m++) {
                    if (gram[i].rhs[j][0] == var[m]) {
                        temp = m;
                        break;
                    }
                }
                if (temp != -1) {
                    for (k = 0; k < terms; k++) {
                        if (lead[temp][k] == 1)
                            lead[i][k] = 1;
                    }
                }
            }
        }
    }
}

void trailing() {
    int i,j,k,m,count,rep,temp=-1;
    for (i = 0; i < vars; i++) {
        for (j = 0; j < gram[i].prodno; j++) {
            count = strlen(gram[i].rhs[j]);
            for (k = 0; k < terms; k++) {
                if (gram[i].rhs[j][count - 1] == term[k]) {
                    trail[i][k] = 1;
                } else if (count > 1 && gram[i].rhs[j][count - 2] == term[k]) {
                    trail[i][k] = 1;
                }
            }
        }
    }

    for (rep = 0; rep < vars; rep++) {
        for (i = 0; i < vars; i++) {
            for (j = 0; j < gram[i].prodno; j++) {
                count = strlen(gram[i].rhs[j]);
                temp = -1;
                for (m = 0; m < vars; m++) {
                    if (gram[i].rhs[j][count - 1] == var[m]) {
                        temp = m;
                        break;
                    }
                }
                if (temp != -1) {
                    for (k = 0; k < terms; k++) {
                        if (trail[temp][k] == 1)
                            trail[i][k] = 1;
                    }
                }
            }
        }
    }
}

void display() {
    int i,j;
    for (i = 0; i < vars; i++) {
        printf("\nLEADING(%c) = {", gram[i].lhs);
        for (j = 0; j < terms; j++) {
            if (lead[i][j] == 1)
                printf("%c, ", term[j]);
        }
        printf("}");
    }
    printf("\n");
    for (i = 0; i < vars; i++) {
        printf("\nTRAILING(%c) = {", gram[i].lhs);
        for (j = 0; j < terms; j++) {
            if (trail[i][j] == 1)
                printf("%c, ", term[j]);
        }
        printf("}");
    }
    printf("\n");
}

int main() {
    get();
    leading();
    trailing();
    display();
    return 0;
}
