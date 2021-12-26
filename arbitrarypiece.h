// Pragma Once
#ifndef _arbitrarypiece_h
#define _arbitrarypiece_h

// Include Modules
#include <iostream>
#include <vector>

using namespace std; 

// Piece Class
class Piece{
    private: 
        char name; // Do you think this should in the derived class or the base class?
        vector <int> position;
        bool onboard; 
        char color; 

    public: 
        vector <int> getPosition(char n); 
        void move(char n, vector <int> np); 
        char getColor(char n);
        void changeState(char n); // change the onboard boolean value
};

#endif