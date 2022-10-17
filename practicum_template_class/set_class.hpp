#include <iostream>
#include <array>

template< typename T, unsigned int N>
std::ostream & operator<<(std::ostream & lhs, const std::array<T, N> & rhs){
    for(unsigned int i=0; i<N; i++){
        lhs << rhs[i] << " ";
    }
    return lhs;
}

template< typename T, unsigned int N>
class set {
private:
    std::array<T, N> collection;

protected:
    unsigned int counter = 0;

public:
    set(){}

    void add(const T &value){
        if(counter == N){
            std::cout << "Set full" << std::endl;
            return;
        }
        for (unsigned int i = 0; i< counter; i++){
            if (collection[i] == value){
                std::cout << "Item already in set" << std::endl;
                return;
            }
        }
        collection[counter] = value;
        counter += 1;
    }

    void remove(T value){
        for(unsigned int i = 0; i < counter; i++){
            std::array<T, N> temp = collection;
            if (temp[i] == value){
                collection[i] = temp[i+1];
                for(unsigned int j=i+1; j<counter; j++){
                    collection[j] = temp[j+1];
                }

                counter -= 1;
                std::cout << "Removed item" << std::endl;
            }
        }
    }

    bool bool_contains(T value){
        for(unsigned int i = 0; i < counter; i++){
            if (collection[i] == value){
                return true;
            }
        }
        return false;
    }

    bool operator>(set & rhs){
        char right_total = 0;
        char left_total = 0;

        for( int j=0; j<3; j++){
            right_total += rhs.collection[j];
            left_total += this->collection[j];
        }

        if (left_total > right_total){return true;}
        else{return false;}
    }

    T max(){
        T current_max = {};
        for (unsigned int i=0; i<N; i++){
            if (collection[i] > current_max){
                current_max = collection[i];
            }
        }
        return current_max;
    }


    friend std::ostream & operator<<(std::ostream & lhs, const set & rhs){
        for(unsigned int i=0; i<rhs.counter; i++){
            lhs << rhs.collection[i] << " ";
        }
        return lhs;
    }
};


