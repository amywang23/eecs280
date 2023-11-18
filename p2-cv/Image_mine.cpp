#include <cassert>
#include "Image.hpp"

// REQUIRES: img points to an Image
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, int width, int height) {
  img -> width = width;
  img -> height = height;
  Matrix_init(&img -> red_channel, width, height);
  Matrix_init(&img -> green_channel, width, height);
  Matrix_init(&img -> blue_channel, width, height);
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, std::istream& is) {
  std::string f1;
  int width;
  int height;
  int t1;
  is >> f1;
  is >> width >> height;
  is >> t1;
  Image_init(img, width, height);

  for(int row = 0; row < height; row++){
    for(int col = 0; col < width; col++){
      Pixel p;
      is >> p.r >> p.g >> p.b;
      Image_set_pixel(img, row, col, p);
    }
  }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
  os << "P3" << "\n";
  os << img -> width << " " << img -> height << "\n";
  os << "255" << "\n";
  // print all the pixels into a matrix shape
  for (int row = 0; row < img -> height; row++) {
    for (int col = 0; col < img -> width; col++) {
      os << Image_get_pixel(img, row, col).r << " " << Image_get_pixel(img, row, col).g << " " << Image_get_pixel(img, row, col).b << " ";
    }
    os << "\n";
  }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  return img -> width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
  return img -> height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  int red = *Matrix_at(&img -> red_channel, row, column);
  int green = *Matrix_at(&img -> green_channel, row, column);
  int blue = *Matrix_at(&img -> blue_channel, row, column);
  Pixel result = {red, green, blue};
  return result;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  int x = *Matrix_at(&img -> red_channel, row, column);
  x = color.r;
  int y = *Matrix_at(&img -> green_channel, row, column);
  y = color.g;
  int z = *Matrix_at(&img -> blue_channel, row, column);
  z = color.b;
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
  for (int row = 0; row < img -> height; row++) {
    for (int col = 0; col < img -> width; col++) {
      Image_set_pixel(img, row, col, color);
    }
  }
}
