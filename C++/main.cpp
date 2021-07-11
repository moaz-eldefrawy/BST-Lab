#include <bits/stdc++.h>
#include "fruits.h"
#include "BST.h"
using namespace std;

int main()
{
    BST tree;
    
    tree.insertFruit(APPLE, 3);
    tree.insertFruit(APPLE, 5);
    tree.insertFruit(APPLE, 2);
    tree.insertFruit(AVOCADO, 4);
    tree.insertFruit(GOOSE_BERRIES, 10);
    tree.insertFruit(BLUE_BERRIES, 20);
    tree.insertFruit(GRAPES, -5);
    tree.insertFruit(AVOCADO, 1);
    tree.insertFruit(AVOCADO, 6);
    tree.Iterate();
    std::cout << std::endl;
    // tree.magnifyByType(AVOCADO, 5);
    tree.Iterate();
    std::cout << std::endl;
    //std::cout << tree.filterByType(OVAL_SHAPED).size();

    auto oval = tree.filterByWeight(-2);
    output_vector(oval);

    return 0;
}