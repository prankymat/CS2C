#include <algorithm>
#include <iostream>
#include <vector>

#include "avl_tree.h"

int main() {
   // 2014 Total Pay for some Foothill CS faculty from
   // http://transparentcalifornia.com/export/2014-community-colleges.csv
   // and
   // http://www.foothill.edu/cs/schedule.php?act=1&dept=C%20S
//   std::vector<std::pair<int, std::string> > professors = {
//      {5089, "Rahul Agarwal"},
//      {15351, "Thomas Riordan"},
//      {20468, "Hadeel Ammari"},
//      {21617, "Viet Trinh"},
//      {36983, "Bita Mazloom"},
//      {38966, "David Harden"},
//      {46862, "Rula Khayrallah"},
//      {49732, "Jesse Cecil"},
//      {52952, "Anand Venkataraman"},
//      {97262, "Ladawn Meade"},
//      {130809, "Elaine Haight"},
//      {144740, "Michael Loceff"},
//      {180789, "William Murphy"},
//   };


   std::vector<std::pair<int, std::string> > professors = {
      {1, "Rahul Agarwal"},
      {2, "Thomas Riordan"},
      {3, "Hadeel Ammari"},
      {4, "Rahul Agarwal"},
      {5, "Thomas Riordan"},
      {6, "Hadeel Ammari"},
      {7, "Rahul Agarwal"},
      {8, "Thomas Riordan"},
      {9, "Hadeel Ammari"},
      {10, "Rahul Agarwal"},
   };

//   std::vector<std::pair<int, std::string> > professors = {
//      {1, "Rahul Agarwal"},
//      {2, "Thomas Riordan"},
//      {3, "Hadeel Ammari"},
//   };


   AVLTree<int, std::string> tree;

//   std::random_shuffle(professors.begin(), professors.end());
   for (const auto& pay_name_pair : professors) {
      std::cout << "insert(" << pay_name_pair.first << ", "
      << pay_name_pair.second << ")" << std::endl;
      tree.insert(pay_name_pair.first, pay_name_pair.second);
   }
   
   std::cout << std::endl;

   for (const auto& pay_name_pair : professors) {
      const auto& key = pay_name_pair.first;
      std::cout << "get(" << key << ") == " << tree.get(key) << std::endl;
   }
   return 0;
}