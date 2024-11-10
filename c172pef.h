#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PERFTABLE {
        int temp;
        int sl;
        int onek;
        int twok;
        int threek;
        int fourk;
        int fivek;
        int sixk;
        int sevenk;
        int eghtk;
    };

struct PERFTABLE sfld[5];

void readAirport(){
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

void runwaySearch(char* rwyID,int* rwyHDG, int* rwyLEN){
    char icao[5];
    char rwyTargetID[4];
    printf("Airport ICAO: ");
    scanf("%s", icao);

    printf("Enter RWY ID: ");
    scanf("%s", rwyTargetID);

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

int adjustPressureAlt(int tablePress){
     if(tablePress>0&&tablePress<1001){
        tablePress = 1000;
    }else if (tablePress>1000&&tablePress<2001){
        tablePress = 2000;
    }else if(tablePress>2000&&tablePress<3001){
        tablePress = 3000;
    }else if(tablePress>3000&&tablePress<4001){
        tablePress =4000;
    }else if (tablePress >4000&&tablePress<5001){
        tablePress = 5000;
    }else if (tablePress>5000&&tablePress<6001){
        tablePress = 6000;
    }else if(tablePress>6000&&tablePress<7001){
        tablePress = 7000;
    }else if(tablePress>7000&&tablePress<8001){
        tablePress = 8000;
    }
    return tablePress;
}

int adjustTemperature(int tableTemp){
     if(tableTemp<=0){
        tableTemp = 0;
    }else if (tableTemp>0&&tableTemp<=10){
        tableTemp = 10;
    }else if(tableTemp>10&&tableTemp<=20){
        tableTemp = 20;
    }else if(tableTemp>20&&tableTemp<=30){
        tableTemp = 30;
    }else if (tableTemp >30){
        tableTemp = 40;
    }
    return tableTemp;
}

void printTable(int tableTemp){

    printf("\nThe Table for %dC is: \n\nPA \tGR\t50FT\n", tableTemp);
    printf("\nSL\t%d\t%d\n1000ft\t%d\t%d\n2000ft\t%d\t%d\n3000ft\t%d\t%d\n4000ft\t%d\t%d\n5000ft\t%d\t%d\n6000ft\t%d\t%d\n7000ft\t%d\t%d\n8000ft\t%d\t%d",
    sfld[tableTemp/10].sl/10000,sfld[tableTemp/10].sl%10000,
    sfld[tableTemp/10].onek/10000,sfld[tableTemp/10].onek%10000,
    sfld[tableTemp/10].twok/10000,sfld[tableTemp/10].twok%10000,
    sfld[tableTemp/10].threek/10000,sfld[tableTemp/10].threek%10000,
    sfld[tableTemp/10].fourk/10000,sfld[tableTemp/10].fourk%10000,
    sfld[tableTemp/10].fivek/10000,sfld[tableTemp/10].fivek%10000,
    sfld[tableTemp/10].sixk/10000,sfld[tableTemp/10].sixk%10000,
    sfld[tableTemp/10].sevenk/10000,sfld[tableTemp/10].sevenk%10000,
    sfld[tableTemp/10].eghtk/10000, sfld[tableTemp/10].eghtk%10000);
   
}

void fetchTable(){
    int ttemp, tsl, t1, t2, t3, t4, t5, t6, t7, t8, index;
    


    FILE *fin;
    fin = fopen("groundRollTable","r");

    while(fscanf(fin,"%d %d %d %d %d %d %d %d %d %d", &ttemp, &tsl, &t1,&t2, &t3, &t4, &t5, &t6, &t7, &t8) == 10){
       
        index = ttemp/10;
        
        sfld[index].temp = ttemp;
        sfld[index].sl = tsl;
        sfld[index].onek = t1;
        sfld[index].twok = t2;
        sfld[index].threek = t3;
        sfld[index].fourk = t4;
        sfld[index].fivek = t5;
        sfld[index].sixk = t6;
        sfld[index].sevenk = t7;
        sfld[index].eghtk = t8;
       
    
    }

    fclose(fin);

   
}
