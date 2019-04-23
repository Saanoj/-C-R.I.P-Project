#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>
#include "cJSON.h"
#include "json.h"
#include "print.h"


//wirte data sert a écrire le json dans un fichier
//ici static permet a la fonction de rester dans ce fichier
//le void * est un pointeur vide il pointe vers aucun type précis
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}
//on prend le fichier et on le met dans un string
char * file2StringCountry(char* file){
    char * buffer = 0;
    long length;
    FILE * f = fopen (file, "rb");

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
// encore un file2String permet de faire mettre fichier en string
char * file2String(char* file){
    char * buffer = 0;
    long length;
    FILE * f = fopen (file, "rb");

    if (f)
    {
      fseek (f, 0, SEEK_END);
      length = ftell (f);
      fseek (f, 0, SEEK_SET);
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

//JSON IP
// on curl pour l'ip et on l'écrit dans un fichier
void doFileIp(){
    CURL *curl_handle;
    static const char *pagefilename = "ip.JSON";
    FILE *pagefile;
    char curl[250];


    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    curl_handle = curl_easy_init();

    /* set URL to get here */


    curl_easy_setopt(curl_handle, CURLOPT_URL,"http://ip-api.com/json?fields=query,city,country,region" );

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


//json country
//on imprime le tous
void printJsonCountry(char* string){
    if(name(string)==1){
    region(string);
    capital(string);
    languages(string);
    currencies(string);
    area(string);
    population(string);
    }else{
    printf("\n\nCe pays n'existe pas!");
    }

}
void doFileCountry(char * country){
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

void doFileZip(int zip){
    CURL *curl_handle;
    static const char *pagefilename = "zip.JSON";
    FILE *pagefile;
    char curl[250];


    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    curl_handle = curl_easy_init();

    /* set URL to get here */

    sprintf(curl,"http://opendata.paris.fr/api/records/1.0/search/?dataset=commercesparis&refine.arro=%d&refine.libact=Café+-+Tabac",zip);
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




