#include "fs.hpp"
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

bool isEnoentPrint(const std::string &path)
{
	if (access(path.c_str(), F_OK) != 0)
	{
		std::cerr << "Error: " << path << ": No such file or directory" << std::endl;
		return (true);
	}
	return (false);
}

bool isEaccessOrEpermPrint(const std::string &path)
{
	struct stat info;
	if (stat(path.c_str(), &info) != 0)
	{
		if (access(path.c_str(), R_OK) != 0)
		{
			std::cerr << "Error :" << path << ": Permission denied" << std::endl;
			return (true);
		}
		std::cerr << "Error :" << path << ": Operation not permitted" << std::endl;
		return (true);
	}
	return (false);
}

bool isEnotdirPrint(const std::string &path)
{
	struct stat info;
	stat(path.c_str(), &info);
	if (!S_ISDIR(info.st_mode))
	{
		std::cerr << "Error :" << path << ": Not a directory" << std::endl;
		return (true);
	}
	return (false);
}

bool isDirEaccessPrint(const std::string &path)
{
	DIR *dir = opendir(path.c_str());
	if (dir == NULL)
	{
		std::cerr << "Error :" << path << ": Permission denied" << std::endl;
		return (true);
	}
	closedir(dir);
	return (false);
}
