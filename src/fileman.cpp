#include "fileman.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <stdexcept>
#include <cerrno>   
using std::runtime_error;
using std::ofstream;
using std::string;
void FileMan::touch(string file) {
    if (!exists(file)) {
        dig(file);
        ofstream of(file.c_str());
    }
}
bool FileMan::exists(string file) {
    struct stat buf;
    int ret = stat(file.c_str(), &buf);
    if (ret && errno == ENOENT) return false;
    return true;
}
void FileMan::dig(string to) {
    int lookhere = 0;
    int foundhere;
    while ((foundhere = to.find("/", lookhere)) != string::npos) {
	    string part = to.substr(0, foundhere + 1);
	    int ret = mkdir(part.c_str(), S_IRWXU | S_IRWXG |
					    S_IROTH | S_IXOTH);
	    if (ret && errno != EEXIST)
		    throw runtime_error("Unable to create directory: " +
		                        part);
	    lookhere = foundhere + 1;
    }
}
