#ifndef _PRINT_NOTE_HPP
#define _PRINT_NOTE_HPP

#include "note_player.hpp"


class note_player_print : public note_player { 

public:
    note_player_print(){}

    void play( const note & n ) override;
};

#endif