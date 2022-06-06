#include <math.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include "histogram.h"

using namespace std;

void svg_rect(double x, double y, double width, double height, string stroke = "blue", string fill = "#aaffaa") {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />\n";
}

void
svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>\n";
}

void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() {
    cout << "</svg>\n";
}

void
show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    double top = 0;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    for (size_t bin : bins) {
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
        top += BIN_HEIGHT;
    }
    //svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    //svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bins[0]));
    //svg_rect(TEXT_WIDTH, top, bins[0] * BLOCK_WIDTH, BIN_HEIGHT);
    svg_end();
}


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

