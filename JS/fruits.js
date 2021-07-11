let types = {
    APPLE: 'apple',
    OVAL_SHAPED: 'oval shaped',
    AVOCADO: 'avocado',
    TINY_FRUIT: 'tiny fruit',
    GRAPES: 'grapes',
    BERRIES: 'berries',
    GOOSE_BERRIES: 'goose berries',
    BLUE_BERRIES: 'blue berries'
}

class BSTNode {
    constructor(weight) {
        this.weight = weight;
        this.left = null;
        this.right = null;
    }
}

class pair {
    constructor(first, second) {
        this.first = first;
        this.second = second;
    }
}

class FruitFactory {
    static create(type, weight) {
        switch (type) {
            case types.APPLE:
                return new Apple(weight);
            case types.AVOCADO:
                return new Avocado(weight);
            case types.GRAPES:
                return new Grapes(weight);
            case types.BLUE_BERRIES:
                return new BlueBerries(weight);
            case types.GOOSE_BERRIES:
                return new GooseBerries(weight);
            default:
                return null;
        }
    }
}

class BST {
    constructor() {
        this.root = null;
    }

    iterateHelper(node) {
        if (node == null)
            return;
        this.iterateHelper(node.left);
        process.stdout.write(`(${node.getType()}, ${node.weight}), `);
        this.iterateHelper(node.right);
    }

    iterate() {
        this.iterateHelper(this.root);
    }

    filterByTypeHelper(node, type, res) {
        if (node === null)
            return;
        this.filterByTypeHelper(node.left, type, res);
        if (node.isType(type))
            res.push(new pair(node.getType(), node.weight));
        this.filterByTypeHelper(node.right, type, res);
    }

    filterByType(type) {
        let res = [];
        this.filterByTypeHelper(this.root, type, res);
        return res;
    }

    findLightestHelper(node) {
        if (node === null)
            return null;
        let cur = node;
        while (cur.left !== null)
            cur = cur.left;
        return cur;
    }

    findLightest() {
        return this.findLightestHelper(this.root);
    }

    deleteFruitHelper(node, type, weight) {
        if (node === null)
            return null;

        if (node.weight < weight)
            node.right = this.deleteFruitHelper(node.right, type, weight);
        else if (node.weight > weight)
            node.left = this.deleteFruitHelper(node.left, type, weight);
        else if (node.isType(type)) {
            if (node.left === null) {
                let right = node.right;
                return right;
            }
            else if (node.right === null) {
                let left = node.left;
                return left;
            }

            let lightest = this.findLightestHelper(node.right);
            let newNode = FruitFactory.create(lightest.getType(), lightest.weight);
            newNode.left = node.left;
            newNode.right = node.right;
            node = newNode;
            node.right = this.deleteFruitHelper(node.right, lightest.getType(), lightest.weight);
        }

        return node;
    }

    deleteFruit(type, weight) {
        this.root = this.deleteFruitHelper(this.root, type, weight);
    }

    insertFruitHelper(node, type, weight) {
        if (node === null)
            return FruitFactory.create(type, weight);
        if (node.weight === weight)
            return null;
        if (node.weight < weight)
            node.right = this.insertFruitHelper(node.right, type, weight);
        else
            node.left = this.insertFruitHelper(node.left, type, weight);
        return node;
    }

    insertFruit(type, weight) {
        this.root = this.insertFruitHelper(this.root, type, weight);
    }

    findHeaviest() {
        if (this.root === null)
            return null;
        let node = this.root;
        while (node.right === null)
            node = node.right;
        return node;
    }

    magnifyByType(type, weight) {
        let toBeMagnified = [];
        this.filterByTypeHelper(this.root, type, toBeMagnified);

        for (let my_pair of toBeMagnified) {
            this.deleteFruit(my_pair.first, my_pair.second);
        }

        for (let my_pair of toBeMagnified)
            this.insertFruit(my_pair.first, my_pair.second + weight);
    }

    filterByWeightHelper(node, weight, res) {
        if (node === null)
            return;
        if (node.weight > weight) {
            this.filterByWeightHelper(node.left, weight, res);
            res.push(new pair(node.getType(), node.weight));
            this.filterByWeightHelper(node.right, weight, res);
        }
        else
            this.filterByWeightHelper(node.right, weight, res);
    }

    filterByWeight(weight) {
        let res = [];
        this.filterByWeightHelper(this.root, weight, res);
        return res;
    }


}



class OvalShaped extends BSTNode {
    constructor(weight) {
        super(weight);
    }

    isType(type) {
        return type === types.OVAL_SHAPED;
    }
};

class Apple extends OvalShaped {
    constructor(weight) {
        super(weight);
    }


    getType() {
        return types.APPLE;
    }

    isType(type) {
        return type === this.APPLE || super.isType(type);
    }
};

class Avocado extends OvalShaped {
    constructor(weight) {
        super(weight);
    }

    getType() {
        return types.AVOCADO;
    }

    isType(type) {
        return type === types.AVOCADO || super.isType(type);
    }
};

class TinyFruit extends BSTNode {
    constructor(weight) {
        super(weight);
    }

    isType(type) {
        return type === types.TINY_FRUIT;
    }
};

class Berries extends TinyFruit {
    constructor(weight) {
        super(weight);
    }


    isType(type) {
        return type == types.BERRIES || super.isType(type);
    }
};

class Grapes extends TinyFruit {
    constructor(weight) {
        super(weight);
    }


    getType() {
        return types.GRAPES;
    }

    isType(type) {
        return type === types.GRAPES || super.isType(type);
    }
};

class BlueBerries extends Berries {
    constructor(weight) {
        super(weight);
    }


    getType() {
        return types.BLUE_BERRIES;
    }

    isType(type) {
        return type === types.BLUE_BERRIES || super.isType(type);
    }
};

class GooseBerries extends Berries {
    constructor(weight) {
        super(weight);
    }


    getType() {
        return types.GOOSE_BERRIES;
    }

    isType(type) {
        return type === types.GOOSE_BERRIES || super.isType(type);
    }
};


let tree = new BST();

tree.insertFruit(types.APPLE, 3);
tree.insertFruit(types.APPLE, 5);
tree.insertFruit(types.APPLE, 2);
tree.insertFruit(types.AVOCADO, 4);
tree.insertFruit(types.GOOSE_BERRIES, 10);
tree.insertFruit(types.BLUE_BERRIES, 20);
tree.insertFruit(types.GRAPES, -5);
tree.insertFruit(types.AVOCADO, 1);
tree.insertFruit(types.AVOCADO, 6);
tree.iterate();
console.log();
tree.magnifyByType(types.AVOCADO, 5);
tree.iterate();
console.log();
console.log(tree.filterByWeight(-2));