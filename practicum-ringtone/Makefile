#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

include maakfile
# melody.cpp : generator.exe
# 	./generator.exe

# source & header files in this project (main.cpp is automatically assumed)

HEADERS += note.hpp
HEADERS += note_player.hpp
HEADERS += fur_elise.hpp

HEADERS += melody.hpp

# HEADERS += note_player_print.hpp
# SOURCES += note_player_print.cpp

HEADERS += note_player_gpio.hpp
SOURCES += note_player_gpio.cpp

SOURCES += melody.cpp

# HEADERS += rtttl_player.hpp
# SOURCES += rtttl_player.cpp

# other places to look for files for this project
SEARCH  := 

# set REATIVE to the next higher directory 
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.due

