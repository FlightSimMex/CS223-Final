
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getAirport(char* ptricao, char* ptricaoPath){
    char path[20] = "files/Airports/";

    printf("Airport ICAO: ");
    scanf("%s", ptricao);
    strncat(path,ptricao,4);
    strcpy(ptricaoPath, path);

}

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
    int airportElevation = 0;

    printf("\n# of Runways: ");
    scanf("%d", &numRunways);

    printf("\nEnter Airport Elevation: ");
    scanf("%d", &airportElevation);

    fprintf(fp, "ICAO: %s\t%d ft", airport, airportElevation);
    
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

void printAirport(char path[20]){
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
    int airportElevation;

    //Parsing the first line for the elevation 
    fgets(discard, 50, fin);
    char *token = strtok(discard, " "); //gets up to the first space
    token = strtok(NULL, "\t");//gets up to the tab (ELEVATION IS BETWEEN TAB AND SECOND SPACE)
    token = strtok(NULL, " ");//gets airport elevation.
    airportElevation = atoi(token);//converts the value into an integer and stores it at airportElevation.
    printf("Elevation: %dft\n", airportElevation);
    fgets(discard, 50, fin);
    printf("%s", discard);//Prints headers


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

int getFieldElevation(char path[20]){
    //opening file based on passed path
    FILE *fin;
    fin = fopen(path, "r");

    //file handeling if not found
    if(fin == NULL){
        printf("\nFILE NOT FOUND");
        exit(0);
    }

    //variable declarations for returns and handeling
    char discard[50];
    int airportElevation;

    //Parsing the first line for the elevation 
    fgets(discard, 50, fin);
    char *token = strtok(discard, " "); //gets up to the first space
    token = strtok(NULL, "\t");//gets up to the tab (ELEVATION IS BETWEEN TAB AND SECOND SPACE)
    token = strtok(NULL, " ");//gets airport elevation.
    airportElevation = atoi(token);//converts the value into an integer and stores it at airportElevation.
    fgets(discard, 50, fin);
    
    //close file
    fclose(fin); 

    //returns airport elevation
    return airportElevation;
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

