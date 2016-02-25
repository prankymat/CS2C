#ifndef avl_tree_h
#define avl_tree_h


template <typename Key, typename Value>
struct AVLTreeNode {
   AVLTreeNode *parent, *left, *right;
   Key key;
   Value value;
   // Note that the height of an empty tree is 0.
   int height;

   AVLTreeNode(const Key& key, const Value& value, AVLTreeNode<Key, Value>* parent)
   : parent(parent), left(nullptr), right(nullptr), key(key), value(value), height(0) {};

   bool isLeaveNode() {
      return left == nullptr && right == nullptr;
   };

   ~AVLTreeNode() {
      delete left;
      delete right;
   };
};

template <typename Key, typename Value>
class AVLTree {

private:
   void updateHeightUpwards(AVLTreeNode<Key, Value>* node) {
      if (node) {
         int lHeight = node->left ? node->left->height : 0;
         int rHeight = node->right ? node->right->height : 0;
         node->height = std::max(lHeight, rHeight) + 1;
         updateHeightUpwards(node->parent);
      }
   };

   int lrDifference(AVLTreeNode<Key, Value>* node) {
      int leftHeight = node && node->left ? node->left->height : 0;
      int rightHeight = node && node->right ? node->right->height : 0;
      return leftHeight - rightHeight;
   };

   AVLTreeNode<Key, Value>* ll_rotation(AVLTreeNode<Key, Value>* parent) {
      AVLTreeNode<Key, Value>*temp = parent->left;
      parent->left = temp->right;
      temp->right = parent;

      temp->parent = parent->parent;
      parent->parent = temp;
      return temp;
   };

   AVLTreeNode<Key, Value>* rr_rotation(AVLTreeNode<Key, Value>* parent) {
      AVLTreeNode<Key, Value>*temp = parent->right;
      parent->right = temp->left;
      temp->left = parent;

      temp->parent = parent->parent;
      parent->parent = temp;
      return temp;
   };

   AVLTreeNode<Key, Value>*lr_rotation(AVLTreeNode<Key, Value>* parent) {
      AVLTreeNode<Key, Value>*temp = parent->left;
      temp = rr_rotation(temp);

      temp->parent = parent;
      parent->left = temp;
      return ll_rotation (parent);
   };

   AVLTreeNode<Key, Value>*rl_rotation(AVLTreeNode<Key, Value>* parent) {
      AVLTreeNode<Key, Value>*temp = parent->right;

      temp = ll_rotation(temp);

      temp->parent = parent;
      parent->right = temp;

      return rr_rotation (parent);
   };

   void fixParents(AVLTreeNode<Key, Value> *ptr, AVLTreeNode<Key, Value>* parent) {
      if (ptr) {
         fixParents(ptr->left, ptr);
         ptr->parent = parent;
         fixParents(ptr->right, ptr);
      }
   }

   AVLTreeNode<Key, Value>* balance(AVLTreeNode<Key, Value>* node) {
      int lrFactor = lrDifference(node);

      if (lrFactor > 1) {
         // Left-Left or Left-Right
         if (lrDifference(node->left) > 0) {
            node = ll_rotation(node);
         } else {
            node = lr_rotation(node);
         }
      } else if (lrFactor < -1) {
         // Right-Left or Right-Right
         if (lrDifference(node->right) > 0) {
            node = rl_rotation(node);
         } else {
            node = rr_rotation(node);
         }
      }

      updateHeightUpwards(node->left);
      updateHeightUpwards(node->right);
      return node;
   };


   AVLTreeNode<Key, Value>* getNode(const Key& key, AVLTreeNode<Key, Value>* tree) const {
      if (tree->key == key) {
         return tree;
      }

      if (key > tree->key) {
         return getNode(key, tree->right);
      } else {
         return getNode(key, tree->left);
      }
   }

   Value& get(const Key& key, AVLTreeNode<Key, Value>* tree) const {
      return getNode(key, tree)->value;
   };

   template <typename Callable>
   void for_each_key_val(const Callable& callable, AVLTreeNode<Key, Value>* node) {
      if (node) {
         for_each_key_val(callable, node->left);
         callable(node->key, node->value);
         for_each_key_val(callable, node->right);
      }
   };

   AVLTreeNode<Key, Value>* insert(const Key& key, const Value& value, AVLTreeNode<Key, Value>* node) {
      if (!node) {
         // empty node, create a new node.
         node = new AVLTreeNode<Key, Value>(key, value, nullptr);
         node->height = 1;

      } else if (key < node->key) {
         // key < node, insert to node left
         node->left = insert(key, value, node->left);

         node->left->parent = node;

         // balance the inserted node
         node = balance(node);
      } else if (key > node->key) {
         // key > node, insert to node right
         node->right = insert(key, value, node->right);

         node->right->parent = node;

         // balance the inserted node
         node = balance(node);
      }
      
      return node;
   };

   AVLTreeNode<Key, Value>* smallestOfNode(AVLTreeNode<Key, Value>* node) {
      if (node && !node->left) {
         return node;
      }
      return smallestOfNode(node->left);
   };

   AVLTreeNode<Key, Value>* biggestOfNode(AVLTreeNode<Key, Value>* node) {
      if (node && !node->right) {
         return node;
      }
      return biggestOfNode(node->right);
   };

   AVLTreeNode<Key, Value>* removeNode(AVLTreeNode<Key, Value>* target) {
      if (target->isLeaveNode()) {
         // Handle leaves case
         AVLTreeNode<Key, Value>* targetParent = target->parent;
         if (targetParent) {
            // at bottom
            if (targetParent->right == target) {
               // right side of parent
               targetParent->right = nullptr;
            } else {
               // left side of parent
               targetParent->left = nullptr;
            }
         } else {
            // at root
            root = nullptr;
         }

         delete target;
         printf("Returning targetParent: %d\n", targetParent->key);
         return targetParent;
      } else {
         // Handle stems case
         AVLTreeNode<Key, Value>* replacement = nullptr;
         if (target->right) {
            replacement = smallestOfNode(target->right);
         }

         if (!replacement || replacement == target) {
            replacement = biggestOfNode(target->left);
         }

         target->key = replacement->key;
         target->value = replacement->value;

         return removeNode(replacement);
      }
   };

public:
   AVLTreeNode<Key, Value> *root;

   AVLTree() : root(nullptr) {};

   ~AVLTree() {
      delete root;
   };

   // Insert a value, while making sure the tree is still a binary search tree.
   // This assumes that the key does not exist in the tree.
   void insert(const Key& key, const Value& value) {
      root = insert(key, value, root);
   };

   // Given a key, find the corresponding value.
   // This assumes that the key exists.
   Value& get(const Key& key) const {
      return get(key, root);
   };

   // Remove the value associated with key,
   // while making sure the tree is still a AVL tree.
   // This assumes that the key exists.
   void remove(const Key& key) {
      AVLTreeNode<Key, Value>* target = getNode(key, root);
      AVLTreeNode<Key, Value>* targetParent = removeNode(target);

      // Balance upwards
      while (targetParent) {
         if (targetParent->left == target) {
            targetParent->left = balance(targetParent->left);
         } else if (targetParent->right == target) {
            targetParent->right = balance(targetParent->right);
         } else {
            printf("OH SHIT SOMETHING ELSE.\n");
         }

         // go up one level
         targetParent = targetParent->parent;
      }
   };

   // Given a callable, that takes a Key and Value, call that callable
   // for every key/value pair in the tree in sorted order.
   // e.g. callable(Key(), Value())
   template <typename Callable>
   void for_each_key_val(const Callable& callable) {
      for_each_key_val(callable, root);
   };
};


#endif /* avl_tree_h */
