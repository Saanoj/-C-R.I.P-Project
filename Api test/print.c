#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cJSON.h"
#include "json.h"
#include <curl/curl.h>

void region(char* string){
    cJSON *region = NULL;
    cJSON *monitor = cJSON_Parse(string);
    cJSON_ArrayForEach(region, monitor) {
        if (cJSON_IsString(region) && (region->valuestring != NULL))
            printf("\n\nNom de la région : %s", region->valuestring);
    }
}
void name(char* string){
    cJSON *name = NULL;
    cJSON *monitor = cJSON_Parse(string);
    cJSON_ArrayForEach(name, monitor) {
        if (cJSON_IsString(name) && (name->valuestring != NULL))
            printf("\n\nNom du pays : %s", name->valuestring);

        else {
            printf("\n\nThis country does not exist !");
            return;
        }
        break;
    }
}

void currencies(char* string){
    cJSON *currencies = NULL;
    cJSON *monitor = cJSON_Parse(string);
    cJSON *currencie = NULL;
    cJSON *name = NULL;
    cJSON *symbol = NULL;

    currencies = cJSON_GetObjectItemCaseSensitive(monitor, "currencies");
    cJSON_ArrayForEach(currencie, currencies)
    {
        name = cJSON_GetObjectItemCaseSensitive(currencie, "name");
        symbol = cJSON_GetObjectItemCaseSensitive(currencie, "symbol");
    }
    printf("\nLa monaie local est : %s et le symbole est : %s ",name->valuestring, symbol->valuestring);
}

