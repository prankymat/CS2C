#ifndef avl_tree_h
#define avl_tree_h

template <typename Key, typename Value>
struct AVLTreeNode {
   AVLTreeNode *parent, *left, *right;
   Key key;
   Value value;

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

//   int difference() {
//      int left_height = left ? left->height : 0;
//      int right_height = right ? right->height : 0;
//
//      return right_height - left_height;
//   };

   // Note that the height of an empty tree is 0.
   int height;

   AVLTreeNode(const Key& key, const Value& value, AVLTreeNode<Key, Value>* parent)
               : parent(parent), left(nullptr), right(nullptr), key(key), value(value), height(0) {};

   ~AVLTreeNode() {
      delete left;
      delete right;
   };
};

template <typename Key, typename Value>
class AVLTree {

private:
   int height(AVLTreeNode<Key, Value>* node) {
      int node_height = 0;
      if (node) {
         int l_height = height (node->left);
         int r_height = height (node->right);
         int max_height = std::max(l_height, r_height);
         node_height = max_height + 1;
      }
      return node_height;
   };

   int rlDifference(AVLTreeNode<Key, Value>* node) {
      return height(node->left) - height(node->right);

   };

   AVLTreeNode<Key, Value>* ll_rotation(AVLTreeNode<Key, Value>* parent) {
      AVLTreeNode<Key, Value>*temp;
      temp = parent->left;
      parent->left = temp->right;
      temp->right = parent;
      return temp;
   };

   AVLTreeNode<Key, Value>* rr_rotation(AVLTreeNode<Key, Value>* parent) {
      AVLTreeNode<Key, Value>*temp;
      temp = parent->right;
      parent->right = temp->left;
      temp->left = parent;
      return temp;
   };

   AVLTreeNode<Key, Value>*lr_rotation(AVLTreeNode<Key, Value>* parent) {
      AVLTreeNode<Key, Value>*temp;
      temp = parent->left;
      parent->left = rr_rotation (temp);
      return ll_rotation (parent);
   };

   AVLTreeNode<Key, Value>*rl_rotation(AVLTreeNode<Key, Value>* parent) {
      AVLTreeNode<Key, Value>*temp;
      temp = parent->right;
      parent->right = ll_rotation (temp);
      return rr_rotation (parent);
   };

   AVLTreeNode<Key, Value>* balance(AVLTreeNode<Key, Value>* node) {
      int rlFactor = rlDifference(node);
      if (rlFactor > 1) {
         // Left-Left or Left-Right
         if (rlDifference(node->left) > 0) {
            node = ll_rotation(node);
         } else {
            node = lr_rotation(node);
         }
      } else if (rlFactor < -1) {
         // Right-Left or Right-Right
         if (rlDifference(node->right) > 0) {
            node = rl_rotation(node);
         } else {
            node = rr_rotation(node);
         }
      }

      return node;
   };

   AVLTreeNode<Key, Value>* getNode(const Key& key, AVLTreeNode<Key, Value>* tree) const {
      if (*tree == key) {
         return tree;
      }

      if (*tree < key) {
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
      } else if (*node > key) {
         // key < node, insert to node left
         node->left = insert(key, value, node->left);
         node->parent = node;

         // balance the inserted node
         node = balance(node);
      } else if (*node < key) {
         // key > node, inswer to node right
         node->right = insert(key, value, node->left);
         node->parent = node;

         // balance the inserted node
         node = balance(node);
      }


      return node;
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
      if (!root) {
         root = new AVLTreeNode<Key, Value>(key, value, nullptr);
      }
      insert(key, value, root);
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


#endif /* avl_tree_h */
