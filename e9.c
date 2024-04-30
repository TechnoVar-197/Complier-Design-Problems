#include <stdio.h>
#include <string.h>

struct Grammar {
    char lhs;
    char rhs[8];
} g[20], item[20], clos[20][10];

char prod[20][20], listofvar[26] = "ABCDEFGHIJKLMNOPQR";
int novar = 1, i = 0, j = 0, k = 0, n = 0, m = 0, arr[30];
int noitem = 0;

int isvariable(char variable) {
    int i; // Declare i as a local variable
    for(i = 0; i < novar; i++) {
        if(g[i].lhs == variable) {
            return i + 1;
        }
    }
    return 0;
}

void findclosure(int z, char a) {
    int n = 0, i = 0, j = 0, k = 0, l = 0, c, flag;
    char temp;
    for(i = 0; i < arr[z]; i++) {
        for(j = 0; j < strlen(clos[z][i].rhs); j++) {
            if(clos[z][i].rhs[j] == '.' && clos[z][i].rhs[j+1] == a) {
                clos[noitem][n].lhs = clos[z][i].lhs;
                strcpy(clos[noitem][n].rhs, clos[z][i].rhs);
                temp = clos[noitem][n].rhs[j];
                clos[noitem][n].rhs[j] = clos[noitem][n].rhs[j+1];
                clos[noitem][n].rhs[j+1] = temp;
                n = n + 1;
            }
        }
    }
    for(i = 0; i < n; i++) {
        for(j = 0; j < strlen(clos[noitem][i].rhs); j++) {
            if(clos[noitem][i].rhs[j] == '.' && isvariable(clos[noitem][i].rhs[j+1]) > 0) {
                for(k = 0; k < novar; k++) {
                    if(clos[noitem][i].rhs[j+1] == clos[0][k].lhs) {
                        for(l = 0; l < n; l++) {
                            if(clos[noitem][l].lhs == clos[0][k].lhs && strcmp(clos[noitem][l].rhs, clos[0][k].rhs) == 0) {
                                break;
                            }
                        }
                        if(l == n) {
                            clos[noitem][n].lhs = clos[0][k].lhs;
                            strcpy(clos[noitem][n].rhs, clos[0][k].rhs);
                            n = n + 1;
                        }
                    }
                }
            }
        }
    }
    arr[noitem] = n;
    flag = 0;
    for(i = 0; i < noitem; i++) {
        if(arr[i] == n) {
            for(j = 0; j < arr[i]; j++) {
                c = 0;
                for(k = 0; k < arr[i]; k++) {
                    if(clos[noitem][k].lhs == clos[i][k].lhs && strcmp(clos[noitem][k].rhs, clos[i][k].rhs) == 0) {
                        c = c + 1;
                    }
                }
                if(c == arr[i]) {
                    flag = 1;
                    goto exit;
                }
            }
        }
    }
    exit:;
    if(flag == 0) {
        arr[noitem++] = n;
    }
}

int main() {
    char list[10], temp[2];
    int i, j, k, z, x, l = 0;

    printf("ENTER THE PRODUCTIONS OF THE GRAMMAR (Enter '0' to end):\n");
    do {
        scanf("%s", prod[i++]);
    } while(strcmp(prod[i - 1], "0") != 0);

    printf("\nAugmented grammar:\n");
    for(n = 0; n < i - 1; n++) {
        m = 0;
        j = novar;
        g[novar++].lhs = prod[n][0];
        for(k = 3; k < strlen(prod[n]); k++) {
            if(prod[n][k] != '|') {
                g[j].rhs[m++] = prod[n][k];
            }
            if(prod[n][k] == '|') {
                g[j].rhs[m] = '\0';
                m = 0;
                j = novar;
                g[novar++].lhs = prod[n][0];
            }
        }
    }

    for(i = 0; i < 26; i++) {
        if(!isvariable(listofvar[i])) {
            break;
        }
    }

    g[0].lhs = listofvar[i];
    temp[0] = g[1].lhs; temp[1] = '\0';
    strcat(g[0].rhs, temp);

    for(i = 0; i < novar; i++) {
        clos[noitem][i].lhs = g[i].lhs;
        strcpy(clos[noitem][i].rhs, g[i].rhs);
        if(strcmp(clos[noitem][i].rhs, "ε") == 0) {
            strcpy(clos[noitem][i].rhs, ".");
        } else {
            for(j = strlen(clos[noitem][i].rhs) + 1; j >= 0; j--) {
                clos[noitem][i].rhs[j] = clos[noitem][i].rhs[j - 1];
            }
            clos[noitem][i].rhs[0] = '.';
        }
    }

    arr[noitem++] = novar;

    printf("\n\nThe augmented grammar is:\n");
    for(z = 0; z < novar; z++) {
        printf("%c->%s\n", clos[noitem - 1][z].lhs, clos[noitem - 1][z].rhs);
    }

    for(z = 0; z < noitem; z++) {
        l = 0;
        for(j = 0; j < arr[z]; j++) {
            for(k = 0; k < strlen(clos[z][j].rhs) - 1; k++) {
                if(clos[z][j].rhs[k] == '.') {
                    for(m = 0; m < l; m++) {
                        if(list[m] == clos[z][j].rhs[k + 1]) {
                            break;
                        }
                    }
                    if(m == l) {
                        list[l++] = clos[z][j].rhs[k + 1];
                    }
                }
            }
        }
        for(x = 0; x < l; x++) {
            findclosure(z, list[x]);
        }
    }

    printf("\n\nThe set of items are:\n\n");
    for(z = 0; z < noitem; z++) {
        printf("I%d\n\n", z);
        for(j = 0; j < arr[z]; j++) {
            printf("%c->%s\n", clos[z][j].lhs, clos[z][j].rhs);
        }
        printf("\n");
    }
    getch();
    return 0;
}
