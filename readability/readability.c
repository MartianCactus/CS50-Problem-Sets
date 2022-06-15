/*
PSEUDOCODE:
 ✓  1) Prompt user for a string input
 ✓  2) Analyze the input for number of letters
 ✓  3) Analyze the input for number of words
 ✓  4) Analyze the input for number of sentences
 ✓   5) Input the variables into the formula
 ✓   6) Output the grade level, 16+ if its higher than 16 and 1- if its lower than 1
*/

#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include <math.h>

int letters(string a);
int words(string a);
int sentences(string a);



int main(void){

    string in = get_string("Input: ");

    float w = (float) words(in);
    float l = (float) letters(in);
    float s = (float) sentences(in);

    //Averaging letters and sentences per 100 words

    float L = l*(100/w);
    float S = s*(100/w);

    //plugging into formula and rounding up

    float index = 0.0588 * L - 0.296 * S - 15.8;

    int ind = (int) round(index);

    //printing the grade level

    if(ind >= 16){

      printf("Grade 16+\n");
      return 0;
    }

    else if(ind < 1){

      printf("Before Grade 1\n");
      return 0;
    }

    else{

        printf("Grade %i\n", ind);
        return 0;
    }

}







//function to calculate number of letters

int letters(string a){

    int count = 0;
    for(int i = 0; i < strlen(a); i++){

        if(a[i] >= 65 && a[i] <= 90){

            count++;
        }

        if(a[i] >= 97 && a[i] <= 122){

            count++;
          }
    }

    return count;

}

//function to calculate number of words

int words(string a){

    int count = 0;
    for(int i = 0; i < strlen(a); i++){

       if(a[i] == ' '){

           count++;
       }
    }
    return count+1;
}

//function to calculate number of sentences

int sentences(string a){

    int count = 0;
    for(int i = 0; i < strlen(a); i++){

       if(a[i] == '!' || a[i] == '?' || a[i] == '.'){

           count++;
       }
    }
    return count;
}