#include "hwlib.hpp"
#include <array>

// Lookup table class
class lookup {
private:
    // Array (60 minutes) --> x = cos values, y = sin values
    std::array<double, 60> cos_values;
    std::array<double, 60> sin_values;

public:
    // Constructor, constexpr --> calculate minute pixels compiletime 
    constexpr lookup():
        cos_values{},
        sin_values{}
    {
        for(int i = 0; i < 60; i++){
            cos_values[i] = double(cos(i * (6.28 / 60)));
            sin_values[i] = double(sin(i * (6.28 / 60)));
        }
    }

    // Functions to lookup x and y cordinates runtime
    constexpr double get_cos( int n ) const {
        return cos_values[n];
    }    
    constexpr double get_sin( int n ) const {
        return sin_values[n];
    }    
};

// Function used to calculate sin, cos
constexpr double power(double g, int n){
    double result = 1;
    while( n > 0 ){
        result *= g;
        --n;
    }
    return result;  
}

// Function used to calculate sin, cos
constexpr double factorial(int n){
    double result = 1;
    while (n > 0){
        result *= n;
        n--;
    }
    return result;
}

// Calculate sin values = x cordinates
constexpr double sin(double a ){
    double sine_value = a - power(a, 3) / factorial(3) + 
                            power(a, 5) / factorial(5) -
                            power(a, 7) / factorial(7) +
                            power(a, 9) / factorial(9) -
                            power(a, 11) / factorial(11) +
                            power(a, 13) / factorial(13) -
                            power(a, 15) / factorial(15) +
                            power(a, 17) / factorial(17) -
                            power(a, 19) / factorial(19) +
                            power(a, 21) / factorial(21) -
                            power(a, 23) / factorial(23) +
                            power(a, 25) / factorial(25) -
                            power(a, 27) / factorial(27) +
                            power(a, 29) / factorial(29);
    return sine_value;
}

// Calculate cos values = y cordinates 
constexpr double cos(double b){
    double cosine_value = 1 -   power(b, 2) / factorial(2) +
                                power(b, 4) / factorial(4) - 
                                power(b, 6) / factorial(6) + 
                                power(b, 8) / factorial(8) -
                                power(b, 10) / factorial(10) +
                                power(b, 12) / factorial(12) -
                                power(b, 14) / factorial(14) +
                                power(b, 16) / factorial(16) -
                                power(b, 18) / factorial(18) +
                                power(b, 20) / factorial(20) -
                                power(b, 22) / factorial(22) +
                                power(b, 24) / factorial(24) -
                                power(b, 26) / factorial(26) +
                                power(b, 28) / factorial(28);
    return cosine_value;
}

// Function to read button presses
bool button_press(hwlib::pin_in & sw){
    sw.refresh();
    if (sw.read()){ return true; }
    else{ return false; }
}

// Update display function --> lookup cordinates
void time_display_update(long long int hour, long long int minute, lookup sinusses, hwlib::window & display ){

    hwlib::cout <<  "Hours: " << hour << " | Minutes: " << minute << hwlib::endl;  

    auto hour_line = hwlib::line(hwlib::xy(64, 32), hwlib::xy(sinusses.get_cos(hour*5) * 20 + 64, sinusses.get_sin(hour*5) * 20 + 32));
    auto minute_line = hwlib::line(hwlib::xy(64, 32), hwlib::xy(sinusses.get_cos(minute) * 30 + 64, sinusses.get_sin(minute) * 30 + 32));

    hour_line.draw(display);
    minute_line.draw(display);

    display.flush();
    }



int main( void ){

    constexpr lookup sinusses;

    auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
    auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
    
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
    auto display = hwlib::glcd_oled( i2c_bus, 0x3c ); 

    auto left_switch = hwlib::target::pin_in( hwlib::target::pins::d9 );
    auto right_switch = hwlib::target::pin_in( hwlib::target::pins::d10 ); 

    int added_hours = 0;
    int added_minutes = 0;
    int old_minutes = 0;


    // Draw initial empty clock    
    for(int i=0; i < 12; i++){

        uint64_t x = sinusses.get_cos(i*5) * 32 + 64;
        uint64_t y = sinusses.get_sin(i*5) * 32 + 32;

        display.write(hwlib::xy(x, y));
    }
    
    time_display_update(0, 0, sinusses, display);

    for(;;){
        long long int time = hwlib::now_us();
        long long int hour = time / 3600000000;
        long long int minute = (time % 3600000000) / 60000000;

        auto left = button_press(left_switch);
        auto right = button_press(right_switch);

        display.clear();
        display.write(hwlib::xy(64, 32));
        
        // Clock static pixels
        for(int i=0; i < 12; i++){
            uint64_t x = sinusses.get_cos(i*5) * 32 + 64;
            uint64_t y = sinusses.get_sin(i*5) * 32 + 32;

            display.write(hwlib::xy(x, y));
        }
        
        // Update hours
        if (left == true){
            added_hours += 1;
            if((hour + added_hours) % 12 == 0){
                hour = 0;
                added_hours = 0;
            }
            time_display_update(hour + added_hours, minute + added_minutes, sinusses, display);
        }
        // Update minutes
        else if (right == true){
            added_minutes += 1;
            if((minute + added_minutes) % 60 == 0){
                minute = 0;
                added_minutes = 0;
                added_hours += 1;
            }
            time_display_update(hour + added_hours, minute + added_minutes, sinusses, display);
        }
        // Update hours +1 after 60 minutes
        else if (old_minutes < minute){
            old_minutes = minute;
            time_display_update(hour + added_hours, minute + added_minutes, sinusses, display);
        }
    }

}