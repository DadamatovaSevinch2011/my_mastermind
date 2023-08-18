#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

void check_guests(char* str){
    if(strlen(str) < 4 || strlen(str) > 4) exit(0);
    for(int i = 0; str[i]; i++){
        if(str[i] >= '9' || str[i] < '0'){
            printf("Pieces will be '0' '1' '2' '3' '4' '5' '6' '7' '8'.!\n");
            exit(0);
        }
    }
    for(int i = 0; str[i]; i++){
        for(int j = i+1; str[j]; j++){
            if(str[i] == str[j]){
                printf("Mustn't be doubles in guest number!\n");
                exit(0);
            }
        }
    }
}


void check_attemps(char* str){
    for(int i = 0; str[i]; i++){
        if(str[i] >= '9' || str[i] < '0'){
            printf("Input only numbers in option '-t'!\n");
            exit(0);
        }
    }
}

int check_given_nbrs(char* str){
    if(strlen(str) > 4){
        printf("Input will be 4 digits long!\n");
        return 0;
    }
    for(int i = 0; str[i]; i++){
        if(str[i] >= '9' || str[i] < '0'){
            printf("Pieces will be '0' '1' '2' '3' '4' '5' '6' '7' '8'.!\n");
            return 0;
        }
    }
    for(int i = 0; str[i]; i++){
        for(int j = i+1; str[j]; j++){
            if(str[i] == str[j]){
                printf("Mustn't be doubles in  number!\n");
                return 0;
            }
        }
    }
    return 1;
}

char* read_from_terminal(char* given_nbr){
    char ch;
    int flag = 0, i = 0;
    while((flag = read(0, &ch, 1)) > 0){
        if(ch == '\n') break;
        given_nbr[i++] = ch;
    }if(flag == 0){
          exit(0);
    }if(strlen(given_nbr) != 4){
        printf("Input will be 4 digits long!\n");
        return 0;
    }
    if(check_given_nbrs(given_nbr) == 0) return 0;
    return given_nbr;
}

int how_many_corrects(char* given_nbr, char* hidden_nbr){
    int placed_pieces = 0;
    for(int i = 0; hidden_nbr[i]; i++){
        for(int j = 0; given_nbr[j]; j++){
            if(given_nbr[j] == hidden_nbr[i]){
                placed_pieces++;
            }
        }
    }
    return placed_pieces;
} 

int how_many_wplaceds(char* given_nbr, char* hidden_nbr){
    int placed_pieces = 0;
    for(int i = 0; hidden_nbr[i]; i++){
        for(int j = i; given_nbr[j]; j++){
            if((hidden_nbr[i] == given_nbr[j]) && (i == j)){
                placed_pieces++;
            }
        }
    }
    return placed_pieces;
}

char* rand_a_hidden_nbr(){
    srand((time(NULL)));
    char* randomized_nbr = (char*)calloc(5, sizeof(char));
    short flag = 0;
    char c;
    for(int i = 0; i < 4; i++){
        flag = 0;
        c = rand()%9 + '0';
        if(i == 0)
            randomized_nbr[i] = c;
        for(short j = 0; j < i; j++){
            if(randomized_nbr[j] == c){flag = 1;i--;break;}
        }
        if(flag == 0)randomized_nbr[i] = c;
    }
    return randomized_nbr;
}

void my_mastermind(char* hidden_nbr, int attemps, int is_c){// printf("Guest nbr: %s\nNbr of attemps: %d\n is_c: %d, is_tm: %d\n", hidden_nbr, attemps, is_c, is_tm);
    if(is_c == 0){
        hidden_nbr = rand_a_hidden_nbr();
    }
    printf("Will you find the secret code?\nPlease enter a valid guess\n---\n");
    for(int round = 0; round < attemps; round++){
        char* given_nbr = (char*)calloc(5, sizeof(char));    
        printf("Round %d\n", round);write(1, ">", 1);
        if((given_nbr = read_from_terminal(given_nbr)) == 0){
            continue;
        }if(strcmp(given_nbr, hidden_nbr) == 0){
            printf("Congratz! You did it!\n");
            exit(0);
        }
        else {
            printf("Well placed pieces: %d\nMisplaced pieces: %d\n---\n", how_many_wplaceds(given_nbr, hidden_nbr), how_many_corrects(given_nbr, hidden_nbr) - how_many_wplaceds(given_nbr, hidden_nbr));
        }
    }
    printf("Game over!\n");
}


