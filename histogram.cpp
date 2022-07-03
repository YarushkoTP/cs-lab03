#include <math.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include "histogram.h"
#include <windows.h>

using namespace std;

void
find_minmax(const vector<double>& numbers, double& min, double& max) //поиск минимального и макс чисел
{
    if (numbers.size() == 0) {
        return;
    }
    min = numbers[0];
    max = numbers[0];
    for (double number : numbers)
    {
        if (number < min)
        {
            min = number;
        }

        if (number > max)
        {
            max = number;
        }
    }
}

//vector<double>
//input_numbers(size_t count) // ввод чисел
//{
//    vector<double> result(count);
//    for (size_t i = 0; i < count; i++) {
//        cin >> result[i];
//    }
//    return result;
//}

//vector<size_t> make_histogram(Input input)
//{
//    double min, max;
//    find_minmax(input.numbers, min, max);
//    double bin_size = (max - min) / input.bin_count;
//    vector<size_t> bins(input.bin_count, 0);
//    for (size_t i = 0; i < input.numbers.size(); i++){
//        bool found = false;
//        for (size_t j = 0; j < input.bin_count - 1 && !found; j++){
//            auto lo = min + j * bin_size;
//            auto hi = min + (j + 1) * bin_size;
//
//            if (lo <= input.numbers[i] && input.numbers[i] < hi){
//               bins[j]++;
//                found = true;
//            }
//        }
//        if (!found){
//            bins[input.bin_count - 1]++;
//        }
//    }
//    return bins;
//}
