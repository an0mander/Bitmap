//--------------------------------------------
// Scott Gift
// smg180@psu.edu
// 
// Bitmap File
//--------------------------------------------
#include <cstdio>
#include <cmath>
#include "BitmapFile.h"

const int BITMAP_FILE_ID = 19778;


//--------------------------------------------
// The struct for storing the bitmap header
//--------------------------------------------
struct BitmapHeader
{
    //header 1
    unsigned short type;        // Magic number for file
    unsigned int   sizefile;    // Size of file
    unsigned short reserved1;   // Reserved
    unsigned short reserved2;   // ...
    unsigned int   offbits;     // Offset to bitmap data

    //header 2
    unsigned int   sizehead;    // Size of info header
    int            width;       // Width of image
    int            height;      // Height of image
    unsigned short planes;      // Number of color planes
    unsigned short bitcount;    // Number of bits per pixel
    unsigned int   comp;        // Type of compression to use
    unsigned int   sizeimage;   // Size of image data
    int            xppm;        // X pixels per meter
    int            yppm;        // Y pixels per meter
    unsigned int   colorus;     // Number of colors used
    unsigned int   colorim;     // Number of important colors
};


//--------------------------------------------
// These are some usefull functions for reading and writing
// in the LittleEndian format
//--------------------------------------------

unsigned short LittleEndianReadWord(FILE *pFile)
{
    byte b0, b1;

    fread(&b0, 1, 1, pFile);
    fread(&b1, 1, 1, pFile);

    return ((b1 << 8) | b0);
}

unsigned int LittleEndianReadDword(FILE *pFile)
{
    byte b0, b1, b2, b3;

    fread(&b0, 1, 1, pFile);
    fread(&b1, 1, 1, pFile);
    fread(&b2, 1, 1, pFile);
    fread(&b3, 1, 1, pFile);

    return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}

int LittleEndianReadLong(FILE *pFile)
{
    byte b0, b1, b2, b3;

    fread(&b0, 1, 1, pFile);
    fread(&b1, 1, 1, pFile);
    fread(&b2, 1, 1, pFile);
    fread(&b3, 1, 1, pFile);

    return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}

void LittleEndianWriteWord(FILE *pFile, unsigned short w)
{
    byte b0, b1;

    b0 = w & 0xFF;
    b1 = (w >> 8) & 0xFF;

    fwrite(&b0, 1, 1, pFile);
    fwrite(&b1, 1, 1, pFile);
}

void LittleEndianWriteDword(FILE *pFile, unsigned int dw)
{
    byte b0, b1, b2, b3;

    b0 = dw & 0xFF;
    b1 = (dw >> 8) & 0xFF;
    b2 = (dw >> 16) & 0xFF;
    b3 = (dw >> 24) & 0xFF;

    fwrite(&b0, 1, 1, pFile);
    fwrite(&b1, 1, 1, pFile);
    fwrite(&b2, 1, 1, pFile);
    fwrite(&b3, 1, 1, pFile);
}

void LittleEndianWriteLong(FILE *pFile, int  l)
{
    byte b0, b1, b2, b3;

    b0 = l & 0xFF;
    b1 = (l >> 8) & 0xFF;
    b2 = (l >> 16) & 0xFF;
    b3 = (l >> 24) & 0xFF;

    fwrite(&b0, 1, 1, pFile);
    fwrite(&b1, 1, 1, pFile);
    fwrite(&b2, 1, 1, pFile);
    fwrite(&b3, 1, 1, pFile);
}



//--------------------------------------------
// This function will return NULL if there was a problem reading in the data
// The returned image pointer should be deleted when done using it
// pWidth_pix are pHeight_pix are outputs that are set when the file is read in
//--------------------------------------------
byte *BitmapReadFromFile(const char *pFileName, int *pWidth_pix, int *pHeight_pix)
{
    FILE *pFile;
    BitmapHeader header;
    byte *pImageData;


    //----------------------------
    // Open the file for reading binary
    //----------------------------
    pFile = fopen(pFileName, "rb");
    if (pFile == NULL)
    {
      return NULL;
    }


	//----------------------------
	// Read in the header
	//----------------------------
	header.type = LittleEndianReadWord(pFile); // Magic number for file
	if (header.type != BITMAP_FILE_ID)
    {
		return false;
	}

	header.sizefile = LittleEndianReadDword(pFile);  // Size of file
	header.reserved1 = LittleEndianReadWord(pFile);  // Reserved
	header.reserved2 = LittleEndianReadWord(pFile);  // ...
	header.offbits = LittleEndianReadDword(pFile);   // Offset to bitmap data

	header.sizehead = LittleEndianReadDword(pFile);  // Size of info header
	header.width = LittleEndianReadLong(pFile);      // Width of image
	header.height = LittleEndianReadLong(pFile);     // Height of image
	header.planes = LittleEndianReadWord(pFile);     // Number of color planes
	header.bitcount = LittleEndianReadWord(pFile);   // Number of bits per pixel
	header.comp = LittleEndianReadDword(pFile);      // Type of compression to use
	header.sizeimage = LittleEndianReadDword(pFile); // Size of image data
	header.xppm = LittleEndianReadLong(pFile);       // X pixels per meter
	header.yppm = LittleEndianReadLong(pFile);       // Y pixels per meter
	header.colorus = LittleEndianReadDword(pFile);   // Number of colors used
	header.colorim = LittleEndianReadDword(pFile);   // Number of important colors


	//----------------------------
	// Check some information about the file
    //  This function will one reading in 24-bit non-compressed data
	//----------------------------
	if (header.comp)
    {
		// <!> Compression is ON, can not handle this
		return false;
	}

	unsigned palette_size = 0;

    if (header.bitcount != 24)
    {
        // <!> not 24-bits (RGB), can not handle this 
        return false;
	}


	//----------------------------
	// Get memory for the image
    // each color is 24-bit (Red, Green, Blue)
	//----------------------------
	pImageData = new unsigned char[header.width * header.height * 3];
	if (pImageData == NULL)
    {
		// <!> could NOT get memory for new Image
		return false;
	}


	//----------------------------
	// Calulcate the pad at the end of each row
    //
    //  this padding is part of how the bitmap file
    //  stores the data.  If the row is not a multiple
    //  of 4, it pads the data
	//----------------------------
	int pad = header.width % 4;


	//----------------------------
	// Read in the Image
    // note: the bitmap file format stores the image upside down
	//----------------------------
	unsigned int r, c;
    unsigned int rWant; // this is the row flipped because of how the image is stored in the file

	// Skip to the Data
    fseek(pFile, header.offbits, SEEK_SET);

	//read in the data
	for (r=0; r < header.height; r++)
    {
        rWant = header.height - r - 1;

		for (c=0; c < header.width; c++)
        {
            // The file stores the color data as Blue, Green, Red
            // We want it as Red, Green, Blue
            fread(pImageData + rWant*header.width*3 + c*3 + 2, 1, 1, pFile); // Blue
            fread(pImageData + rWant*header.width*3 + c*3 + 1, 1, 1, pFile); // Green
            fread(pImageData + rWant*header.width*3 + c*3 + 0, 1, 1, pFile); // Red
		} //for c

		// padding
        fseek(pFile, pad, SEEK_CUR);

	} // for r


	//----------------------------
	// Done
	//----------------------------
	fclose(pFile);
    if (pWidth_pix != NULL) *pWidth_pix = header.width;
    if (pHeight_pix != NULL) *pHeight_pix = header.height;
	return pImageData;
}


//--------------------------------------------
// This function will write the image to a .bmp file
//--------------------------------------------
bool BitmapWriteToFile(const char *pFileName, unsigned char *pImageData, int width_pix, int height_pix)
{
	FILE *pFile;
    BitmapHeader header;

    //----------------------------
	// Open the file for writting binary
	//----------------------------
    pFile = fopen(pFileName, "wb");
    if (pFile == NULL)
    {
        return NULL;
    }


	//----------------------------
	// Calulcate the pad at the end of each row
    //
    //  this padding is part of how the bitmap file
    //  stores the data.  If the row is not a multiple
    //  of 4, it pads the data
	//----------------------------
	int pad = width_pix % 4;


	//----------------------------
	// Make Header
	//----------------------------
	header.type = BITMAP_FILE_ID;
	header.sizefile = (3.0*width_pix + pad)*height_pix + 54; //54 = 14 for the Header and 40 for the InfoHeader
	header.reserved1 = 0;
	header.reserved2 = 0;
	header.offbits = 54;

	header.sizehead = 40;
	header.width = width_pix;
	header.height = height_pix;
	header.planes = 1;
	header.bitcount = 24;
	header.comp = 0;
	header.sizeimage = (3.0*width_pix + pad)*height_pix;
	header.xppm = 2834;
	header.yppm = 2834;
	header.colorus = 0;
	header.colorim = 0;


	//----------------------------
	// Write the header
	//----------------------------
	LittleEndianWriteWord(pFile, header.type);
	LittleEndianWriteDword(pFile, header.sizefile);
	LittleEndianWriteWord(pFile, header.reserved1);
	LittleEndianWriteWord(pFile, header.reserved2);
	LittleEndianWriteDword(pFile, header.offbits);

	LittleEndianWriteDword(pFile, header.sizehead);
	LittleEndianWriteLong(pFile, header.width);
	LittleEndianWriteLong(pFile, header.height);
	LittleEndianWriteWord(pFile, header.planes);
	LittleEndianWriteWord(pFile, header.bitcount);
	LittleEndianWriteDword(pFile, header.comp);
	LittleEndianWriteDword(pFile, header.sizeimage);
	LittleEndianWriteLong(pFile, header.xppm);
	LittleEndianWriteLong(pFile, header.yppm);
	LittleEndianWriteDword(pFile, header.colorus);
	LittleEndianWriteDword(pFile, header.colorim);


	//----------------------------
	// Write the image data
    // note: the bitmap file format stores the image upside down
	//----------------------------
	int r, c;
	unsigned char n = 0; // this is our variable to write when padding
    unsigned int rWant; // this is the row flipped because of how the image is stored in the file

	for (r=0; r < header.height; r++ )
    {
        rWant = header.height - r - 1;

		for (c=0; c < header.width; c++ )
        {
            // The file stores the color data as Blue, Green, Red
            // pImageData has it as Red, Green, Blue
            fwrite(pImageData + rWant*header.width*3 + c*3 + 2, 1, 1, pFile); // Blue
            fwrite(pImageData + rWant*header.width*3 + c*3 + 1, 1, 1, pFile); // Green
            fwrite(pImageData + rWant*header.width*3 + c*3 + 0, 1, 1, pFile); // Red
		}

		// add the padding at the end of each row
		for (c=0; c < pad; c++)
        {
            fwrite(&n, 1, 1, pFile);
        }

    } // for r


	//----------------------------
	// Done
	//----------------------------
	fclose(pFile);
	return true;
}


