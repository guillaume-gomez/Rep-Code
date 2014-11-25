#include <iostream>
#include <fstream>
#include <stdexcept>
#include "include/GrayImage.h"

#include "include/Historigram.h"
#include "include/Image.hpp"
using namespace std;

int main()
{

    try
    {
     ifstream is;
     is.open("chat.pgm", ios::binary);
     ofstream titre("test.pgm" , ios::binary);
     ofstream titre2("justeCarre.pgm" , ios::binary);
     ofstream histr("historigrammeChat.pgm" , ios::binary);



      Image <ubyte> i (8,4);
       //GrayImage i (4,4);
      i.clear();
      i.rectangle(0,0,2,3,200);
      i.fillRectangle(3,1,2,2,255);
      i.writePGM(titre2);
      Image <ubyte> *pi = Image<ubyte>::readFormat(is);
      //GrayImage *pi = GrayImage::readFormat(is);


            try
            {
               //   pi->rectangle(4,5,14,12,255);
                //  pi->fillRectangle(20,100,30,80,200);
                //  pi->rectangle(200,100,10,10,255);
                  pi->writePGM(titre);
            }
              catch ( runtime_error & re)
            {
            cerr << re.what()<<endl;
            }

            Historigram hist (*pi);
            Image<ubyte> *test = hist.draw();
            test->writePGM(histr);
    }
    catch ( runtime_error & re)
    {
        cerr << re.what()<<endl;
    }

    return 0 ;
}
