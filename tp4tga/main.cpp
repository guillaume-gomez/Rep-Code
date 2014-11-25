#include <stdexcept>
#include "include/Image.hpp"
#include "include/Color.h"
using namespace std;


    int main()
    {
        string str = "remy t'as gueule" ;
        try
        {
             Color c1(222,69,242);
             ifstream titre ("Lena.ppm",ios::binary);
              Image<Color> *pii = Image<Color>::readPPM(titre);
                        pii->rectangle(200,100,10,25,c1);
                        pii->fillRectangle(300,150,15,15,c1 );
             //on sauvegarde l'image creer
              {
               ofstream titre2("LenaModifiée.tga",ios::binary);
               pii->writeTGA(titre2 , " La fameuse Lena");
              }
               delete pii ;
            ifstream titre3  ("nicolas.ppm" , ios::binary);
            Image<Color> * p3 = Image<Color>::readPPM(titre3);
            // pii->rectangle(200,100,10,25,c1);
            // pii->fillRectangle(300,150,15,15,c1 );
             ofstream titre4 ( "returnTest.ppm" , ios::binary );
             p3->writeTGA(titre4 , str , false);

            delete p3;


            ifstream titre5 ("chat.tga" , ios::binary);
            Image<Color> *piii = Image<Color>::readTGA(titre5);
            ofstream titre6 ("conversionRLE.ppm" ,ios::binary);
            string commentaire ("guiguig");
             piii->writePPM(titre6 , commentaire);
                delete piii;

              ifstream titre7 ("chat.tga" , ios::binary);
                Image<Color> *p4 = Image<Color>::readTGA(titre7);
            ofstream titre8 ("conversionpalette.tga" ,ios::binary);
            string commentaire2 ("test");
             p4->writeTGA(titre8 , commentaire2);
               delete p4;


        }
        catch ( runtime_error & re)
        {
            cerr << re.what()<<endl;
        }


        return 0 ;
    }
