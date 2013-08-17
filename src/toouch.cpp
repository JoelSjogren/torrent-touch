/**********************************
*  toouch.cpp                     *
*                                 *
*  by Joel Sjögren                *
**********************************/
#define BOOST_FILESYSTEM_VERSION 2
#include "fileman.h"
#include "args.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <libtorrent/entry.hpp>
#include <libtorrent/bencode.hpp>
#include <libtorrent/torrent_info.hpp>
#include <libtorrent/lazy_entry.hpp>
#include <boost/filesystem/operations.hpp>
#include <string>
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::vector;
using std::ifstream;
using std::ios_base;
using boost::filesystem::file_size;
using libtorrent::lazy_entry;
using libtorrent::torrent_info;
void touchAll(string in, string out);
void errorExit(const char* msg);
int main(int argc, char* argv[]) {
    string in, out;
    parseArgs(argc, argv, in, out);
    cout << "in: `" << in << "'" << endl;
    cout << "out: `" << out << "'" << endl;
    touchAll(in, out);
    FileMan::dig(out);
}
void errorExit(const char* msg) {
    cerr << "E: " << msg << endl;
    exit(1);
}
void touchAll(string in, string out) {
    int size = file_size(in);
    vector<char> buf(size);
    ifstream(in.c_str(), ios_base::binary).read(&buf[0], size);
    lazy_entry e;
    int ret = lazy_bdecode(&buf[0], &buf[0] + buf.size(), e);
    if (ret != 0) errorExit("invalid bencoding");
    torrent_info t(e);
    int index = 0;
    for (torrent_info::file_iterator i = t.begin_files();
         i != t.end_files(); ++i, ++index) {
//        std::cout << i->path.string() << std::endl;
        FileMan::touch(out + i->path.string());
    }
}








