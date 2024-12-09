#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
//wordle-hard
//guess with capital letters only pleaaase
char hint;
int no_cow(char*guess, char* word){
    int cow = 0;
    for(int i = 0;i<4;i++){
        if(guess[i]==word[i]){
            cow++;
        }
    }
    return cow;
}

int word_search(char*word, char array[3000][5]){
    for(int i = 0;i<3000;i++){
        if(strcmp(word, array[i])==0){
            return 1;//word found
        }
    }
    return 0;//not found
}

int no_bull(char* guess, char* word){
    int bull = 0;
    for(int i = 0;i<4;i++){
        for(int j =0;j<4;j++){
            if(i == j){
                continue;
            }
            if(guess[i] == word[j]){
                bull++;
                hint = guess[i];
            }
        }
    }
    return bull;
}

int check_repeats(char* word){
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            if(i == j){
                continue;
            }
            if(word[i] == word[j]){
                return 0;//repeats
            }
        }
    }
    return 1;
}


int main(){
    char str[5];
    char array_words[3000][5];
    char array_all_words[3000][5];
    FILE* ptr = NULL;
    ptr = fopen("words.txt", "r");
    int i = 0;
    int count = 0;

if(!ptr)
{
    printf("error!");
}
    while(fgets(str, sizeof(str), ptr)!=NULL){
        if (str[strlen(str) - 1] == '\n') {
            str[strlen(str) - 1] = '\0';}

        strcpy(array_all_words[i], str);
        if(check_repeats(str)==1){
            strcpy(array_words[count], str);
            count++;
        }
        i++;
    }
    fclose(ptr);
    srand(time(NULL));
    int n = rand()%count;
    char* word = array_words[n];

    //array_words has all the 4 letter words with no repeats.
    //array_all_words has all 4 letter valid words.
    char guess[5];
    int cow, bull;

    
    int turn = 1;

    printf("WELCOME TO COW-BULL\n");
    printf("COW: letter is in the right place!\n");
    printf("BULL: letter is present but in the wrong place!\n");
    printf("ENTER your GUESS\n");

    int total = 11;

    while(turn != total){
        scanf("%4s", guess);
        if(strcmp(guess, "hint")==0){
            if(cow == 0 && bull == 0){
                printf("one of the letters is %c", word[1]);
            }
            if(bull != 0){
                printf("one of the bulls is the letter %c" , hint);
            }
        }
        if(word_search(guess, array_all_words)==0){
            printf("Please enter a valid word!\n");
            continue;
        }

        cow = no_cow(guess, word);
        bull = no_bull(guess, word);
       
        printf("turn %d:\n cows - %d\n bulls - %d\n", turn, cow, bull);
        if(strcmp(guess, word)==0){
            printf("YES! you guessed the word right. it was %s", word);
            printf("you took %d tries", turn);
            break;
        }
        turn++;
    }

    if(turn == total){
        printf("OOPS you lost! the word was %s", word);
    }
    
    return 0;
}
