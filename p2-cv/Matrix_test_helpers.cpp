
/* Matrix_test_helpers.cpp
 * Originally written by James Juett at the University of Michigan
 * for project 3 in EECS 280, Winter 2016.
 */

#include "Matrix_test_helpers.hpp"

bool Matrix_equal(const Matrix* mat1, const Matrix* mat2){
  if (Matrix_width(mat1) != Matrix_width(mat2)){ return false; }
  if (Matrix_height(mat1) != Matrix_height(mat2)){ return false; }

  for(int r = 0; r < Matrix_height(mat1); ++r){
    for(int c = 0; c < Matrix_width(mat1); ++c){
      if (*Matrix_at(mat1, r, c) != *Matrix_at(mat2, r, c)){ return false; }
    }
  }
  
  return true;
}

bool array_equal(const int arr1[], const int arr2[], int n){
  for(int i = 0; i < n; ++i){
    if(arr1[i] != arr2[i]){ return false; }
  }

  return true;
}

