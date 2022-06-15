#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;
FILE *img = NULL;

int main(int argc, char *argv[])
{
    //Checking if the user has input valid cmd argument
    if(argc != 2){

        printf("Please input exactly one command line argument containing the name of the forensic file\n");
        return 1;
    }

    // Opening card.raw
    FILE *file = fopen(argv[1], "r");


    int n = 0;
    BYTE buffer[512];
    char filename[20];
    bool newfile;

   // Looping till there is nothing left to read from the card
    while(fread(buffer, 512, 1, file) == 1){

    //Checking if a new jpeg has occured
    newfile = (buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xe0) == 0xe0);

    //CLosing current image file and opening new one if a new jpeg indeed has been found
    if(newfile){

        if(n > 0){
        fclose(img);
            }

        sprintf(filename, "%03i.jpg", n);
        n++;


       img = fopen(filename, "w");

       //Quitting if the file pointer returns null
       if(img == NULL){

           return 1;
       }


    }

    //Writing the data into the newly made file
    if(n > 0){
    fwrite(buffer, 512, 1, img);
    }
  }

  //Closing card.raw file and freeing malloc'd space
  fclose(file);


}