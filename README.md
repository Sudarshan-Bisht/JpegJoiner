# JpegJoiner
Joins multiple jpegs vertically.
Description: This program “CreateTextureAtlas” reads all the jpeg files from a given folder, then using libjpeg convert all the jpegs into uncompressed format (RGB) one by one. Have all the uncompressed data into a buffer and then finally compress this into jpeg using again libjpeg. This solution expects same resolution for all the pictures, otherwise output would be corrupt. Output jpeg picture follow a certain pattern where pictures are stitched downward. I have not tested that what is the maximum number of input files we can provide.

Building Instructions on Windows:
1. First build Boost libraries.
2. Then build libjpeg.
3. Go to CreateTextureAtlas folder, open CreateTextureAtlas.sln in Visual Studio and build the solution, provide include path and library path for Boost and libjpeg respectively in VS. The output executable will be located in CreateTextureAtlas\Release folder

Building Instructions on Linux:
1. First build Boost libraries. (Use sudo apt-get install command)
2. Then build libjpeg. (Use sudo apt-get install command)
3. Open terminal, go to CreateTextureAtlas folder, type “make”, this will execute Makfile and output executable will be located in CreateTextureAtlas/Release_Linux folder 

Testing:
1. On Windows, open command prompt, go to CreateTextureAtlas\Release, and type following command;  CreateTextureAtlas.exe inputFolderPath
2. On Linux, open Terminal, go to CreateTextureAtlas/Release_Linux, and type following command; ./CreateTextureAtlas_Linux inputFolderPath
3.Output picture i.e. AtlasTextureOutput.jpg will be saved in the same folder.
4.Output metadata i.e. AtlasTextureMetadata.txt will be saved in the same folder

