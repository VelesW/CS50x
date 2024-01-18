#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double average_value;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average_value = (image[i][j].rgbtGreen + image[i][j].rgbtBlue + image[i][j].rgbtRed) / 3.;
            image[i][j].rgbtGreen = round(average_value);
            image[i][j].rgbtBlue = round(average_value);
            image[i][j].rgbtRed = round(average_value);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2.0; j++)
        {
            tmp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCopy[height][width];
    double avg_R, avg_G, avg_B, counter; // Average of Red, Green, Blue in pixels

    for (int i = 0; i < height; i++) // loop for image
    {
        for (int j = 0; j < width; j++) // loop for image
        {
            avg_R = 0;
            avg_G = 0;
            avg_B = 0;
            counter = 0;

            for (int a = -1; a < 2; a++) // loop to calculate blur for one pixel
            {
                for (int b = -1; b < 2; b++) // loop to calculate blur for one pixel
                {
                    if (i + a < 0 || i + a > height - 1)
                    {
                        continue;
                    }
                    if (j + b < 0 || j + b > width - 1)
                    {
                        continue;
                    }
                    avg_R += image[i + a][j + b].rgbtRed;
                    avg_G += image[i + a][j + b].rgbtGreen;
                    avg_B += image[i + a][j + b].rgbtBlue;
                    counter++;
                }
            }
            imageCopy[i][j].rgbtRed = round(avg_R / counter);
            imageCopy[i][j].rgbtGreen = round(avg_G / counter);
            imageCopy[i][j].rgbtBlue = round(avg_B / counter);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = imageCopy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = imageCopy[i][j].rgbtGreen;
            image[i][j].rgbtRed = imageCopy[i][j].rgbtRed;
        }

    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCopy[height][width];

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    double gxRed, gxGreen, gxBlue, gyRed, gyGreen, gyBlue;

    for (int i = 0; i < height; i++) // loop for all image
    {
        for (int j = 0; j < width; j++) // loop for all image
        {
            gxRed = 0;
            gxGreen = 0;
            gxBlue = 0;
            gyRed = 0;
            gyGreen = 0;
            gyBlue = 0;
            for (int a = -1; a < 2; a++) // loop for one pixel
            {
                for (int b = -1; b < 2; b++) // loop for one pixel
                {
                    if (i + a < 0 || i + a > height - 1)
                    {
                        continue;
                    }

                    if (j + b < 0 || j + b > width - 1)
                    {
                        continue;
                    }

                    gxRed += image[i + a][j + b].rgbtRed * gx[a + 1][b + 1];
                    gxGreen += image[i + a][j + b].rgbtGreen * gx[a + 1][b + 1];
                    gxBlue += image[i + a][j + b].rgbtBlue * gx[a + 1][b + 1];

                    gyRed += image[i + a][j + b].rgbtRed * gy[a + 1][b + 1];
                    gyGreen += image[i + a][j + b].rgbtGreen * gy[a + 1][b + 1];
                    gyBlue += image[i + a][j + b].rgbtBlue * gy[a + 1][b + 1];
                }
            }

            int redVal = round(sqrt(gxRed * gxRed + gyRed * gyRed));
            int greenVal = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int blueVal = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));

            imageCopy[i][j].rgbtRed = (redVal > 255) ? 255 : redVal; // conditional expression, if red > 255 => red = 255 else red = red
            imageCopy[i][j].rgbtGreen = (greenVal > 255) ? 255 :
                                        greenVal; // conditional expression if green > 255 => green = 255 else green = green
            imageCopy[i][j].rgbtBlue = (blueVal > 255) ? 255 : blueVal; // conditional expression if blue > 255 => blue = 255 else blue = blue
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = imageCopy[i][j].rgbtRed;
            image[i][j].rgbtGreen = imageCopy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = imageCopy[i][j].rgbtBlue;
        }
    }

    return;
}