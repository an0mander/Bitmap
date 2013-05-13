#include <iostream>
#include "Color.h"
using namespace std;

Color::Color()
{
    m_name = "";
        m_red = 0;
        m_green = 0;
        m_blue = 0;
    }

Color::~Color()
{
}

// set the color data
void Color::Set(string name, unsigned char red, unsigned char green, unsigned char blue)
{
    m_name= name;
        m_red = red;
        m_green = green;
        m_blue = blue;
}
// prints the contents of the class on a single line to cout

void Color::Print()
{
        cout << m_name << ": ";
        cout << (int)m_red << ", ";
        cout << (int)m_green << ", ";
        cout << (int)m_blue << endl;
}
