template <typename ArrayLike, typename T>
int ternary_search(const ArrayLike& array, const T& value, int low, int high) {
   if (low == high) {
      return -1;
   }

   int third = (high - low) / 3;
   int left = low + third;
   int right = low + 2 * third;

   if (value <= array[left]) {
      // Left pile
      if (value == array[left]) {
         // Found at left
         return left;
      }
      return ternary_search(array, value, low, left);
   } else if (value >= array[right]) {
      // Right pile
      if (value == array[right]) {
         // Found at right
         return right;
      }
      return ternary_search(array, value, right+1, high);
   } else {
      // Middle pile
      return ternary_search(array, value, left+1, right);
   }
}