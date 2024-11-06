#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    char airport[5];
    printf("ICAO CODE: ");
    scanf("%s", airport);
    
    FILE *fp;
    fp = fopen(airport, "w");

    int i;
    char rwyID[4];
    char rwyHDG[4];
    char rwyLEN[6];
    int size;

    struct Airport{
        char id[4];
        char hdg[4];
        char length[6];
    };

    

    printf("\nNumber of Runwys: ");
    scanf("%d", &size);

    struct Airport runways[size];

    fprintf(fp, "ICAO: %s\nID\tHDG\tLENGTH\n", airport);
    for (int i = 0; i < size; ++i)
    {
        // Read data
        printf("Record #%d\n", i + 1);
        printf("RWY ID: "); scanf("%s", rwyID);
        printf("RWY HDG: "); scanf("%s", rwyHDG);
        printf("RWY LENGTH:  "); scanf("%s", rwyLEN);
        printf("\n");

        strcpy(runways[i].id, rwyID);
        strcpy(runways[i].hdg, rwyHDG);
        strcpy(runways[i].length, rwyLEN);


        // Save data
        // fprintf(fp, "%s\t%s\t%s\n", runways[i].id, runways[i].hdg, runways[i].length);
    }

    for(int i = 0; i < size; ++i){
        fprintf(fp, "%s\t%s\t%s\n", runways[i].id, runways[i].hdg, runways[i].length);
    }

    fclose(fp);
}
