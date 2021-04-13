#pragma once


namespace itis {

  inline constexpr bool BLACK = true;
  inline constexpr bool RED = false;

  struct Node {
    int key; // data as well
    Node *parent{nullptr};
    Node *left{nullptr}; Node *right{nullptr};
    bool color = BLACK;
  };

  class RedBlackTree {
   private:
    int size{0};
    Node* root{nullptr};

   public:
    int find(int key);
    int find(int key, Node* node);
    void insert(int element);
    void remove(int key);

    int getSize() const {
      return size;
    }
  };

}  // namespace itis