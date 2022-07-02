#include <math.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include "histogram.h"

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

vector<size_t>
make_histogram(const vector<double>& numbers, size_t bin_count) //создание гистограмы
{
    double min, max;
    find_minmax(numbers, min, max);
    vector<size_t> bins(bin_count, 0);
    double bin_size = (max - min) / bin_count;

    for (double number : numbers)
    {
        bool found = false;
        for (size_t j = 0; j < (bin_count - 1) && !found; j++)
        {
            auto low = min + j * bin_size;
            auto hight = min + (j + 1) * bin_size;

            if ((low <= number) && (number < hight)) {
                bins[j]++;
                found = true;
            }
        }
        if (!found) {
            bins[bin_count - 1]++;
        }
    }
    return bins;
}
