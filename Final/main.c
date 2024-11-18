#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sourcecode/c172pef.h"

int main(){
    //Variable Declarations
    int  groundRoll, fiftyFeet, rwyHDG =0, rwyLEN= 0, programEnd = 0;
    char rwyTargetID[4];

    while(!programEnd){
        //Gather Int values
        int actualWeight = inputInt("\nEnter the Weight of the Aircraft: ");
        int weight = inputInt("\nEnter the Weight at touchdown: ");
        int windDir = inputInt("\nEnter the Wind direction(1-360 degrees): ");
        int windSpeed = inputInt("\nEnter the Wind Speed in MPH: ");
        int tableTemp = inputInt("\nEnter the Temperature in Celcius: ");
        int tablePress = inputInt("\nEnter the Pressure Altitude in ft: ");
        int elevation = inputInt("\nEnter the Elevation in ft: ");
        int altimeter = inputInt("\nEnter the Altimeter Settings: ");

        //Gather Weather Information
        printf("\nWeather Data:\n");

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

        programEnd = inputInt("\nCalculate New Performance?\n1. Yes\n2. No\n");
        programEnd -=1;

    }
    
    return 0;
    
}
