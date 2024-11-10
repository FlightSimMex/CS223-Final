#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sourcecode\c172pef.h"

int main(){
    int tableTemp;
    printf("Enter Temperature in C: ");
    scanf("%d", &tableTemp);
    fetchTable();
    printTable(tableTemp);
    readAirport();

}