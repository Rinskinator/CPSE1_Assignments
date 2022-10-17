#include <iostream>
#include <fstream>

#include "compressor.hpp"

int main( void ){	
    // Compress object
    lz_compressor< 4096 > compressor;
    
    // Open original file, check succes
    std::ifstream f1;
    f1.open( "wilhelmus.txt" );
    if( ! f1.is_open()){
        std::cerr << "input file not opened";
        return -1;      
    }
    
    // Open compressed file, check succes
    std::ofstream f2;
    f2.open( "compressed.txt" );
    if( ! f2.is_open()){
        std::cerr << "output file not opened";
        return -1;      
    }

    std::ofstream asm_file;
    asm_file.open("compress.asm");
    asm_file << ".cpu cortex-m0 \n"
            << ".data \n"
            << ".align 2 \n"
            << ".global wilhelmus_string \n"
            << "wilhelmus_string: \n"
            << "    .asciz \"";
        
    compressor.compress( 
        [ &f1 ]()-> int { auto c = f1.get(); return f1.eof() ? '\0' : c; }, // Get char c from text return '\0' if end of file else return char c
        [ &f2, &asm_file ]( char c ){ 
            if (c == '\n'){
                asm_file << "\\n";
            }
            else{
                asm_file.put( c );  // Use char c and put in compressed.txt
            }            
        } // Use char c and put in compressed.txt
    );

}