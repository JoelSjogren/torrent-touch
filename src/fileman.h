#pragma once
#include <string>
namespace FileMan {
    void touch(std::string file);
    bool exists(std::string file);
    void dig(std::string to);
//    bool isDirectory(std::string file);
//    void markDirectory(std::string file);
}
