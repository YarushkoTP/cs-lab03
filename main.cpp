#include <math.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include "histogram.h"
#include "svg.h"

using namespace std;

//void
//find_minmax(const vector<double>& numbers, double& min, double& max) //поиск минимального и макс чисел
//{
    //min = numbers[0];
    //max = numbers[0];
    //for (double number : numbers)
    //{
        //if (number < min)
        //{
            //min = number;
        //}

        //if (number > max)
        //{
            //max = number;
        //}
    //}
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

void
show_histogram_text(vector<size_t> bins) //вывод гистограмы звездочками
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
    size_t max_bin = bins[0];
    for (double bin : bins)
    {
        if (bin > max_bin)
        {
            max_bin = bin;
        }
    }
    for (double bin : bins)
    {
        size_t height = bin;
        // проверить масштабирование(пересчитать height)

        if (max_bin > MAX_ASTERISK)
        {
            height = MAX_ASTERISK * (static_cast<double> (bin) / max_bin);
        }


        if (bin < 100) {
            cout << " ";
        }

        if (bin < 10) {
            cout << " ";
        }
        cout << bin << "|";
        for (size_t i = 0; i < height; i++)
        {
            cout << "*";
        }
        cout << endl;
    }
}

vector<double>
input_numbers(size_t count) // ввод чисел
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}


int main()
{
    //ввод данных

    size_t number_count;
    cerr << "Enter number count: ";

    cin >> number_count;
    cerr << "Enter numbers: ";

    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter bin count: ";
    cin >> bin_count;

    //расчет данных

    const auto bins = make_histogram(numbers, bin_count);

    //вывод гистрограмы

    show_histogram_svg(bins);

    return 0;
}

