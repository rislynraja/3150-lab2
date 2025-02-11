#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "./include/doctest.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int prefix_sum(int array[], int last) { /* last must be less than length of the array */
  int sum = 0;
  for (int i=0; i < last; i++) {
    sum += array[i];
  }
  return sum;
}

bool non_negative_sum(int myArray[], int len) { 
    bool value = true;
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += myArray[i];
        if (sum > 0) {
            value = false; // non negative value
            break;
        }
    }
    return value;
}

bool non_pos_prefix_sum(int myArray[], int len) {
    bool value = true;
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += myArray[i];
        if (sum < 0) {
            value = false; // non positive value
            break;
        }
    }
    return value;
}

void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void show_data(int array[], const int length) {
  for (int i=0; i < length; i++) {
    cout << array[i] << " ";
  }
  // cout << endl; // for going to the next line
}

void fisher_yates(int array[], const int length) {

  std::srand(std::time(nullptr)); // random number generated using the current time in seconds as the seed
  // without seed = same num; if inside loop = diff each time

  for (int i = length - 1; i > 0; i--) {
    int rnd_location = (std::rand()) % (i + 1); // random index to swap with
    swap(& array[i], & array[rnd_location]); // swapping
  }

}

void setupPlusAndMinuses(int ary[], int totalLength, int n){ // generates list (before shuffling w fisher yates)
    for (int i = 0; i < n; i++) {
        ary[i] = 1;
    }
    for (int i = n; i < totalLength; i++) {
        ary[i] = -1;
    }
}

int prefixSumChecker(int ary[], int totalLength) {
    
    bool test1 = non_negative_sum(ary, totalLength);
    bool test2 = non_pos_prefix_sum(ary, totalLength);

    if (test1 || test2) {
        return 1;
    }
    else {
        return 0; // none of the tests passed
    }
}

double lab2(int n, int iterations) {
    int totalLength = 2 * n;
    int allAry[iterations][totalLength]; // maybe store all arrays together
    int valid = 0;

    for (int i = 0; i < iterations; i++) {
        setupPlusAndMinuses(allAry[i], totalLength, n); // filling the first 𝑛 elements with 1 and the next 𝑛 elements with -1
        fisher_yates(allAry[i], totalLength); // call fisher yates to randomly shuffle list

        // Toss out any scrambled lists that do not have non-negative or non-positive prefix sums
        // . Count the number of non-negative and non-positive prefix sums and compare these with the 
        // total number of +1,-1 randomly generated sequences.

        if (prefixSumChecker(allAry[i], totalLength) == 1) {
            valid = valid + 1; // test passed so valid
        }

    }

    double finalRatio = (double)valid / iterations;
    return finalRatio;
}



TEST_CASE ("testing fisher yates algorithm + prefix sum checker") {

    // checking prefix sum using array i make directly
    int arr1[] = {1, -1, 1, -1, 1, -1};
    int arr2[] = {1, 1, 1, -1, 1, -1};
    int arr3[] = {1, -1, 1, 1, 1, 1};
    int arr4[] = {-1, -1, 1, -1, 1, -1};
    int arr5[] = {-1, -1, -1, -1, 1, 1};
    CHECK(prefixSumChecker(arr1, 6) == 1);
    CHECK(prefixSumChecker(arr2, 6) == 1);
    CHECK(prefixSumChecker(arr3, 6) == 1);
    CHECK(prefixSumChecker(arr4, 6) == 1);
    CHECK(prefixSumChecker(arr5, 6) == 1);

    // check small edge case
    int arr11[] = {1, -1};
    int arr12[] = {-1, 1};
    fisher_yates(arr11, 2);
    fisher_yates(arr12, 2);
    CHECK(prefixSumChecker(arr11, 2) == 1);
    CHECK(prefixSumChecker(arr12, 2) == 1);

    // large number test cases
    double l1 = lab2(5, 2);
    double l2 = lab2(2, 500);
    double l3 = lab2(2, 1000);
    double l4 = lab2(2, 10000);
    double l5 = lab2(20, 10000);

    CHECK(l1 >= 0.0);
    CHECK(l1 <= 1.0); // range should be right
    CHECK(l2 >= 0.0);
    CHECK(l2 <= 1.0);
    CHECK(l3 >= 0.0);
    CHECK(l3 <= 1.0);
    CHECK(l4 >= 0.0);
    CHECK(l4 <= 1.0);
    CHECK(l5 >= 0.0);
    CHECK(l5 <= 1.0);
    
    int n2 = 100;
    int arr22[2 * n2];
    setupPlusAndMinuses(arr22, 2 * n2, n2);
    fisher_yates(arr22, 2 * n2);
    CHECK(prefixSumChecker(arr22, 2 * n2) == 0);

}