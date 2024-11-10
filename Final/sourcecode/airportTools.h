
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void createAirport(){
    char airport[5];
    char path[20] = "files/Airports/";
    
    printf("Airport ICAO: ");
    scanf("%s", airport);
    strncat(path,airport,4);
    

    FILE *fp;
    fp = fopen(path, "w");

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


void readAirport(){
    char icao[5];
    char path[20] = "files/Airports/";
    
    printf("Airport ICAO: ");
    scanf("%s", icao);
    strncat(path,icao,4);
    

    FILE *fin;
    fin = fopen(path, "r");

    if(fin == NULL){
        printf("\nFILE NOT FOUND");
        exit(0);
    }

    char discard[50];
    char rid[4];
    int rhdg;
    int rlen;
    fgets(discard, 50, fin);
    printf("%s", discard);
    fgets(discard, 50, fin);
    printf("%s", discard);


    struct Runway{
        char id[4];
        int hdg;
        int length;
    };
    int rwy=0;

    struct Runway airport[20];

    while(fscanf(fin, "%s %d %d", rid, &rhdg, &rlen)==3){
        strcpy(airport[rwy].id, rid);
        airport[rwy].hdg = rhdg;
        airport[rwy].length = rlen;
        rwy++;
    }
    fclose(fin); 

    for(int r =0; r < rwy; r++){
        printf("%s\t%d\t%d\n", airport[r].id, airport[r].hdg, airport[r].length);
    }
}

void runwaySearch(char* rwyID,int* rwyHDG, int* rwyLEN){
    char icao[5];
    char rwyTargetID[4];
    char path[20] = "files/Airports/";
    
    printf("Airport ICAO: ");
    scanf("%s", icao);
    strncat(path,icao,4);

    printf("Enter RWY ID: ");
    scanf("%s", rwyTargetID);

    FILE *fin;
    fin = fopen(path, "r");

    if(fin == NULL){
        printf("\nFILE NOT FOUND");
        exit(0);
    }

    char discard[50];
    char rid[4];
    int rhdg;
    int rlen;
    fgets(discard, 50, fin);
    printf("%s", discard);
    fgets(discard, 50, fin);
    printf("%s", discard);


    struct Runway{
        char id[4];
        int hdg;
        int length;
    };
    int rwy=0;

    struct Runway airport[20];

    while(fscanf(fin, "%s %d %d", rid, &rhdg, &rlen)==3){
        strcpy(airport[rwy].id, rid);
        airport[rwy].hdg = rhdg;
        airport[rwy].length = rlen;
        rwy++;
    }
    int found = 0;
    for(int r = 0; r < rwy; r++){
        if(strcmp(rwyTargetID,airport[r].id) == 0){
           *rwyHDG = airport[r].hdg;
           *rwyLEN = airport[r].length;
           strcpy(rwyID,rwyTargetID);
           found = 1;
        }
    }
    if(found == 0){
        printf("Runway Not Found\n");
    }

    fclose(fin);
    
}

