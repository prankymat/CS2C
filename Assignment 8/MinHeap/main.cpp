//
//  main.cpp
//  MinHeap
//
//  Created by Matthew Wo on 2/24/16.
//  Copyright © 2016 Matthew Wo. All rights reserved.
//

#include <iostream>

#include "minheap.h"
int main(int argc, const char * argv[]) {
   // insert code here...
//   std::cout << "Hello, World!\n";

   MinHeap<int> minheap;

   int arr[] = {3,2,1,0,-1,12,13,15,16,18,19,20,21,22};
//   int arr[] = {-1,0,1,2,3};
   for (auto a : arr) {
      minheap.push(a);
      printf("After pushing %d, top is %d\n", a, minheap.top());
   }


   int size = minheap.size();
   for (int i = 0; i < size; ++i) {
      printf("Before popping, top is %d\n", minheap.top());
      minheap.pop();
//      printf("After popping %dth time, top is now %d, size is %d\n", i+1, minheap.top(), minheap.size());
   }
//   minheap.push(2);
//   minheap.push(1);
//   minheap.push(0);
//   minheap.push(-1);
//   minheap.push(-2);
//   minheap.push(-3);
//   std::cout << minheap.top() << "\n";
//   minheap.pop();
//   std::cout << minheap.top() << "\n";
//   minheap.pop();
//   std::cout << minheap.top() << "\n";
    return 0;
}
