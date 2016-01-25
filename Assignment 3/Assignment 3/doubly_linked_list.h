// Contents of "doubly_linked_list.h":
#ifndef _DOUBLY_LINKED_LIST_H_
#define _DOUBLY_LINKED_LIST_H_

#include <initializer_list>

template <typename T>
class DoublyLinkedList {
   class node {
   public:
      node() : previous(nullptr), next(nullptr), obj(nullptr) {};
      node(node *previous, node *next, T obj) : obj(obj), previous(previous), next(next) {};
      T obj;
      node *previous;
      node *next;
   };

   // Any data members you need should go here, in the private section
   node *front;
   node *back;

   int size_;
public:
   class iterator {
      // Any data members you need should go here, in the private section
      bool reversed;
      node *current;
      node *previous;

      // Private non-default constructor to hide it from client.
      iterator(node *previous, node *current, bool reversed) : reversed(reversed), current(current), previous(previous) {};

   public:
      iterator() : reversed(false), current(nullptr), previous(nullptr) {};
      // Prefix --
      iterator& operator--() {
         if (!reversed) {
            previous = current;
            current = current ? current->previous : nullptr;
         } else {
            previous = current;
            current = (current ? current->next : nullptr);
         }
         return *this;
      };
      // Prefix ++
      iterator& operator++() {
         if (!reversed) {
            // go right
            previous = current;
            current = (current ? current->next : nullptr);
         } else {
            // go left
            current = current ? current->previous : nullptr;
            previous = current;
         }
         return *this;
      };
      T& operator*() { return current->obj; };
      const T& operator*() const { return (const T&)current->obj; };
      bool operator!=(const iterator& other) const { return current != other.current && previous != other.previous; };

      friend class DoublyLinkedList;
   };


   ~DoublyLinkedList() {
      for (iterator itr = begin(); itr != end(); ++itr) {
         erase(itr);
      }
   };

   DoublyLinkedList() : front(nullptr), back(nullptr), size_(0) {};
   DoublyLinkedList(const DoublyLinkedList& other) {
      for (auto itr : other.begin()) {
         push_back(*itr);
      }
   };
   DoublyLinkedList(std::initializer_list<T> list) : DoublyLinkedList() {
      for (auto itr : list) {
         push_back(itr);
      }
   };

   int size() const noexcept { return size_; };
   void push_back(const T& value) {
      if (size_++ == 0) {
         // is empty list, prepend.
         front = new node(nullptr, nullptr, value);
         back = front;
      } else {
         // is not empty list, append.
         node *n = new node(back, nullptr, value);
         back -> next = n;
         back = n;
      }
   };
   void remove(const T& val) {
      auto itr_end = end();
      for (auto itr = begin(); itr != itr_end;) {
         if (*itr == val) {
            erase(itr);
         } else {
            ++itr;
         }
      }
   };

   iterator erase(iterator position) {
      if (!position.current && position.previous) {
         // is end
         return position;
      }

      node *to_be_deleted = position.current;
      if (!position.previous && position.current) {
         // is front
         node *next = position.current->next;
         front = next;

         // assign only if front is not null
         front && (front->previous = nullptr);

         // update position
         position.current = front;
         position.previous = nullptr;
      } else if (position.current && !position.current->next) {
         // is back
         node *prev = position.previous;
         back = prev;

         to_be_deleted = prev->next;
         prev->next = nullptr;

         // update position
         position.current = nullptr;
         position.previous = back;
      } else {
         // is middle
         node *head = position.previous;
         node *tail = position.current->next;
         head->next = tail;
         tail->previous = head;

         // update position
         position.current = tail;
         position.previous = head;
      }

      --size_;
      delete to_be_deleted;
      return position;

//      node *cur = position.current;
//      if (cur == nullptr && position.previous != nullptr) {
//         // is end
//         return position;
//      } else if (position.previous == nullptr) {
//         // is front
//         if (size_ == 1) {
//            // only one element
//            front = back = nullptr;
//            position.current = nullptr;
//            position.previous = nullptr;
//         } else {
//            // has linked nodes
//            node *next = cur->next;
//            next->previous = nullptr;
//            front = next;
//            position.current = front;
//            position.previous = nullptr;
//         }
//      } else if (cur->next == nullptr) {
//         // is back
//         node *previous = position.previous;
//         position.previous->next = nullptr;
//         back = previous;
//         position.current = previous;
//         position.previous = back->previous;
//      } else {
//         // is middle
//         position.previous->next = cur->next;
//         cur->next->previous = position.previous;
//         position.current = cur->next;
//         position.previous = cur->previous;
//      }
//      --size_;
//      delete cur;
//      return position;
   };
   iterator insert(iterator position, const T& value) {
      node *cur = position.current;
      if (position.previous == nullptr && position.current != nullptr) {
         // is begin
         node *temp = new node(nullptr, front, value);
         front->previous = temp;
         front = temp;
         cur = temp;
      } else if (position.current == nullptr && position.previous != nullptr) {
         // is end
         node *temp = new node(back, nullptr, value);
         back->next = temp;
         back = temp;
         cur = temp;
      } else {
         // is middle
         node *temp = new node(cur->previous, cur, value);
         cur->previous->next = temp;
         cur->previous = temp;
         cur = temp;
      }
      ++size_;
      return iterator(position.previous, cur, position.reversed);
   };

   iterator begin() { return iterator(nullptr, front, false); };
   iterator rbegin() { return iterator(nullptr, back, true); };
   iterator end() { return iterator(back, nullptr, false); };
   iterator rend() { return iterator(front, nullptr, true); };
};

#endif  // _DOUBLY_LINKED_LIST_H_