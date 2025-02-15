#pragma once

#include <string>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

bool isEnoentPrint(const std::string &path);
bool isEaccessOrEpermPrint(const std::string &path);
bool isEnotdirPrint(const std::string &path);
bool isDirEaccessPrint(const std::string &path);
