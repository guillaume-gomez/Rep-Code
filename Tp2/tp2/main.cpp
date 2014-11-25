#include <iostream>
#include <fstream>
#include <stdexcept>
#include "include/Image.hpp"
#include "include/Color.h"
using namespace std;

void creationImagePGM();

    int main()
    {

        try
        {
          creationImagePGM();
          Color c1 (255,0,0);

          Image <Color> i (8,4);
          i.clear();
          i.rectangle(0,0,2,3,c1);
          i.fillRectangle(3,1,2,2,c1);


            ifstream titre ("Lena.ppm",ios::binary);
              Image<Color> *pii = Image<Color>::readPPM(titre);
                        pii->rectangle(200,100,10,25,c1);
                        pii->fillRectangle(300,150,15,15,c1 );
          //on sauvegarde l'image creer
              {
               ofstream titre2("LenaModifiée.ppm",ios::binary);
               pii->writePPM(titre2);
              }

                ifstream titre3 ("chat_petit.ppm",ios::binary);
                pii = Image<Color>::readPPM(titre3);
                Image<Color>* pi3 = pii->BilinearScale(823,400);
                ofstream titre4 ( "tp2_BilinearScale.pgm",ios::binary);
                pi3->writePPM(titre4);

              delete pii;
        }
        catch ( runtime_error & re)
        {
            cerr << re.what()<<endl;
        }


        return 0 ;
    }

void creationImagePGM()
{
   Image <ubyte> i (8,4);
          i.clear();
          i.rectangle(0,0,2,3,200);
          i.fillRectangle(3,1,2,2,255);

          //on sauvegarde l'image creer
              {
               ofstream titre2("justeCarre.pgm" , ios::binary);
               i.writePGM(titre2);

              }

                  {
                   ifstream is ("chat.pgm", ios::binary);
                   Image <ubyte> *pi = Image<ubyte>::readPGM(is);

                    pi->rectangle(4,5,14,12,255);
                    pi->fillRectangle(20,100,30,80,200);
                    pi->rectangle(200,100,10,10,255);

                    {
                    ofstream titre("chat_Black_And_White.pgm" , ios::binary);
                    pi->writePGM(titre);
                    }

                    delete pi;
                  }

}


