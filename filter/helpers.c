#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int value;

    for(int i = 0; i < height; i++){

        for(int j = 0; j < width; j++){

            value = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);


            image[i][j].rgbtRed = value;
            image[i][j].rgbtGreen = value;
            image[i][j].rgbtBlue = value;
        }

    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    float rvalue;
    float gvalue;
    float bvalue;

    int red;
    int green;
    int blue;

    for(int i = 0; i < height; i++){

        for(int j = 0; j < width; j++){

            rvalue = (0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue);
            gvalue = (0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue);
            bvalue = (0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue);

           red = rvalue;
           green = gvalue;
           blue = bvalue;


            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }

    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image2[height][width];


    for(int i = 0; i < height; i++){

        for(int j = 0; j < width; j++){

                image2[i][j] = image[i][width -1 -j];

          }
      }

      for(int i = 0; i < height; i++){

        for(int j = 0; j < width; j++){

                image[i][j] = image2[i][j];
          }
      }
   return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE image2[height][width];

     for(int i = 0; i < height; i++){

        for(int j = 0; j < width; j++){

        image2[i][j].rgbtRed = image[i][j].rgbtRed;
        image2[i][j].rgbtBlue = image[i][j].rgbtBlue;
        image2[i][j].rgbtGreen = image[i][j].rgbtGreen;

        }
     }

     for(int i = 0; i < height; i++){

        for(int j = 0; j < width; j++){


                if(i == 0){

                    if(j == 0){

                    image[i][j].rgbtRed = ((image2[i][j].rgbtRed) + (image2[i][j+1].rgbtRed) +
                                 (image2[i+1][j].rgbtRed) + (image2[i+1][j+1].rgbtRed))/3;

                image[i][j].rgbtGreen = (
                                 (image2[i][j].rgbtGreen) + (image2[i][j+1].rgbtGreen) +
                                 (image2[i+1][j].rgbtGreen) + (image2[i+1][j+1].rgbtGreen))/3;

                image[i][j].rgbtBlue = ((image2[i][j].rgbtBlue) + (image2[i][j+1].rgbtBlue) +
                                 (image2[i+1][j].rgbtBlue) + (image2[i+1][j+1].rgbtBlue))/3;
                    }

                   else if(j == width-1){

                        image[i][j].rgbtRed = (
                                 (image2[i][j-1].rgbtRed) + (image2[i][j].rgbtRed) +
                                 (image2[i+1][j-1].rgbtRed) + (image2[i+1][j].rgbtRed))/3;

                image[i][j].rgbtGreen = (
                                 (image2[i][j-1].rgbtGreen) + (image2[i][j].rgbtGreen)  +
                                 (image2[i+1][j-1].rgbtGreen) + (image2[i+1][j].rgbtGreen))/3;

                image[i][j].rgbtBlue = (
                                 (image2[i][j-1].rgbtBlue) + (image2[i][j].rgbtBlue)  +
                                 (image2[i+1][j-1].rgbtBlue) + (image2[i+1][j].rgbtBlue))/3;

                    }

                    else{
                        image[i][j].rgbtRed = (
                                 (image2[i][j-1].rgbtRed) + (image2[i][j].rgbtRed) + (image2[i][j+1].rgbtRed) +
                                 (image2[i+1][j-1].rgbtRed) + (image2[i+1][j].rgbtRed) + (image2[i+1][j+1].rgbtRed))/3;

                image[i][j].rgbtGreen = (
                                 (image2[i][j-1].rgbtGreen) + (image2[i][j].rgbtGreen) + (image2[i][j+1].rgbtGreen) +
                                 (image2[i+1][j-1].rgbtGreen) + (image2[i+1][j].rgbtGreen) + (image2[i+1][j+1].rgbtGreen))/3;

                image[i][j].rgbtBlue = (
                                 (image2[i][j-1].rgbtBlue) + (image2[i][j].rgbtBlue) + (image2[i][j+1].rgbtBlue) +
                                 (image2[i+1][j-1].rgbtBlue) + (image2[i+1][j].rgbtBlue) + (image2[i+1][j+1].rgbtBlue))/3;

                    }

                }

                else if(i == height-1){

                    if(j == 0){

                         image[i][j].rgbtRed = ((image2[i-1][j].rgbtRed) + (image2[i-1][j+1].rgbtRed) +
                                 (image2[i][j].rgbtRed) + (image2[i][j+1].rgbtRed))/3;

                image[i][j].rgbtGreen = ((image2[i-1][j].rgbtGreen) + (image2[i-1][j+1].rgbtGreen) +
                                  (image2[i][j].rgbtGreen) + (image2[i][j+1].rgbtGreen))/3;

                image[i][j].rgbtBlue = ((image2[i-1][j].rgbtBlue) + (image2[i-1][j+1].rgbtBlue) +
                                  (image2[i][j].rgbtBlue) + (image2[i][j+1].rgbtBlue) )/3;
                    }

                    else if(j == width-1){

                         image[i][j].rgbtRed = ((image2[i-1][j-1].rgbtRed) + (image2[i-1][j].rgbtRed) +
                                 (image2[i][j-1].rgbtRed) + (image2[i][j].rgbtRed)
                                 )/3;

                image[i][j].rgbtGreen = ((image2[i-1][j-1].rgbtGreen) + (image2[i-1][j].rgbtGreen) +
                                 (image2[i][j-1].rgbtGreen) + (image2[i][j].rgbtGreen) )/3;

                image[i][j].rgbtBlue = ((image2[i-1][j-1].rgbtBlue) + (image2[i-1][j].rgbtBlue) +
                                 (image2[i][j-1].rgbtBlue) + (image2[i][j].rgbtBlue))/3;
                    }

                    else{

                         image[i][j].rgbtRed = ((image2[i-1][j-1].rgbtRed) + (image2[i-1][j].rgbtRed) + (image2[i-1][j+1].rgbtRed) +
                                 (image2[i][j-1].rgbtRed) + (image2[i][j].rgbtRed) + (image2[i][j+1].rgbtRed) )/3;

                image[i][j].rgbtGreen = ((image2[i-1][j-1].rgbtGreen) + (image2[i-1][j].rgbtGreen) + (image2[i-1][j+1].rgbtGreen) +
                                 (image2[i][j-1].rgbtGreen) + (image2[i][j].rgbtGreen) + (image2[i][j+1].rgbtGreen) )/3;

                image[i][j].rgbtBlue = ((image2[i-1][j-1].rgbtBlue) + (image2[i-1][j].rgbtBlue) + (image2[i-1][j+1].rgbtBlue) +
                                 (image2[i][j-1].rgbtBlue) + (image2[i][j].rgbtBlue) + (image2[i][j+1].rgbtBlue) )/3;
                    }
                }

                else{




                    image[i][j].rgbtRed = ((image2[i-1][j-1].rgbtRed) + (image2[i-1][j].rgbtRed) + (image2[i-1][j+1].rgbtRed) +
                                     (image2[i][j-1].rgbtRed) + (image2[i][j].rgbtRed) + (image2[i][j+1].rgbtRed) +
                                     (image2[i+1][j-1].rgbtRed) + (image2[i+1][j].rgbtRed) + (image2[i+1][j+1].rgbtRed))/3;

                    image[i][j].rgbtGreen = ((image2[i-1][j-1].rgbtGreen) + (image2[i-1][j].rgbtGreen) + (image2[i-1][j+1].rgbtGreen) +
                                     (image2[i][j-1].rgbtGreen) + (image2[i][j].rgbtGreen) + (image2[i][j+1].rgbtGreen) +
                                     (image2[i+1][j-1].rgbtGreen) + (image2[i+1][j].rgbtGreen) + (image2[i+1][j+1].rgbtGreen))/3;

                    image[i][j].rgbtBlue = ((image2[i-1][j-1].rgbtBlue) + (image2[i-1][j].rgbtBlue) + (image2[i-1][j+1].rgbtBlue) +
                                     (image2[i][j-1].rgbtBlue) + (image2[i][j].rgbtBlue) + (image2[i][j+1].rgbtBlue) +
                                     (image2[i+1][j-1].rgbtBlue) + (image2[i+1][j].rgbtBlue) + (image2[i+1][j+1].rgbtBlue))/3;

                }
           }


        }



    return;
}
