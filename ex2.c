#include <stdio.h>
#include<string.h>
#define max 10
#define max_stack [3] ={0}
int transition_table[max][max];

int main () {
    int i=0,j=1;
    char re[100];
    printf("Enter the regular Expression");
    fgets(re,sizeof(re),stdin);
    re[strlen(re)-1]='\0';
    while(i<strlen(re)){
        switch(re[i]){
            case 'a':
                if (transition_table[i][0]==0){
                    transition_table[i][0]=j;
                    j++;
                }
                i++;
                break;
            case 'b':
                if (transition_table[i][1]==0){
                    transition_table[i][1]=j;
                    j++;
                }
                i++;
                break;
            case 'e':
                if (transition_table[i][2]==0){
                    transition_table[i][2]=j;
                    j++;
                }
                i++;
                break;  
            default:
                printf("invalid character in Regular Expression");
                return 1;
        }
    }
    for (i=0;i<strlen(re);i++){
        if(transition_table[i][0]!=0){
            printf("q[%d,a] ----> q%d\n",i,transition_table[i][0]);
            }
        if(transition_table[i][1]!=0){
            printf("q[%d,b] ----> q%d\n",i,transition_table[i][1]);
            }
        if(transition_table[i][2]!=0){
            printf("q[%d,e] ----> q%d\n",i,transition_table[i][2]);
            }
        else{
            printf("q[%d,e] ----> q%d\n",i,transition_table[i][2]);
        }
    }
    getch();
    return 0;
}