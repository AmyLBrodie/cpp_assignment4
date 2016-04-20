
/* 
 * Author: Amy Brodie (BRDAMY004)
 * CSC3022H Tutorial 4
 * Created on 17 April 2016, 1:35 PM
 */

#include <cstdlib>
#include <sstream>
#include <string>
#include <iostream>
#include "Image.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    string option;
    string image1;
    string image2;
    int f;
    string outputImageName;
    
    for (int i=0; i<argc; i++){
        string temp = string(argv[i]);
        if (i == 1){
            option = temp;
        }
        else if (option == "-a"){
            image1 = string(argv[2]);
            image2 = string(argv[3]);
            outputImageName = string(argv[4]);
            BRDAMY004::Image image;
            BRDAMY004::Image image0;
            image.load(image1);
            image0.load(image2);
            image.addImages(image0);
            image.save(outputImageName);
            break;
        }
        else if (option == "-s"){
            image1 = string(argv[2]);
            image2 = string(argv[3]);
            outputImageName = string(argv[4]);
            BRDAMY004::Image image;
            BRDAMY004::Image image0;
            image.load(image1);
            image0.load(image2);
            image.subtractImages(image0);
            image.save(outputImageName);
            break;
        }
        else if (option == "-i"){
            image1 = string(argv[2]);
            outputImageName = string(argv[3]);
            BRDAMY004::Image image;
            image.load(image1);
            image.invertImage();
            image.save(outputImageName);
            break;
        }
        else if (option == "-l"){
            image1 = string(argv[2]);
            image2 = string(argv[3]);
            outputImageName = string(argv[4]);
            BRDAMY004::Image image;
            BRDAMY004::Image image0;
            image.load(image1);
            image0.load(image2);
            image.maskImages(image0);
            image.save(outputImageName);
            break;
        }
        else if (option == "-t"){
            image1 = string(argv[2]);
            istringstream iss(argv[3]);
            iss >> f;
            outputImageName = string(argv[4]);
            cout << f << endl;
            BRDAMY004::Image image;
            image.load(image1);
            image.threshholdImage(f);
            image.save(outputImageName);
            break;
        }
    }
    return 0;
}

