
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    char airport[5];
    printf("ICAO CODE: ");
    scanf("%s", airport);
    
    FILE *fp;
    fp = fopen(airport, "w");

    int numRunways;
    char rwyID[4];
    int rwyHDG;
    int rwyLEN;

    printf("\n# of Runways: ");
    scanf("%d", &numRunways);

    fprintf(fp, "ICAO: %s", airport);
    fprintf(fp, "\nID\tHDG\tLENGTH\n");
    for(int i = 0; i< numRunways; i++){
        printf("\nEnter Runway ID: ");
        scanf("%s", rwyID);
        printf("%s HDG: ", rwyID);
        scanf("%d", &rwyHDG);
        printf("%s LENGTH: ", rwyID);
        scanf("%d", &rwyLEN);
        fprintf(fp, "%s\t%d\t%d\n", rwyID, rwyHDG, rwyLEN);
    }

    
    fclose(fp);
}