## NAME ##
toouch - replicate torrent file lists

## DESCRIPTION ##
The purpose of this text-based application is to do what a torrent client would: create a directory and fill it with files specified by a torrent or magnet link. This application, however, only touches the files. Thus, every file has size 0.

## COMPILE & INSTALL
Packages needed:

 - scons
 - libtorrent-rasterbar-dev

To compile, run:

    $ scons

To install, copy the generated executable to a directory in your $PATH. I suggest /usr/local/bin:

    # cp toouch /usr/local/bin
