#include <stdio.h>
#include <string.h>
int main() {
    char str[10];
int i=0;
    fgets(str, 10, stdin);
    printf("%s", str);
    
    for(i=0;str[i]!='\0';i++){
        if((int)str[i]>=42 && (int)str[i]<=47 || (int)str[i]==61 ){
            printf("%c\t - op\n",str[i]);
        }
        else{
            printf("%c\t - id\n",str[i]);
        }
    }
    getch();
    return 0;
}