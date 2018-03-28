#include "PictureOperation.h"

/* we will be using this uninitialized pointer later to store raw, uncompressd image */
unsigned char *raw_image = NULL;
unsigned long long location = 0;
long x_cordinate = 0;
long y_cordinate = 0;

/* dimensions of the image we want to write */
int WIDTH = 0;
int HEIGHT = 0;
int BYTES_PER_PIXEL = 3; /* or 1 for GRACYSCALE images */

void freeAllocatedBuffer(unsigned char *buffer)
{
	// free allocated buffer. 
	if (buffer != NULL)
	{
		free(buffer);
		buffer = NULL;
	}
}

int ReadTextureAtlas(const char *filename, std::ofstream &metadataFile, int pictureCount)
{
	try
	{
		/* these are standard libjpeg structures for reading(decompression) */
		struct jpeg_decompress_struct cinfo;
		struct jpeg_error_mgr jerr;
		/* libjpeg data structure for storing one row, that is, scanline of an image */
		JSAMPROW row_pointer[1];

		FILE *infile = fopen(filename, "rb");

		int i = 0;

		if (!infile)
		{
			printf("Error opening jpeg file %s\n!", filename);
			return -1;
		}
		/* here we set up the standard libjpeg error handler */
		cinfo.err = jpeg_std_error(&jerr);
		/* setup decompression process and source, then read JPEG header */
		jpeg_create_decompress(&cinfo);
		/* this makes the library read from infile */
		jpeg_stdio_src(&cinfo, infile);
		/* reading the image header which contains image information */
		jpeg_read_header(&cinfo, TRUE);

		WIDTH = cinfo.image_width;
		HEIGHT = cinfo.image_height;

		metadataFile << filename << "\t" << "\t";
		metadataFile << x_cordinate << "\t";
		metadataFile << y_cordinate << "\t";
		metadataFile << WIDTH << "\t";
		metadataFile << HEIGHT << "\t";
		metadataFile <<"\n";

		x_cordinate += 0;
		y_cordinate -= HEIGHT;

		/* Start decompression jpeg here */
		jpeg_start_decompress(&cinfo);

		/* allocate memory to hold the uncompressed image */
		if (raw_image == NULL)
		{
			raw_image = (unsigned char*)malloc(cinfo.output_width*cinfo.output_height*cinfo.num_components*pictureCount);
		}
		/* now actually read the jpeg into the raw buffer */
		row_pointer[0] = (unsigned char *)malloc(cinfo.output_width*cinfo.num_components);
		/* read one scan line at a time */
		while (cinfo.output_scanline < cinfo.image_height)
		{
			jpeg_read_scanlines(&cinfo, row_pointer, 1);
			for (i = 0; i<cinfo.image_width*cinfo.num_components; i++)
				raw_image[location++] = row_pointer[0][i];
		}
		/* wrap up decompression, destroy objects, free pointers and close open files */
		jpeg_finish_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);
		free(row_pointer[0]);
		fclose(infile);
	}
	catch (const std::exception&)
	{
		freeAllocatedBuffer(raw_image);
		return 0;
	}

	return 1;
}


int WriteTextureAtlas(const char *filename, std::ofstream &metadataFile,int pictureCount)
{
	try
	{
		struct jpeg_compress_struct cinfo;
		struct jpeg_error_mgr jerr;

		/* this is a pointer to one row of image data */
		JSAMPROW row_pointer[1];
		FILE *outfile = fopen(filename, "wb");

		if (!outfile)
		{
			printf("Error opening output jpeg file %s\n!", filename);
			return -1;
		}
		cinfo.err = jpeg_std_error(&jerr);
		jpeg_create_compress(&cinfo);
		jpeg_stdio_dest(&cinfo, outfile);

		/* Setting the parameters of the output file here */
		cinfo.image_width = WIDTH;
		cinfo.image_height = HEIGHT*pictureCount;
		cinfo.input_components = BYTES_PER_PIXEL;
		cinfo.in_color_space = JCS_RGB;
		/* default compression parameters, we shouldn't be worried about these */

		jpeg_set_defaults(&cinfo);
		cinfo.num_components = 3;
		//cinfo.data_precision = 4;
		cinfo.dct_method = JDCT_FLOAT;
		jpeg_set_quality(&cinfo, 15, TRUE);
		/* Now do the compression .. */
		jpeg_start_compress(&cinfo, TRUE);
		/* like reading a file, this time write one row at a time */
		while (cinfo.next_scanline < cinfo.image_height)
		{
			row_pointer[0] = &raw_image[cinfo.next_scanline * cinfo.image_width * cinfo.input_components];
			jpeg_write_scanlines(&cinfo, row_pointer, 1);
		}
		/* similar to read file, clean up after we're done compressing */
		jpeg_finish_compress(&cinfo);
		jpeg_destroy_compress(&cinfo);
		fclose(outfile);
		metadataFile.close();

		freeAllocatedBuffer(raw_image);

	}
	catch (const std::exception&)
	{
		freeAllocatedBuffer(raw_image);
		return 0;
	}
		
	return 1;
}

