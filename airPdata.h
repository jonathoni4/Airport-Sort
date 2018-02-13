//
//  airPdata.h
//  CS 1 homework
//
//  Created by Jonathon Irigoyen on 9/23/17.
//  Copyright © 2017 Jonathon Irigoyen. All rights reserved.
//

#ifndef airPdata_h
#define airPdata_h

typedef struct airPdata{
    int  seqNumber; //The process output’s sequence number
    char*LocID;    //Airport’s ‘‘Short Name’’, ie MCO
    char*fieldName; //Airport Name
    char*city;     //Associated City
    float longitude; //Longitude
    float latitude; //Latitude
} airPdata;

#endif /* airPdata_h */
