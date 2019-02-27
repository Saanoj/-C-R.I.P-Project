#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cJSON.h"
#include <curl/curl.h>
#include "json.h"


int main(int argc, char *argv[])
{
    system("chcp 65001");
    system("cls");
    int state=0;
    int errorChar=0;
    char country[20];
    char stay;
    doFileIp();

    while(state==0){

        fflush(stdin);
        printf("\nSaisissez un pays: ");
        scanf("%s",&country);

        doFileCountry(country);
        char * result = malloc(file2String("country.JSON"));
        result=file2String("country.JSON");
        printJsonCountry(result);
        free(result);
        printf("\n\n");

        while(errorChar==0){
            fflush(stdin);
            printf("Voulez vous saisir un autre pays? (o/n): ");
            scanf("%c",&stay);
            if(stay == 'o'){
                state=0;
                errorChar=1;
            }else if(stay == 'n'){
                state=1;
                errorChar=1;
            }else{
                errorChar=0;
                printf("\nRéponse non reconnu, retapez\n");
            }
        }
        errorChar=0;
    }

    return 0;
}
