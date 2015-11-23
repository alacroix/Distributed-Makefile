#include "PathUtils.h"

std::string parent_path(const std::string str) {
    size_t found;
    found = str.find_last_of("/\\");
    return str.substr(0,found);
}

bool file_exists(const std::string str) {
    return access(str.c_str(), F_OK ) != -1;
}