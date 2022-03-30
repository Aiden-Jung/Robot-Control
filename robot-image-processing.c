/***********************************************************************
* Name(s)  Chris Won & Aiden Hyunseok Jung                            *
* Box(s):  4724      & 3877                                           *
* Assignment name: Module100 - Image Processing Project               *
* Assignment for: 10 April 2018                                       *
***********************************************************************/

/* *********************************************************************
* Academic honesty certification:                                     *
*   Written/online sources used:                                      *
*     none                                                            *
*   Help obtained                                                     *
*     none                                                            *
*   My/our signature(s) below confirms that the above list of sources *
*   is complete AND that I/we have not talked to anyone else          *
*   (e.g., CSC 161 students) about the solution to this problem       *
*                                                                     *
*   Signature: Aiden Hyunseok Jung                                    *
***********************************************************************/
     
#include <stdio.h>
#include "MyroC.h"

/*
  Procedure: pixelStrip(Picture* pic, char color)
  Purpose: sets the R,G, or B value of every pixel
           in the picture to 0, depending on
           what char color is
  Precondition: * memory allocated for *pic
                * color is either 'R', 'G', 'B'
  Postcondition: pixels corresponding to color
                 will be set to 0. other pixels
                 remain unchanged
*/
void pixelStrip(Picture* pic, char color);

/*
  Procedure: intInc(unsigned char* color)
  Purpose: increases the intensity of the given color
           (helper procedure for pictureRedder, etc.)
  Precondition: memory allocated for *color
  Postcondition: * value of color does not exceed 255
                 * increase is inversely proportional
                   to the current intensity
*/
void intInc(unsigned char* color);

/*
  Procedure: pictureRedder(Picture* pic)
  Purpose: increases the intensity of red
  Precondition: memory for pic is allocated
  Postcondition: * red intensity of *pic is increased
                 * pixel color value will not exceed 255
                 * increase in color intensity is inversely
                   proportional to the current intensity
                   (i.e. intensity increases comparatively less
                    for higher intensity)
*/
void pictureRedder(Picture* pic);

/*
  Procedure: pictureGreener(Picture* pic)
  Purpose: increases the intensity of green
  Precondition: memory for pic is allocated
  Postcondition: * green intensity of *pic is increased
                 * pixel color value will not exceed 255
                 * increase in color intensity is inversely
                   proportional to the current intensity
                   (i.e. intensity increases comparatively less
                    for higher intensity)
*/
void pictureGreener(Picture* pic);

/*
  Procedure: pictureBluer(Picture* pic)
  Purpose: increases the intensity of blue
  Precondition: memory for pic is allocated
  Postcondition: * blue intensity of *pic is increased
                 * pixel color value will not exceed 255
                 * increase in color intensity is inversely
                   proportional to the current intensity
                   (i.e. intensity increases comparatively less
                    for higher intensity)
*/
void pictureBluer(Picture* pic);

/*
  Procedure: circleSelect(Picture* pic, int xCenter, int yCenter, int radius)
  Purpose: selects a circle from the robot picture and turns each pixel within
  the circle to the corresponding grayscale value
  Precondition: * memory for *pic allocated
                * xCenter and yCenter are within the dimension of the picture
                * radius is nonnegative
  Postcondition: roughly estimated circle appears on the picture with
                 grayscale values
*/
void circleSelect(Picture* pic, int xCenter, int yCenter, int radius);

/*
  Procedure: symmetry(Picture* pic)
  Purpose: mirrors the picture
  Precondition: * memory for *pic allocated
  Postcondition: the picture is symmetric along the middle line
*/
void symmetry(Picture* pic);

int main()
{
    rConnect("/dev/rfcomm0");
    
    Picture original;
    original = rTakePicture();
    rSavePicture(&original, "original.jpg");

    Picture pic1 = original;
    Picture pic2 = original;
    Picture pic3 = original;
    Picture pic4 = original;
    Picture pic5 = original;
    Picture pic6 = original;
    Picture pic7 = original;
    Picture pic8 = original;
    
    pixelStrip(&pic1, 'R');
    rSavePicture(&pic1, "red_stripped.jpg");
    pixelStrip(&pic2, 'G');
    rSavePicture(&pic2, "green_stripped.jpg");
    pixelStrip(&pic3, 'B');
    rSavePicture(&pic3, "blue_stripped.jpg");

    pictureRedder(&pic4);
    rSavePicture(&pic4, "redder.jpg");
    pictureGreener(&pic5);
    rSavePicture(&pic5, "greener.jpg");
    pictureBluer(&pic6);
    rSavePicture(&pic6, "bluer.jpg");

    circleSelect(&pic7, 100, 100, 100);
    rSavePicture(&pic7, "circle.jpg");

    symmetry(&pic8);
    rSavePicture(&pic8, "symmetry.jpg");

    rDisconnect();
    return 0;
}

// Procedure Implementations

/*
  Procedure: pixelStrip(Picture* pic, char color)
  Purpose: sets the R,G, or B value of every pixel
           in the picture to 0, depending on
           what char color is
  Precondition: * memory allocated for *pic
                * color is either 'R', 'G', 'B'
  Postcondition: pixels corresponding to color
                 will be set to 0. other pixels
                 remain unchanged
*/
void pixelStrip(Picture* pic, char color)
{
    int i, j;

    for(i = 0; i < (*pic).height; i++)
    {
        for(j = 0; j < (*pic).width; j++)
        {
            if(color == 'R')
                (*pic).pix_array[i][j].R = 0;
            else if(color == 'G')
                (*pic).pix_array[i][j].G = 0;
            else if(color == 'B')
                (*pic).pix_array[i][j].B = 0;
        }
    }
}

/*
  Procedure: intInc(unsigned char* color)
  Purpose: increases the intensity of the given color
           (helper procedure for pictureRedder, etc.)
  Precondition: memory allocated for *color
  Postcondition: * value of color does not exceed 255
                 * increase is inversely proportional
                   to the current intensity
*/
void intInc(unsigned char* color)
{
    if((*color) < 255)
    {
        (*color) += (255 / 2) - ((*color) * (1/2));
    }
}

/*
  Procedure: pictureRedder(Picture* pic)
  Purpose: increases the intensity of red
  Precondition: memory for pic is allocated
  Postcondition: * red intensity of *pic is increased
                 * pixel color value will not exceed 255
                 * increase in color intensity is inversely
                   proportional to the current intensity
                   (i.e. intensity increases comparatively less
                    for higher intensity)
*/
void pictureRedder(Picture* pic)
{
    int i, j;

    for(i = 0; i < (*pic).height; i++)
        for(j = 0; j < (*pic).width; j++)
            intInc(&((*pic).pix_array[i][j].R));
}

/*
  Procedure: pictureGreener(Picture* pic)
  Purpose: increases the intensity of green
  Precondition: memory for pic is allocated
  Postcondition: * green intensity of *pic is increased
                 * pixel color value will not exceed 255
                 * increase in color intensity is inversely
                   proportional to the current intensity
                   (i.e. intensity increases comparatively less
                    for higher intensity)
*/
void pictureGreener(Picture* pic)
{
    int i, j;

    for(i = 0; i < (*pic).height; i++)
        for(j = 0; j < (*pic).width; j++)
            intInc(&((*pic).pix_array[i][j].G));
}

/*
  Procedure: pictureBluer(Picture* pic)
  Purpose: increases the intensity of blue
  Precondition: memory for pic is allocated
  Postcondition: * blue intensity of *pic is increased
                 * pixel color value will not exceed 255
                 * increase in color intensity is inversely
                   proportional to the current intensity
                   (i.e. intensity increases comparatively less
                    for higher intensity)
*/
void pictureBluer(Picture* pic)
{
    int i, j;

    for(i = 0; i < (*pic).height; i++)
        for(j = 0; j < (*pic).width; j++)
            intInc(&((*pic).pix_array[i][j].B));
}

/*
  Procedure: circleSelect(Picture* pic, int xCenter, int yCenter, int radius)
  Purpose: selects a circle from the robot picture and turns each pixel within
  the circle to the corresponding grayscale value
  Precondition: * memory for *pic allocated
                * xCenter and yCenter are within the dimension of the picture
                * radius is nonnegative
  Postcondition: roughly estimated circle appears on the picture with
                 grayscale values
*/
void circleSelect(Picture* pic, int xCenter, int yCenter, int radius)
{
	int row, col;
	unsigned char gray;
	
    for(row = 0; row < (*pic).height; row++)
    {
        for(col = 0; col < (*pic).width; col++)
        {
            if((xCenter - col) * (xCenter - col) + (yCenter - row) * (yCenter - row) <= radius * radius)
            {
				gray = ((*pic).pix_array[row][col].R * 0.3) + ((*pic).pix_array[row][col].G * 0.59) + ((*pic).pix_array[row][col].B * 0.11);
				(*pic).pix_array[row][col].R = gray;
                (*pic).pix_array[row][col].G = gray;
                (*pic).pix_array[row][col].B = gray;
            }
        }
    }
}

/*
  Procedure: symmetry(Picture* pic)
  Purpose: mirrors the picture
  Precondition: * memory for *pic allocated
  Postcondition: the picture is symmetric along the middle line
*/
void symmetry(Picture* pic)
{
	int row, col;
    int line = ((*pic).width / 2) + 1;
    
    for(row = 0; row < (*pic).height; row++)
    {
        for(col = line; col < (*pic).width; col++)
        {
			if(2 * line - col >= 0 && 2 * line - col <= (*pic).width)
			{
				(*pic).pix_array[row][col].R = (*pic).pix_array[row][2 * line - col].R;
				(*pic).pix_array[row][col].G = (*pic).pix_array[row][2 * line - col].G;
				(*pic).pix_array[row][col].B = (*pic).pix_array[row][2 * line - col].B;
			}
        }
    }
}
