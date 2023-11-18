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
    string filename = argv[1];
    ifstream fin;
    fin.open(filename.c_str());

    if (!fin.is_open()){
        cout << "Unable to open " << filename << endl;
        exit(EXIT_FAILURE);
    }
    Image* img = new Image;
    Image_init(img, fin);

    Image* output = new Image;
    // Image_init(output, );

    if(argc == 4){
        int height = img -> height;
        seam_carve(img, int(argv[3]), height);
    }
    else if (argc == 5 || (argv[3] > 0 && int(argv[3]) <= img -> width) 
    || (argv[4] > 0 && int(argv[4]) <= img -> height)) {
        seam_carve(img, int(argv[3]), int(argv[4]));
    }
    else{
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    }
}
