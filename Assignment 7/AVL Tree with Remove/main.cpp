#include <algorithm>
#include <iostream>
#include <vector>

#include "avl_tree.h"

#include <random>

std::mt19937 r{std::random_device{}()};

int main() {
   // 2014 Total Pay for some Foothill CS faculty from
   // http://transparentcalifornia.com/export/2014-community-colleges.csv
   // and
   // http://www.foothill.edu/cs/schedule.php?act=1&dept=C%20S
//   std::vector<std::pair<int, std::string> > professors = {
//      {1, "Rahul Agarwal"},
//      {2, "Thomas Riordan"},
//      {3, "Hadeel Ammari"},
//      {4, "Viet Trinh"},
//      {5, "Bita Mazloom"},
//      {6, "David Harden"},
//      {7, "Rula Khayrallah"},
//      {8, "Jesse Cecil"},
//      {9, "Anand Venkataraman"},
//      {10, "Ladawn Meade"},
//      {11, "Elaine Haight"},
//      {12, "Michael Loceff"},
//      {13, "William Murphy"},
//   };

//   std::vector<std::pair<int, std::string> > professors = {
//      {5, "Rahul Agarwal"},
//      {1, "Thomas Riordan"},
//      {4, "Hadeel Ammari"},
//      {3, "Viet Trinh"},
//      {2, "Bita Mazloom"},
//   };

   std::vector<std::pair<int, std::string> > professors = {
      {1, "Rahul Agarwal"},
      {2, "Thomas Riordan"},
      {3, "Hadeel Ammari"},
      {4, "Viet Trinh"},
      {5, "Bita Mazloom"},
   };


//   std::shuffle(professors.begin(), professors.end(), r);

   AVLTree<int, std::string> tree;

   for (const auto& pay_name_pair : professors) {
      std::cout << "insert(" << pay_name_pair.first << ", "
      << pay_name_pair.second << ")" << std::endl;
      tree.insert(pay_name_pair.first, pay_name_pair.second);
      printf("Printing tree\n");
      tree.display(tree.root, 0);
      printf("\n");
   }
   std::cout << std::endl;

   tree.display(tree.root, 0);

   std::cout << std::endl;

   for (const auto& pay_name_pair : professors) {
      const auto& key = pay_name_pair.first;
      std::cout << "get(" << key << ") == " << tree.get(key) << std::endl;
   }

//   std::random_shuffle(professors.begin(), professors.end());
   for (const auto& pay_name_pair : professors) {
      std::cout << "remove(" << pay_name_pair.first << ", "
      << pay_name_pair.second << ")" << std::endl;
      tree.remove(pay_name_pair.first);
      // maybe some print statements to see how the tree looks...

      printf("Printing tree after removing %d\n", pay_name_pair.first);

      tree.display(tree.root, 0);

      printf("\n\n");
   }

//   for (const auto& i : {5,1,4,2,3}) {
//      std::cout << "remove(" << i << ")" << std::endl;
//      tree.remove(i);
//      // maybe some print statements to see how the tree looks...
//
//      printf("Printing tree after removing %d\n", i);
//
//      tree.display(tree.root, 0);
//
//      printf("\n\n");
//   }

   return 0;
}