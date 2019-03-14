#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cJSON.h"
#include "json.h"
#include <curl/curl.h>

int name(char* string)
{
    cJSON *name = NULL;
    cJSON *monitor = cJSON_Parse(string);
    cJSON_ArrayForEach(name, monitor)
    {
        if (cJSON_IsString(name) && (name->valuestring != NULL))
        {
            printf("\n\nNom du pays : %s", name->valuestring);
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    }
}
void region(char* string)
{
    cJSON *region = NULL;
    cJSON *monitor = cJSON_Parse(string);
    region = cJSON_GetObjectItemCaseSensitive(monitor, "region");
    printf("\nLa région du pays est : %s", region->valuestring);
}
void capital(char* string)
{
    cJSON *capital = NULL;
    cJSON *monitor = cJSON_Parse(string);
    capital = cJSON_GetObjectItemCaseSensitive(monitor, "capital");
    printf("\nLa capital est %s", capital->valuestring);
}

void languages(char* string)
{
    cJSON *languages = NULL;
    cJSON *monitor = cJSON_Parse(string);
    cJSON *language = NULL;
    cJSON *nativeName = NULL;
    cJSON *symbol = NULL;

    languages = cJSON_GetObjectItemCaseSensitive(monitor,"languages");
    cJSON_ArrayForEach(language, languages)
    {
        nativeName = cJSON_GetObjectItemCaseSensitive(language, "nativeName");
    }
    printf("\nLa langue est le %s ",nativeName->valuestring);
}

void currencies(char* string)
{
    cJSON *currencies = NULL;
    cJSON *monitor = cJSON_Parse(string);
    cJSON *currencie = NULL;
    cJSON *name = NULL;
    cJSON *symbol = NULL;

    currencies = cJSON_GetObjectItemCaseSensitive(monitor,"currencies");
    cJSON_ArrayForEach(currencie, currencies)
    {
        name = cJSON_GetObjectItemCaseSensitive(currencie, "name");
        symbol = cJSON_GetObjectItemCaseSensitive(currencie, "symbol");
    }
    printf("\nLa monaie local est : %s et le symbole est : %s ",name->valuestring, symbol->valuestring);
}

void population(char* string)
{
    cJSON *population = NULL;
    cJSON *monitor = cJSON_Parse(string);
    population = cJSON_GetObjectItemCaseSensitive(monitor, "population");
    printf("\nIl y a  %d habitants", population->valueint);
}

void area(char* string)
{
    cJSON *area = NULL;
    cJSON *monitor = cJSON_Parse(string);
    area = cJSON_GetObjectItemCaseSensitive(monitor, "area");
    printf("\nLe pays fait %d m²", area->valueint);
}

char* getCountry(char* string)
{
    cJSON *country = NULL;
    cJSON *monitor = cJSON_Parse(string);
    country = cJSON_GetObjectItemCaseSensitive(monitor, "country");
    puts(string);
    return country->valuestring;
}
char* getParis(char* string)
{
    cJSON *city = NULL;
    cJSON *monitor = cJSON_Parse(string);
    city = cJSON_GetObjectItemCaseSensitive(monitor, "city");
    puts(string);
    return city->valuestring;
}

void adresse(char* string)
{
    cJSON *records = NULL;
    cJSON *monitor = cJSON_Parse(string);
    cJSON *record = NULL;
    cJSON *field = NULL;
    cJSON *adresse_complete = NULL;
    cJSON *fields = NULL;

    records = cJSON_GetObjectItemCaseSensitive(monitor,"records");

    puts("Addresse de tabac  dans votre arrondissement:");

    cJSON_ArrayForEach(record, records)
    {

    fields = cJSON_GetObjectItemCaseSensitive(record,"fields");

        cJSON_ArrayForEach(field, fields)
        {
            adresse_complete = cJSON_GetObjectItemCaseSensitive(fields, "adresse_complete");
                }
            if (adresse_complete->valuestring != NULL && cJSON_IsString(adresse_complete)){
            printf("%s\n", adresse_complete->valuestring);
        }

    }


}
