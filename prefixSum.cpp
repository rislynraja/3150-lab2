#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "./include/doctest.h"
#include <iostream>
#include "prefixSum.h"

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
        if (sum < 0) {
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
        if (sum > 0) {
            value = false; // non positive value
            break;
        }
    }
    return value;
}