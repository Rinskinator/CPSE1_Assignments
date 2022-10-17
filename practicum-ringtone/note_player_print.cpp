// #include "hwlib.hpp"
#include "note_player_print.hpp"

#include <iostream>
#include <fstream>


void note_player_print::play(const note & n){
    std::cout << "Frequency: " << n.frequency << std::endl;
    std::cout << "Note duration: " << n.duration << std::endl;

    std::ofstream song_file;
    song_file.open("melody.cpp", std::ios_base::app);
    song_file << "\t\tp.play(note{" << n.frequency << ", " << n.duration << "});\n";
    song_file.close();
}


