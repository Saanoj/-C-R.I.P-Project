#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cJSON.h"
#include <curl/curl.h>
#include "json.h"
#include "print.h"

int main(int argc, char **argv)
{
    system("chcp 65001");
    system("cls");
    int state=0;
    int errorChar=1;
    char* country = malloc(40);
    char* geoParis = malloc(40);
    char country2[40];
    int zip;

    char res;
    char stay;


    while(state==0)
    {
        while(errorChar ==1){
            fflush(stdin);
            printf("\nVoulez-vous que l'ont vous géolocalise ? (O/N) ");
            scanf("%c",&res);

            if (res=='O' || res == 'o')
            {
                doFileIp();
                char * result = malloc(file2String("ip.JSON"));
                result=file2String("ip.JSON");
                geoParis = getParis(result);
                country = getCountry(result);
                doFileCountry(country);
                free(country);
                free(result);
                errorChar = 0;
            }
            else if(res == 'N' ||res =='n')
            {

                fflush(stdin);
                printf("\nSaisissez un pays: ");
                scanf("%s",&country2);
                doFileCountry(country2);

                errorChar = 0;


            }else
            {
                printf("Ce n'est pas un réponse disponible");

            }
        }





        char * result = malloc(file2StringCountry("country.JSON"));
        result=file2StringCountry("country.JSON");
        printJsonCountry(result);
        free(result);
        printf("\n\n");

        //geoParis = "Paris";
        if(geoParis =="Paris"){
            fflush(stdin);
            printf("\nJe vois que vous êtes a Paris\n");
            printf("\nVoulez-vous me donnez votre arrondisement (750XX):");
            scanf("%d",&zip);
            if(checkZip(zip) == 1){

                doFileZip(zip);
                char * result = malloc(file2String("zip.JSON"));
                result=file2String("zip.JSON");

                adresse(result);
                free(result);
            }
        }


        free(geoParis);


        while(errorChar==0)
        {
            fflush(stdin);
            printf("Voulez vous saisir un autre pays? (o/n): ");
            scanf("%c",&stay);
            if(stay == 'o' || stay == 'O' )
            {
                state=0;
                errorChar=1;
            }
            else if(stay == 'n' || stay == 'N')
            {
                state=1;
                errorChar=1;
            }
            else
            {
                errorChar=0;
                printf("\nRéponse non reconnu, retapez\n");
            }
        }
        errorChar=0;
    }

    return 0;
}

int checkZip(int zip){
    int tab[20] = {75001,7502,7503,75004,75005,75006,75007,7508,75008,75010,75011,75012,75012,75014,75015,75016,75017,75018,75019,75020};
    int i;
    for(i = 0;i<20;i++){
        if(tab[i]==zip)
            return 1;
    }
    return 0;
}
