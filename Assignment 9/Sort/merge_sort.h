#ifndef merge_sort_h
#define merge_sort_h

#include <vector>

void merge(std::vector<long>& temp, std::vector<long>& left, std::vector<long>& right) {
   temp.clear();

   long l_index = 0, r_index = 0, k = 0;
   while(l_index < left.size() && r_index < right.size()) {
      if(left[l_index] <= right[r_index]) {
         temp.push_back(left[l_index++]);
      }else {
         temp.push_back(right[r_index++]);
      }
      ++k;
   }

   while(l_index < left.size()){
      temp.push_back(left[l_index++]);
   }

   while(r_index < right.size()){
      temp.push_back(right[r_index++]);
   }
}

void merge_sort(std::vector<long>& v) {
   if (v.size() > 1) {
      // sort only if more than one item
      auto mid = v.begin() + v.size() / 2;

      std::vector<long> left(v.begin(), mid);  // get left pile
      merge_sort(left);
      std::vector<long> right(mid, v.end());   // get right pile
      merge_sort(right);
      merge(v, left, right);
   }
}


void sort(std::vector<long>& values) {
   merge_sort(values);
}

#endif /* merge_sort_h */
