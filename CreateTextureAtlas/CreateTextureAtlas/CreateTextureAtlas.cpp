#include "PicturesPath.h"
#include "PictureOperation.h"


int main(int argc, char *argv[])
{
	const char *outputPicturefile = "AtlasTextureOutput.jpg";
	const char *outputMetadataFile = "AtlasTextureMetadata.txt";

	std::vector<fs::path> filePathList;
	if (argc > 1)
	{
		filePathList = GetPicturesPath(argv[1], ".jpg", ".jpeg");
	}
	else
	{
		cout << "Please provide valid folder path !!!";
		return 0;
	}

	ofstream metadataFile;
	int pictureCount = filePathList.size();
	if (pictureCount > 0)
	{
		metadataFile.open(outputMetadataFile);

		for (int i = 0; i < pictureCount; i++)
		{
			if (ReadTextureAtlas(&(filePathList.at(i).string())[0], metadataFile, pictureCount) <= 0)
			{
				cout << "Issue with reading input picures.";
				return 0;
			}
		}

		if (WriteTextureAtlas(outputPicturefile, metadataFile, pictureCount) <= 0)
		{
			cout << "Issue with writing output picture.";
			return -1;
		}
	}
	
	return 0;
}
