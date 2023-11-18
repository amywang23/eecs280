#include <iostream>
#include "p1_library.hpp"
#include "stats.hpp"
#include <cassert>
#include <vector>
#include <cmath>

using namespace std;

string filename;
string column_name;

int main() {
  cout << "enter a filename\n";
  cin >> filename;
  cout << "enter a column name\n";
  cin >> column_name;
  cout << "reading column " << column_name << " from " << filename << "\n";

  vector<double> v = extract_column(filename, column_name);

  cout << "Summary (value: frequency)" << "\n"; //call summarize method 
  vector<pair<double, int>> result = summarize(v);
  for(int i = 0; i < result.size(); i++){
    cout << result[i].first << ": " << result[i].second << "\n";
  }

  cout << "\n";

  cout << "count = " << count(v) << "\n"; //count method
  cout << "sum = " << sum(v) << "\n"; //sum method
  cout << "mean = " << mean(v) << "\n"; //mean method
  cout << "stdev = " << stdev(v) << "\n"; //standard deviation method
  cout << "median = " << median(v) << "\n"; //median method
  cout << "mode = " << mode(v) << "\n"; //mode method
  cout << "min = " << min(v) << "\n"; //min method
  cout << "max = " << max(v) << "\n"; //max method

  cout << "  0th percentile = " << percentile(v, 0) << "\n"; //percentile method
  cout << " 25th percentile = " << percentile(v, 0.25) << "\n";
  cout << " 50th percentile = " << percentile(v, 0.5) << "\n";
  cout << " 75th percentile = " << percentile(v, 0.75) << "\n";
  cout << "100th percentile = " << percentile(v, 1) << "\n";
}