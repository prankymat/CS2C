#include <iostream>
#include "ternary_search.h"

using namespace std;

template <class T>
class MyArray {
private:
   T* arr;
   int size;
public:
   MyArray(T* arr, int size) : arr(arr), size(size) {};
   T& operator[](int index);
   T& operator[](int index) const;
};

template <class T>
T& MyArray<T>::operator[](int index) {
   if (index >= size) {
      cout << "WARNING: index: " << index << " greater than " << size << endl;
   }
   cout << "accessing index: " << index << endl;
   return arr[index];
};

template <class T>
T& MyArray<T>::operator[](int index) const {
   if (index >= size) {
      cout << "WARNING: index: " << index << " greater than " << size << endl;
   }
   cout << "const accessing index: " << index << endl;
   return arr[index];
};

void test1() {
   int nums[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
   for (int i = 0; i <= 90; i += 10) {
      if (ternary_search(nums, i, 0, 10) != i / 10) {
         std::cout
         << "Searching for " << i << " returned index "
         << ternary_search(nums, i, 0, 10) << " instead of "
         << i / 10 << "." << std::endl;
         return;
      }

      // search for something that doesn't exist.
      if (ternary_search(nums, i + 1, 0, 10) != -1) {
         std::cout
         << "Searching for " << i + 1 << " returned index "
         << ternary_search(nums, i + 1, 0, 10) << " instead of -1."
         << std::endl;
         return;
      }
   }
   std::cout << "On this small example, your search algorithm seems correct.\n";
}

int main() {
   int nums2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
//   std::cout << ternary_search(nums2, 4, 0, 10) << std::endl;
   MyArray<int> arr(nums2, 10);

   cout << ternary_search(arr, 11, 0, 10) << endl;

   test1();

   int nums3[] = {0};

   MyArray<int> arr2(nums3, 986);
   cout << ternary_search(arr2, 723, 0, 986) << endl;

   return 0;
}
