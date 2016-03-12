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

   bool isLeftChild() {
      return parent && parent->left == this;
   };

   bool isRightChild() {
      return parent && parent->right == this;
   };

   ~AVLTreeNode() {
      delete left;
      delete right;
   };
};

template <typename Key, typename Value>
class AVLTree {

private:
   int lrDifference(AVLTreeNode<Key, Value>* node) {
      int leftHeight = node && node->left ? node->left->height : 0;
      int rightHeight = node && node->right ? node->right->height : 0;
      return leftHeight - rightHeight;
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


   void insert(const Key& key, const Value& value, AVLTreeNode<Key, Value>* node) {
      if (key < node->key) {
         // Insert to left subtree
         if (node->left) {
            // Has child, go left
            insert(key, value, node->left);
         } else {
            // No more child, insert here
            auto child = new AVLTreeNode<Key, Value>(key, value, node);
            child->height = 1;
            node->left = child;
            balanceUpwards(node->left);
         }
      } else {
         // Insert to right subtree
         if (node->right) {
            // Has child, go right
            insert(key, value, node->right);
         } else {
            // No more child, insert here
            auto child = new AVLTreeNode<Key, Value>(key, value, node);
            child->height = 1;
            node->right = child;
            balanceUpwards(node->right);
         }
      }
   };

   int height(AVLTreeNode<Key, Value>* node) {
      int h = 0;
      if (node) {
         int l_height = height(node->left);
         int r_height = height(node->right);
         int max_height = std::max(l_height, r_height);
         h = max_height + 1;
      }
      return h;
   }

   void balanceUpwards(AVLTreeNode<Key, Value>* node) {
      if (node) {
         node->height = height(node);

         fixHeight(root);

         root = balance(root);

         fixHeight(root);

         balanceUpwards(node->parent);
      }
   }


   void updateHeightUpwards(AVLTreeNode<Key, Value>* node) {
      if (node) {
         int lHeight = node->left ? node->left->height : 0;
         int rHeight = node->right ? node->right->height : 0;
         node->height = std::max(lHeight, rHeight) + 1;
         updateHeightUpwards(node->parent);
      }
   };


   AVLTreeNode<Key, Value>* ll_rotation(AVLTreeNode<Key, Value>* parent) {
      auto temp = parent->left;
      parent->left = temp->right;

      parent->left && (parent->left->parent = temp);

      temp->right = parent;

      temp->right && (temp->right->parent = parent->parent);
      return temp;
   };

   AVLTreeNode<Key, Value>* rr_rotation(AVLTreeNode<Key, Value>* parent) {
      auto temp = parent->right;
      parent->right = temp->left;

      (parent->right) && (parent->right->parent = temp);

      temp->left = parent;

      (temp->left) && (temp->left->parent = parent->parent);
      return temp;
   };

   AVLTreeNode<Key, Value>*lr_rotation(AVLTreeNode<Key, Value>* parent) {
      auto temp = rr_rotation(parent->left);
      temp->parent = parent;
      parent->left = temp;

      temp = ll_rotation(parent);
      temp->parent = parent->parent;
      return temp;
   };

   AVLTreeNode<Key, Value>*rl_rotation(AVLTreeNode<Key, Value>* parent) {
      auto temp = ll_rotation(parent->right);
      temp->parent = parent;

      parent->right = temp;

      temp = rr_rotation (parent);
      temp->parent = parent->parent;
      return temp;
   };

   AVLTreeNode<Key, Value>* balance(AVLTreeNode<Key, Value>* node) {
      int lrFactor = lrDifference(node);
      if (lrFactor > 1) {
         // Left-Left or Left-Right
         if (lrDifference(node->left) > 0) {
            // Left-Left
            printf("Balance left left\n");
            auto temp = ll_rotation(node);
            temp->parent = node->parent;
            node = temp;
         } else {
            // Left-Right
            printf("Balance left right\n");
            auto temp = lr_rotation(node);
            temp->parent = node->parent;
            node = temp;
         }
      } else if (lrFactor < -1) {
         // Right-Left or Right-Right
         if (lrDifference(node->right) > 0) {
            // Right-Right
            printf("Balance right right\n");
            auto temp = rl_rotation(node);
            temp->parent = node->parent;
            node = temp;
         } else {
            // Right-Left
            printf("Balance right left\n");
            auto temp = rr_rotation(node);
            temp->parent = node->parent;
            node = temp;
         }
      } else {
         printf("Didn't need to balance at %d\n", node ? node->key : 0);
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

   void fixHeight(AVLTreeNode<Key, Value>* node) {
      if (node) {
         fixHeight(node->left);
         node->height = height(node);
         fixHeight(node->right);
      }
   }

   void fixParents(AVLTreeNode<Key, Value>* node, AVLTreeNode<Key, Value>* parent) {
      if (node) {
         fixParents(node->left, node);
         node->parent = parent;
         fixParents(node->right, node);
      }
   }


   void removeNode(AVLTreeNode<Key, Value>* target) {
      fixParents(root, nullptr);
      fixHeight(root);
      if (target->isLeaveNode()) {
         // Handle leaves case
         AVLTreeNode<Key, Value>* targetParent = target->parent;
         if (targetParent) {
            // at bottom
            if (target->isRightChild()) {
               // right side of parent
               targetParent->right = nullptr;
            } else if (target->isLeftChild()) {
               // left side of parent
               targetParent->left = nullptr;
            }
         } else {
            // at root
            root = nullptr;
         }

         delete target;
         balanceUpwards(targetParent);
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

         removeNode(replacement);
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
      if (root) {
         insert(key, value, root);
      } else {
         root = new AVLTreeNode<Key, Value>(key, value, nullptr);
         root->height = 1;
      }
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
      removeNode(target);
   };

   // Given a callable, that takes a Key and Value, call that callable
   // for every key/value pair in the tree in sorted order.
   // e.g. callable(Key(), Value())
   template <typename Callable>
   void for_each_key_val(const Callable& callable) {
      for_each_key_val(callable, root);
   };

   void display(AVLTreeNode<Key, Value> *ptr, int level)
   {
      int i;
      if (ptr!=NULL)
      {
         display(ptr->right, level + 1);
         printf("\n");
         if (ptr == root)
            std::cout<<"Root -> ";
         for (i = 0; i < level && ptr != root; i++)
            std::cout<<"        ";
         //         std::cout<<ptr->key;
         printf("(%d:%d)", ptr->key, ptr->height);
         display(ptr->left, level + 1);
      }
   }
};


#endif /* avl_tree_h */
