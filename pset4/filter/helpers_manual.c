#include "helpers.h"
#include "math.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round(( (double) image[i][j].rgbtBlue + (double) image[i][j].rgbtGreen + (double) image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE reflection[height][width];
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            reflection[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            reflection[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            reflection[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
        }
    }

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = reflection[i][j].rgbtBlue;
            image[i][j].rgbtGreen = reflection[i][j].rgbtGreen;
            image[i][j].rgbtRed = reflection[i][j].rgbtRed;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurry[height][width];

    //Cycle through the middle part
    for (int i = 1; i < height - 1; i ++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            blurry[i][j].rgbtRed = (int) round( (float) (image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed
            + image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed
            + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9);

            blurry[i][j].rgbtGreen = (int) round( (float) (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen
            + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen
            + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9);

            blurry[i][j].rgbtBlue = (int) round( (float) (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue
            + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue
            + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9);
        }

    }

    //Cycle through the top and bottom
    for (int j = 1; j < width - 1; j++)
    {
       blurry[0][j].rgbtRed = (int) round( (float) (image[0][j - 1].rgbtRed + image[0][j].rgbtRed + image[0][j + 1].rgbtRed
        + image[1][j - 1].rgbtRed + image[1][j].rgbtRed + image[1][j + 1].rgbtRed) / 6);

        blurry[0][j].rgbtGreen = (int) round( (float) (image[0][j - 1].rgbtGreen + image[0][j].rgbtGreen + image[0][j + 1].rgbtGreen
        + image[1][j - 1].rgbtGreen + image[1][j].rgbtGreen + image[1][j + 1].rgbtGreen) / 6);

        blurry[0][j].rgbtBlue = (int) round( (float) (image[0][j - 1].rgbtBlue + image[0][j].rgbtBlue + image[0][j + 1].rgbtBlue
        + image[1][j - 1].rgbtBlue + image[1][j].rgbtBlue + image[1][j + 1].rgbtBlue) / 6);

        blurry[height - 1][j].rgbtRed = (int) round( (float) (image[height - 1][j - 1].rgbtRed + image[height - 1][j].rgbtRed + image[height - 1][j + 1].rgbtRed
        + image[height - 2][j - 1].rgbtRed + image[height - 2][j].rgbtRed + image[height - 2][j + 1].rgbtRed) / 6);

        blurry[height - 1][j].rgbtGreen = (int) round( (float) (image[height - 1][j - 1].rgbtGreen + image[height - 1][j].rgbtGreen + image[height - 1][j + 1].rgbtGreen
        + image[height - 2][j - 1].rgbtGreen + image[height - 2][j].rgbtGreen + image[height - 2][j + 1].rgbtGreen) / 6);

        blurry[height - 1][j].rgbtBlue = (int) round( (float) (image[height - 1][j - 1].rgbtBlue + image[height - 1][j].rgbtBlue + image[height - 1][j + 1].rgbtBlue
        + image[height - 2][j - 1].rgbtBlue + image[height - 2][j].rgbtBlue + image[height - 2][j + 1].rgbtBlue) / 6);
    }

    //Cycle through the sides
    for (int i = 1; i < height - 1; i++)
    {
       blurry[i][0].rgbtRed = (int) round( (float) (image[i - 1][0].rgbtRed + image[i][0].rgbtRed + image[i + 1][0].rgbtRed
        + image[i - 1][1].rgbtRed + image[i][1].rgbtRed + image[i + 1][1].rgbtRed) / 6);

       blurry[i][0].rgbtGreen = (int) round( (float) (image[i - 1][0].rgbtGreen + image[i][0].rgbtGreen + image[i + 1][0].rgbtGreen
        + image[i - 1][1].rgbtGreen + image[i][1].rgbtGreen + image[i + 1][1].rgbtGreen) / 6);

       blurry[i][0].rgbtBlue = (int) round( (float) (image[i - 1][0].rgbtBlue + image[i][0].rgbtBlue + image[i + 1][0].rgbtBlue
        + image[i - 1][1].rgbtBlue + image[i][1].rgbtBlue + image[i + 1][1].rgbtBlue) / 6);

        blurry[i][width - 1].rgbtRed = (int) round( (float) (image[i - 1][width - 1].rgbtRed + image[i][width - 1].rgbtRed + image[i + 1][width - 1].rgbtRed
        + image[i - 1][width - 2].rgbtRed + image[i][width - 2].rgbtRed + image[i + 1][width - 2].rgbtRed) / 6);

        blurry[i][width - 1].rgbtGreen = (int) round( (float) (image[i - 1][width - 1].rgbtGreen + image[i][width - 1].rgbtGreen + image[i + 1][width - 1].rgbtGreen
        + image[i - 1][width - 2].rgbtGreen + image[i][width - 2].rgbtGreen + image[i + 1][width - 2].rgbtGreen) / 6);

        blurry[i][width - 1].rgbtBlue = (int) round( (float) (image[i - 1][width - 1].rgbtBlue + image[i][width - 1].rgbtBlue + image[i + 1][width - 1].rgbtBlue
        + image[i - 1][width - 2].rgbtBlue + image[i][width - 2].rgbtBlue + image[i + 1][width - 2].rgbtBlue) / 6);
    }

    //Get the corners
    blurry[0][0].rgbtRed = (int) round( (float) (image[0][0].rgbtRed + image[0][1].rgbtRed + image[1][0].rgbtRed + image[1][1].rgbtRed) / 4);

    blurry[0][width - 1].rgbtRed = (int) round( (float) (image[0][width - 1].rgbtRed + image[0][width - 2].rgbtRed + image[1][width - 1].rgbtRed + image[1][width - 2].rgbtRed) / 4);

    blurry[height - 1][0].rgbtRed = (int) round( (float) (image[height - 1][0].rgbtRed + image[height - 1][1].rgbtRed + image[height - 2][0].rgbtRed + image[height - 2][1].rgbtRed) / 4);

    blurry[height - 1][width - 1].rgbtRed = (int) round( (float) (image[height - 1][width - 1].rgbtRed + image[height - 2][width - 1].rgbtRed
    + image[height - 1][width - 2].rgbtRed + image[height - 2][width - 2].rgbtRed) / 4);


    blurry[0][0].rgbtGreen = (int) round( (float) (image[0][0].rgbtGreen + image[0][1].rgbtGreen + image[1][0].rgbtGreen + image[1][1].rgbtGreen) / 4);

    blurry[0][width - 1].rgbtGreen = (int) round( (float) (image[0][width - 1].rgbtGreen + image[0][width - 2].rgbtGreen + image[1][width - 1].rgbtGreen + image[1][width - 2].rgbtGreen) / 4);

    blurry[height - 1][0].rgbtGreen = (int) round( (float) (image[height - 1][0].rgbtGreen + image[height - 1][1].rgbtGreen + image[height - 2][0].rgbtGreen + image[height - 2][1].rgbtGreen) / 4);

    blurry[height - 1][width - 1].rgbtGreen = (int) round( (float) (image[height - 1][width - 1].rgbtGreen + image[height - 2][width - 1].rgbtGreen
    + image[height - 1][width - 2].rgbtGreen + image[height - 2][width - 2].rgbtGreen) / 4);


    blurry[0][0].rgbtBlue = (int) round( (float) (image[0][0].rgbtBlue + image[0][1].rgbtBlue + image[1][0].rgbtBlue + image[1][1].rgbtBlue) / 4);

    blurry[0][width - 1].rgbtBlue = (int) round( (float) (image[0][width - 1].rgbtBlue + image[0][width - 2].rgbtBlue + image[1][width - 1].rgbtBlue + image[1][width - 2].rgbtBlue) / 4);

    blurry[height - 1][0].rgbtBlue = (int) round( (float) (image[height - 1][0].rgbtBlue + image[height - 1][1].rgbtBlue + image[height - 2][0].rgbtBlue + image[height - 2][1].rgbtBlue) / 4);

    blurry[height - 1][width - 1].rgbtBlue = (int) round( (float) (image[height - 1][width - 1].rgbtBlue + image[height - 2][width - 1].rgbtBlue
    + image[height - 1][width - 2].rgbtBlue + image[height - 2][width - 2].rgbtBlue) / 4);


    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = blurry[i][j].rgbtBlue;
            image[i][j].rgbtGreen = blurry[i][j].rgbtGreen;
            image[i][j].rgbtRed = blurry[i][j].rgbtRed;
        }
    }


    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE Gx[height][width];
    RGBTRIPLE Gy[height][width];
    RGBTRIPLE edges[height][width];

    //Set kernels to 0
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Gx[i][j].rgbtBlue = 0;
            Gy[i][j].rgbtBlue = 0;

            Gx[i][j].rgbtGreen = 0;
            Gy[i][j].rgbtGreen = 0;

            Gx[i][j].rgbtRed = 0;
            Gy[i][j].rgbtRed = 0;
        }
    }

    int Gxm[3][3] =
    {
        {-1, 0, 1},
        {2, 0, 2},
        {-1, 0, 1}
    }

    int Gxy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    }


    //Calculate weighted sum
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Gx[i][j].rgbtBlue += image[i - 1][j - 1].rgbtBlue * (-1);
            Gx[i][j].rgbtBlue += image[i][j - 1].rgbtBlue * (-2);
            Gx[i][j].rgbtBlue += image[i + 1][j - 1].rgbtBlue * (-1);
            Gx[i][j].rgbtBlue += image[i - 1][j + 1].rgbtBlue * 1;
            Gx[i][j].rgbtBlue += image[i][j + 1].rgbtBlue * 2;
            Gx[i][j].rgbtBlue += image[i + 1][j + 1].rgbtBlue * 1;

            Gx[i][j].rgbtGreen += image[i - 1][j - 1].rgbtGreen * (-1);
            Gx[i][j].rgbtGreen += image[i][j - 1].rgbtGreen * (-2);
            Gx[i][j].rgbtGreen += image[i + 1][j - 1].rgbtGreen * (-1);
            Gx[i][j].rgbtGreen += image[i - 1][j + 1].rgbtGreen * 1;
            Gx[i][j].rgbtGreen += image[i][j + 1].rgbtGreen * 2;
            Gx[i][j].rgbtGreen += image[i + 1][j + 1].rgbtGreen * 1;

            Gx[i][j].rgbtRed += image[i - 1][j - 1].rgbtRed * (-1);
            Gx[i][j].rgbtRed += image[i][j - 1].rgbtRed * (-2);
            Gx[i][j].rgbtRed += image[i + 1][j - 1].rgbtRed * (-1);
            Gx[i][j].rgbtRed += image[i - 1][j + 1].rgbtRed * 1;
            Gx[i][j].rgbtRed += image[i][j + 1].rgbtRed * 2;
            Gx[i][j].rgbtRed += image[i + 1][j + 1].rgbtRed * 1;


            Gy[i][j].rgbtBlue += image[i - 1][j - 1].rgbtBlue * (-1);
            Gy[i][j].rgbtBlue += image[i - 1][j].rgbtBlue * (-2);
            Gy[i][j].rgbtBlue += image[i - 1][j + 1].rgbtBlue * (-1);
            Gy[i][j].rgbtBlue += image[i + 1][j - 1].rgbtBlue * 1;
            Gy[i][j].rgbtBlue += image[i + 1][j].rgbtBlue * 2;
            Gy[i][j].rgbtBlue += image[i + 1][j + 1].rgbtBlue * 1;

            Gy[i][j].rgbtGreen += image[i - 1][j - 1].rgbtGreen * (-1);
            Gy[i][j].rgbtGreen += image[i - 1][j].rgbtGreen * (-2);
            Gy[i][j].rgbtGreen += image[i - 1][j + 1].rgbtGreen * (-1);
            Gy[i][j].rgbtGreen += image[i + 1][j - 1].rgbtGreen * 1;
            Gy[i][j].rgbtGreen += image[i + 1][j].rgbtGreen * 2;
            Gy[i][j].rgbtGreen += image[i + 1][j + 1].rgbtGreen * 1;

            Gy[i][j].rgbtRed += image[i - 1][j - 1].rgbtRed * (-1);
            Gy[i][j].rgbtRed += image[i - 1][j].rgbtRed * (-2);
            Gy[i][j].rgbtRed += image[i - 1][j + 1].rgbtRed * (-1);
            Gy[i][j].rgbtRed += image[i + 1][j - 1].rgbtRed * 1;
            Gy[i][j].rgbtRed += image[i + 1][j].rgbtRed * 2;
            Gy[i][j].rgbtRed += image[i + 1][j + 1].rgbtRed * 1;

        }
    }

    //Combine kernels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            edges[i][j].rgbtBlue = (int) sqrt(pow((double) Gx[i][j].rgbtBlue, 2) + pow((double) Gy[i][j].rgbtBlue, 2));
            edges[i][j].rgbtGreen = (int) sqrt(pow((double) Gx[i][j].rgbtGreen, 2) + pow((double) Gy[i][j].rgbtGreen, 2));
            edges[i][j].rgbtRed = (int) sqrt(pow((double) Gx[i][j].rgbtRed, 2) + pow((double) Gy[i][j].rgbtRed, 2));
        }
    }


    //Copy to main image
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = edges[i][j].rgbtBlue;
            image[i][j].rgbtGreen = edges[i][j].rgbtGreen;
            image[i][j].rgbtRed = edges[i][j].rgbtRed;
        }
    }

    return;
}




//typedef struct
//{
//    BYTE  rgbtBlue;
//    BYTE  rgbtGreen;
//    BYTE  rgbtRed;
//} __attribute__((__packed__))
//RGBTRIPLE;