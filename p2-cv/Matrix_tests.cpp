#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.
TEST(test_fill_large) {
  Matrix* mat = new Matrix;
  Matrix_init(mat, 500, 500);
  Matrix_fill(mat, 42);
  for(int r = 0; r < 500; ++r){
    for(int c = 0; c < 500; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), 42);
    }
  }
  delete mat;

}

TEST(test_init) {
  Matrix* mat = new Matrix;
  Matrix_init(mat, 4, 4);
  for(int r = 0; r < 4; ++r){
    for(int c = 0; c < 4; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), 0);
    }
  }
  delete mat;

}

TEST(test_matrix_print) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 2, 2);

  *Matrix_at(mat, 0, 0) = 42;
  ostringstream expected;
  expected << "2 2\n"
           << "42 0 \n"
           << "0 0 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

TEST(test_matrix_width) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 2, 7);

  ASSERT_EQUAL(Matrix_width(mat), 2);
  delete mat;
}

TEST(test_matrix_height) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 2, 7);

  ASSERT_EQUAL(Matrix_height(mat), 7);
  delete mat;
}

TEST(test_matrix_row) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 3);
  *Matrix_at(mat, 1, 2) = 4;
  const int* ptr = Matrix_at(mat, 1, 2);
  ASSERT_EQUAL(Matrix_row(mat, ptr), 1);
  delete mat;
}

TEST(test_matrix_column) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 3);
  *Matrix_at(mat, 1, 2) = 4;
  const int* ptr = Matrix_at(mat, 1, 2);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 2);
  delete mat;
}

TEST(test_matrix_at) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 3);
  *Matrix_at(mat, 2, 2) = 4;
  int* ptr = Matrix_at(mat, 2, 2);
  
  ASSERT_EQUAL(Matrix_at(mat, 2, 2), ptr);
  delete mat;

}

TEST(test_matrix_fill) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 3);
  Matrix_fill(mat, 5);
  for(int r = 0; r < 3; ++r) {
    for(int c = 0; c < 3; ++c) {
      ASSERT_EQUAL(*Matrix_at(mat, r, c), 5);
    }
  }
  delete mat;

}

TEST(test_matrix_border) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 3);
  Matrix_fill_border(mat, 5);
  for (int col = 0; col < Matrix_width(mat); col++) {
    ASSERT_EQUAL(*Matrix_at(mat, 0, col), 5);
    ASSERT_EQUAL(*Matrix_at(mat, Matrix_height(mat)-1, col), 5);
  }
  for (int row = 0; row < Matrix_height(mat); row++) {
    ASSERT_EQUAL(*Matrix_at(mat, row, 0), 5);
    ASSERT_EQUAL(*Matrix_at(mat, row, Matrix_width(mat)-1), 5);
  }
  delete mat;
}

TEST(test_matrix_max) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 3);
  Matrix_fill(mat, 5);
  *Matrix_at(mat, 2, 1) = 17;
  ASSERT_EQUAL(Matrix_max(mat), 17);
  delete mat;
}

TEST(test_matrix_column_of_min_value_in_row) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 3);
  Matrix_fill(mat, 3);
  *Matrix_at(mat, 1, 2) = 5;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 3), 0);
  delete mat;

}

TEST(test_matrix_min_value_in_row) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 3);
  Matrix_fill(mat, 3);
  *Matrix_at(mat, 1, 2) = 5;
  *Matrix_at(mat, 1, 1) = -7;

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 3), -7);
  delete mat;
}

//--------------------------------------------------------------//


TEST(test_init) {
  Matrix* mat = new Matrix;
  Matrix_init(mat, 1, 1);
  for(int r = 0; r < 1; ++r){
    for(int c = 0; c < 1; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), 0);
    }
  }
  delete mat;

}

TEST(test_matrix_print) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);

  *Matrix_at(mat, 0, 0) = 42;
  ostringstream expected;
  expected << "42\n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

TEST(test_matrix_width) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 2);

  ASSERT_EQUAL(Matrix_width(mat), 1);
  delete mat;
}

TEST(test_matrix_height) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 2, 1);

  ASSERT_EQUAL(Matrix_height(mat), 1);
  delete mat;
}

TEST(test_matrix_row) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);
  *Matrix_at(mat, 0, 0) = 4;
  const int* ptr = Matrix_at(mat, 0, 0);
  ASSERT_EQUAL(Matrix_row(mat, ptr), 4);
  delete mat;
}

TEST(test_matrix_column) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);
  *Matrix_at(mat, 0, 0) = 4;
  const int* ptr = Matrix_at(mat, 0, 0);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 4);
  delete mat;
}

TEST(test_matrix_at) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);
  *Matrix_at(mat, 0, 0) = 4;
  int* ptr = Matrix_at(mat, 0, 0);
  
  ASSERT_EQUAL(Matrix_at(mat, 0, 0), ptr);
  delete mat;

}

TEST(test_matrix_fill) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);
  Matrix_fill(mat, 5);
  for(int r = 0; r < 1; ++r) {
    for(int c = 0; c < 1; ++c) {
      ASSERT_EQUAL(*Matrix_at(mat, r, c), 5);
    }
  }
  delete mat;

}

TEST(test_matrix_border) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);
  Matrix_fill_border(mat, 5);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 5);

  delete mat;
}

TEST(test_matrix_max) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);
  Matrix_fill(mat, 5);
  *Matrix_at(mat, 0, 0) = 8;
  ASSERT_EQUAL(Matrix_max(mat), 18);
  delete mat;
}

TEST(test_matrix_column_of_min_value_in_row) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);
  Matrix_fill(mat, 5);
  *Matrix_at(mat, 0, 0) = 2;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 0), 2);
  delete mat;

}

TEST(test_matrix_min_value_in_row) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);
  Matrix_fill(mat, 5);
  *Matrix_at(mat, 0, 0) = 3;
  *Matrix_at(mat, 0, 0) = 5;

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 0), 5);
  delete mat;
}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here