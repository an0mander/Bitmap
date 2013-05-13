//---------------------------------------------------- 
// Name: Moyo Williams
// E-mail Address: mow5248@psu.edu
// Class: CMPSC 122, Section 102
// Project # 2
// Date:02/11/2013
// Converting a txt file with bitmap commands into a bitmap file
//----------------------------------------------------
#include <iostream> 
#include <string> 
using namespace std;

#pragma once

#ifndef byte
#define byte unsigned char
#endif

class Image
{
    private:
        int m_width;
        int m_height;
        byte *m_pImage;

    public:
        Image();
        ~Image();

        bool New(int width, int height);
        void Clear(byte red, byte green, byte blue);
        bool SaveFile(string filename);
        void SetPixel(byte red, byte green, byte blue, int x,int y);
        void DrawRectangle(byte red, byte green, byte blue, int x1, int y1, int width,int height);
        void FillRectangle(byte red, byte green, byte blue, int x1, int y1, int width,int height);
        void DrawLine(byte red, byte green, byte blue, int x1, int y1, int x2, int y2);
        
};



