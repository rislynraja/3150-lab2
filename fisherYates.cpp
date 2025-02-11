#include <iostream>
#include <random>
#include "fisherYates.h"

#include <cstdlib>
#include <ctime>

using namespace std;

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
