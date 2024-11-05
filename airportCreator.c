#include <stdio.h>
#include <stdlib.h>

int main(){

    char name[] = "";
    int numRunways;
    printf("Enter Airport Identifier: ");
    scanf("%s", name);

    struct Runway{
        int number;
        int length;
    };

    FILE *fout;
    fout = fopen(name, "w");

    printf("\n\nEnter Number of Runways: ");
    scanf("%d", &numRunways);
    int runways[numRunways];

    for(int i = 1; i < numRunways; i ++){
        int runwayIdent = 01;
        int runwayLength = 000;
        printf("\n\nEnter Runway Identifier: ");
        scanf("%d", &runwayIdent);
        printf("\n\nEnter Runway Length: ");
        scanf("%d", &runwayIdent);
        runways[i-1] = runwayIdent;
        struct Runway name = {runwayIdent, runwayLength};
    }

}