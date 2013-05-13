//---------------------------------------------------- ----------
// Name: Moyo Williams
// E-mail Address: mow5248@psu.edu
// Class: CMPSC 122, Section 102
// Project # 2
// Date:02/11/2013
// Converting a txt file with bitmap commands into a bitmap file
//----------------------------------------------------------------

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "color.h"
#include "Image.h"

using namespace std;

Color GetColor(string colorName, vector<Color> colorList);

int main()

{

    string userInput;
    string str;
    ifstream inputFile;
    string file_bmp;
    vector<Color>ColorList;//color list vector


//******************************************************
//The block of code below accepts user input and       *
//appends the type of file extension to the userinput  *
//then it opens the file the userinputed. It also      *
//automatically converts the userinput into a .bmp file*
//******************************************************
    
    cout << "Enter input file name" << endl;
    getline (cin, userInput);
    if (userInput.empty()) return 0;
    size_t position = userInput.find_last_of("."); // find '.' in the name
  if (position == string::npos) 
    { // there is no '.' in the name
		file_bmp = userInput + ".bmp";
		userInput += ".txt";
	}
	else file_bmp = userInput.substr(0,position) + ".bmp";

//***************************************************************
//The block of code below reads in the file and using string    *
//functions searches for the aruments of the commands/functions *
//and uses them to use the functions                            *
//***************************************************************
    
    
    inputFile.open(userInput);
    int i,j,k,l,m,n;
    int x1, y1;
    int width,height, x,y;
    string command;
    string line;
    Color c1;
    Image image;
    vector<Color> colorList;
    string colorName;

    while(true)
    {
        getline(inputFile, line);
        if (inputFile.fail())
	    {
		    cout << "Could Not Open File!" << endl;
            break;
	    }
        
        if(line.length() > 0)
        {
            i = line.find('(');
            command = line.substr(0,i);

            cout << command << endl;
            
            if(command == "NewColor")
            {
                j = line.find(',', i+1);
                k = line.find(',', j+1);
                l = line.find(',', k+1);
                m = line.find(')', l+1);

                c1.Set(line.substr(i+1,j-i-1),
                       atoi(line.substr(j+1,k-j-1).c_str()),
                       atoi(line.substr(k+1,l-k-1).c_str()),
                       atoi(line.substr(l+1,m-l-1).c_str()));
            
                colorList.push_back(c1);
            } 

             if (command == "New")
              {
                j = line.find(',', i+1);
                k = line.find(')', l+1);

                image.New(atoi(line.substr(i+1,j-i-1).c_str()),
                          atoi(line.substr(j+1,k-j-1).c_str()));//function call

               
               }
            
        
              if (command == "Clear")
              {
                j = line.find(')', i+1);

                colorName = line.substr(i+1,j-i-1);
                c1 = GetColor(colorName, colorList);

                image.Clear(c1.Red(), c1.Green(), c1.Blue());
        
              }        
        
             if (command == "SetPixel")
              {
                j = line.find(',', i+1);
                k = line.find(',', j+1);
                m = line.find(')', l+1);

                colorName = line.substr(i+1,j-i-1);
                c1 = GetColor(colorName, colorList);

                x1 = atoi(line.substr(j+1,k-j-1).c_str());//arguments
                y1 = atoi(line.substr(k+1,m-k-1).c_str());//arguments

                image.SetPixel(c1.Red(), c1.Blue(), c1.Green(),x1,y1);
             }
             
             if (command == "DrawLine")
              {
                j = line.find(',', i+1);
                k = line.find(',', j+1);
                l = line.find(',', k+1);
                n = line.find(',', l+1);
                m = line.find(')', n+1);

               
                //cout<<line.substr(i+1,j-i-1)<<endl;
                //cout<<atoi(line.substr(j+1,k-j-1).c_str())<<endl;
                          
             }

             if (command == "DrawRectangle")
              {
                j = line.find(',', i+1);
                k = line.find(',', j+1);
                l = line.find(',', k+1);
                n = line.find(',', l+1);
                m = line.find(')', l+1);

                colorName = line.substr(i+1,j-i-1);
                c1 = GetColor(colorName, colorList);

                x = atoi(line.substr(j+1,k-j-1).c_str());//arguments
                y = atoi(line.substr(k+1,l-k-1).c_str());//arguments
                width = atoi(line.substr(l+1,n-l-1).c_str());//arguments
                height = atoi(line.substr(n+1,m-n-1).c_str());//arguments
                image.DrawRectangle(c1.Red(),c1.Green(),c1.Blue(), x,y,width,height);//function call
             }

             if (command == "FillRectangle")
              {
                j = line.find(',', i+1);
                k = line.find(',', j+1);
                l = line.find(',', k+1);
                n = line.find(',', l+1);
                m = line.find(')', n+1);


                colorName = line.substr(i+1,j-i-1);
                c1 = GetColor(colorName, colorList);

                x1 = atoi(line.substr(j+1,k-j-1).c_str());
                y1 = atoi(line.substr(k+1,m-k-1).c_str());
                width = atoi(line.substr(l+1,n-l-1).c_str());
                height = atoi(line.substr(n+1,m-n-1).c_str());

                image.FillRectangle(c1.Red(),c1.Green(),c1.Blue(), x1,y1,width,height);

             }

        }
    }  

    for(i=0; i < colorList.size(); i++)
        colorList[i].Print();


    image.SaveFile(file_bmp);


}

//***********************************************************
//Function for writing the colors into a color list vector  *
//                                                          *
//***********************************************************
Color GetColor(string colorName, vector<Color> colorList)
{
    Color c1;

    

    for(int i=0; i < colorList.size(); i++)
    {
        if (colorList[i].name() == colorName)
        {
           c1 = colorList[i];
           break;
        }
    }

    return c1;
}
