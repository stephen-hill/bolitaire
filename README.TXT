This software is a work from yzonesoft, released under GNU GPL licence.
The things you are not allowed to do are the following,
1) Removing my credits in any part of the software
2) saying that all this software is yours 
* read GNU GPL licence for more info
* also read the GNU GPL licence faq

   __  __
  \  \/ / 
   \ / /   ___   __     __    __      ___   __  ___  __          __    __   __
    | |      /  |  |  |/  |  |_      \__   |  |  |  |_   |   |  /__\  |__| |_
    |_|    /__  |__|  |   |  |__      __/  |__|  |  |    \/\/   |  |  | \  |__

   yzonesoft@yahoo.com                              Copyright (C) 2005  Yogesh       
   http://yzonesoft.buildtolearn.net

for info about compiling this software read readme.txt

Copyright (C) 2005  Yogesh
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

----------------------------------------------------------------------------------

Compiling Bolitaire
===================

Bolitaire depends on the following libraries

   PROGRAM               LICENCE INFO
           
1) allegro               Giftware  
2) allegro mp3           LGPL
3) jpg allegro           zlib/libpng
4) alrand                LGPL

In order to compile Bolitaire you need to install all the above libraries, the happy 
news is they are also free.

Note: in allegro mp3 almp3.c source you need to add this function and compile

    void make_custom_changes(ALMP3_MP3STREAM *mp3, int bytes)
    {
      mp3->current_frame = bytes / mp3->framebytes;
    }
    
    otherwise bolitaire wont compile

There is no make file for Bolitaire, which means you have to compile it by hand.


Compiling bolitaire under linux
===============================
Install all other depended libraries[modified almp3]. Now to compile bolitaire issues this command from terminal,

gcc driver.c main.c almp3.c browser.c function.c function2.c function3.c function4.c -o bolitaire `allegro-config --shared` -ljpgal -lalmp3 -lalrand

where bolitaire is the executable name.


Compiling bolitaire under DOS
===============================
Install DJGPP, now install all other depended libraries[modified almp3]. Now to compile bolitaire issues this command from command prompt,

gcc main.c almp3.c browser.c functi~3.c functi~2.c functi~1.c function.c driver.c -o bolitaire.exe -ljpgal -lalmp3 -lalleg -lalrand

use upx.exe to reduce the size of the executable.

Compiling bolitaire under windows
==================================
Boltaire was developed using Dev-cpp IDE, Get the latest from www.bloodshed.net. when I
used version 4.9.9.2 was latest, now install all the required libraries. 
compiling using Dev-cpp
-----------------------
1) create new console project, import all the source files
2) In project options/parameters/linker, order the libs in this order
   a) libalmp3.a
   b) libjpgal.a
   c) liballeg.a
   d) libalrand.a
3) Execute/compile and run or just press F9 to compile and execute bolitaire.

compiling from command prompt
-----------------------------
issue this command from the source directory to compile bolitaire
gcc main.c almp3.c browser.c functi~3.c functi~2.c functi~1.c function.c driver.c -o bolitaire.exe -ljpgal -lalmp3 -lalleg -lalrand


Compiling bolitaire under BeOS
===============================
Install BeOS developement packages, then install all other required libraries, some libraries makefile script wont work, In case compile them by hand like this

=to compile almp3=
gcc -c -Wall -O2 -march=pentium -fomit-frame-pointer -finline-functions -ffast-math -Idecoder -Iinclude decoder/layer2.c -o obj/djgpp/static/layer2.o
gcc -c -Wall -O2 -march=pentium -fomit-frame-pointer -finline-functions -ffast-math -Idecoder -Iinclude decoder/layer3.c -o obj/djgpp/static/layer3.o
gcc -c -Wall -O2 -march=pentium -fomit-frame-pointer -finline-functions -ffast-math -Idecoder -Iinclude decoder/interface.c -o obj/djgpp/static/interface.o
gcc -c -Wall -O2 -march=pentium -fomit-frame-pointer -finline-functions -ffast-math -Idecoder -Iinclude decoder/decode_i386.c -o obj/djgpp/static/decode_i386.o
gcc -c -Wall -O2 -march=pentium -fomit-frame-pointer -finline-functions -ffast-math -Idecoder -Iinclude decoder/dct64_i386.c -o obj/djgpp/static/dct64_i386.o
gcc -c -Wall -O2 -march=pentium -fomit-frame-pointer -finline-functions -ffast-math -Idecoder -Iinclude decoder/common.c -o obj/djgpp/static/common.o
gcc -c -Wall -O2 -march=pentium -fomit-frame-pointer -finline-functions -ffast-math -Idecoder -Iinclude decoder/tabinit.c -o obj/djgpp/static/tabinit.o
gcc -c -Wall -O2 -march=pentium -fomit-frame-pointer -finline-functions -ffast-math -Idecoder -Iinclude src/almp3.c -o obj/djgpp/static/almp3.o
ar rs lib/djgpp/libalmp3.a obj/djgpp/static/layer2.o obj/djgpp/static/layer3.o obj/djgpp/static/interface.o obj/djgpp/static/decode_i386.o obj/djgpp/static/dct64_i386.o obj/djgpp/static/common.o obj/djgpp/static/tabinit.o obj/djgpp/static/almp3.o

dont care that the directory is djgpp, it s not a problem.
then copy the include files to /beos/develop/headers and libalmp3.a /beos/develop/lib/x86

=to compile alrand=
$ gcc -Wall -W -O2 -o alrand.o -c alrand.c
$ gcc -Wall -W -O2 -o mersenne.o -c mersenne.c
$ gcc -Wall -W -O2 -o lcg.o -c lcg.c
$ ar cr libalrand.a alrand.o mersenne.o lcg.o

then copy the include files to /beos/develop/headers/alrand and libalrand.a /beos/develop/lib/x86

=to compile jpgalleg=
follow the instructions in the library to install, it may stuck when compiling example reaches, but required libjpgal.a has been generated already, so copy the include files to /beos/develop/headers and libjpgal.a /beos/develop/lib/x86 


after installing all libraries successfully compile bolitairefrom a terminal issuing the following command,
gcc main.c driver.c browser.c almp3.c function.c function2.c function3.c function4.c -o Bolitaire `allegro-config --shared` -ljpgal -lalmp3 -lalrand

Note: the information above may not be sufficient or if you come across any trouble during compiling visit 
http:\\yzonesoft.buildtolearn.net or www.yzonesoft.tk forum to post your doubts.


Note: you are expected to update and release the text files(faq.txt, credits.txt, common bug report.txt, read1st.txt, faq.txt, todo.txt release_notes.txt) along with the source and binary release version.
