#include "PicturesPath.h"

vector<fs::path> GetPicturesPath(const fs::path& root, const string& jpgExt, const string& jpegExt)
{
	vector<fs::path> ret;

	if (!fs::exists(root) || !fs::is_directory(root))
		return ret;

	fs::recursive_directory_iterator it(root);
	fs::recursive_directory_iterator endit;

	while (it != endit)
	{
		if (fs::is_regular_file(*it) && (it->path().extension() == jpgExt || it->path().extension() == jpegExt))
		{
			ret.push_back(it->path());
		}
		it++;
	}

	return ret;
}