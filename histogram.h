#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED

#include <vector>

using namespace std;


void find_minmax(const vector<double>& numbers, double& min, double& max);

vector<double> input_numbers(size_t count);

//vector<size_t> make_histogram(input);

#endif // HISTOGRAM_H_INCLUDED
