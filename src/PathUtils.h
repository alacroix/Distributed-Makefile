#ifndef DISTRIBUTED_MAKEFILE_PATHUTILS_H
#define DISTRIBUTED_MAKEFILE_PATHUTILS_H

#include <iostream>
#include <boost/filesystem.hpp>

std::string parent_path(const std::string str);

bool file_exists(const std::string str);

std::string get_absolutePath();

#endif //DISTRIBUTED_MAKEFILE_PATHUTILS_H
