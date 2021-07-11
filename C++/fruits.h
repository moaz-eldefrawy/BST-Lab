#pragma once

enum FruitType
{
    APPLE,
    OVAL_SHAPED,
    AVOCADO,
    TINY_FRUIT,
    GRAPES,
    BERRIES,
    GOOSE_BERRIES,
    BLUE_BERRIES
};

class BSTNode
{
public:
    int weight;
    BSTNode *left;
    BSTNode *right;
    BSTNode() : left(nullptr), right(nullptr) {}
    BSTNode(int weight) : weight(weight), left(nullptr), right(nullptr) {}
    virtual bool isType(FruitType _type) = 0;
    virtual FruitType getType() = 0;
};




class OvalShaped : public BSTNode
{
public:
    OvalShaped(int weight) : BSTNode(weight) {}

    virtual bool isType(FruitType type)
    {
        return type == OVAL_SHAPED;
    }
};

class Apple : public OvalShaped
{
public:
    Apple(int weight) : OvalShaped(weight) {}

    virtual FruitType getType()
    {
        return APPLE;
    }

    virtual bool isType(FruitType type)
    {
        return type == APPLE || OvalShaped::isType(type);
    }
};

class Avocado : public OvalShaped
{
public:
    Avocado(int weight) : OvalShaped(weight) {}

    virtual FruitType getType()
    {
        return AVOCADO;
    }

    virtual bool isType(FruitType type)
    {
        return type == AVOCADO || OvalShaped::isType(type);
    }
};

class TinyFruit : public BSTNode
{
public:
    TinyFruit(int weight) : BSTNode(weight) {}

    virtual bool isType(FruitType type)
    {
        return type == TINY_FRUIT;
    }
};

class Berries : public TinyFruit
{
public:
    Berries(int weight) : TinyFruit(weight) {}

    virtual bool isType(FruitType type)
    {
        return type == BERRIES || TinyFruit::isType(type);
    }
};

class Grapes : public TinyFruit
{
public:
    Grapes(int weight) : TinyFruit(weight) {}

    virtual FruitType getType()
    {
        return GRAPES;
    }

    virtual bool isType(FruitType type)
    {
        return type == GRAPES || TinyFruit::isType(type);
    }
};

class BlueBerries : public Berries
{
public:
    BlueBerries(int weight) : Berries(weight) {}

    virtual FruitType getType()
    {
        return BLUE_BERRIES;
    }

    virtual bool isType(FruitType type)
    {
        return type == BLUE_BERRIES || Berries::isType(type);
    }
};

class GooseBerries : public Berries
{
public:
    GooseBerries(int weight) : Berries(weight) {}

    virtual FruitType getType()
    {
        return GOOSE_BERRIES;
    }

    virtual bool isType(FruitType type)
    {
        return type == GOOSE_BERRIES || Berries::isType(type);
    }
};

class FruitFactory
{
public:
    static BSTNode *create(FruitType type, int weight)
    {
        switch (type)
        {
        case APPLE:
            return new Apple(weight);
        case AVOCADO:
            return new Avocado(weight);
        case GRAPES:
            return new Grapes(weight);
        case BLUE_BERRIES:
            return new BlueBerries(weight);
        case GOOSE_BERRIES:
            return new GooseBerries(weight);
        default:
            return nullptr;
        }
    }

};
