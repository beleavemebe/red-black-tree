#pragma once

namespace itis {

  inline constexpr bool BLACK = true;
  inline constexpr bool RED = false;

  struct Node {
    int key;
    Node* parent{nullptr};
    Node* left{nullptr};
    Node* right{nullptr};
    bool color = BLACK;

    Node(Node* parent_, int key_, bool color_) : key(key_), parent(parent_), color(color_) {}

    ~Node() {
      key = 0;
      parent = nullptr;
      left = nullptr;
      right = nullptr;
      color = BLACK;
    }
  };

  struct RedBlackTree {
   private:
    int size{0};
    Node* root{nullptr};
    bool insert(int key, Node* node);
    Node* find(int key, Node* node) const;
    void remove(Node* node);
    void fixInsertion(Node* node);
    void fixDeletion(Node* node);
    void rotateLeft(Node* node);
    void rotateRight(Node* node);
    Node* successor(Node* node);
    // null safety
    bool colorOf(Node* node);
    Node* parentOf(Node* node);
    Node* leftOf(Node* node);
    Node* rightOf(Node* node);
    void setColor(Node* node, bool color);

   public:
    RedBlackTree();
    ~RedBlackTree();
    Node* find(int key) const;
    void insert(int key);
    void remove(int key);

    int getSize() const {
      return size;
    }
  };

}  // namespace itis