#ifndef avl_tree_h
#define avl_tree_h


template <typename Key, typename Value>
struct AVLTreeNode {
   AVLTreeNode *parent, *left, *right;
   Key key;
   Value value;
   // Note that the height of an empty tree is 0.
   int height;

   AVLTreeNode(const Key& key, const Value& value, AVLTreeNode* parent)
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
   typedef AVLTreeNode<Key, Value> Node;
   int lrDifference(Node* node) {
      int leftHeight = node && node->left ? node->left->height : 0;
      int rightHeight = node && node->right ? node->right->height : 0;
      return leftHeight - rightHeight;
   };

   Node* getNode(const Key& key, Node* tree) const {
      if (tree->key == key) {
         return tree;
      }

      if (key > tree->key) {
         return getNode(key, tree->right);
      } else {
         return getNode(key, tree->left);
      }
   }

   Value& get(const Key& key, Node* tree) const {
      return getNode(key, tree)->value;
   };

   template <typename Callable>
   void for_each_key_val(const Callable& callable, Node* node) {
      if (node) {
         for_each_key_val(callable, node->left);
         callable(node->key, node->value);
         for_each_key_val(callable, node->right);
      }
   };


   void insert(const Key& key, const Value& value, Node* node) {
      if (key < node->key) {
         // Insert to left subtree
         if (node->left) {
            // Has child, go left
            insert(key, value, node->left);
         } else {
            // No more child, insert here
            auto child = new Node(key, value, node);
            child->height = 1;
            node->left = child;
            balance(node->left);
         }
      } else {
         // Insert to right subtree
         if (node->right) {
            // Has child, go right
            insert(key, value, node->right);
         } else {
            // No more child, insert here
            auto child = new Node(key, value, node);
            child->height = 1;
            node->right = child;
            balance(node->right);
         }
      }
   };

   int height(Node* node) {
      int h = 0;
      if (node) {
         int l_height = height(node->left);
         int r_height = height(node->right);
         int max_height = std::max(l_height, r_height);
         h = max_height + 1;
      }
      return h;
   }

   void updateHeightUpwards(Node* node) {
      if (node) {
         int lHeight = node->left ? node->left->height : 0;
         int rHeight = node->right ? node->right->height : 0;
         node->height = std::max(lHeight, rHeight) + 1;
         updateHeightUpwards(node->parent);
      }
   };

#define getNodeOrNullptr(node,direction) (node ? node->direction : nullptr)
#define setOnlyNotNull(target,direction,node) (target && (target->direction = node))
   void balance(Node* node) {
      if (!node) {
         return;
      }

      updateHeightUpwards(node->left);
      updateHeightUpwards(node);
      updateHeightUpwards(node->right);

      Node * nodes[3] = {0};
      Node * subtrees[4] = {0};
      Node * nodeParent = node->parent;


      int lrFactor = lrDifference(node);
      if (lrFactor > 1) {
         // Left-Left or Left-Right
         if (lrDifference(node->left) > 0) {
            // Left-Left
            nodes[0] = node;
            nodes[2] = node->left;
            nodes[1] = getNodeOrNullptr(nodes[2],left);

            subtrees[0] = getNodeOrNullptr(nodes[1],left);  //A
            subtrees[1] = getNodeOrNullptr(nodes[1],right); //B
            subtrees[2] = getNodeOrNullptr(nodes[2],right); //C
            subtrees[3] = getNodeOrNullptr(nodes[0],right); //D
         } else {
            // Left-Right
            nodes[0] = node;
            nodes[1] = node->left;
            nodes[2] = getNodeOrNullptr(nodes[1],right);

            subtrees[0] = getNodeOrNullptr(nodes[1],left);
            subtrees[1] = getNodeOrNullptr(nodes[2],left);
            subtrees[2] = getNodeOrNullptr(nodes[2],right);
            subtrees[3] = getNodeOrNullptr(nodes[0],right);
         }
      } else if (lrFactor < -1) {
         // Right-Left or Right-Right
         if (lrDifference(node->right) < 0) {
            // Right-Right
            nodes[1] = node;
            nodes[2] = node->right;
            nodes[0] = getNodeOrNullptr(nodes[2],right);

            subtrees[0] = getNodeOrNullptr(nodes[1],left);
            subtrees[1] = getNodeOrNullptr(nodes[2],left);
            subtrees[2] = getNodeOrNullptr(nodes[0],left);
            subtrees[3] = getNodeOrNullptr(nodes[0],right);
         } else {
            // Right-Left
            nodes[1] = node;
            nodes[0] = node->right;
            nodes[2] = getNodeOrNullptr(nodes[0],left);

            subtrees[0] = getNodeOrNullptr(nodes[1],left);
            subtrees[1] = getNodeOrNullptr(nodes[2],left);
            subtrees[2] = getNodeOrNullptr(nodes[2],right);
            subtrees[3] = getNodeOrNullptr(nodes[0],right);
         }
      } else {
         balance(node->parent);
         return;
      }


      if (node == root) {
         root = nodes[2];
         root->parent = nullptr;
      } else if (node->isLeftChild()) {
         setOnlyNotNull(nodeParent,left,nodes[2]);
         nodes[2]->parent = nodeParent;
      } else if (node->isRightChild()) {
         setOnlyNotNull(nodeParent,right,nodes[2]);
         nodes[2]->parent = nodeParent;
      }

      setOnlyNotNull(nodes[2],left,nodes[1]);
      setOnlyNotNull(nodes[1],parent,nodes[2]);
      setOnlyNotNull(nodes[2],right,nodes[0]);
      setOnlyNotNull(nodes[0],parent,nodes[2]);

      setOnlyNotNull(nodes[1],left,subtrees[0]);
      setOnlyNotNull(subtrees[0],parent,nodes[1]);
      setOnlyNotNull(nodes[1],right,subtrees[1]);
      setOnlyNotNull(subtrees[1],parent,nodes[1]);

      setOnlyNotNull(nodes[0],left,subtrees[2]);
      setOnlyNotNull(subtrees[2],parent,nodes[0]);
      setOnlyNotNull(nodes[0],right,subtrees[3]);
      setOnlyNotNull(subtrees[3],parent,nodes[0]);

      updateHeightUpwards(nodes[1]);
      updateHeightUpwards(nodes[0]);

      balance(getNodeOrNullptr(nodes[2],parent));
   };



   Node* smallestOfNode(Node* node) {
      if (node && !node->left) {
         return node;
      }
      return smallestOfNode(node->left);
   };

   Node* biggestOfNode(Node* node) {
      if (node && !node->right) {
         return node;
      }
      return biggestOfNode(node->right);
   };

   void removeNode(Node* target) {
      if (target->isLeaveNode()) {
         // Handle leaves case
         Node* targetParent = target->parent;
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
         balance(targetParent);
      } else {
         // Handle stems case
         Node* replacement = nullptr;
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
   Node *root;

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
         root = new Node(key, value, nullptr);
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
      Node* target = getNode(key, root);
      removeNode(target);
   };

   // Given a callable, that takes a Key and Value, call that callable
   // for every key/value pair in the tree in sorted order.
   // e.g. callable(Key(), Value())
   template <typename Callable>
   void for_each_key_val(const Callable& callable) {
      for_each_key_val(callable, root);
   };

   void display(Node *ptr, int level)
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
         printf("(%d:%d)", ptr->key, ptr->height);
         display(ptr->left, level + 1);
      }
   }
};


#endif /* avl_tree_h */
