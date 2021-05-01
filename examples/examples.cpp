#include <iostream>

#include "red_black_tree.hpp"

using namespace std;
using namespace itis;

int main() {
    auto* tree = new RedBlackTree;
    tree->insert(13);
    tree->insert(8);
    tree->insert(1);
    tree->insert(11);
    tree->insert(6);
    tree->insert(17);
    tree->insert(15);
    tree->insert(25);
    tree->insert(22);
    tree->insert(27);

    tree->remove(13);
    tree->remove(25);
    tree->remove(1);
    cout << tree->find(13) << endl; // 0
    cout << tree->find(11) << endl;
    return 0;
}