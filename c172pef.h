#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

void printPerfTable(int tableTemp){
    int ttemp, tsl, t1, t2, t3, t4, t5, t6, t7, t8;

    struct GROUNDROLLTABLE {
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
    
    struct GROUNDROLLTABLE temp0;
    struct GROUNDROLLTABLE temp10;
    struct GROUNDROLLTABLE temp20;
    struct GROUNDROLLTABLE temp30;
    struct GROUNDROLLTABLE temp40;

    FILE *fin;
    fin = fopen("groundRollTable","r");
    if (fin == NULL){
        printf("Missing groundRollTable file.");
        exit(0);
    }
    while(fscanf(fin,"%d %d %d %d %d %d %d %d %d %d", &ttemp, &tsl, &t1,&t2, &t3, &t4, &t5, &t6, &t7, &t8) == 10){
        switch (ttemp)
        {
        case 0:
            temp0.temp = ttemp;
            temp0.sl = tsl;
            temp0.onek = t1;
            temp0.twok = t2;
            temp0.threek = t3;
            temp0.fourk = t4;
            temp0.fivek = t5;
            temp0.sixk = t6;
            temp0.sevenk = t7;
            temp0.eghtk = t8;
            break;
        case 10:
            temp10.temp = ttemp;
            temp10.sl = tsl;
            temp10.onek = t1;
            temp10.twok = t2;
            temp10.threek = t3;
            temp10.fourk = t4;
            temp10.fivek = t5;
            temp10.sixk = t6;
            temp10.sevenk = t7;
            temp10.eghtk = t8;
            break;
        case 20:
            temp20.temp = ttemp;
            temp20.sl = tsl;
            temp20.onek = t1;
            temp20.twok = t2;
            temp20.threek = t3;
            temp20.fourk = t4;
            temp20.fivek = t5;
            temp20.sixk = t6;
            temp20.sevenk = t7;
            temp20.eghtk = t8;
            break;
        case 30:
            temp30.temp = ttemp;
            temp30.sl = tsl;
            temp30.onek = t1;
            temp30.twok = t2;
            temp30.threek = t3;
            temp30.fourk = t4;
            temp30.fivek = t5;
            temp30.sixk = t6;
            temp30.sevenk = t7;
            temp30.eghtk = t8;
            break;
        case 40:
            temp40.temp = ttemp;
            temp40.sl = tsl;
            temp40.onek = t1;
            temp40.twok = t2;
            temp40.threek = t3;
            temp40.fourk = t4;
            temp40.fivek = t5;
            temp40.sixk = t6;
            temp40.sevenk = t7;
            temp40.eghtk = t8;
            break;
        default:
            break;
        }
    }
    
    switch (tableTemp)
    {
    case 0:
        printf("\nThe Table for %dC is: ", tableTemp);
        printf("\nSL\t%d\n1000ft\t%d\n2000ft\t%d\n3000ft\t%d\n4000ft\t%d\n5000ft\t%d\n6000ft\t%d\n7000ft\t%d\n8000ft\t%d",temp0.sl,temp0.onek,temp0.twok,temp0.threek,temp0.fourk,temp0.fivek,temp0.sixk,temp0.sevenk,temp0.eghtk);
        break;
    case 10:
        printf("\nThe Table for %dC is: ", tableTemp);
        printf("\nSL\t%d\n1000ft\t%d\n2000ft\t%d\n3000ft\t%d\n4000ft\t%d\n5000ft\t%d\n6000ft\t%d\n7000ft\t%d\n8000ft\t%d",temp10.sl,temp10.onek,temp10.twok,temp10.threek,temp10.fourk,temp10.fivek,temp10.sixk,temp10.sevenk,temp10.eghtk);
        break;
    case 20:
        printf("\nThe Table for %dC is: ", tableTemp);
        printf("\nSL\t%d\n1000ft\t%d\n2000ft\t%d\n3000ft\t%d\n4000ft\t%d\n5000ft\t%d\n6000ft\t%d\n7000ft\t%d\n8000ft\t%d",temp20.sl,temp20.onek,temp20.twok,temp20.threek,temp20.fourk,temp20.fivek,temp20.sixk,temp20.sevenk,temp20.eghtk);
        break;
    case 30:
        printf("\nThe Table for %dC is: ", tableTemp);
        printf("\nSL\t%d\n1000ft\t%d\n2000ft\t%d\n3000ft\t%d\n4000ft\t%d\n5000ft\t%d\n6000ft\t%d\n7000ft\t%d\n8000ft\t%d",temp30.sl,temp30.onek,temp30.twok,temp30.threek,temp30.fourk,temp30.fivek,temp30.sixk,temp30.sevenk,temp30.eghtk);
        break;
    case 40:
        printf("\nThe Table for %dC is: ", tableTemp);
        printf("\nSL\t%d\n1000ft\t%d\n2000ft\t%d\n3000ft\t%d\n4000ft\t%d\n5000ft\t%d\n6000ft\t%d\n7000ft\t%d\n8000ft\t%d",temp40.sl,temp40.onek,temp40.twok,temp40.threek,temp40.fourk,temp40.fivek,temp40.sixk,temp40.sevenk,temp40.eghtk);
        break;
    default:
        break;
    }
    fclose(fin);
}

int fetchGroundRoll(int tableTemp, int tablePressure){

    int ttemp, tsl, t1, t2, t3, t4, t5, t6, t7, t8;

    struct GROUNDROLLTABLE {
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
    
    struct GROUNDROLLTABLE temp0;
    struct GROUNDROLLTABLE temp10;
    struct GROUNDROLLTABLE temp20;
    struct GROUNDROLLTABLE temp30;
    struct GROUNDROLLTABLE temp40;

    FILE *fin;
    fin = fopen("groundRollTable","r");

     if (fin == NULL){
        printf("Missing groundRollTable file.");
        exit(0);
    }
    
    while(fscanf(fin,"%d %d %d %d %d %d %d %d %d %d", &ttemp, &tsl, &t1,&t2, &t3, &t4, &t5, &t6, &t7, &t8) == 10){
        switch (ttemp)
        {
        case 0:
            temp0.temp = ttemp;
            temp0.sl = tsl;
            temp0.onek = t1;
            temp0.twok = t2;
            temp0.threek = t3;
            temp0.fourk = t4;
            temp0.fivek = t5;
            temp0.sixk = t6;
            temp0.sevenk = t7;
            temp0.eghtk = t8;
            break;
        case 10:
            temp10.temp = ttemp;
            temp10.sl = tsl;
            temp10.onek = t1;
            temp10.twok = t2;
            temp10.threek = t3;
            temp10.fourk = t4;
            temp10.fivek = t5;
            temp10.sixk = t6;
            temp10.sevenk = t7;
            temp10.eghtk = t8;
            break;
        case 20:
            temp20.temp = ttemp;
            temp20.sl = tsl;
            temp20.onek = t1;
            temp20.twok = t2;
            temp20.threek = t3;
            temp20.fourk = t4;
            temp20.fivek = t5;
            temp20.sixk = t6;
            temp20.sevenk = t7;
            temp20.eghtk = t8;
            break;
        case 30:
            temp30.temp = ttemp;
            temp30.sl = tsl;
            temp30.onek = t1;
            temp30.twok = t2;
            temp30.threek = t3;
            temp30.fourk = t4;
            temp30.fivek = t5;
            temp30.sixk = t6;
            temp30.sevenk = t7;
            temp30.eghtk = t8;
            break;
        case 40:
            temp40.temp = ttemp;
            temp40.sl = tsl;
            temp40.onek = t1;
            temp40.twok = t2;
            temp40.threek = t3;
            temp40.fourk = t4;
            temp40.fivek = t5;
            temp40.sixk = t6;
            temp40.sevenk = t7;
            temp40.eghtk = t8;
            break;
        default:
            break;
        }
    }
    
    switch (tableTemp)
    {
    case 0:
        switch(tablePressure){
            case 0:
                return temp0.sl;
                break;
            case 1000:
                return temp0.onek;
                break;
            case 2000:
                return temp0.twok;
                break;
            case 3000:
                return temp0.threek;
                break;
            case 4000:
                return temp0.fourk;
                break;
            case 5000:
                return temp0.fivek;
                break;
            case 6000:
                return temp0.sixk;
                break;
            case 7000:
                return temp0.sevenk;
                break;
            case 8000:
                return temp0.eghtk;
                break;
            default:
                break;
        }
        break;
    case 10:
        switch(tablePressure){
            case 0:
                return temp10.sl;
                break;
            case 1000:
                return temp10.onek;
                break;
            case 2000:
                return temp10.twok;
                break;
            case 3000:
                return temp10.threek;
                break;
            case 4000:
                return temp10.fourk;
                break;
            case 5000:
                return temp10.fivek;
                break;
            case 6000:
                return temp10.sixk;
                break;
            case 7000:
                return temp10.sevenk;
                break;
            case 8000:
                return temp10.eghtk;
                break;
            default:
                break;
        }
        break;
    case 20:
        switch(tablePressure){
            case 0:
                return temp20.sl;
                break;
            case 1000:
                return temp20.onek;
                break;
            case 2000:
                return temp20.twok;
                break;
            case 3000:
                return temp20.threek;
                break;
            case 4000:
                return temp20.fourk;
                break;
            case 5000:
                return temp20.fivek;
                break;
            case 6000:
                return temp20.sixk;
                break;
            case 7000:
                return temp20.sevenk;
                break;
            case 8000:
                return temp20.eghtk;
                break;
            default:
                break;
        }
        break;
    case 30:
        switch(tablePressure){
            case 0:
                return temp30.sl;
                break;
            case 1000:
                return temp30.onek;
                break;
            case 2000:
                return temp30.twok;
                break;
            case 3000:
                return temp30.threek;
                break;
            case 4000:
                return temp30.fourk;
                break;
            case 5000:
                return temp30.fivek;
                break;
            case 6000:
                return temp30.sixk;
                break;
            case 7000:
                return temp30.sevenk;
                break;
            case 8000:
                return temp30.eghtk;
                break;
            default:
                break;
        }
        break;
    case 40:
        switch(tablePressure){
            case 0:
                return temp40.sl;
                break;
            case 1000:
                return temp40.onek;
                break;
            case 2000:
                return temp40.twok;
                break;
            case 3000:
                return temp40.threek;
                break;
            case 4000:
                return temp40.fourk;
                break;
            case 5000:
                return temp40.fivek;
                break;
            case 6000:
                return temp40.sixk;
                break;
            case 7000:
                return temp40.sevenk;
                break;
            case 8000:
                return temp40.eghtk;
                break;
            default:
                break;
        }
        break;
    default:
        break;
    }

    fclose(fin);

}