#pragma once

#include <boost/filesystem.hpp>

using namespace std;
typedef std::vector<std::string> stringvec;
namespace fs = ::boost::filesystem;

/**
* GetPicturesPath Provides the filenames with path of all files that have the specified extension
// in the specified directory and all subdirectories.
*
* \param folder path
* \param .jpg extention 
* \param .jpeg extension
*/
vector<fs::path> GetPicturesPath(const fs::path& root, const string& jpgExt, const string& jpegExt);
