#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;

            int averageRGB = round((red + green + blue) / 3);

            image[i][j].rgbtRed = averageRGB;
            image[i][j].rgbtGreen = averageRGB;
            image[i][j].rgbtBlue = averageRGB;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float redSum = 0;
            float greenSum = 0;
            float blueSum = 0;
            int pixelCount = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if ((i + k >= height) || (i + k < 0))
                    {
                        continue;
                    }
                    else if ((j + l >= width) || (j + l < 0))
                    {
                        continue;
                    }
                    else
                    {
                        redSum += tmp[i + k][j + l].rgbtRed;
                        greenSum += tmp[i + k][j + l].rgbtGreen;
                        blueSum += tmp[i + k][j + l].rgbtBlue;
                        pixelCount++;
                    }
                }
            }

            image[i][j].rgbtRed = round(redSum / pixelCount);
            image[i][j].rgbtGreen = round(greenSum / pixelCount);
            image[i][j].rgbtBlue = round(blueSum / pixelCount);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float redGx = 0;
            float greenGx = 0;
            float blueGx = 0;
            float redGy = 0;
            float greenGy = 0;
            float blueGy = 0;


            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if ((i + k >= height) || (i + k < 0))
                    {
                        continue;
                    }
                    else if ((j + l >= width) || (j + l < 0))
                    {
                        continue;
                    }
                    else
                    {
                        redGx += tmp[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                        greenGx += tmp[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                        blueGx += tmp[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                        redGy += tmp[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                        greenGy += tmp[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                        blueGy += tmp[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                    }
                }
            }

            int red = round(sqrt((redGx * redGx) + (redGy * redGy)));

            if (red > 255)
            {
                red = 255;
            }

            int green = round(sqrt((greenGx * greenGx) + (greenGy * greenGy)));

            if (green > 255)
            {
                green = 255;
            }

            int blue = round(sqrt((blueGx * blueGx) + (blueGy * blueGy)));

            if (blue > 255)
            {
                blue = 255;
            }

            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }

    return;
}
