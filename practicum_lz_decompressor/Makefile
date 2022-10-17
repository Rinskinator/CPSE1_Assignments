#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################


main_compressed.exe : main_compressed.o
	g++ main_compressed.o -o main_compressed.exe

compress.asm : main_compressed.exe wilhelmus.txt 
	.\main_compressed.exe

main_compressed.o : main_compressed.cpp compressor.hpp
	g++ -c main_compressed.cpp -o main_compressed.o

# source files in this project (main.cpp is automatically assumed)
SOURCES := decompressor.asm compress.asm

# header files in this project
HEADERS := match.hpp compressor.hpp decompressor.hpp

# other places to look for files for this project
SEARCH  := ../07-library

# set REATIVE to the next higher directory 
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.due