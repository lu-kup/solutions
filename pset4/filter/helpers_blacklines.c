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
    RGBTRIPLE blacklines[height + 2][width + 2];
    RGBTRIPLE blurry[height][width];

    //Create a copy with blacklines

    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            blacklines[i][j].rgbtRed = 0;
            blacklines[i][j].rgbtGreen = 0;
            blacklines[i][j].rgbtBlue = 0;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blacklines[i + 1][j + 1].rgbtRed = image[i][j].rgbtRed;
            blacklines[i + 1][j + 1].rgbtGreen = image[i][j].rgbtGreen;
            blacklines[i + 1][j + 1].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    //Cycle through the middle part
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            blurry[i][j].rgbtRed = round((blacklines[i + 1][j - 1 + 1].rgbtRed + blacklines[i + 1][j + 1 + 1].rgbtRed
            + blacklines[i - 1 + 1][j - 1 + 1].rgbtRed + blacklines[i - 1 + 1][j + 1].rgbtRed + blacklines[i - 1 + 1][j + 1 + 1].rgbtRed
            + blacklines[i + 1 + 1][j - 1 + 1].rgbtRed + blacklines[i + 1 + 1][j + 1].rgbtRed + blacklines[i + 1 + 1][j + 1 + 1].rgbtRed) / 8);

            blurry[i][j].rgbtGreen = round((blacklines[i + 1][j - 1 + 1].rgbtGreen + blacklines[i + 1][j + 1 + 1].rgbtGreen
            + blacklines[i - 1 + 1][j - 1 + 1].rgbtGreen + blacklines[i - 1 + 1][j + 1].rgbtGreen + blacklines[i - 1 + 1][j + 1 + 1].rgbtGreen
            + blacklines[i + 1 + 1][j - 1 + 1].rgbtGreen + blacklines[i + 1 + 1][j + 1].rgbtGreen + blacklines[i + 1 + 1][j + 1 + 1].rgbtGreen) / 8);

            blurry[i][j].rgbtBlue = round((blacklines[i + 1][j - 1 + 1].rgbtBlue + blacklines[i + 1][j + 1 + 1].rgbtBlue
            + blacklines[i - 1 + 1][j - 1 + 1].rgbtBlue + blacklines[i - 1 + 1][j + 1].rgbtBlue + blacklines[i - 1 + 1][j + 1 + 1].rgbtBlue
            + blacklines[i + 1 + 1][j - 1 + 1].rgbtBlue + blacklines[i + 1 + 1][j + 1].rgbtBlue + blacklines[i + 1 + 1][j + 1 + 1].rgbtBlue) / 8);
        }

    }

    // Copy blurry copy into main image
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
    return;
}




//typedef struct
//{
//    BYTE  rgbtBlue;
//    BYTE  rgbtGreen;
//    BYTE  rgbtRed;
//} __attribute__((__packed__))
//RGBTRIPLE;