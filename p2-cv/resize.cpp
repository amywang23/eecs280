#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <cstring>
#include "Image.hpp"
#include "processing.hpp"
#include "Matrix_test_helpers.hpp"
#include "Image_test_helpers.hpp"

using namespace std;

const string OUT_PPM_EXT = ".out.ppm";
const string OUT_TXT_EXT = ".out.txt";

int main(int argc, char *argv[]){

    if (argc != 4 && argc != 5) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     return -1;

    }
    string filename = argv[1];
    ifstream fin;
    fin.open(filename.c_str());

    if (!fin.is_open()){
        cout << "Unable to open " << filename << endl;
        return -1;
    }
    Image* og = new Image;
    Image_init(og, fin);

    if (stoi(argv[3]) < 0 || stoi(argv[3]) > Image_width(og)) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     return -1;
    }
    if (argc == 5) {
        if (stoi(argv[4]) < 0 || stoi(argv[4]) > Image_height(og)) {
             cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     return -1;
    
        }
    }

    int newWidth = atoi(argv[3]);
    int newHeight = Image_height(og);
    if (argc == 5) {
        newHeight = atoi(argv[4]);
    }
    seam_carve(og, newWidth, newHeight);
    string fileOut = argv[2];
    ofstream finalOut;
    finalOut.open(fileOut.c_str());
    Image_print(og, finalOut);
    
    return 0;
}
