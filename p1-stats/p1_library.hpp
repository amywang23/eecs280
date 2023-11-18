#ifndef P1_LIBRARY_HPP
#define P1_LIBRARY_HPP
/* p1_library.hpp
 *
 * Libraries needed for EECS 280 project 1
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * 2015-04-28
 */

#include <vector>
#include <string>

//MODIFIES: v
//EFFECTS: sorts v
void sort(std::vector<double> &v);

//EFFECTS: extracts one column of data from a tab separated values file (.tsv)
//  Prints errors to stdout and exits with non-zero status on errors
std::vector<double> extract_column(std::string filename, std::string column_name);

#endif
