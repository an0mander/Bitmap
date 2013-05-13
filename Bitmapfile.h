//--------------------------------------------
// Scott Gift
// smg180@psu.edu
// 
// Bitmap File Header
//
// Note: this will only read and write Bitmaps of 24 bits
//--------------------------------------------
#pragma once

// define a byte as an unsigned character
#ifndef byte
#define byte unsigned char
#endif

// This function will return NULL if there was a problem reading in the data
// The returned image pointer should be deleted when done using it
// pWidth_pix are pHeight_pix are outputs that are set when the file is read in
// Color data nwill be RGB (24-bits)
byte *BitmapReadFromFile(const char *pFileName, int *pWidth_pix, int *pHeight_pix);

// This function will write the image to a .bmp file
// pImageData needs to be 24-bit image of size width and height given
// Color data needs to be RGB (24-bits)
bool BitmapWriteToFile(const char *pFileName, byte *pImageData, int width_pix, int height_pix);


