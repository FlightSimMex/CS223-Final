
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sourcecode\airportTools.h"

int main(){
    int programEnd = 0;
    int input = 0;
    char rwyTargetID[4];
    int rwyHDG =0, rwyLEN= 0;
    
    while(!programEnd){
        printf("Press: \n1. Airport Generator\n2. Airport Reader\n3. Runway Search\n");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            createAirport();
            printf("New action?\n1. Yes\n2. No\n");
            scanf("%d", &input);
            if(input == 2){
                programEnd = 1;
            }
            break;
        case 2:
            readAirport();
            printf("New action?\n1. Yes\n2. No\n");
            scanf("%d", &input);
            if(input == 2){
                programEnd = 1;
            }
            break;
        case 3:
            runwaySearch(rwyTargetID, &rwyHDG, &rwyLEN);
            if(rwyHDG > 0){
                printf("%s\t%d\t%d\n", rwyTargetID, rwyHDG, rwyLEN);
            }
            printf("New action?\n1. Yes\n2. No\n");
            scanf("%d", &input);
            if(input == 2){
                programEnd = 1;
            }
            break;
        default:
            printf("No action selected.");
            printf("New action?\n1. Yes\n2. No\n");
            scanf("%d", &input);
            if(input == 2){
                programEnd = 1;
            }
            break;
        }
    }
    
    return 0;
}