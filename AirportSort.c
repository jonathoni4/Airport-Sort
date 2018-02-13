
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airPdata.h"

void parseLine(char *line, airPdata *apd);
void printData(int length, airPdata *apd);
void deleteStruct(airPdata *apd);

#define BUFFER_SIZE 500



float sexag2decimal(char *degreeString){
    int d, m, mi, c, count=0;
    char compass;
    float s, answer = 0.0f;
    
    if(degreeString == NULL)
    {
        return 0;
    }
    sscanf(degreeString, "%d-%d-%f%c", &d, &m, &s, &compass);

    if(m < 0 || m > 59  || d < 0 || d > 180 ||  s < 0 || s > 60 )
    {
        return 0;
    }
    c = mi;
    while(c != 0)
    {
        c /= 10;
        ++count;
      
    }
    
    
    answer = (float)d + ((float)(m/(float)60.0f)) + ((float)s/(float)((3600.0f)));
    if (compass == 'W')
    {
        answer = -answer;
    }
    if (compass == 'S')
    {
        answer = -answer;
    }
    return answer;
    
}
void sortByLatitude(airPdata *airports, int length){
    int i = 0, front, slot;
    airPdata swap;
   
        for (front = 0 ; front < ( length - 1 ); front++)
    {for (slot = 0 ; slot < length - front - 1; slot++)
    {if ((airports+slot)->latitude > (airports+slot+1)->latitude)
    {swap       = *(airports+slot);
        *(airports+slot)   = *(airports+slot+1);
        *(airports+slot+1) = swap;
    }
        
    }
    }

        for(i=0; i<length; i++){
            if (strlen((airports+i)->LocID) > 3 || ((airports+i)->LocID[0] == 'X' && ((airports+i)->LocID[1] >= 0 && (airports+i)->LocID[1] <=9)) || (((airports+i)->LocID[0] == 'F' && (airports+i)->LocID[1] == 'L') && ((airports+i)->LocID[1] >= 0 && (airports+i)->LocID[1] <=9)) || ((airports+i)->LocID[0] <= '9' && (airports+i)->LocID[0] >= '0') || ((airports+i)->LocID[0] <='9' && (airports+i)->LocID[0] >= '0') || ((airports+i)->LocID[1] <='9' && (airports+i)->LocID[1] >= '0') || ((airports+i)->LocID[2] <='9' && (airports+i)->LocID[2] >= '0'))
                ;
            else {printf("%s,%s,%s,%.4f,%.4f\n",(airports+i)->LocID,(airports+i)->fieldName,
                         (airports+i)->city,(airports+i)->latitude,(airports+i)->longitude);
            }
        }

        /* Constructing tree given in the above figure */
}
void sortByLocID(airPdata *airports, int length){
    int i = 0, front, slot;
    airPdata swap;
 
    

    
    for (front = 0 ; front < ( length - 1 ); front++)
    {for (slot = 0 ; slot < length - front - 1; slot++)
    {if ((strcmp((airports+slot)->LocID, (airports+slot+1)->LocID)) > 0)
    {
        swap   = *(airports+slot);
        *(airports+slot)   = *(airports+slot+1);
        *(airports+slot+1) = swap;
    }
        
    }
    }
    
    for(i=0; i<length; i++){
        if (strlen((airports+i)->LocID) > 3 || ((airports+i)->LocID[0] == 'X' && ((airports+i)->LocID[1] >= 0 && (airports+i)->LocID[1] <=9)) || (((airports+i)->LocID[0] == 'F' && (airports+i)->LocID[1] == 'L') && ((airports+i)->LocID[1] >= 0 && (airports+i)->LocID[1] <=9)) || ((airports+i)->LocID[0] <= '9' && (airports+i)->LocID[0] >= '0') || ((airports+i)->LocID[0] <='9' && (airports+i)->LocID[0] >= '0') || ((airports+i)->LocID[1] <='9' && (airports+i)->LocID[1] >= '0') || ((airports+i)->LocID[2] <='9' && (airports+i)->LocID[2] >= '0'))
            ;
        else {printf("%s,%s,%s,%.4f,%.4f\n",(airports+i)->LocID,(airports+i)->fieldName,
                     (airports+i)->city,(airports+i)->latitude,(airports+i)->longitude);
        }
    }
    
    
   
}

int main (int argc, char *argv[]){

	// Declare input buffer and other parameters
	FILE *fid;
	char buffer[BUFFER_SIZE];
	int count = 0;

	
	// Check for command line input and open input file.
	if(argc==3){
		fid = fopen(argv[1], "r");
		if(fid==NULL){
			printf("File %s failed to open. Aborting.\n", argv[1]);
			return 2;
		}
	}
	else{
		printf("Incorect number of input parameters. Please specify the name of the input file only.\n");
		printf("Syntax: ./hw1ecl.exe [input file]\n");
		return 1;
	}
	
	
	// Determine length of the file.
	while(fgets(buffer, BUFFER_SIZE, fid) != NULL){
		count++;
	}
	rewind(fid);
	
	
	// Declare a struct array and allocate memory.
	airPdata *data;

	data = malloc(sizeof(airPdata)*count);
	if(data==NULL){
		printf("Memory allocation for airPdata array failed. Aborting.\n");
		return 2;
	}

	// Read and parse each line of the inputt file.
	for(int i = 0; i<count; i++){
		fgets(buffer, BUFFER_SIZE, fid);
		
		// fgets() includes the New Line delimiter in the output string. 
		// i.e. "This is my string.\n\0"
		// We will truncate the string to drop the '\n' if it is there.
		// Note: There will be no '\n' if the line is longer than the buffer.
		if(buffer[strlen(buffer) - 1] == '\n') buffer[strlen(buffer)-1] = '\0';
		
		parseLine(buffer, data+i);
	}
    printf("code,name,city,lat,lon\n");
    if(*argv[2] == 'a' || *argv[2] == 'A' ){
        sortByLocID(data, count);
    }
    else if(*argv[2] == 'n' || *argv[2] == 'N' ){
        sortByLatitude(data, count);
    }
    else{
         printf("hw3Sort ERROR: sortParameter invalid or not found.");
        return 0;
    }
	// close the input file.
	fclose(fid);

	// Output the data to stdout.
	

	// Free the memory used for fields of the structs.
	for(int i=0; i<count; i++){
		deleteStruct(data+i);
	}

	// Free the memory for the struct array.
	free(data);

	return 0;

}


void parseLine(char *line, airPdata *apd){

	int i=0, j=0, commas=0;
	
	while(commas<15){
		while(*(line+i)!=','){
			i++;
		}
		
		// strncpy does not append a '\0' to the end of the copied sub-string, so we will
		// replace the comma with '\0'. 
		*(line+i) = '\0';

		switch (commas){
	
		case 1:   //Grab the second "field" - Location ID
			apd->LocID = malloc(sizeof(char)*(i-j+1));
			if(apd->LocID==NULL){
                        	printf("malloc failed to initialize airPdata.LocID.\n");
                                exit(-1);
                        }
                        strncpy(apd->LocID, line+j, i-j+1);
                        break;
		case 2:   //Grab the third "field" - Field Name
			apd->fieldName = malloc(sizeof(char)*(i-j+1));
			if(apd->fieldName==NULL){
				printf("malloc failed to initialize airPdata.fieldName.\n");
				exit(-1);
			}
			strncpy(apd->fieldName, line+j, i-j+1);
			break;
		case 3:   //Grab the fourth "field" - City
			apd->city = malloc(sizeof(char)*(i-j+1));
			if(apd->city==NULL){
				printf("malloc failed to initialize airPdata.city.\n");
				exit(-1);
			}
			strncpy(apd->city, line+j, i-j+1);
			break;
		
		case 8:   //Grab the ninth "field" - Latitude (sexagesimal string)
			
			sscanf(line+j, "%f", &(apd->latitude));
            apd->latitude = sexag2decimal(line+j);
			break;
		case 9:   //Grab the tenth "field" - Longitude (sexagesimal string)
			sscanf(line+j, "%f", &(apd->longitude));
			apd->longitude = sexag2decimal(line+j);
			break;
		
		}

		j=++i;
		commas++;
	}
    
    
}

void printData(int length, airPdata *data){
    
        
	printf("code,name,city,lat,lon\n");
	for(int i=0; i<length; i++){
		printf("%s,%s,%s,%.4f,%.4f\n",(data+i)->LocID,(data+i)->fieldName,
		  (data+i)->city,(data+i)->latitude,(data+i)->longitude);
	}
}

void deleteStruct(airPdata *apd){


	free(apd->city);
	free(apd->fieldName);
	free(apd->LocID);

}
/*
 * This code is supplied for HW3 as a baseline for solving the 
 * problems uniq to HW3 - sorting decimal latitude and airports.
 * It will likely use the code from the AVL labs to expedite the
 * sorting. MMc 11182017
 */
