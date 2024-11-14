#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sourcecode/c172pef.h"



int main(){
    //Variable Declarations
    int programEnd = 0;
    int tableTemp, tablePress, groundRoll, fiftyFeet, weight, rwyHDG =0, rwyLEN= 0, windDir, windSpeed, actualWeight, elevation, altimeter;
    char rwyTargetID[4];

    while(!programEnd){
        //Gets Weight
        printf("\n\nEnter weight before takeoff in lbs: ");
        scanf("%d", &actualWeight);
        printf("\nEnter landing weight in lbs: ");
        scanf("%d", &weight);

        //Gather Weather Information
        printf("\nWeather Data:\n");
        printf("\nEnter Wind Direction: ");
        scanf("%d", &windDir);
        printf("\nEnter Wind Speed: ");
        scanf("%d", &windSpeed);
        printf("\nEnter Temperature in C: ");
        scanf("%d", &tableTemp);
        printf("\nEnter Pressure Altitude in ft: ");
        scanf("%d", &tablePress);
        printf("\nEnter Elevation in feet: ");
        scanf("%D", &elevation);
        printf("\nEnter Altimeter Settings: ");
        scanf("%d", &altimeter);

        //Gets Airport/Runway info, rwyID, rwyHDG and rwyLEN.
        printf("\nAirport Data:\n");
        runwaySearch(rwyTargetID, &rwyHDG, &rwyLEN);

        //Imports performance table from files/data/groundRollTable
        fetchTable();
    
        //Obtains table data for landing roll and 50ft distance.
        getDistances(tableTemp, tablePress, &groundRoll, &fiftyFeet);

        if(rwyLEN>=groundRoll){
            printf("\nDistance Required: %d\t Distance Available: %d\t LANDING ALLOWED\n",groundRoll, rwyLEN); 
        }

        printf("\nCalculate New Performance?\n1. Yes\n2. No\n");
        scanf("%d",programEnd);
        programEnd -=1;

    }
    
    return 0;
    
}
