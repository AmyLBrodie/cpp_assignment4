
/* 
 * Author: Amy Brodie (BRDAMY004)
 * CSC3022H Tutorial 4
 * Created on 17 April 2016, 1:35 PM
 */

#include <cstdlib>
#include <sstream>

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
            break;
        }
        else if (option == "-s"){
            image1 = string(argv[2]);
            image2 = string(argv[3]);
            outputImageName = string(argv[4]);
            break;
        }
        else if (option == "-i"){
            image1 = string(argv[2]);
            outputImageName = string(argv[3]);
            break;
        }
        else if (option == "-l"){
            image1 = string(argv[2]);
            image2 = string(argv[3]);
            outputImageName = string(argv[4]);
            break;
        }
        else if (option == "-t"){
            image1 = string(argv[2]);
            istringstream iss(argv[3]);
            iss >> f;
            break;
        }
    }
    return 0;
}

