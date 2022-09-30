#include <math.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>
#include <sstream>
#include <string>
#include <windows.h>

using namespace std;

struct Input {
    vector<double> numbers;
    size_t bin_count;
};

void
ver(int argc, char** argv, CURL* curl) {
	bool verbose = false;

	for (int i = 0; i < argc && !verbose; i++)
	{
		if (bool(strstr(argv[i], "-verbose"))) {
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
			verbose = true;
		}
	}

	bool oper = false;
	if (!verbose) {
		for (int i = 0; i < argc && !oper; i++)
		{
			if (bool(strstr(argv[i], "-"))) {
				oper = true;

				cerr << "U CAN!";
			}
		}
	}

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

size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    size_t data_size = item_size * item_count;
    buffer->write((char*)items, data_size);
    return data_size;
}

Input download(const string& address, bool flag) {
    long L=0;
    stringstream buffer;
    CURL *curl = curl_easy_init();
        if(curl) {
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            if (flag)
                curl_easy_setopt(curl, CURLOPT_VERBOSE, L);
            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                cerr << curl_easy_strerror(res) << endl;
                exit(1);
            }
            curl_easy_cleanup(curl);
        }

    return read_input(buffer, false);
}

int main(int argc, char* argv[])
{
    //¬вод исходных данных
    Input input;

    if (argc > 1) {
        bool flag = false;
        for (int i = 0; i < argc; i++)
        {
            if (!strcmp(argv[i], "-verbose")) //сравнение строк
                flag = true;
            else
                if (!strncmp(argv[i], "-", 1)) //сравнение первого символа
                {
                    cerr << "-verbose in work" << endl;
                    return 0;
                }
            if (flag)
            {
                if (!strcmp(argv[1], "-verbose"))
                    input = download(argv[2], flag);
                else
                    input = download(argv[1], flag);
            }
            else
                input = download(argv[1], flag);
        }
    }
        else
            input = read_input(cin, true);

    const auto bins = make_histogram(input); //обработка данных
    show_histogram_svg(bins); //вывод
    return 0;
    }
