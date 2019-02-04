#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void zerofgets(char * str, int size)
{
    fflush(stdin);
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = 0;
}

int main(int argc, char ** argv)
{
    system("color F0");
    char country[100];
    zerofgets(country,100);
    char api[500];
    puts(country);
    sprintf(api,"curl https://restcountries.eu/rest/v2/name/%s -o country.JSON",country);


    system(api);
    return 0;
}
