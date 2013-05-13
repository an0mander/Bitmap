//---------------------------------------------------- 
// Name: Moyo Williams
// E-mail Address: mow5248@psu.edu
// Class: CMPSC 122, Section 102
// Project # 2
// Date:02/11/2013
// Converting a txt file with bitmap commands into a bitmap file
//----------------------------------------------------

#include <iostream>
#include "image.h"
#include "BitmapFile.h"

using namespace std;

Image::Image(void)
{
    m_width = 0;
    m_height =0;
    m_pImage = NULL;
}

Image::~Image(void)
{

}

bool Image::New(int x, int y)//get memory for the image
{
  m_width = x;
	m_height = y;
	m_pImage = new byte[ x * y * 3];
	return true;
}

//******************************************************
//sets the image to the colors found in the color list *             
//******************************************************


void Image::Clear(byte R, byte G, byte B)//
{   
	for (int y = 0; y < m_height; y++)
	{
		for (int x= 0; x < m_width; x++)
		{
            SetPixel(R, G, B, x, y);
		}
	}
}


//*******************************************
//save the file as a bitmap                 *
//*******************************************

bool Image::SaveFile(string filename)
{
	return BitmapWriteToFile(filename.c_str(), m_pImage, m_width, m_height);
}


//*******************************************
//Sets a pixel on the bitmap image          *
//*******************************************

void Image::SetPixel(byte red, byte green, byte blue, int x,int y)
{
    if (m_pImage == NULL) return;
    if (x < 0) return;
    if (y < 0) return;
    if (x >= m_width) return;
    if(y >= m_height) return;
 
	m_pImage[y*m_width * 3 + x*3 + 0] = red;
	m_pImage[y*m_width * 3 + x*3 + 1] = green;
	m_pImage[y*m_width * 3 + x*3 + 2] = blue;

}

//******************************************************
//Draw a rectangle                                     *             
//******************************************************

void Image::DrawRectangle(byte red, byte green, byte blue, int x1, int y1, int width,int height)
{


}

//******************************************************
//Fills arectangle on the bitmapimage                  *             
//******************************************************


void Image::FillRectangle(byte red, byte green, byte blue, int x1, int y1, int width,int height)
{
    for (int y = y1; y < y1+height; y++)
	{
		for (int x= x1; x < x1+width; x++)
        {
            SetPixel(red, green, blue, x, y);
        }
    }


}

//******************************************************
//Draws a line on the bitmap image                     *             
//******************************************************

void Image::DrawLine(byte red, byte green, byte blue, int x1, int y1, int x2, int y2)
{

int x,y;
if  (x1 == x2)
{   
    for (y = y1;  y <=y2; y++)
        SetPixel(red, blue, green, x1, y1);

    return;

}
        

if  (y1 == y2)
{   
    for (x = x2;  x <= x2; x++)
        SetPixel(red, blue, green, x1, y1);
    return;

}


}
