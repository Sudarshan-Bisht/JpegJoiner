#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <jpeglib.h>
#include <boost/filesystem.hpp>

/**
* ReadTextureAtlas Reads from a jpeg file on disk specified by filename and saves into the
* buffer in an uncompressed format.
*
* \returns positive integer if successful, -1 otherwise
* \param *filename char string specifying the file name to read from
* \param file stream where metadata to be saved 
* \param number of pictures in the folder
*/
int ReadTextureAtlas(const char *filename, std::ofstream &metadataFile, int pictureCount);

/**
* WriteTextureAtlas Writes the raw image data stored in the buffer
* to a jpeg image with default compression and smoothing options in the file
* specified by *filename.
*
* \returns positive integer if successful, -1 otherwise
* \param *filename char string specifying the file name to save to
* \param file stream where metadata to be saved
* \param number of pictures in the folder
*
*/
int WriteTextureAtlas(const char *filename, std::ofstream &metadataFile,int pictureCount);
