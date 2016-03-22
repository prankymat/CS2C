#ifndef BinarySearchTree_h
#define BinarySearchTree_h

template <typename Key, typename Value>
struct BinarySearchTreeNode {
   BinarySearchTreeNode *left, *right, *parent;
   Key key;
   Value value;

   BinarySearchTreeNode(const Key& key, const Value& value, BinarySearchTreeNode<Key, Value>* parent)
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
};

template <typename Key, typename Value>
class BinarySearchTree {
private:
   Value& get(const Key& key, BinarySearchTreeNode<Key, Value>* tree) {
      if (*tree == key) {
         return tree->value;
      }

      if (*tree < key) {
         return get(key, tree->right);
      } else {
         return get(key, tree->left);
      }
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

   void deleteNode(BinarySearchTreeNode<Key, Value>* node) {
      if (node && node->left) {
         deleteNode(node->left);
      }

      if (node && node->right) {
         deleteNode(node->right);
      }

      delete node;
   };

public:
   BinarySearchTreeNode<Key, Value> *root;

   BinarySearchTree() : root(nullptr) {};

   ~BinarySearchTree() {
      deleteNode(root);
   };

   // Insert a value, while making sure the tree is still a binary search tree.
   // This assumes that the key does not exist in the tree.
   void insert(const Key& key, const Value& value) {
      if (!root) {
         root = new BinarySearchTreeNode<Key, Value>(key, value, nullptr);
      }
      insert(key, value, root);
   };
   // Given a key, find the corresponding value.
   // This assumes that the key exists.
   Value& get(const Key& key) {
      return get(key, root);
   };


};


#endif /* BinarySearchTree_h */
