#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(){

    char icao[5];
    printf("Airport ICAO: ");
    scanf("%s", icao);

    

    FILE *fin;
    fin = fopen(icao, "r");

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