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
