#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <windows.h>
#include <sys/stat.h>
#define Vso 40

//This type of structure is defined to contain the information from a landing performacne table wiht independant variables for each 1000ft of pressure altitude.
struct PERFTABLE {
        int temp;//Temperature
        int sl;//Sea Level
        int onek;//1000ft
        int twok;//2000ft
        int threek;//3000ft
        int fourk;//4000ft
        int fivek;//5000ft
        int sixk;//6000ft
        int sevenk;//7000ft
        int eghtk;//8000ft
    };

//Array of performance tables, for 5 different temperatures. SFLD = Short Field Landing Distance (Index 0=0C, 1=10C, 2=20C ...)
struct PERFTABLE sfld[5];


//PRINT OUTPUT Creates file for Output data and prints information to that file. (Many parameters for all the data to be dispayed)
void printOutput(char* ptricao, char* ptrrwyID, int appSpeed, int groundRoll, int clear50ft, int windDir, int windSpeed, int tempC, int pressureAltitude){
    //Creating and opening file
    FILE *fout;
    fout = fopen("files/Output/out.txt", "w");

    fprintf(fout, "\nLanding Performance\n\t%s %s", ptricao, ptrrwyID);//Prints ICAO code and Selected Runway ID
    fprintf(fout, "\n\nOutputs:\n");
    fprintf(fout, "\tVref: %dkts\t\t\tVapp: %dkts\n\tGround Roll: %dft\t\tDistance to Clear a 50ft obstacle: %dft", appSpeed, appSpeed + 5, groundRoll, clear50ft);//Prints Reference Speed, Approach Speed, Ground Roll Distance, Distance to clear a 50ft obstacle.
    fprintf(fout, "\n\nComputed Using:\n");
    fprintf(fout, "\tTemp: %dC\t\t\tPressure Altitude: %dft\n\tWind %d degrees at %dkts", tempC, pressureAltitude, windDir, windSpeed);//Prints Envirormental conditions used for the calculations.

    fclose(fout);//closes file after edditing.

    system("start files/Output/out.txt");//Opens file for user to view
} 

/**Airport File Handeling and Data Search Functions */

//GET AIRPORT Collects the user input for the Airport Identifier (ICAO) and creates the corresponding file path associated with that ICAO or to be associated with that ICAO
void getAirport(char* ptricao, char* ptricaoPath){
    char path[20] = "files/Airports/"; //default path for airport files

    //Gathering user input ICAO
    printf("Airport ICAO: ");
    scanf("%s", ptricao);//Stores and returns ICAO using pointer

    //Path Creation
    strncat(path,ptricao,4);//Concatenates the ICAO with the default path
    strcpy(ptricaoPath, path);//returns the path using pointer
}

//CREATE AIRPORT Tool to Create a new airport file based on user inputs
void createAirport(){
    char airport[5];
    char path[20] = "files/Airports/";//Default file path
    
    printf("Airport ICAO: ");//Gathers new ICAO code for new file
    scanf("%s", airport);
    strncat(path,airport,4);//Concatenates ICAO and default path
    
    //Open file
    FILE *fp;
    fp = fopen(path, "w");

    //Variable declarations
    int numRunways;
    char rwyID[4];
    int rwyHDG;
    int rwyLEN;
    int airportElevation = 0;

    //Obtain number of runways from user
    printf("\n# of Runways: ");
    scanf("%d", &numRunways);

    //Obtain airport elevation from user
    printf("\nEnter Airport Elevation: ");
    scanf("%d", &airportElevation);

    //Store airport Elevation and ICAO code in file
    fprintf(fp, "ICAO: %s\t%d ft", airport, airportElevation);
    
    //Print header to file
    fprintf(fp, "\nID\tHDG\tLENGTH\n");

    //Colect and Store runway information for number of runways
    for(int i = 0; i< numRunways; i++){
        printf("\nEnter Runway ID: ");
        scanf("%s", rwyID);//Store Runway Identifier
        printf("%s HDG: ", rwyID);
        scanf("%d", &rwyHDG);//Store Runway Heading
        printf("%s LENGTH: ", rwyID);
        scanf("%d", &rwyLEN);//Store Runway Length
        fprintf(fp, "%s\t%d\t%d\n", rwyID, rwyHDG, rwyLEN);//Store values for this runway on the next line of the file
    }
    
    fclose(fp);//close file

    //Updating supported airports index file
    //open file
    FILE *fadd;
    fadd = fopen("files/Airports/Index", "a");

    fprintf(fadd,"\n%s", airport);//append new airport
    fclose(fadd);//close file
}

//PRINT AIRPORT Debugging tool to print the airport information contained in an airport file.
void printAirport(char path[20]){
    //Open File
    FILE *fin;
    fin = fopen(path, "r");

    //Check if file exists or exit
    if(fin == NULL){
        printf("\nFILE NOT FOUND");
        exit(0);
    }

    //Variable decalrations
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

    //declaration of structure type Runway contains Runway Identifier first two digits of heading + optional L (Left), R (Right), C (Center), starts with G if its a grass runway
    struct Runway{
        char id[5];//Runway Identifier EX. 07L, G22R
        int hdg;//Runway heading 001-360
        int length;//Runway Length in feet
    };

    //Initilaize current runway to 0 for loop
    int rwy=0;
    
    struct Runway airport[20];//Array of Runway structures named airport (Contains the ruwnays for a specific airport)

    while(fscanf(fin, "%s %d %d", rid, &rhdg, &rlen)==3){//scans the file for each ruwnay
        strcpy(airport[rwy].id, rid);//stores runway identifier
        airport[rwy].hdg = rhdg;//stores runway haeding
        airport[rwy].length = rlen;//stores runway length
        rwy++;//Moves to next runway
    }

    fclose(fin);//close file after finished reading

    for(int r =0; r < rwy; r++){//Loops for the number of ruwnays
        printf("%s\t%d\t%d\n", airport[r].id, airport[r].hdg, airport[r].length);// prints ruwnay infrmation for each runway
    }

}

//DELETE AIRPORT Deletes airport file for passed path and removed the passed ICAO from the airport index file.
void deleteAirport(char airport[5],char path[20]){
        if(remove(path) == 0){
            char line[10];//empty line 
            
            FILE *fin, *fout;//file ptrs

            //open files
            fin = fopen("files/Airports/Index", "r");
            fout = fopen("files/Airports/IndexTemp", "w+");

            //copy to a temporary file
            while(fscanf(fin, "%s",line) == 1){
                if(strncmp(line,airport,4)==0){
                    continue;//Skip delete target
                }else{
                    fprintf(fout, "%s\n", line);
                }
            }

            fclose(fin);//close file
            fclose(fout);//close file

            //Open files in oposite mode
            fout = fopen("files/Airports/Index", "w+");
            fin = fopen("files/Airports/IndexTemp", "r");

            //Copy back with target remobved
            while(fscanf(fin, "%s",line) == 1){
                fprintf(fout, "%s\n", line);
            }

            fclose(fin);//close file
            fclose(fout);//close file

            //delete temporary file
            if(remove("files/Airports/IndexTemp")==0){
                printf("File Successfuly Removed!\n");
            }
        }
        
    
}

//GET FIELD ELEVAITON Takes a string path for the airport file path to be accessed.
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

//RUNWAY SEARCH Takes a string path for airport file to be accessed, ptrs for the Runway identifier, heading, length to return data.
void runwaySearch(char path[20],char* ptrrwyID,int* ptrrwyHDG, int* ptrrwyLEN){
   

    //Opening file
    FILE *fin;
    fin = fopen(path, "r");

    //Handeling for file not found
    if(fin == NULL){
        printf("\nFILE NOT FOUND");
        exit(0);
    }

    //Variable declarations
    char discard[50];
    char rid[4];
    int rhdg;
    int rlen;


    //Discards the first two lines which contain airport identifier, elevaiton and headers
    fgets(discard, 50, fin);
    fgets(discard, 50, fin);


    //Runway structure declaration contining identifier heading and length.
    struct Runway{
        char id[4];
        int hdg;
        int length;
    };

    //Runway itterator definition and initialization
    int rwy=0;

    struct Runway airport[20];//Decalres an array of runway structurs named airport to import the data from file

    //Iterates based on the number of runways
    while(fscanf(fin, "%s %d %d", rid, &rhdg, &rlen)==3){//Reads lines from file containing runway identifier, heading and leangth.
        strcpy(airport[rwy].id, rid);//Stores runway identifier
        airport[rwy].hdg = rhdg;//Stores runwat heading
        airport[rwy].length = rlen;//Stores runway length
        rwy++;//Moves to next runway
    }

    //Print ruwnays for slection
    int rwyOption = 1, selctedRunway = 0;//varuables for looping
    char rwyTargetID[4];//variable to store target
    printf("Select Runway: \n");
    for(int r = 0; r < rwy; r++){//print ruwnays
        printf("%d. %s\n",rwyOption,airport[r].id);
        rwyOption++;
    }
    scanf("%d", &selctedRunway);//user selction
    strcpy(rwyTargetID,airport[selctedRunway-1].id);//store selection


    int found = 0;//boolean operator to end searh if target found.

    //Loops through each runway in airport and compaires its identifier to the target identifier
    for(int r = 0; r < rwy; r++){
        if(strcmp(rwyTargetID,airport[r].id) == 0){//If the identifires match
           *ptrrwyHDG = airport[r].hdg;//returns heading using a pointer
           *ptrrwyLEN = airport[r].length;//returns the length using a pointer
           strcpy(ptrrwyID,rwyTargetID);//copies the runway id and returns the ID found using a pointer
           found = 1;//Sets boolean operator to found
        }
    }
    if(found == 0){
        printf("Runway Not Found\n");//If the runway was not found tells the user
    }

    fclose(fin);//close file
    
}

/**Envirormental Conditions Calculations and Adjustment Functions*/

//ADJUST PRESSURE ALTITUDE Takes in an input pressure and rounds it to the next 1000ft for use in the performance calculations as per the Cessna 172SP Pilot Operating Handbook.
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

//ADJUST TEMPERATURE Takes in an input temperature and rounds it ot the next 10 degress Celcius for use in the perfomacnce calculations as per the 172SP Pilot Operating Handbook.
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

//CALCULATE PRESSURE ALTITUDE Takes in the current altimeter setting and airport elevation to calculate the takeoff pressure altitude for use in performance calculations
int calculatePressureAltitude(double altimeter, int elevation){
    int temporary = (29.92 - altimeter) * 1000 + elevation;// calculates pressure altitude uising formula (STD altimeter - Current altimeter) *  1000 + airport elevation
    int result = ceil(temporary);//Rounds result
    return result;
}

//HEADWIND COMPONENT Takes in runway heading and wind direction and speed, uses trigonometry to calculate the component of wind aligned with the runway heading either Headwind(+) or tailwind (-)
int headwindComponent(int rwyHDG, int windDir, int windSpeed){
    double headwindSpeed = windSpeed * cos(abs(windDir - rwyHDG));//calculates headwind speed component using formula Headwind/Tailwind = Wind Speed * cosine(absolute value(difference in wind direction and runway heading))
    int result = ceil(headwindSpeed);//rounds result
    return result;
}

//CROSSWIND COMPONENT Takes in runway heading and wind direction and speed, uses trigonometry to calculate the componet of wind perpendicular to the runway haeding From the Left(+) or from the Right(-)
int crosswindComponent(int rwyHDG, int windDir, int windSpeed){
    double crosswindSpeed = windSpeed * sin(abs(windDir - rwyHDG));//Calculates the crosswind compnent using the formula Crosswind = wind speed * sine(absolute value(difference in wind direction and runway heading))
    int result = ceil(crosswindSpeed);//rounds output.
    return result;
}


/** DEBUGGING TOOLS */
//Prints the Performace Table given a temperature
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


/** IMPORTING PERFOMANCE INFORMATION 
 * VERY IMPORTANT FUNCTION GETS ALL THE PERFORMANCE VALUES AND STORES THEM IN THE HEADER FILE
*/

//FETCH TABLE Reads the performance table file and stores it in the header file array of structures
void fetchTable(){
    int ttemp, tsl, t1, t2, t3, t4, t5, t6, t7, t8, index;//temporary variables to read values
    
    //Open file
    FILE *fin;
    fin = fopen("files/Data/groundRollTable","r");

    //Iteraties and assignes corresponding values from file
    while(fscanf(fin,"%d %d %d %d %d %d %d %d %d %d", &ttemp, &tsl, &t1,&t2, &t3, &t4, &t5, &t6, &t7, &t8) == 10){//reads line from file
       
        index = ttemp/10;//Index is set to the temperature /10
        
        //Storing values in header array structure
        sfld[index].temp = ttemp;//Temperature
        sfld[index].sl = tsl;//Sea Level
        sfld[index].onek = t1;//1000ft
        sfld[index].twok = t2;//2000ft
        sfld[index].threek = t3;//3000ft
        sfld[index].fourk = t4;//4000ft
        sfld[index].fivek = t5;//5000ft
        sfld[index].sixk = t6;//6000ft
        sfld[index].sevenk = t7;//7000ft
        sfld[index].eghtk = t8;//8000ft
       
    }

    fclose(fin);//closes file
    
   
}


/** PERFORMANCE CALCULATION FUNCTIONS */

//GET DISTANCES Takes in temperature, pressure altitudem and two pointers to return: one for ground roll and one for distance to clear a 50ft obstacle 
int getDistances(int temp, int press, int* ptrGR, int* ptr50ft){
    //Adjusting inputs to be used in the table per C172 Manual
    press = adjustPressureAlt(press);//adjusts pressure altitude and re-stores it in press.
    temp = adjustTemperature(temp)/10;//adjusts temperature and re-stores it in temp dividing it by 10 to match the index of the Runway structure array aiport[]
    

    switch (press/1000)//switches based on the pressure altitude/1000
    {
    case 0:
        *ptrGR = sfld[temp].sl/10000;//Returns the Gorund roll by dividing multiplexed value stored in file SAME FOR ALL OTHER CASES
        *ptr50ft = sfld[temp].sl%10000;//Returns the distance to clear 50 foot obstacle by dividing and returning the remainder of the multiplexed value stored in the file SAME FOR ALL OTHER CASES
        break;
    case 1:
        *ptrGR = sfld[temp].onek/10000;
        *ptr50ft = sfld[temp].onek%10000;
        break;
    case 2:
        *ptrGR = sfld[temp].twok/10000;
        *ptr50ft = sfld[temp].twok%10000;
        break;
    case 3:
        *ptrGR = sfld[temp].threek/10000;
        *ptr50ft = sfld[temp].threek%10000;
        break;
    case 4:
        *ptrGR = sfld[temp].fourk/10000;
        *ptr50ft = sfld[temp].fourk%10000;
        break;
    case 5:
        *ptrGR = sfld[temp].fivek/10000;
        *ptr50ft = sfld[temp].fivek%10000;
        break;
    case 6:
        *ptrGR = sfld[temp].sixk/10000;
        *ptr50ft = sfld[temp].sixk%10000;
        break;
    case 7:
        *ptrGR = sfld[temp].sevenk/10000;
        *ptr50ft = sfld[temp].sevenk%10000;
        break;
    case 8:
        *ptrGR = sfld[temp].eghtk/10000;
        *ptr50ft = sfld[temp].eghtk%10000;
        break;
    default:
        break;
    }

}

//ADJUST DISTANCES Takes in headwind component, runway identifer and two pointers to return: one for ground roll and one for distance to clear a 50ft obstacle
void adjustDisance(int headWindComponent, char rwyID[],int* ptrGR, int* ptr50ft){
    //Local variable declarations for value handeling
    double totalAdjustmentGR, totalAdjustment50;
    int groundRoll, fiftyFeet;
    char ruwnayID[2];
    groundRoll = *ptrGR;//stores current value for local computations
    fiftyFeet = *ptr50ft;//stores current value for local computations
    strncpy(ruwnayID,rwyID,1);//stores first character for identification of grass runways



    //WIND ADJUSTMENTS
    if(headWindComponent>0){//IF HEADWIND OBSERVED 
        double adjustment = 0.1/9;//ADJUSTMENT IS SET TO -10% for every 9KTS OF HEADWIND
        totalAdjustmentGR =- (adjustment*headWindComponent);//updates total adjustment value
        totalAdjustment50 =- (adjustment*headWindComponent);//updates total adjustment value
    }else if(headWindComponent<0){//IF TAILWIND
        double adjustment = 0.1/2;//ADJUSTMENT IS SET TO +10% for every 2KTS OF TAILWIND
        totalAdjustmentGR =+ -(adjustment*headWindComponent);//updates total adjustment value
        totalAdjustment50 =+ -(adjustment*headWindComponent);//updates total adjustment value
    }else if(headWindComponent<-10){//IF TAILWIND IS MORE THAN 10KTS
        printf("\nLanding not allowed: TALIWIND COMPONENT EXCEEDED!");//EXITS DUE TO AICRAFT LIMITATIONS BEING EXCEEDED
        exit(0);
    }


    //RUNWAY TYPE ADJUSTMENT
    if(strcmp(ruwnayID, "G") == 0){//IF GRASS RUNWAY
        totalAdjustmentGR = totalAdjustmentGR+ 0.45;//updates total adjustment value by +45%
    }

    //APPLIES TOTAL ADJUSTMENT

    //50FT DISTANCE 
    if(totalAdjustment50>0){//IF TOTAL ADJUSTMENT IS POSITIVE
        fiftyFeet = (int) round(fiftyFeet*(totalAdjustment50+1.0));//Casts double to INT and rounds value to next whole number. Multiplies current distance by 1+ADJUSTMENT%
    } else if(totalAdjustment50 <0){
        fiftyFeet = (int) round(fiftyFeet*(1+totalAdjustment50));//Casts double to INT and rounds value to next whole number. Multiplies current distance by 1-ADJUSTMENT%
    }

    //GROUND ROLL DISTANCE
    if(totalAdjustmentGR>0){
        groundRoll = (int) round(groundRoll*(totalAdjustmentGR+1.0));//Casts double to INT and rounds value to next whole number. Multiplies current distance by 1+ADJUSTMENT%

    } else if(totalAdjustmentGR <0){
        groundRoll = (int) round(groundRoll*(1+totalAdjustmentGR));//Casts double to INT and rounds value to next whole number. Multiplies current distance by 1-ADJUSTMENT%
    }

    //RETURNS VALUES USING PASSED POINTERS
    *ptrGR = groundRoll;
    *ptr50ft = fiftyFeet;
    
}

//APPROACH SPEED Takes in weight and calculates new approach speed
int approachSpeed(double actualWeight){
    double Vapp = 1.3 * Vso * sqrt(actualWeight/2550);// Vapp = 1.3*STALL SPEED AT MAX WEIGHT(DEFINED IN PRE-PROCESSOR DIRECTIVE TO 40)*SQUARE ROOT OF WEIGHT RATIO (ACTUAL WEIGHT/MAX WEIGHT)
    int result = ceil(Vapp);//Rounds Approach speed to next whole number
    return result;
}


