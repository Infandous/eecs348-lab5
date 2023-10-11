#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void calculate(int score){
    int possibilities[] = {6,3,2,8,7};
    int possibility[5]; //used to hold the scores for a given possibility
    printf("possible scores for a game with %d points:\n",score);
    //brute force possible scores
    for (int i = 0; i<(score/possibilities[0]);i++){ //TD
        for (int j = 0; j<(score/possibilities[1]);j++){ //FG
            for (int t = 0; t<(score/possibilities[2]);t++){ //S
                for (int s = 0; s<(score/possibilities[3]);s++){//TD+2
                    for (int o = 0; o<(score/possibilities[4]);o++){ //TD+1
                        if (((i*possibilities[0] + j*possibilities[1]) + (t*possibilities[2]) + (s*possibilities[3]) + (o*possibilities[4])) == score) {
                            printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", s,o,i,j,t);
                        }
                    }
                }
            }
        }

    }
}

int main(){
    char score[4]; //to hold input. An NFL score should not be greater than 3 digits in length + the newline character
    bool quit = false; //used to determine if the program will exit
    while (!quit){

    
        printf("enter 1 or 0 to exit\n");
        printf("enter your NFL score:");
        fgets(score, sizeof(score), stdin); //read score intro str

        // Remove the newline character
        int len = strlen(score);
        if (len > 0 && score[len - 1] == '\n') {
            score[len - 1] = '\0'; //set newline to null
        }

        if (atoi(score)==0 || atoi(score)==1){//exit if score is 1 or 0
            quit=true;
        }else{
            calculate(atoi(score)); //call calculate function to find possibilites
        }

    }

    return 0;
}