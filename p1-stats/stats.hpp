#ifndef STATS_HPP
#define STATS_HPP
/* stats.hpp
 *
 * Simple statistics library
 *
 * EECS 280 Project 1
 *
 */

#include <vector>

//NOTE: no "using namespace std;" in a .hpp file!  That's why we use "std::vector
//instead of "vector" later on.  You can add "using namespace std;" to your
//stats.cpp if you want to.

//REQUIRES: v is not empty
//EFFECTS: returns a summary of the dataset as (value, frequency) pairs
//  In the returned vector-of-pairs, the inner item is a (value, frequency)
//  pair.  The outer vector contains many of these pairs.  The pairs should be
//  sorted by value.
//  {
//    {1, 2},
//    {2, 3},
//    {17, 1}
//  }
//
// This means that the value 1 occurred twice, the value 2 occurred three times,
// and the value 17 occurred once
std::vector<std::pair<double, int> > summarize(std::vector<double> v);

//EFFECTS: returns the count of the numbers in v
int count(std::vector<double> v);

//REQUIRES: v is not empty
//EFFECTS: returns the sum of the numbers in v
double sum(std::vector<double> v);

//REQUIRES: v is not empty
//EFFECTS: returns the arithmetic mean of the numbers in v
//  http://en.wikipedia.org/wiki/Arithmetic_mean
double mean(std::vector<double> v);

//REQUIRES: v is not empty
//EFFECTS: returns the median of the numbers in v
//  https://en.wikipedia.org/wiki/Median#Finite_data_set_of_numbers
double median(std::vector<double> v);

//REQUIRES: v is not empty
//EFFECTS: returns the mode of the numbers in v
//  http://en.wikipedia.org/wiki/Mode_(statistics)
//  Example: mode({1,2,3}) = 1
//  Example: mode({1,1,2,2}) = 1
//  Example: mode({2,2,1,1}) = 1
//  Example: mode({1,2,1,2}) = 1
//  Example: mode({1,2,1,2,2}) = 2
//  In the event of a tie, return the smallest value (as in the 
//  above examples)
//HINT 1: use the sort() function provided in p1_library.hpp
//HINT 2: use a nested loop
//HINT 3: use a variable to remember the most frequent number seen so far
double mode(std::vector<double> v);

//REQUIRES: v is not empty
//EFFECTS: returns the min number in v
double min(std::vector<double> v);

//REQUIRES: v is not empty
//EFFECTS: returns the max number in v
double max(std::vector<double> v);

//REQUIRES: v contains at least 2 elements
//EFFECTS: returns the corrected sample standard deviation of the numbers in v
//  http://en.wikipedia.org/wiki/Standard_deviation#Corrected_sample_standard_deviation
double stdev(std::vector<double> v);

//REQUIRES: v is not empty
//          p is between 0 and 1, inclusive
//EFFECTS: returns the percentile p of the numbers in v like Microsoft Excel.
//  Refer to the project spec for the formula to use.
//  NOTE: the definition in the image uses indexing from 1.  You will need to
//  adapt it to use indexing from 0.
double percentile(std::vector<double> v, double p);

#endif
