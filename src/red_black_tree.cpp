#include "red_black_tree.hpp"

namespace itis {

  RedBlackTree::RedBlackTree() : size(0), root(nullptr) {}

  RedBlackTree::~RedBlackTree() {
    while (root != nullptr) {
      remove(root);
    }
    delete root;
  }

  Node* RedBlackTree::find(int key) const {
    return find(key, root);
  }

  void RedBlackTree::insert(int key) {
    if (insert(key, root)) {
      size++;
    }
  }

  void RedBlackTree::remove(int key) {
    auto* node = find(key);
    if (node != nullptr) {
      remove(node);
    }
  }

  Node* RedBlackTree::find(int key, Node* node) const {
    if (node != nullptr) {
      if (key == node->key) {
        return node;
      }
      if (key > node->key) {
        return find(key, node->right);
      }
      return find(key, node->left);
    }
    return nullptr;
  }


  bool RedBlackTree::insert(int key, Node* node) {
    if (root == nullptr) {
      root = new Node(nullptr, key, BLACK);
      return true;
    }
    Node* y;
    while (node != nullptr) {
      y = node;
      if (key == node->key) {
        return false;
      }
      if (key < node->key) {
        node = node->left;
      } else {
        node = node->right;
      }
    }
    auto* newNode = new Node(y, key, RED);
    if (y == nullptr) {
      root = newNode;
    } else if (newNode->key < y->key) {
      y->left = newNode;
    } else {
      y->right = newNode;
    }
    if (newNode->parent->parent != nullptr) {
      fixInsertion(newNode);
    }
    return true;
  }

  void RedBlackTree::fixInsertion(Node* node) {
    while (node != nullptr && node != root && node->parent->color == RED) {
      if (node->parent == node->parent->parent->left) {
        auto* uncle = node->parent->parent->right;
        if (uncle != nullptr && uncle->color == RED) {
          node->parent->color = BLACK;
          uncle->color = BLACK;
          node->parent->parent->color = RED;
          node = node->parent->parent;
        } else {
          if (node == node->parent->right) {
            node = node->parent;
            rotateLeft(node);
          }
          node->parent->color = BLACK;
          node->parent->parent->color = RED;
          rotateRight(node->parent->parent);
        }
      } else {
        auto* uncle = node->parent->parent->left;
        if (uncle != nullptr && uncle->color == RED) {
          node->parent->color = BLACK;
          uncle->color = BLACK;
          node->parent->parent->color = RED;
          node = node->parent->parent;
        } else {
          if (node == node->parent->left) {
            node = node->parent;
            rotateRight(node);
          }
          node->parent->color = BLACK;
          node->parent->parent->color = RED;
          rotateLeft(node->parent->parent);
        }
      }
    }
    root->color = BLACK;
  }

  void RedBlackTree::remove(Node* node) {
    size--;
    if (node->left != nullptr && node->right != nullptr) {
      auto* succ = successor(node);
      node->key = succ->key;
      node = succ;
    }

    auto* replacement = node->left;
    if (replacement == nullptr) {
      replacement = node->right;
    }

    if (replacement != nullptr) {
      replacement->parent = node->parent;
      if (node->parent == nullptr) {
        root = replacement;
      } else if (node == node->parent->left) {
        node->parent->left = replacement;
      } else {
        node->parent->right = replacement;
      }
      node->right = node->left = node->parent = nullptr;
      if (node->color == BLACK) {
        fixDeletion(node);
      }
      delete node;
    } else if (node->parent == nullptr) {
      delete node;
      root = nullptr;
    } else {
      if (node->color == BLACK) {
        fixDeletion(node);
      }
      if (node->parent != nullptr) {
        if (node == node->parent->left) {
          node->parent->left = nullptr;
        } else if (node == node->parent->right) {
          node->parent->right = nullptr;
        }
        node->parent = nullptr;
        delete node;
      }
    }
  }

  void RedBlackTree::fixDeletion(Node* node) {
    while (node != root && colorOf(node) == BLACK) {
      if (node == nullptr) return;
      if (node == leftOf(parentOf(node))) {
        Node* brother = rightOf(parentOf(node));

        if (colorOf(brother) == RED) {
          setColor(brother, BLACK);
          setColor(parentOf(node), RED);
          rotateLeft(parentOf(node));
          brother = rightOf(parentOf(node));
        }

        if (colorOf(leftOf(brother))  == BLACK &&
            colorOf(rightOf(brother)) == BLACK) {
          setColor(brother, RED);
          node = parentOf(node);
        } else {
          if (colorOf(rightOf(brother)) == BLACK) {
            setColor(leftOf(brother), BLACK);
            setColor(brother, RED);
            rotateRight(brother);
            brother = rightOf(parentOf(node));
          }
          setColor(brother, colorOf(parentOf(node)));
          setColor(parentOf(node), BLACK);
          setColor(rightOf(brother), BLACK);
          rotateLeft(parentOf(node));
          node = root;
        }
      } else {
        Node* brother = leftOf(parentOf(node));

        if (colorOf(brother) == RED) {
          setColor(brother, BLACK);
          setColor(parentOf(node), RED);
          rotateRight(parentOf(node));
          brother = leftOf(parentOf(node));
        }

        if (colorOf(rightOf(brother)) == BLACK &&
            colorOf(leftOf(brother)) == BLACK) {
          setColor(brother, RED);
          node = parentOf(node);
        } else {
          if (colorOf(leftOf(brother)) == BLACK) {
            setColor(rightOf(brother), BLACK);
            setColor(brother, RED);
            rotateLeft(brother);
            brother = leftOf(parentOf(node));
          }
          setColor(brother, colorOf(parentOf(node)));
          setColor(parentOf(node), BLACK);
          setColor(leftOf(brother), BLACK);
          rotateRight(parentOf(node));
          node = root;
        }
      }
    }
    setColor(node, BLACK);
  }

  Node* RedBlackTree::successor(Node* target) {
    if (target->right != nullptr) {
      auto* p = target->right;
      while (p->left != nullptr) {
        p = p->left;
      }
      return p;
    }
    auto* p = target->parent;
    auto* ch = target;
    while (p != nullptr && ch == p->right) {
      ch = p;
      p = p->parent;
    }
    return p;
  }

  // Null safety

  bool RedBlackTree::colorOf(Node* node) {
    return node == nullptr ? BLACK : node->color;
  }

  Node* RedBlackTree::parentOf(Node* node) {
    return node == nullptr ? nullptr : node->parent;
  }

  Node* RedBlackTree::leftOf(Node* node) {
    return node == nullptr ? nullptr : node->left;
  }

  Node* RedBlackTree::rightOf(Node* node) {
    return node == nullptr ? nullptr : node->right;
  }

  void RedBlackTree::setColor(Node* node, bool color) {
    if (node != nullptr) {
      node->color = color;
    }
  }

  void RedBlackTree::rotateRight(Node* x) {
    if (x == nullptr)
      return;
    Node* y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  void RedBlackTree::rotateLeft(Node* x) {
    if (x == nullptr)
      return;
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

}  // namespace itis
