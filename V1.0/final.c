#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sourcecode/c172pef.h"

//GET INT Gathers and returns integer input from user, value asked for can be costumized by passing a string
int getINT(char* str){
	int input;	
    printf("Enter %s: ", str);
	scanf("%d", &input);
	return input;
}
//GET DOUBLE Gathers and returns double input from user, value asked for can be costumized by passing a string
double getDOUBLE(char* str){
	double input;	
    printf("Enter %s: ", str);
	scanf("%lf", &input);
	return input;
}

int main(){
     //Variable Declarations
    int programEnd = 0;
    int headWind, xWind, tempC, altSetting, rwyHDG, rwyLEN, airportElevation, pressureAltitude, groundRoll, clear50ft, appSpeed, again = 1;
    char icao[5], icaoPath[20], rwyID[5];

    int menuSelection = 0;

    //MAIN LOOP
    while(programEnd!=1){
        
        printf("Select Action: \n1.Calculate Performance\n2.View Supported Airports\n3.Add New Airport\n4.Remove Airport\n");
        scanf("%d", &menuSelection);

        switch (menuSelection)
        {
        case 1://Calculate Performance
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

                    //Determines program end
                    printf("\nCalculation complete! outputting file:\n");
                    printf("\nWould you like to calculate new performance?\n1.Yes\t2.No\n");
                    scanf("%d", &again);
                }
            break;
        case 2://View Supported Airports
            char temp[] = "";//Empty String for Reading
            //Open File
            FILE *fr;
            fr = fopen("files/Airports/Index", "r");
            //Check if file exists or exit
            if(fr == NULL){
                printf("\nFILE NOT FOUND");
                exit(0);
            }
            while(fscanf(fr, "%s",temp)>0){//While not empty
                printf("%s\n",temp);//print line
            }
            fclose(fr);//clsoe file
            break;
        case 3://Add New Airport
            createAirport();//Calls funciton to create new airport (in c172pef.h)
            break;
        case 4:
            getAirport(icao,icaoPath);//gets airport to be deleted
            deleteAirport(icao, icaoPath);//deletes desired airport file and edits the airport index file
            break;
        default://Invalid Action
            printf("Invalid Input\n");
            break;
        }

        //DETERMINE PROGRAM END
        int newAction = 0;
        printf("\nNew Action?\n1.Yes\t2.No\n");
        scanf("%d",&newAction);
        if(newAction!=1){
            printf("\nThank you for using the program goodbye!");
            programEnd = 1;
        }
    }
    return 0;
}

