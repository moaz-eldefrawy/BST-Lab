#include "BST.h"
#include <iostream>
#include <bits/stdc++.h>


std::string repr(FruitType type)
{
    switch (type)
    {
    case APPLE:
        return "apple";
    case AVOCADO:
        return "avocado";
    case GRAPES:
        return "grapes";
        
    case BLUE_BERRIES:
        return "blue berries";
        
    case GOOSE_BERRIES:
        return "goose berries";
        
    default:
        return "";
    }
}

void output_vector(std::vector<std::pair<FruitType, int>>& arr)
{
    for(auto [t, w]: arr)
        std::cout << '(' << repr(t) << ", " << w << "), ";
    std::cout << std::endl;
}


void BST::Iterate(BSTNode *node)
{
    if (node == nullptr)
        return;
    Iterate(node->left);
    std::cout << '(' << repr(node->getType()) << ", " << node->weight << "), ";
    Iterate(node->right);
}

void BST::Iterate()
{
    Iterate(root);
}

void BST::filterByType(BSTNode *node, FruitType type, std::vector<std::pair<FruitType, int>> &res)
{
    if (node == nullptr)
        return;
    filterByType(node->left, type, res);
    if (node->isType(type))
        res.push_back({node->getType(), node->weight});
    filterByType(node->right, type, res);
}

void BST::filterByWeight(BSTNode *node, int weight, std::vector<std::pair<FruitType, int>> &res)
{
    if (node == nullptr)
        return;
    if (node->weight > weight)
    {
        filterByWeight(node->left, weight, res);
        res.push_back({node->getType(), node->weight});
        filterByWeight(node->right, weight, res);
    }
    else
        filterByWeight(node->right, weight, res);
}

std::vector<std::pair<FruitType, int>> BST::filterByWeight(int weight)
{
    std::vector<std::pair<FruitType, int>> res;
    filterByWeight(root, weight, res);
    return res;
}

std::vector<std::pair<FruitType, int>> BST::filterByType(FruitType type)
{
    std::vector<std::pair<FruitType, int>> res;
    filterByType(root, type, res);
    return res;
}



BSTNode *BST::findLightest(BSTNode *node)
{
    if (node == nullptr)
        return nullptr;
    BSTNode *cur = node;
    while (cur->left != nullptr)
        cur = cur->left;
    return cur;
}

BSTNode *BST::deleteFruit(BSTNode *node, FruitType type, int weight)
{
    if (node == nullptr)
        return nullptr;

    if (node->weight < weight)
        node->right = deleteFruit(node->right, type, weight);
    else if (node->weight > weight)
        node->left = deleteFruit(node->left, type, weight);
    else if (node->isType(type))
    {
        if (node->left == nullptr)
        {
            BSTNode *right = node->right;
            delete node;
            return right;
        }
        else if (node->right == nullptr)
        {
            BSTNode *left = node->left;
            delete node;
            return left;
        }

        BSTNode *lightest = findLightest(node->right);
        BSTNode *newNode = FruitFactory::create(lightest->getType(), lightest->weight);
        newNode->left = node->left;
        newNode->right = node->right;
        delete node;
        node = newNode;
        node->right = deleteFruit(node->right, lightest->getType(), lightest->weight);
    }

    return node;
}

BSTNode *BST::insertFruit(BSTNode *node, FruitType type, int weight)
{
    if (node == nullptr)
        return FruitFactory::create(type, weight);
    if (node->weight == weight)
        return nullptr;
    if (node->weight < weight)
        node->right = insertFruit(node->right, type, weight);
    else
        node->left = insertFruit(node->left, type, weight);
    return node;
}

void BST::insertFruit(FruitType type, int weight)
{
    root = insertFruit(root, type, weight);
}

void BST::deleteFruit(FruitType type, int weight)
{
    root = deleteFruit(root, type, weight);
}

BSTNode *BST::findHeaviest()
{
    if (root == nullptr)
        return nullptr;
    BSTNode *node = root;
    while (node->right != nullptr)
        node = node->right;
    return node;
}

BSTNode *BST::findLightest()
{
    return findLightest(root);
}

void BST::magnifyByType(FruitType type, int weight)
{
    std::vector<std::pair<FruitType, int>> toBeMagnified;
    filterByType(root, type, toBeMagnified);

    for (auto [t, w] : toBeMagnified)
        deleteFruit(t, w);

    for (auto [t, w] : toBeMagnified)
        insertFruit(t, w + weight);
}
