template <typename ArrayLike, typename T>
int ternary_search(const ArrayLike& array, const T& value, int low, int high) {
   if (low > high) {
      return -1;
   }

   int left = low + (high - low) / 3;
   int right = low + 2 * (high - low) / 3;

   if (value <= array[left]) {
      // Left pile
      return (value == array[left] ? left : ternary_search(array, value, low, left-1));
   } else if (value >= array[right]) {
      // Right pile
      return (value == array[right] ? right : ternary_search(array, value, right+1, high));
   } else {
      // Middle pile
      return ternary_search(array, value, left, right);
   }
}