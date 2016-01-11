template <typename ArrayLike, typename T>
int ternary_search(const ArrayLike& array, const T& value, int low, int high) {
   // Replace the code below with code that actually does a tenary search.
   for (int i = low; i < high; ++i) {
      if (array[i] == value) {
         return i;
      }
   }
   return -1;
}