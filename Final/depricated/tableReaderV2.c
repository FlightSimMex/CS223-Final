#include <stdio.h>
#include <stdlib.h>
#include <string.h>





void createGroundRollTable(){
    int groundRollData[5][10] = {{0,545,565,585,610,630,655,680,705,735},{10,565,585,610,630,655,680,705,730,760},{20,585,605,630,655,680,705,730,760,790},{30,605,625,650,675,700,725,755,785,815},{40,625,650,670,695,725,750,780,810,840}};
    FILE *fout;
    fout = fopen("groundRollTable","w");
    fprintf(fout,"\n");
    for(int row = 0; row<5; row++){
        for(int col = 0; col<10;col++){
            fprintf(fout,"%d\t", groundRollData[row][col]);
        }
        fprintf(fout,"\n");
    }
    
    fclose(fout);
}


int fetchGroundRoll(int tableTemp, int tablePressure){

    int ttemp, tsl, t1, t2, t3, t4, t5, t6, t7, t8, index;
    const int tempRange = 5;
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
    
    struct GROUNDROLLTABLE sfld[tempRange];

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

    switch(tablePressure){
            case 0:
                return sfld[tableTemp/10].sl;
                break;
            case 1000:
                return sfld[tableTemp/10].onek;
                break;
            case 2000:
                return sfld[tableTemp/10].twok;
                break;
            case 3000:
                return sfld[tableTemp/10].threek;
                break;
            case 4000:
                return sfld[tableTemp/10].fourk;
                break;
            case 5000:
                return sfld[tableTemp/10].fivek;
                break;
            case 6000:
                return sfld[tableTemp/10].sixk;
                break;
            case 7000:
                return sfld[tableTemp/10].sevenk;
                break;
            case 8000:
                return sfld[tableTemp/10].eghtk;
                break;
            default:
                break;
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

void printTable(int tableTemp){
    int ttemp, tsl, t1, t2, t3, t4, t5, t6, t7, t8, index;
    const int tempRange = 5;
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
    
    struct GROUNDROLLTABLE sfld[tempRange];

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

    printf("\nThe Table for %dC is: ", tableTemp);
    printf("\nSL\t%d\n1000ft\t%d\n2000ft\t%d\n3000ft\t%d\n4000ft\t%d\n5000ft\t%d\n6000ft\t%d\n7000ft\t%d\n8000ft\t%d",sfld[tableTemp/10].sl,sfld[tableTemp/10].onek,sfld[tableTemp/10].twok,sfld[tableTemp/10].threek,sfld[tableTemp/10].fourk,sfld[tableTemp/10].fivek,sfld[tableTemp/10].sixk,sfld[tableTemp/10].sevenk,sfld[tableTemp/10].eghtk);
    
}

int main(){
    int tableTemp, tablePress, groundRoll;
    printf("Enter Temperature in C: ");
    scanf("%d", &tableTemp);
    //printf("Enter Pressure Altitude in ft: ");
    //scanf("%d", &tablePress);
    //tablePress = adjustPressureAlt(tablePress);
    //groundRoll = fetchGroundRoll(tableTemp, tablePress);

    //printf("The Ground Roll for %dC at %dft PA is: %d\n", tableTemp,tablePress,groundRoll);

    printTable(tableTemp);

}