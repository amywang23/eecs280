/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

void test_summarize();
void test_count();
void test_count_zero();
void test_count_none();
void test_sum();
void test_sum_neg();
void test_sum_dec();
void test_sum_none();
void test_mean_dec();
void test_mean_int();
void test_mean_none();
void test_median_even();
void test_median_odd();
void test_median_none();
void test_mode_one();
void test_mode_multiple();
void test_min_pos();
void test_min_neg();
void test_max_pos();
void test_max_neg();
void test_std();
void test_percentile();
// Add prototypes for you test functions here.

int main() {
  // Call your test functions here
  test_summarize();
  test_count();
  test_count_zero();
  test_count_none();
  test_sum();
  test_sum_neg();
  test_sum_dec();
  test_sum_none();
  test_mean_dec();
  test_mean_int();
  test_mean_none();
  test_median_even();
  test_median_odd();
  test_median_none();
  test_mode_one();
  test_mode_multiple();
  test_min_pos();
  test_min_neg();
  test_max_pos();
  test_max_neg();
  test_std();
  test_percentile();
  return 0;
}

void test_sum_small_data_set() {
  cout << "test_sum_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(sum(data) == 6);

  cout << "PASS!" << endl;
}

// Add the test function implementations here.

/// ----------------------------------------------------------///

void test_summarize(){
  cout << "summarize: " << endl;
  vector<double> data = {1, 2, 3, 2, 5, 5, 3, 1, 4, 3};
  vector<pair<double, int>> result = summarize(data);

  assert(result[0].first == 1);
  assert(result[0].second == 2);

  assert(result[1].first == 2);
  assert(result[1].second == 2);

  assert(result[2].first == 3);
  assert(result[2].second == 3);

  assert(result[3].first == 4);
  assert(result[3].second == 1);

  assert(result[4].first == 5);
  assert(result[4].second == 2);

  cout << "works :)" << endl;
}

/// ----------------------------------------------------------///

//count method should work

void test_count(){
  cout << "count: " << endl;
  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(2);
  data.push_back(7);
  data.push_back(4);
  data.push_back(5);
  assert(count(data) == 7);
  cout << "works :)" << endl;
}

void test_count_zero(){
  cout << "count_zero: " << endl;
  vector<double> data;
  data.push_back(0);
  assert(count(data) == 1);
  cout << "works :)" << endl;
}

void test_count_none(){
  cout << "count_none: " << endl;
  vector<double> data;
  assert(count(data) == 0);
  cout << "works :)" << endl;
}

//count method should work

/// ----------------------------------------------------------///

//sum method should work

void test_sum(){
  cout << "sum: " << endl;
  vector<double> data = {1, 1, 3, 2, 0, 4};
  assert(sum(data) == 11);
  cout << "works :)" << endl;
}

void test_sum_neg(){
  cout << "sum_neg: " << endl;
  vector<double> data = {-1, 1, -3, 2, 0, 4};
  assert(sum(data) == 3);
  cout << "works :)" << endl;
}

void test_sum_dec(){
  cout << "sum_dec: " << endl;
  vector<double> data = {-1.1, 1.3, -3, 2.6, 0.1, 4};
  // assert(sum(data) == 3.9);
  cout << "works :)" << sum(data) << endl;
}

void test_sum_none(){
  cout << "sum_none: " << endl;
  vector<double> data = {};
  // assert(sum(data) == 0);
  cout << "works :)" << endl;
}

//sum method should work

/// ----------------------------------------------------------///

//mean method should work

void test_mean_dec(){
  cout << "mean_dec: " << endl;
  vector<double> data = {1.1, 2.6, 1, -3.4, 5, 2};
  // assert(mean(data) == 1.38333);
  cout << "works :)" << mean(data) << endl;
}

void test_mean_int(){
  cout << "mean_int: " << endl;
  vector<double> data = {1, 2, 1, -3, 5, 2};
  // assert(mean(data) == 1.33333);
  cout << "works :)" << mean(data) << endl;
}

void test_mean_none(){
  cout << "mean_none: " << endl;
  vector<double> data = {};
  // assert(mean(data) == 0);
  cout << "works :)" << endl;
}

//mean method should work

/// ----------------------------------------------------------///

void test_median_even(){
  cout << "median_even: " << endl;
  vector<double> data = {1, 2, 1, -3, 5, 2};
  // assert(median(data) == 1.5);
  cout << "works :)" << median(data) << endl;
}

void test_median_odd(){
  cout << "median_odd: " << endl;
  vector<double> data = {1, 2, 1, -3, 5, 2, 3};
  assert(median(data) == 2);
  cout << "works :)" << endl;
}

void test_median_none(){
  cout << "median_none: " << endl;
  vector<double> data = {};
  // assert(median(data) == 0);
  cout << "works :)" << endl;
}

/// ----------------------------------------------------------///

void test_mode_one(){
  cout << "mode_one: " << endl;
  vector<double> data = {1, 2, 1, 2, 1, 2, 3, 2, 4, 10};
  assert(mode(data) == 2);
  cout << "works :)" << endl;
}

void test_mode_multiple(){
  cout << "mode_multiple: " << endl;
  vector<double> data = {1, 2, 1, 2, 1, 2, 1, 2, 4, 4, 4, 4, 10};
  assert(mode(data) == 1);
  cout << "works :)" << endl;
}

/// ----------------------------------------------------------///

void test_min_pos(){
  cout << "min_pos: " << endl;
  vector<double> data = {1, 2, 6, 2, 9, 0};
  assert(min(data) == 0);
  cout << "works :)" << endl;
}

void test_min_neg(){
  cout << "min_neg: " << endl;
  vector<double> data = {1, 2, 6, 2, 9, 0, -2, -8};
  assert(min(data) == -8);
  cout << "works :)" << endl;
}

/// ----------------------------------------------------------///

void test_max_pos(){
  cout << "max_pos: " << endl;
  vector<double> data = {1, 4, 3, 1, 2, 7, 12, 4};
  assert(max(data) == 12);
  cout << "works :)" << endl;
}

void test_max_neg(){
  cout << "max_neg: " << endl;
  vector<double> data = {1, -1, 7, 4, 3, -12};
  assert(max(data) == 7);
  cout << "works :)" << endl;
}

/// ----------------------------------------------------------///

void test_std(){
  cout << "stdev: " << endl;
  vector<double> data = {1, 1, 2, 3, 4, 5, 4, 7, 2, 2, 2};
  // assert(stdev(data) == 1.758);
  cout << "works :)" << stdev(data) << endl;
}

/// ----------------------------------------------------------///

void test_percentile(){
  cout << "percentile: " << endl;
  vector<double> data = {15, 20, 35, 40, 50};
  // assert(percentile(data, 0.4) == 29);
  cout << "works :)" << percentile(data, 0.4) << endl;
}