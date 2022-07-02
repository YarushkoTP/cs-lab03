#include <math.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include "histogram.h"
#include "svg.h"

using namespace std;

struct Input {
    vector<double> numbers;
    size_t bin_count;
};

vector<double> input_numbers(istream& in, size_t cnt) {
    vector<double> result(cnt);
    for (size_t i = 0; i < cnt; i++)
    {
        in >> result[i];
    }
    return result;
}

Input read_input(istream& in, bool prompt) {
    Input data;
    if (prompt)
        cerr << "enter number count: ";
    size_t number_count;
    in >> number_count;
    if (prompt)
        cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);
    if (prompt)
        cerr << "enter bin count: ";
    in >> data.bin_count;
    return data;
}

vector<size_t> make_histogram(Input input)
{
    double min, max;
    find_minmax(input.numbers, min, max);
    double bin_size = (max - min) / input.bin_count;
    vector<size_t> bins(input.bin_count, 0);
    for (size_t i = 0; i < input.numbers.size(); i++){
        bool found = false;
        for (size_t j = 0; j < input.bin_count - 1 && !found; j++){
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;

            if (lo <= input.numbers[i] && input.numbers[i] < hi){
                bins[j]++;
                found = true;
            }
        }
        if (!found){
            bins[input.bin_count - 1]++;
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

int main(istream& in, bool prompt, const vector<double>& numbers, size_t bin_count)
{
    //ввод данных

    const auto input = read_input(cin, true);

    //расчет данных

    const auto bins = make_histogram(input);

    //вывод гистрограмы

    show_histogram_svg(bins);

    return 0;
}
