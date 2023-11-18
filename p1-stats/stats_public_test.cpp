// THIS TEST CASE WILL ONLY TELL YOU IF YOUR CODE COMPILES.
// YOU NEED TO WRITE YOUR OWN COMPREHENSIVE TEST CASES IN stats_tests.cpp

#include "stats.hpp"
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

int main()
{
  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  cout << "count" << count(data) << endl;
  cout << "sum" << sum(data) << endl;
  cout << "mean" << mean(data) << endl;
  cout << "median" << median(data) << endl;
  cout << "mode" << mode(data) << endl;
  cout << "min" << min(data) << endl;
  cout << "max" << max(data) << endl;
  cout << "stdev" << stdev(data) << endl;
  cout << "percentile" << percentile(data, 0.5) << endl;

  summarize(data);

  return 0;
}

