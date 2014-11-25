#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include "include/Image.hpp"
#include "include/Color.h"
using namespace std;


    int main()
    {
        try
        {
            Color c1 ( 12,25,255);
             ifstream titre ("Lena.ppm",ios::binary);
              Image<Color> *pii = Image<Color>::readPPM(titre);
                        pii->rectangle(200,100,10,25,c1);
                        pii->fillRectangle(300,150,15,15,c1 );
             //on sauvegarde l'image creer
              {
               ofstream titre2("LenaModifiée.ppm",ios::binary);
               pii->writePPM(titre2);

               for(unsigned int quality = 0 ; quality <= 100 ; quality +=5 )
               {
                   ostringstream oss;
                   oss << "out_" << setfill('0') << setw(3) << quality << ".jpeg";
                   pii->writeJPEG(oss.str().c_str(),quality);
               }
               pii->writeJPEG("LenaJPEGer.jpeg",75);
              }

              delete pii ;

        }
        catch ( runtime_error & re)
        {
            cerr << re.what()<<endl;
        }


        return 0 ;
    }
