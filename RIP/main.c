#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cJSON.h"
#include <curl/curl.h>
#include "json.h"
#include "print.h"
#include <string.h>

int main(int argc, char ** argv)
{
    system("chcp 65001");// Permet de mettre le code en UTF-8 les accent et tous
    system("cls");// on efface ne marche que sur windows
    menu(); // on lance le menu
    return 0;
}
void menu()
{
    int state = 1; // boucle principal du programme
    while(state == 1)
    {
        int geoParis;
        int charGood = 0;
        while(charGood == 0)//demande de géolocation
        {
            char res;
            fflush(stdin);
            printf("\nVoulez-vous que l'ont vous géolocalise ? (O/N) ");
            scanf("%c",&res);
            if (res=='O' || res == 'o')
            {
                geoParis = findGeo();// crée le fichier pays et check la ville
                // si la fonction renvoie 1 c'est que on est géolocalisé dans Paris
                charGood = 1;

            }
            else if(res == 'N' ||res =='n')
            {
                findNotGeo();// demande le pays et crée le fichier
                charGood = 1;
            }
            else
            {
                printf("Ce n'est pas un réponse disponible");
            }
        }

        printResult();// on affiche les resultat du pays


        geoParis = 1;
        if(geoParis)// on test si on est dans Paris
        {
            tabac();// demande d'arrondisment et afichage des tabac
        }

        if (redo())
        {
            state = 1;
        }
        else
        {
            state = 0;
        }


    }

}

void printResult(){
    char * result;
    result=file2StringCountry("country.JSON");// on met le ficher de pays dans un string
    printJsonCountry(result); // on imprime tous le tralala
    printf("\n\n");
}

void tabac()
{
    int zip;
    fflush(stdin);
    printf("\nJe vois que vous êtes a Paris\n");
    printf("\nVoulez-vous me donnez votre arrondisement (750XX):");
    scanf("%d",&zip);
    if(checkZip(zip) == 1)
    {
        char * result;
        doFileZip(zip);// on crée le fichier pour les tabac
        result=file2String("zip.JSON");//on met en string
        adresse(result);//et on imprime
    }
}
int redo()// relancer de programme
{
    int errorChar = 0;
    while(errorChar==0)
    {
        char stay;
        fflush(stdin);
        printf("Voulez vous saisir un autre pays? (o/n): ");
        scanf("%c",&stay);
        if(stay == 'o' || stay == 'O' )
        {
            return 1;
        }
        else if(stay == 'n' || stay == 'N')
        {
            return 0;
        }
        else
        {
            printf("\nRéponse non reconnu, retapez\n");
        }
    }
}
int findGeo()
{

    doFileIp();//on fais le curl de l'ip et on écrit le fichier
    char * result;
    char * geoParis;
    char * country;

    result=file2String("ip.JSON");// on met en string
    geoParis=getParis(result);
    country=getCountry(result);
    doFileCountry(country);//on imprime

    return checkParis(geoParis);//retourn 1 si dans paris
}

int checkParis(char * geoParis)
{
    if (strstr(geoParis, "Paris"))
    {
        return TRUE;
    }
    return FALSE;
}

void findNotGeo()//sans géoloc
{
    char * country;
    fflush(stdin);
    printf("\nSaisissez un pays: ");
    scanf("%s",&country);
    doFileCountry(country);
}


int checkZip(int zip)//ob check si le code postal est bien dans paris
{
    int tab[20] = {75001,75002,75003,75004,75005,75006,75007,7508,75009,75010,75011,75012,75013,75014,75015,75016,75017,75018,75019,75020};
    int i;
    for(i = 0; i<20; i++)
    {
        if(tab[i]==zip)
            return 1;
    }
    return 0;
}
