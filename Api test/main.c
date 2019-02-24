#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cJSON.h"
#include <curl/curl.h>

char * file2String();
void zerofgets(char * str, int size);
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);
void printJson(char* string);
char * file2String();
void doFile(char * country);


void zerofgets(char * str, int size)
{
    fflush(stdin);
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = 0;
}
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

int main(int argc, char *argv[])
{
    int state=0;
    int errorChar=0;
    char country[20];
    char stay;
    char * result = malloc(file2String());

    while(state==0){

        fflush(stdin);
        printf("\nSaisissez un pays: ");
        scanf("%s",&country);

        doFile(country);
        result=file2String();
        printJson(result);

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
                system("cls");
                printf("\nChar non reconnu, retapez\n");
            }
        }
        errorChar=0;
    }

    free(result);
    return 0;
}

void printJson(char* string){

    cJSON *root = cJSON_Parse(string);

    cJSON *name = cJSON_GetObjectItem(root, "name");
    cJSON *alpha3Code = cJSON_GetObjectItem(root, "alpha3Code");
    cJSON *capital = cJSON_GetObjectItem(root, "capital");
    cJSON *population = cJSON_GetObjectItem(root, "population");
    cJSON *latlngs = cJSON_GetObjectItem(root, "latlng");
    cJSON *latlng;
    cJSON *borders = cJSON_GetObjectItem(root, "borders");
    cJSON *border;
    cJSON *bordersCount = cJSON_GetArraySize(borders);
    int i;

    if (cJSON_IsString(name) && (name->valuestring != NULL) && cJSON_IsString(alpha3Code) && (alpha3Code->valuestring != NULL) &&
        cJSON_IsString(capital) && (capital->valuestring != NULL) && cJSON_IsNumber(population) && (population->valueint != NULL)){

        printf("\nNom du pays : %s", name->valuestring);
        printf("\nCapitale : %s", capital->valuestring);

        printf("\nCode pays : %s", alpha3Code->valuestring);
        printf("\nPopulation : %d habitants", population->valueint);

        for (i = 0; i < 2; i++) {
            latlng = cJSON_GetArrayItem(latlngs, i)->valueint;
            if(i==0){
                printf("\nLongitude: %d degres", latlng);
            }else if(i==1){
                printf("\nLatitude: %d degres", latlng);
            }
        }

        printf("\nPays limitrophes: ");
        if(bordersCount != 0){
            for (i = 0; i < bordersCount; i++) {
                latlng = cJSON_GetArrayItem(borders, i)->valuestring;
                printf(" %s,", latlng);
            }
        }else{
            printf(" Pas de pays voisins");
        }
    }else{
        printf("\nCe pays n'existe pas !");
        return;
    }

}

char * file2String(){
    char * buffer = 0;
    long length;
    FILE * f = fopen ("country.JSON", "rb");

    if (f)
    {
      fseek (f, -1, SEEK_END);
      length = ftell (f);
      fseek (f, +1, SEEK_SET);
      buffer = malloc (length);
      if (buffer)
      {
        fread (buffer, 1, length, f);
      }
      fclose (f);
    }

    if (buffer)
    {
      return buffer;
    }
}
void doFile(char * country){
    CURL *curl_handle;
    static const char *pagefilename = "country.JSON";
    FILE *pagefile;
    char curl[250];


    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    curl_handle = curl_easy_init();

    /* set URL to get here */

    sprintf(curl,"http://restcountries.eu/rest/v2/name/%s",country);
    curl_easy_setopt(curl_handle, CURLOPT_URL,curl );

    /* Switch on full protocol/debug output while testing */
    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);

    /* disable progress meter, set to 0L to enable and disable debug output */
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

    /* send all data to this function  */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

    /* open the file */
    pagefile = fopen(pagefilename, "wb");
    if(pagefile)
    {

        /* write the page body to this file handle */
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);

        /* get it! */
        curl_easy_perform(curl_handle);

        /* close the header file */
        fclose(pagefile);
    }

    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);

    curl_global_cleanup();
    system("cls");
    }





