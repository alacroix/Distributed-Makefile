#include "PathUtils.h"

std::string parent_path(const std::string str) {
    size_t found;
    found = str.find_last_of("/\\");
    return str.substr(0,found);
}
