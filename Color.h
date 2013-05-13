//---------------------------------------------------- 
// Name: Moyo Williams
// E-mail Address: mow5248@psu.edu
// Class: CMPSC 122, Section 102
// Project # 2
// Date:02/11/2013
// Converting a txt file with bitmap commands into a bitmap file
//----------------------------------------------------

#include <iostream>
#include <string>
using namespace std;

#pragma once

class Color
{
    private:
        string m_name;
        unsigned char m_red;
        unsigned char m_green;
        unsigned char m_blue;
   
    public:
        Color();
        ~Color();
        
        
        string name() const
            { return m_name; }
        unsigned char Red() const
            { return m_red; }
        unsigned char Green() const
            { return m_green; }
        unsigned char Blue() const
            { return m_blue; }
        
        // set the color data
        void Set(string name, unsigned char red, unsigned char green, unsigned char blue);
        
        // prints the contents of the class on a single line to cout
        void Print();
};
