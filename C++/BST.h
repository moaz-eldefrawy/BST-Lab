#pragma once
#include <vector>
#include "fruits.h"
#include <string>
void output_vector(std::vector<std::pair<FruitType, int>>&);
std::string repr(FruitType type);
class BST
{
private:
    BSTNode* root;
    void Iterate(BSTNode *node);
    void filterByType(BSTNode* node, FruitType type, std::vector<std::pair<FruitType, int>>& res);
    void filterByWeight(BSTNode* node, int weight, std::vector<std::pair<FruitType, int>>& res);

    BSTNode* insertFruit(BSTNode* node, FruitType type, int weight);
    BSTNode* findLightest(BSTNode* node);
    BSTNode* deleteFruit(BSTNode* node, FruitType type, int weight);

public:
    void insertFruit(FruitType type, int weight);
    void deleteFruit(FruitType type, int weight);
    BST() : root(nullptr) {}
    void Iterate();
    std::vector<std::pair<FruitType, int>> filterByType(FruitType type);
    std::vector<std::pair<FruitType, int>> filterByWeight(int weight);
    void magnifyByType(FruitType type, int weight);
    BSTNode* findHeaviest();
    BSTNode* findLightest();
};
