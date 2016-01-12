template <typename ArrayLike, typename T>
int ternary_search(const ArrayLike& array, const T& value, int low, int high) {

   int left = low + (high - low) / 3;
   int right = low + (high - low) * 2 / 3;
   
   if (value == array[left]) {
      return left;
   } else if (value == array[right]) {
      return right;
   }

   if (left == right) {
      return -1;
   }

   if (value > array[left] && value < array[right]) {
      return ternary_search(array, value, left, right);
   } else if (value < array[left]) {
      return ternary_search(array, value, low, left);
   } else if (value > array[right]) {
      return ternary_search(array, value, right, high);
   }

   return -1;
}