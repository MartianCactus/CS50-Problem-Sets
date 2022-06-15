/*
 PSEUDOCODE:
 ✓  1) See the key and fulfill all conditions (no more than one arg / arg should have decimal digits only)
 ✓  2) Make integer a and set it equal to key
 ✓  3) Ask for plaintext                                                                                         _
    4) Increase ASCII number of letter by "a" and if it is above a certain threshold, revert back to first char.  | Repeat for
    5) Change value of a on each run of loop                                                                             _| every letter
    6) Output
*/


#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[]){

//Checking if key is valid
    if(argc != 2){

        printf("You may be entering an incorrect number of command line arguments! Make sure you enter exactly one!!\n");
        return 1;
        }

    for(int i = 0; i < strlen(argv[1]) ; i++){

        if(argv[1][i] != '1' && argv[1][i] != '2' && argv[1][i] != '3' && argv[1][i] != '4' && argv[1][i] != '5' && argv[1][i] != '6' && argv[1][i] != '7' &&
        argv[1][i] != '8' && argv[1][i] != '9' && argv[1][i] != '0'){

            printf("Usage: ./caesar key\n");
            return 1;
        }
    }


//Prompting user for plaintext input

    string pt = get_string("plaintext: ");

//Converting plaintext to ciphertext

    for(int i = 0; i < strlen(pt) ; i++){
     //Converting value of key from String to Int   
         int a = atoi(argv[1]);

        if(pt[i] >= 65 && pt[i] <= 90){

                while((int)pt[i] + a > 90){

                    a = a - 26;
                }

            pt[i] += a;


        }

        else if(pt[i] >= 97 && pt[i] <= 122){


            while((int)pt[i] + a > 122){

                a = a - 26;

            }

            pt[i] += a;

        }


    }

    printf("ciphertext: %s\n", pt);

}


