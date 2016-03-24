//
//  main.cpp
//  Sort
//
//  Created by Matthew Wo on 3/11/16.
//  Copyright © 2016 Matthew Wo. All rights reserved.
//

#include <iostream>

#include "merge_sort.h"

int main(int argc, const char * argv[]) {

   std::vector<long> v;

   v.push_back(5);
   v.push_back(4);
   v.push_back(3);
   v.push_back(2);
   v.push_back(1);

   sort(v);

   for (auto itr : v) {
      printf("%ld\n", itr);
   }

   return 0;
}
