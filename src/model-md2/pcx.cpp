//
//	pcx.cpp - source file / freeware
//
//	David Henry - tfc_duke@hotmail.com
//


#include	<fstream>
#include	"pcx.h"



// --------------------------------------------------
// LoadFilePCX() - load a Zsoft PCX image [.pcx]
//
// parameters :
//    - filename [in]  : image source file
//    - pixels	 [out] : 32 bits rgba image data
//    - width    [out] : image width in pixels
//    - height   [out] : image height in pixels
//    - flipvert [in]  : flip vertically
//
// return value :
//    - -1 : no image data
//    -  0 : failure
//    -  1 : success
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// accepted image formats :
//     # RLE 8 bits / version 5
// --------------------------------------------------

int LoadFilePCX( const char *filename, unsigned char **pixels, int *width, int *height, bool flipvert )
{
	std::ifstream		file;			// file stream
	PCXHEADER			*header;		// header PCX
	unsigned char		*data;			// uncompressed paletted image data
	unsigned char		*ptr;			// pointer to pixels data
	unsigned char		c;				// temporary variable
	char				*buffer;		// buffer storing the entire file
	int					idx = 0;		// temporary variable
	int					numRepeat;		// temporary variable
	int					i, j;			// temporary variables



	/////////////////////////////////////////////////////
	// read the entire file in the buffer

	file.open( filename, std::ios::in | std::ios::binary );

	if( file.fail() )
		return 0;

	file.seekg( 0, std::ios::end );
	long flen = file.tellg();
	file.seekg( 0, std::ios::beg );

	buffer = new char[ flen + 1 ];
	file.read( buffer, flen );
	char *pBuff = buffer;

	file.close();

	/////////////////////////////////////////////////////

	header = (PCXHEADER *)pBuff;

	if( (header->manufacturer	!= 10)	||
		(header->version		!= 5)	||
		(header->encoding		!= 1)	||
		(header->bitsPerPixel	!= 8) )
	{
		return 0;
	}


	header->width	= header->width	 - header->x + 1;
	header->height	= header->height - header->y + 1;


	if( width )
		*width = header->width;

	if( height )
		*height = header->height;

	if( !pixels )
	{
		delete [] buffer;
		return (-1);
	}


	// allocate memory for image data
	data = new unsigned char[ header->width * header->height ];

	pBuff = (char *)&buffer[ 128 ];

	// uncode compressed image (RLE)
	while( idx < (header->width * header->height) )
	{
		if( (c = *(pBuff++)) > 0xbf )
		{
			numRepeat = 0x3f & c;
			c = *(pBuff++);

			for( i = 0; i < numRepeat; i++ )
				data[ idx++ ] = c;
		}
		else
			data[ idx++ ] = c;
	}


	// the palette is located at the 769th last byte of the file
	pBuff = &buffer[ flen - 769 ];

	// verify the palette; first char must be equal to 12
	if( *(pBuff++) != 12 )
	{
		delete [] buffer;
		delete [] data;
		return 0;
	}

	// read the palette
	header->palette = (unsigned char *)pBuff;


	// allocate memory for 32 bits pixel data
	*pixels = new unsigned char[ header->width * header->height * 4 ];

	ptr = &(*pixels)[0];

	// convert from paletted to 32 bits rgba pixels
	for( j = header->height - 1; j > 0; j-- )
	{
		if( flipvert )
			ptr = &(*pixels)[ j * header->width * 4 ];

		for( i = 0; i < header->width; i++, ptr += 4 )
		{
			int color = 3 * data[ j * header->width + i ];

			ptr[0] = (unsigned char)header->palette[ color + 0 ];
			ptr[1] = (unsigned char)header->palette[ color + 1 ];
			ptr[2] = (unsigned char)header->palette[ color + 2 ];
			ptr[3] = (unsigned char)255;
		}
	}


	// free memory
	delete [] data;
	delete [] buffer;

	// return success
	return 1;
}
