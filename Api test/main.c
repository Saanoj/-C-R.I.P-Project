#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cJSON.h"
#include <curl/curl.h>

char * file2String();
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
    doFile("france");
    char * result = malloc(file2String());
    result=file2String();
    printJson(result);
    free(result);
    return 0;
}

void printJson(char* string){
    cJSON *name = NULL;
    cJSON *names = NULL;
    cJSON *monitor = cJSON_Parse(string);
    names = cJSON_GetObjectItemCaseSensitive(monitor, "name");
   // cJSON_ArrayForEach(name, names) {

        if (cJSON_IsString(name) && (name->valuestring != NULL))
            printf("\n\nNom du pays : %s", name->valuestring);
        else {
            printf("\n\nThis country does not exist !");
            return;
        }
   // }
}

char * file2String(){
    char * buffer = 0;
    long length;
    FILE * f = fopen ("country.JSON", "rb");

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
    //system("cls");
    }





