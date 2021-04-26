#pragma once

namespace itis {

  inline constexpr bool BLACK = true;
  inline constexpr bool RED = false;


  struct Node {
    int key;
    int* data = &key;
    Node *parent{nullptr};
    Node *left{nullptr};
    Node *right{nullptr};
    bool color = BLACK;

    Node(Node* parent_, int key_, bool color_)
        : key(key_), parent(parent_), color(color_) {}

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
    Node* find(int key, Node* node) const;
    bool insert(int key, Node* node);
    void remove(Node* node);
    void fixInsertion(Node* node);
    void fixDeletion(Node* node);
    void rotateLeft(Node* node);
    void rotateRight(Node* node);
    Node* successor(Node* node);


   public:
    RedBlackTree();
    ~RedBlackTree();
    Node* find(int key) const;
    void insert(int key);
    void remove(int key);
    void traverse();

    int getSize() const {
      return size;
    }
  };

}  // namespace itis