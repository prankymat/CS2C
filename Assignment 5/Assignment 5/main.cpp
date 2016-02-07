#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>

#include "binary_search_tree.h"

void printKeyValString(int key, std::string val) {
   std::cout << key << " : " << val << "\n";
}

int main() {
   // 2014 Total Pay for some Foothill CS faculty from
   // http://transparentcalifornia.com/export/2014-community-colleges.csv
   // and
   // http://www.foothill.edu/cs/schedule.php?act=1&dept=C%20S

   std::vector<std::pair<int, std::string> > professors = {
      {11,"Rahul Agarwal"},
      {5,"Thomas Riordan"},
      {1,"Hadeel Ammari"},
      {4,"Viet Trinh"},
      {7,"Bita Mazloom"},
      {12,"David Harden"},
      {3,"Rula Khayrallah"},
      {2,"Jesse Cecil"},
      {13,"Anand Venkataraman"},
      {10,"Ladawn Meade"},
      {8, "Elaine Haight"},
      {9, "Michael Loceff"},
      {6, "William Murphy"},
   };

   BinarySearchTree<int, std::string> tree;
   std::random_shuffle(professors.begin(), professors.end());
   for (const auto& pay_name_pair : professors) {
      std::cout << "insert(" << pay_name_pair.first << ", "
      << pay_name_pair.second << ")" << std::endl;
      tree.insert(pay_name_pair.first, pay_name_pair.second);
   }
   std::cout << std::endl;


   for (const auto& pay_name_pair : professors) {
      std::cout << "remove(" << pay_name_pair.first << ", "
      << pay_name_pair.second << ")" << std::endl;
      tree.remove(pay_name_pair.first);
   }

   std::cout << "\n\nprinting tree..." << "\n";

   tree.for_each_key_val(printKeyValString);

   std::cout << "\n\nending..." << "\n";

   return 0;
}