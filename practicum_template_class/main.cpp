#define CATCH_CONFIG_MAIN
#include "C:\Catch2-2.13.6\Catch2-2.13.6\single_include\catch2\catch.hpp"

#include <iostream>
#include <array>

#include "set_class.hpp"


/// Test cases T=int, N=10 ///

TEST_CASE("Print set elements function <int, 10>"){
    set<int, 10> t; 
    std::stringstream s;
    s << t;
    REQUIRE (s.str() == "");
}

TEST_CASE("Addition single set element <int, 10>"){
    set<int, 10> t;
    t.add(4);
    std::stringstream s;
    s << t;
    REQUIRE(s.str() == "4 ");
}

TEST_CASE("Addition negative set element <int, 10>"){
    set<int, 10> t;
    t.add(-2);
    std::stringstream s;
    s << t;
    REQUIRE(s.str() == "-2 ");
}

TEST_CASE("Addition set duplicates <int, 10>"){ 
    set<int, 10> t;
    t.add(2);
    t.add(2);
    std::stringstream s;
    s << t;
    REQUIRE(s.str() == "2 ");
}

TEST_CASE("Addition set element (fill) <int, 10>"){
    set<int, 10> t;
    for(unsigned int i=0; i<10; i++){
        t.add(i);
    }
    std::stringstream s;
    s << t;
    REQUIRE(s.str() == "0 1 2 3 4 5 6 7 8 9 ");
}

TEST_CASE("Set addition exceeding limit <int, 10>"){
    set<int, 10> t;
    for(unsigned int i=0; i<11; i++){
        t.add(i);
    }
    std::stringstream s;
    s << t;
    REQUIRE(s.str() == "0 1 2 3 4 5 6 7 8 9 ");
}

TEST_CASE("Contains value is false <int, 10>"){
    set<int, 10> t;
    bool x = t.bool_contains(4);
    REQUIRE(x == 0);
}

TEST_CASE("Contains value is true <int, 10>"){
    set<int, 10> t;
    t.add(4);
    bool x = t.bool_contains(4);
    REQUIRE(x == 1);
}

TEST_CASE("Contains zero <int, 10>"){
    set<int, 10> t;
    bool x = t.bool_contains(0);
    REQUIRE(x == 0);
}

TEST_CASE("Remove value <int, 10>"){
    set<int, 10> t;
    for(unsigned int i=0; i<10; i++){
        t.add(i);
    }
    t.remove(5);            // In array
    t.remove(11);           // Not in array
    std::stringstream s;
    s << t;
    REQUIRE (s.str() == "0 1 2 3 4 6 7 8 9 ");
}

TEST_CASE("Maximum value <int, 10>"){
    set<int, 10> t;
    for(unsigned int i=0; i<10; i++){
        t.add(i);
    }
    int s = t.max();
    REQUIRE(s == 9);
}

/// Test cases T=float, N=7 ///

TEST_CASE("Addition set element (fill set) <float, 7>"){ 
    set<float, 7> t;        
    float loop_var = 0.0;
    for(unsigned int i=0; i<7; i++){
        t.add(loop_var);
        loop_var += 0.1;
    }

    std::stringstream s;
    s << t;
    REQUIRE(s.str() == "0 0.1 0.2 0.3 0.4 0.5 0.6 ");
}

TEST_CASE("Addition exceeding set limit (fill set) <float, 7>"){ 
    set<float, 7> t;        
    float loop_var = 0.0;
    for(unsigned int i=0; i<7; i++){
        t.add(loop_var);
        loop_var += 0.1;
    }

    std::stringstream s;
    s << t;
    REQUIRE(s.str() == "0 0.1 0.2 0.3 0.4 0.5 0.6 ");
}

TEST_CASE("Addition negative element"){
    set<float, 7> t;
    t.add(-0.5);
    std::stringstream s;
    s << t;
    REQUIRE(s.str() == "-0.5 ");
}

TEST_CASE("Remove value <float, 7>"){
    set<float, 7> t;
    float loop_var = 0.0;
    for(unsigned int i=0; i<7; i++){
        t.add(loop_var);
        loop_var += 0.1;
    }
    t.remove(0.5);
    std::stringstream s;
    s << t;
    REQUIRE (s.str() == "0 0.1 0.2 0.3 0.4 0.6 ");
}

TEST_CASE("Contains value is false <float, 7>"){
    set<float, 7> t;
    bool x = t.bool_contains(0.4);
    REQUIRE(x == 0);
}

TEST_CASE("Maximum value <float, 7>"){
    set<float, 7> t;
    for(float i=0.0; i<0.7; i+= 0.1){
        t.add(i);
    }
    float s = t.max();
    REQUIRE(s == 0.6f);
}

/// Test cases T=char, N=5 ///

TEST_CASE("Addition set element (fill) with duplicates <char, 5>"){ // Dubbele chars gaan nog niet goed.
    set<char, 5> t;

    t.add('G');
    t.add('e');
    t.add('r');
    t.add('t');
    t.add('t');

    std::stringstream s;
    s << t;
    REQUIRE(s.str() == "G e r t ");
}

TEST_CASE("Addition set element exceeding limit <char, 5>"){ // Size overschrijden gaat nog niet goed
    set<char, 5> t;

    t.add('G');
    t.add('e');
    t.add('r');
    t.add('t');
    t.add('!');
    t.add(':');

    std::stringstream s;
    s << t;
    REQUIRE(s.str() == "G e r t ! ");
}

TEST_CASE("Remove value <char, 5>"){
    set<char, 5> t;
    
    t.add('G');
    t.add('e');
    t.add('r');
    t.add('t');
    t.add('!');

    t.remove('!');
    std::stringstream s;
    s << t;
    REQUIRE (s.str() == "G e r t ");
}

TEST_CASE("Contains value is false <char, 5>"){
    set<char, 5> t;
    bool x = t.bool_contains('!');
    REQUIRE(x == 0);
}

TEST_CASE("Maximum value <char, 5>"){
    set<char, 5> t;

    t.add('G');
    t.add('e');
    t.add('r');
    t.add('t');
    t.add('!');

    char s = t.max();
    REQUIRE(s == 't');
}

// /// Test cases 5.4 //

TEST_CASE("Addition (std::array<<char, 3>, 5>) "){
    set<std::array<char, 3>, 5> t;
    
    t.add({'H', 'o', 'i'});
    t.add({'M', '&', 'M'});
    t.add({'U', 'T', 'P'});
    t.add({'s', 'e', 't'});
    t.add({'a', 'd', 'd'});

    std::stringstream s;
    s << t;
    REQUIRE(s.str() == "H o i  M & M  U T P  s e t  a d d  ") ;
}


TEST_CASE("Removing (std::array<<char, 3>, 5>) "){
    set<std::array<char, 3>, 5> t;
    
    t.add({'H', 'o', 'i'});
    t.add({'M', '&', 'M'});
    t.add({'U', 'T', 'P'});
    t.add({'s', 'e', 't'});
    t.add({'a', 'd', 'd'});

    t.remove({'H', 'o', 'i'});

    std::stringstream s;
    s << t;
    REQUIRE(s.str() == "M & M  U T P  s e t  a d d  ") ;
}


TEST_CASE("Contains value is true (std::array<<char, 3>, 5>)"){
    set<std::array<char, 3>, 5> t;
    t.add({'H', 'o', 'i'});
    bool x = t.bool_contains({'H', 'o', 'i'});
    REQUIRE(x == 1);
}

TEST_CASE("Maximum value double array (std::array<<char, 3>, 5>)"){
    set<std::array<char, 3>, 5> t;

    t.add({'H', 'o', 'i'});         // 288
    t.add({'M', '&', 'M'});         // 192
    t.add({'U', 'T', 'P'});         // 249
    t.add({'s', 'e', 't'});         // 332
    t.add({'a', 'd', 'd'});         // 297

    std::stringstream s;
    s << t.max();
    REQUIRE(s.str() == "s e t " );
}

/// Test cases different template parameters /// 

TEST_CASE("Addition (std::array<<int, 4>, 3>) "){
    set<std::array<int, 4>, 3> t;
    
    t.add({0,1,2,3});
    t.add({4,5,6,7});
    t.add({8,9,10,11});
    t.add({8,9,10,11});

    std::stringstream s;
    s << t;
    REQUIRE(s.str() == "0 1 2 3  4 5 6 7  8 9 10 11  ") ;
}

TEST_CASE("Addition exeeding limit (std::array<<int, 4>, 3>) "){
    set<std::array<int, 4>, 3> t;
    
    t.add({0,1,2,3});
    t.add({4,5,6,7});
    t.add({8,9,10,11});
    t.add({12,13,14,15});
    
    std::stringstream s;
    s << t;
    REQUIRE(s.str() == "0 1 2 3  4 5 6 7  8 9 10 11  ") ;
}



TEST_CASE("Removal (std::array<<int, 4>, 3>) "){
    set<std::array<int, 4>, 3> t;
    
    t.add({0,1,2,3});
    t.add({4,5,6,7});
    t.add({8,9,10,11});

    t.remove({0,1,2,3});

    std::stringstream s;
    s << t;
    REQUIRE(s.str() == "4 5 6 7  8 9 10 11  ") ;
}

TEST_CASE("Contains (std::array<<int, 4>, 3>) "){
    set<std::array<int, 4>, 3> t;
    
    t.add({0,1,2,3});
    t.add({4,5,6,7});
    t.add({8,9,10,11});

    bool x = t.bool_contains({0,1,2,3});

    REQUIRE(x == 1) ;
}


TEST_CASE("Max (std::array<<int, 4>, 3>) "){
    set<std::array<int, 4>, 3> t;
    
    t.add({0,1,2,3});
    t.add({4,5,6,7});
    t.add({8,9,10,11});

    std::stringstream s;
    s << t.max();
    REQUIRE(s.str() == "8 9 10 11 ");
}