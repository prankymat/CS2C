#include <vector>

template<typename T>
class MinHeap {
private:
   void swap(long a, long b) {
      T temp = values[a];
      values[a] = values[b];
      values[b] = temp;
   };

   void floatTop() {
      // Heapify
      long index = size()-1;
      long parent = (index-1)/2;

      while (index >= 0 && parent >= 0 && values[index] < values[parent]) {
         swap(index, parent);
         index = parent;
         parent = (index-1)/2;
      }
   }

   void sinkBottom(long index = 0) {
      long left = 2*index + 1;
      long right = 2*index + 2;

      long size_ = values.size();

      bool didSwap = false;

      if (index < size_ && (left < size_ || right < size_)) {
         // may need swap
         if (left >= size_) {
            // only right parent
            if (values[right] < values[index]) {
               // need swap
               swap(index, right);
               index = right;
               didSwap = true;
            }
         } else if (right >= size_) {
            // only left parent
            if (values[left] < values[index]) {
               // need swap
               swap(index, left);
               index = left;
               didSwap = true;
            }
         } else {
            // have both parents
            if (values[left] < values[index] || values[right] < values[index]) {
               // need swap
               long swap_index = 0;
               if (values[left] < values[right]) {
                  swap_index = left;
               } else {
                  swap_index = right;
               }

               swap(index, swap_index);
               index = swap_index;
               didSwap = true;
            }
         }
      }

      if (didSwap) {
         sinkBottom(index);
      }
   }

public:
   std::vector<T> values;  // in real life, values would be private
   typedef typename std::vector<T>::iterator iterator;

   void push(const T& value) {
      values.push_back(value);
      floatTop();
   };

   void pop() {
      swap(0, size()-1);
      values.pop_back();
      sinkBottom();
   };

   const T& top() const {
      return values[0];
   };

   const int size() {
      return int(values.size());
   };

   const bool empty() const {
      return values.empty();
   };

   iterator begin() {
      return values.begin();
   };

   iterator end() {
      return values.back();
   };
};