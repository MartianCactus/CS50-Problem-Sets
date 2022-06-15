#include <stdio.h>
#include <cs50.h>

int main(void){

    int a;

    do {
     a = get_int("How big do you want the thingy to be?");

    } while(a<1 || a>8);

    for(int i=1; i<=a;i++){

        for(int j=1; j<=a-i; j++){

            printf(" ");

                }

        for(int k=1; k<=i-1; k++){

            printf("#");
        }

    printf("#\n");

    }

}