/* 
Project Name: Mini Project 2
Group members: Shane Ramphal, Kush Shastri
Description: This program will receive the position of a user and the position of multiple other users. It will also be 
able to recieve this data from a file. 
*/ 

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


//create structure user t
typedef struct user_t{
    char name[50];
    double longitude, latitude, altitude,time;
} user; //when a struct type needs to be created, just call user_ _ _. 


//struct that holds the name and distance of the other users from our user  
typedef struct { 
    user user; 
    double distance;
} userdistance;


//FUNCTIONS

// this function will scan the position and time of a user into the user_t structure 
void scan_user(user *u){
    puts("enter name: ");
    scanf("%s", &u->name);
    puts("Enter longitude:");
    scanf("%d", &u->longitude); 
    puts("Enter latitude:");
    scanf("%d", &u->latitude);
    puts("Enter altitude:");
    scanf("%d", &u->altitude);
    puts("Enter time:");
    scanf("%d", &u->time);

}

//function that calls scan_user to fill our_user structure and other_users array 
void fill(user *x, user *y, int size){ //use pointers so both parameters are returned at the end of fill

    //fill our users 
    printf("Enter your data\n"); 
    scan_user(x); //call scan user for ouruser in the main function and use address to fill values 

    //fill other_users array  
    printf("Enter other users data\n");
    for (int i = 0; i<size; i++){
        scan_user(&y[i]);
    }
    
}


void calculate(user *x, user *y, int size, userdistance *users){ //receives our user and other user 
//c is our_user, y is other_users array 


//create an array of structures holding the distance from each user 

//our user location data 
double ourlat=x->latitude;
double ourlong=x->longitude;
double ouralt=x->altitude;

for(int i=0;i<size;i++){
    //other user location data 
    double otherlat=y[i].latitude;
    double otherlong=y[i].longitude;
    double otheralt=y[i].altitude;

    users[i].user.altitude = y[i].altitude;
    users[i].user.latitude = y[i].latitude;
    users[i].user.longitude = y[i].longitude;
    strcpy(users[i].user.name,y[i].name);
    users[i].distance= sqrt(pow(ourlat-otherlat,2)+pow(ourlong-otherlong,2)+pow(ouralt-otheralt,2));
    
}

}

// finds which other user has the smallest distance from out user 
userdistance closest_user(userdistance *users, int size){
    
    userdistance min;
    min.distance = users[0].distance;
    for (int i =0; i < size; i++ ){
        if(users[i].distance < min.distance)    
           min.user = users[i].user;
           min.distance = users[i].distance;
    } 
    return min; //returns the user with the smallest distance 
}



void scan_user_file(char *fname){ //receives file name 

user our_user;

FILE *file;
file= fopen(fname,"r");//open file to read 
 if (file == NULL) {
    puts("Error: Empty File");
    exit(1); //if the file is empty, exit the program
  }

int numofusers;
fscanf(file, "%d", &numofusers); //reads the first line of the txt file and assigns it to variable "numofusers"
//fetches all the our_user data from the file 
fscanf(file, "%s", &our_user.name);
fscanf(file, "%lf", &our_user.time);
fscanf(file, "%lf", &our_user.latitude);
fscanf(file, "%lf", &our_user.longitude);
fscanf(file, "%lf", &our_user.altitude);

user other_user[numofusers]; //create other_user struct 
//use for loop for other users
for(int i=0;i<numofusers; i++){
    fscanf(file, "%s", &other_user[i].name);
    fscanf(file, "%lf", &other_user[i].time);
    fscanf(file, "%lf", &other_user[i].latitude);
    fscanf(file, "%lf", &other_user[i].longitude);
    fscanf(file, "%lf", &other_user[i].altitude);
}

//find the closest user 
    userdistance users_distance[numofusers];
    calculate(&our_user, other_user, numofusers, users_distance);
    userdistance closest; 
    closest = closest_user(users_distance,numofusers);

    printf("The closest user is\nName: %s\nLatitude: %lf\nLongitude: %lf\nAltitude: %lf",closest.user.name,closest.user.latitude,closest.user.longitude, closest.user.altitude);

}



int main(){ 

    
user our_user; //create structure called our_user which is filled using scan user 
int otherusers; //variable for how many otherusers there are (option 1)



printf("do you want to read a file or enter manually? (type 1 for manually, 2 for file ):  ");
char choice;
scanf("%d",&choice);


if(choice==1){
    //create other user structure 
    printf("enter how many other users there are: ");
    scanf("%d", &otherusers);
    user other_user[otherusers]; //create an array of users called other_users (assign number of other users entered)

    //call fill function 
    fill(&our_user, other_user,otherusers);

    //find closest other user 
    userdistance users_distance[otherusers];
    calculate(&our_user, other_user, otherusers, users_distance);
    userdistance closest; 
    closest = closest_user(users_distance,otherusers);

    // print the name and position of the closest user 
    printf("The closest user is\nName: %s\nLatitude: %d\nLongitude: %d\nAltitude: %d",closest.user.name,closest.user.latitude,closest.user.longitude, closest.user.altitude);

}

//if the user enters 2, promt for file name and call scan user file function 
else if(choice==2){
    char fname[250];
    printf("Enter file directory: "); 
    scanf("%s", fname);
    scan_user_file(fname); //scan file 
    
}
//if user enters an invalid argument, print the following 
else {
    puts("Invalid Input"); 
}
    
}