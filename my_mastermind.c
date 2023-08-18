

#include "lib_s.h"
int main(int argc, char** argv){
    int is_c = 0, is_tm = 0, attemps = 10;
    char* hidden_nbr = (char*)calloc(5, sizeof(char));
    for(int i = 0; argv[i]; i++){
        if(strcmp(argv[i], "-c") == 0 && argc > 2){
            check_guests(argv[i+1]);
            strcpy(hidden_nbr, argv[i+1]);
            is_c++;            
        }else if(strcmp(argv[i], "-t") == 0 && argc > 2){
            check_attemps(argv[i+1]);
            attemps = atoi(argv[i+1]);
            is_tm++;
        }
    }
    if(is_c || is_tm || argc == 1)
        my_mastermind(hidden_nbr, attemps, is_c);
}