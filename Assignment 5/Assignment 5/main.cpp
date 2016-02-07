#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>

#include "binary_search_tree.h"



void printKeyValString(int key, std::string val) {
   std::cout << key << " : " << val << "\n";
}

void printKeyValInt(int key, int val) {
   std::cout << key << " : " << val << "\n";
}

std::vector<int> v;
void extract(int key, std::string value) {
   v.push_back(key);
}

//void removeKey(int key, std::string val) {
//   std::cout << "Removing: " << key << "\n";
//   tree.remove(key);
//}

int main() {
   // 2014 Total Pay for some Foothill CS faculty from
   // http://transparentcalifornia.com/export/2014-community-colleges.csv
   // and
   // http://www.foothill.edu/cs/schedule.php?act=1&dept=C%20S
//
//   std::vector<std::pair<int, int> > professors = {
//      {11,1},
//      {5,1},
//      {1, 1},
//      {8,1},
//      {4,1},
//      {3, 1},
//      {12,1},
//      {2, 1},
//      {10,1},
//      {7,1},
//      {9,1},
//      {6,1},
//      {13,1},
//   };


//   std::vector<std::pair<int, std::string> > professors = {
//      {4, "0"},
//      {2, "0"},
//      {1, "0"},
//      {3, "0"},
//   };

//   std::vector<std::pair<int, std::string> > professors = {
//      {4, "0"},
//      {2, "0"},
//      {1, "0"},
//   };

//   std::vector<std::pair<int, std::string> > professors = {
//      {1, "0"},
//      {2, "0"},
//      {3, "0"},
//      {4, "0"},
//   };

//   std::vector<std::pair<int, std::string> > professors = {
//      {4, "0"},
//      {3, "0"},
//      {2, "0"},
//      {1, "0"},
//   };

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
//   std::random_shuffle(professors.begin(), professors.end());
   for (const auto& pay_name_pair : professors) {
      std::cout << "insert(" << pay_name_pair.first << ", "
      << pay_name_pair.second << ")" << std::endl;
      tree.insert(pay_name_pair.first, pay_name_pair.second);
   }
   std::cout << std::endl;


//   tree.for_each_key_val(removeKey);

//   for (int i = 0; i < 13; ++i) {
//      std::cout << "removing: " << i+1 << std::endl;
//      tree.remove(i+1);
//   }
   for (const auto& pay_name_pair : professors) {
      std::cout << "remove(" << pay_name_pair.first << ", "
      << pay_name_pair.second << ")" << std::endl;
      tree.remove(pay_name_pair.first);
   }

   std::cout << "\n\nprinting tree..." << "\n";

   tree.for_each_key_val(extract);

   std::cout << "is sorted " << std::is_sorted(v.begin(), v.end()) << "\n";

   std::cout << "\n\nending..." << "\n";

   return 0;
}