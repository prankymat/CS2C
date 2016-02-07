#ifndef binary_search_tree_h
#define binary_search_tree_h

template <typename Key, typename Value>
struct BinarySearchTreeNode {
   BinarySearchTreeNode *left, *right, *parent;
   Key key;
   Value value;

   BinarySearchTreeNode(const Key& key, const Value& value, BinarySearchTreeNode* parent)
   : left(nullptr), right(nullptr), parent(parent), key(key), value(value) {}

   bool operator>(const Key& key) const {
      return this->key > key;
   };

   bool operator<(const Key& key) const {
      return this->key < key;
   };

   bool operator==(const Key& key) const {
      return this->key == key;
   };

   bool isNode() { return !left && !right; };

   ~BinarySearchTreeNode() {
      delete left;
      delete right;
   };
};

template <typename Key, typename Value>
class BinarySearchTree {

private:
   BinarySearchTreeNode<Key, Value>* getNode(const Key& key, BinarySearchTreeNode<Key, Value>* tree) const {
      if (*tree == key) {
         return tree;
      }

      if (*tree < key) {
         return getNode(key, tree->right);
      } else {
         return getNode(key, tree->left);
      }
   }

   Value& get(const Key& key, BinarySearchTreeNode<Key, Value>* tree) const {
      return getNode(key, tree)->value;
   };

   void insert(const Key& key, const Value& value, BinarySearchTreeNode<Key, Value>* node) {
      if (*node < key) {
         if (node->isNode() || !node->right) {
            node->right = new BinarySearchTreeNode<Key, Value>(key, value, node);
         } else {
            insert(key, value, node->right);
         }
      } else if (*node > key) {
         if (node->isNode() || !node->left) {
            node->left = new BinarySearchTreeNode<Key, Value>(key, value, node);
         } else {
            insert(key, value, node->left);
         }
      }
   };

   BinarySearchTreeNode<Key, Value>* smallestOfNode(BinarySearchTreeNode<Key, Value>* node) {
      if (node && !node->left) {
         return node;
      }
      return smallestOfNode(node->left);
   };

   BinarySearchTreeNode<Key, Value>* biggestOfNode(BinarySearchTreeNode<Key, Value>* node) {
      if (node && !node->right) {
         return node;
      }
      return biggestOfNode(node->right);
   };

   template <typename Callable>
   void for_each_key_val(const Callable& callable, BinarySearchTreeNode<Key, Value>* node) {
      if (node) {
         for_each_key_val(callable, node->left);
         callable(node->key, node->value);
         for_each_key_val(callable, node->right);
      }
   };

   void removeNode(BinarySearchTreeNode<Key, Value>* target) {
      if (target->isNode()) {
         // Handle leaves case
         BinarySearchTreeNode<Key, Value>* targetParent = target->parent;
         if (targetParent) {
            // at bottom
            if (targetParent->right == target) {
               // right side of parent
               targetParent->right = nullptr;
            } else {
               // left side of parent
               targetParent->left = nullptr;
            }

            delete target;
         } else {
            // at root
            delete root;
            root = nullptr;
         }
      } else {
         // Handle stems case
         BinarySearchTreeNode<Key, Value>* replacement = nullptr;
         if (target->right) {
            replacement = smallestOfNode(target->right);
         }

         if (!replacement || replacement == target) {
            replacement = biggestOfNode(target->left);
         }

         target->key = replacement->key;
         target->value = replacement->value;

         removeNode(replacement);
      }
   };

public:
   BinarySearchTreeNode<Key, Value> *root;

   BinarySearchTree() : root(nullptr) {};

   ~BinarySearchTree() {
      delete root;
   };

   // Insert a value, while making sure the tree is still a binary search tree.
   // This assumes that the key does not exist in the tree.
   void insert(const Key& key, const Value& value) {
      if (!root) {
         root = new BinarySearchTreeNode<Key, Value>(key, value, nullptr);
      }
      insert(key, value, root);
   };

   // Remove the value associated with key,
   // while making sure the tree is still a binary search tree.
   // This assumes that the key exists.
   void remove(const Key& key) {
      BinarySearchTreeNode<Key, Value> *target = getNode(key, root);
      removeNode(target);
   };

   // Given a key, find the corresponding value.
   // This assumes that the key exists.
   Value& get(const Key& key) const {
      return get(key, root);
   };
   // Given a callable, that takes a Key and Value, call that callable
   // for every key/value pair in the tree in sorted order.
   // e.g. callable(Key(), Value())
   template <typename Callable>
   void for_each_key_val(const Callable& callable) {
      for_each_key_val(callable, root);
   };
};

#endif /* binary_search_tree_h */
