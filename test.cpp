#include "histogram.h"

#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void
test_negative() {
    double min = -10000;
    double max = -10000;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}

void
test_same() {
    double min = -10000;
    double max = 10000;
    find_minmax({2, 2, 2}, min, max);
    assert(min == 2);
    assert(max == 2);
}

void
test_single() {
    double min = -10000;
    double max = 10000;
    find_minmax({2}, min, max);
    assert(min == 2);
    assert(max == 2);
}

void
test_vacuum() {
    double min = -10000;
    double max = 10000;
    find_minmax({}, min, max);
    assert(min == -10000);
    assert(max == 10000);
}


int
main() {
    test_positive();
    test_negative();
    test_same();
    test_single();
    test_vacuum();
}
