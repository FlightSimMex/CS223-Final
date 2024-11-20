#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sourcecode/c172pef.h"

int getINT(char* str){
	int input;	
    printf("Enter %s: ", str);
	scanf("%d", &input);
	return input;
}
double getDOUBLE(char* str){
	double input;	
    printf("Enter %s: ", str);
	scanf("%lf", &input);
	return input;
}
void getCHAR(char* str,  char* output){
	char input[] = " ";	
    printf("Enter %s: ", str);
	scanf("%s", input);
    strcpy(output, input);
}

int main(){
     //Variable Declarations
    int programEnd = 0;
    int headWind, xWind, tempC, altSetting, rwyHDG, rwyLEN, airportElevation, pressureAltitude, groundRoll, clear50ft, appSpeed, again = 1;
    char icao[5], icaoPath[20], rwyID[5];

    //While loop to keep program running until the user ends it
    while (again == 1){

        //Initialize while in loop to run properly 
        int weight = 0, windDir = 0, windSpeed = 0;

        //Initialize variables while getting user inputs
        while(weight<1600||weight>2550){ //Input validation for weight between Basic Empty Weight and Maximum Gross Weight
            weight = getINT("Landing Weight(betweeen 1600-2550 pounds)");//gets weight
        }
        printf("\nEnvironmental: \n");//Envirormental Inputs
        while(windDir<1||windDir>361){ //Input validation for weight between 1->360
            windDir = getINT("Wind Direction");//gets wind direction
        }
        while(windSpeed<1||windSpeed>361){ //Input validation for weight between 1->360
            windSpeed = getINT("Wind Speed (KTS)");//gets wind direction
        }
        tempC = getINT("Temperature (Celsius)");//gets Temperature
        altSetting = getDOUBLE("Altimeter (Hg)");//gets Altimeter Setting

        printf("\nAirport Information: \n");//Airport Information Inputs
        getAirport(icao, icaoPath); //Gets Airport and Airport File Path returns using pointers
        runwaySearch(icaoPath, rwyID, &rwyHDG, &rwyLEN);//searches for a runway given the file path of an airport and returns the ID, heading and length using pointers.
        airportElevation = getFieldElevation(icaoPath);// gets the airport elevation from the airport file.

        //Calculating Envirormental Conditions
        pressureAltitude = calculatePressureAltitude(altSetting, airportElevation);
        headWind = headwindComponent(rwyHDG, windDir, windSpeed);
        xWind = crosswindComponent(rwyHDG, windDir, windSpeed);

        //Adjust Envirormental Conditions for Table Raeding
        pressureAltitude = adjustPressureAlt(pressureAltitude);
        tempC = adjustTemperature(tempC);

        //VERY IMPORTANT FUNCTION IMPORTING THE PERFORMANCE TABLE INTO THE HEADER FILE FOR USE!!!
        fetchTable();

        //Reading Table data for given conditions.
        getDistances(tempC, pressureAltitude, &groundRoll, &clear50ft);//Reads table data and returns the groundRoll and distance to clear a 50ft obstacle using pointers.

        //Adjusting distances for the envirormental conditions and runway type
        adjustDisance(headWind, rwyID, &groundRoll, &clear50ft); //Takes the haedwind/tailwind components, and rwyID (to determine if its a grass runway), and adjusts landing distances based on the C172 PIM. Returns new values using pointers.

        //Calculate Appraoch Speed
        appSpeed = approachSpeed(weight);

        printOutput(icao, rwyID, appSpeed, groundRoll, clear50ft, windDir, windSpeed, tempC, pressureAltitude);//Write output to file and call file to output

        printf("\n\nWould you like to run the program again?\n1:Yes\n2:No\n");
        scanf("%d", &again);

        if(again >= 2 || again < 1){
            printf("\nThank you for using the program goodbye!");
        }
    }
    return 0;
}

