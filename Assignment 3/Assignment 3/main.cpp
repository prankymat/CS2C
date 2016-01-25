//
//  main.cpp
//  Assignment 3
//
//  Created by Matthew Wo on 1/19/16.
//  Copyright © 2016 Matthew Wo. All rights reserved.
//

#include <iostream>

#include <vector>

#include "doubly_linked_list.h"

using namespace std;

int main(int argc, const char * argv[]) {

   DoublyLinkedList<int> dList;

//   for (int i = 0; i < 4; ++i) {
//      dList.push_back(i);
//   }

   dList.push_back(1);
   dList.push_back(2);
   dList.push_back(3);

   dList.remove(3);

   for (auto itr : dList) {
      cout << "here" << itr;
   }

//   int *a = new int(3);
//   int *b = a;
//   int c = 10;
//
//   a = &c;
//   delete b;


//
//   dList.erase(dList.begin());
//   for (auto itr : dList) {
//      cout << itr << endl;
//   }

//   cout << "---\n";
//
//   dList.erase(dList.begin());
//   for (auto itr : dList) {
//      cout << itr << endl;
//   }

//   cout << "---\n";
//
//   dList.erase(--dList.end());
//   for (auto itr : dList) {
//      cout << itr << endl;
//   }

//   for (auto itr = dList.rbegin(); itr != dList.rend(); ++itr) {
//      cout << *itr << endl;
//   }



//   std::cout << "Size: " << dList.size() << "\n";


//   auto itr = dList.begin();
//
//   itr = dList.erase(itr);
//
//   ++itr; ++itr;
//   dList.erase(itr);
//
//   itr = --dList.end();
//
//   dList.erase(itr);



//   dList.insert(found, 100);

//   auto end = dList.end();
//   dList.insert(++(++dList.begin()), 1000);
//   dList.insert(--(--end), 9000);
//
//   dList.remove(0);
//   dList.remove(9);
//   dList.remove(1);
//   dList.remove(2);
//   dList.remove(3);
//   dList.remove(3000);
//
//   end = dList.end();
//   dList.erase(--(--end));

   


//   for (auto itr = --dList.end(); itr != dList.begin(); --itr) {
//      cout << "erasing: " << *itr << endl;
//      dList.erase(itr);
//   }

//   for (auto itr = dList.begin(); itr != dList.end(); ++itr) {
//      cout << "erasing: " << *itr << endl;
//      dList.erase(itr);
//   }



//   for (auto iter = dList.end(), iter_end = dList.begin(); iter != iter_end; --iter) {
//      cout << *iter << " ";
//   }
//   cout << "\nsize is: " << dList.size() << "\n";

//   DoublyLinkedList<string> sentence;
//   sentence.push_back("a");
//      sentence.push_back("b");
//      sentence.push_back("c");
//      sentence.push_back("d");
//
//   for (const std::string& word : sentence) {
//      cout << word << " ";
//   }
//   cout << "\nsize is: " << sentence.size() << "\n";
//   sentence.erase(--sentence.end());
//
//   for (const std::string& word : sentence) {
//      cout << word << " ";
//   }
//   cout << "\nsize is: " << sentence.size() << "\n";
//   sentence.erase(--sentence.end());
//
//   for (const std::string& word : sentence) {
//      cout << word << " ";
//   }
//   cout << "\nsize is: " << sentence.size() << "\n";
//   sentence.erase(++sentence.begin());
//
//   for (const std::string& word : sentence) {
//      cout << word << " ";
//   }
//   cout << "\nsize is: " << sentence.size() << "\n";
//   sentence.erase(sentence.begin());
//   
//   for (const std::string& word : sentence) {
//      cout << word << " ";
//   }
//   cout << "\nsize is: " << sentence.size() << "\n";



//   dList.erase(dList.begin());
//   dList.erase(++dList.begin());
//   dList.erase(--dList.end());

//   int i = 0;
//   for (auto itr = dList.begin(); itr != dList.end(); ++itr) {
//      std::cout << i++ << " " << *itr << "\n";
//   }
//
//   std::cout << "Size: " << dList.size() << "\n";

//   vector<int> intv;
//   intv.push_back(0);
//   intv.push_back(1);
//   intv.push_back(2);

//   for (auto itr = intv.begin(); itr != intv.end(); ++itr) {
//      intv.erase(itr);
//   }

//   cout << (intv.begin() == --(intv.end())) << endl;

//   for (auto itr = intv.begin(); itr != intv.end(); ++itr) {
//      cout << *itr << endl;
//   }


//   vector<int> v;
//   v.push_back(1);
//   v.push_back(2);
//   v.push_back(3);
//
//   for (auto itr = v.begin(); itr != ++v.end(); ++itr) {
//      auto i = v.erase(itr);
//      cout << *i << endl;
//   }
//   *v.end();
//
//   v.push_back(1);
//   v.erase(v.begin());
//   v.push_back(3);
//   v.push_back(4);
//   v.push_back(5);
//
//   vector<int>::iterator found;
//   for (vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr) {
//      if (*itr == 3) {
//         found = itr;
//      }
//   }
//
//   v.insert(found, 2);
//
//   for (auto itr : v) {
//      cout << itr << endl;
//   }

   return 0;
}
