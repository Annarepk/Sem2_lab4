#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

template<typename Type>
using Mapper = Type(*)(Type &);

template<typename Type>
using Condition = bool (*)(Type &);

template<typename Type>
using Reducer = Type(*)(const Type &, const Type &);

template<typename Type>
class Leaf {
private:
    Type value;
    Leaf *left;
    Leaf *right;
public:

    Leaf() : value(NULL), left(nullptr), right(nullptr) {}

    explicit Leaf(Type val) : value(val), left(nullptr), right(nullptr) {}

    Type &Get() { return value; }

    Leaf *&Left() { return left; }

    Leaf *&Right() { return right; }
};

template<typename Type>
class BinaryTree {
private:
    Leaf<Type> *root;
    int size;
public:
    BinaryTree<Type>() : root(nullptr), size(0) {}

    ~BinaryTree() {
        deleteTree(this->Root());
    }


    void deleteTree(Leaf<Type> *leaf) {
        if (leaf == nullptr) return;
        deleteTree(leaf->Left());
        deleteTree(leaf->Right());
        delete leaf;
    }

    Leaf<Type> *&Root() { return root; }

    int &Size() { return size; }

    void PrintPRL(Leaf<Type> *leaf) {
        if (leaf == nullptr) return;
        PrintPRL(leaf->Right());
        PrintPRL(leaf->Left());
        cout << '(' << leaf->Get() << ") ";
    }

    void PrintPLR(Leaf<Type> *leaf) {
        if (leaf == nullptr) return;
        PrintPLR(leaf->Left());
        PrintPLR(leaf->Right());
        cout << '(' << leaf->Get() << ") ";
    }

    bool Find(Type key) {
        Leaf<Type> *current = this->Root();
        while (current && current->Get() != key) {
            if (current->Get() > key) current = current->Left();
            else current = current->Right();
        }
        return current != nullptr;
    }

    void Insert(Type key) {
        if (this->Root() == nullptr) {
            this->Root() = new Leaf<Type>(key);
            this->Size()++;
            return;
        }

        Leaf<Type> *current = this->Root();

        while (true) {
            if (key == current->Get()) {
                return;
            } else if (key < current->Get()) {
                if (current->Left() == nullptr) {
                    current->Left() = new Leaf<Type>(key);
                    break;
                }
                current = current->Left();
            } else {
                if (current->Right() == nullptr) {
                    current->Right() = new Leaf<Type>(key);
                    break;
                }
                current = current->Right();
            }
        }

        this->Size()++;
    }


    void Remove(Type key) {
        if (this->Root() == nullptr) return;

        Leaf<Type> *parent = nullptr;
        Leaf<Type> *current = this->Root();

        // Поиск узла
        while (current && current->Get() != key) {
            parent = current;
            if (key < current->Get()) current = current->Left();
            else current = current->Right();
        }

        if (!current) return;

        if (current == this->Root() && !current->Left() && !current->Right()) {
            delete current;
            this->Root() = nullptr;
            this->Size() = 0;
            return;
        }

        Leaf<Type> *child = nullptr;
        if (!current->Left()) child = current->Right();
        else if (!current->Right()) child = current->Left();

        if (child) {
            if (current == this->Root()) {
                this->Root() = child;
            } else if (parent->Left() == current) {
                parent->Left() = child;
            } else {
                parent->Right() = child;
            }
            delete current;
            this->Size()--;
            return;
        }

        Leaf<Type> *replaceParent = current;
        Leaf<Type> *replace = current->Right();

        while (replace->Left()) {
            replaceParent = replace;
            replace = replace->Left();
        }

        current->Get() = replace->Get();  // перенос значения

        Leaf<Type> *replaceChild = (replace->Right()) ? replace->Right() : nullptr;

        if (replaceParent->Left() == replace)
            replaceParent->Left() = replaceChild;
        else
            replaceParent->Right() = replaceChild;

        delete replace;
        this->Size()--;
    }

    void Map(Mapper<Type> func) { this->ChangerMap(this->Root(), func); }

    void Where(Condition<Type> filter) {
        std::set<Type> toRemove;
        ChangerWhere(this->Root(), filter, toRemove);

        for (const Type &val: toRemove) {
            this->Remove(val);
        }
    }

    void Clear(Leaf<Type> *leaf) {
        if (leaf == nullptr) return;
        Clear(leaf->Left());
        Clear(leaf->Right());
        delete leaf;
    }


    void Reduce(Reducer<Type> reduce) {
        if (this->Root() == nullptr) return;

        Type base = this->Root()->Get();
        ChangerReduce(this->Root()->Left(), reduce, &base);
        ChangerReduce(this->Root()->Right(), reduce, &base);

        deleteTree(this->Root());
        this->Root() = new Leaf<Type>(base);
        this->Size() = 1;
    }

private:
    void ChangerMap(Leaf<Type> *leaf, Mapper<Type> func) {
        if (leaf == nullptr) return;
        ChangerMap(leaf->Left(), func);
        ChangerMap(leaf->Right(), func);
        Type &ref = leaf->Get();
        ref = func(ref);
    }

    void ChangerWhere(Leaf<Type> *leaf, Condition<Type> filter, std::set<Type> &buffer) {
        if (leaf == nullptr) return;

        std::vector<Leaf<Type> *> stack;
        stack.push_back(leaf);

        while (!stack.empty()) {
            Leaf<Type> *current = stack.back();
            stack.pop_back();

            if (!filter(current->Get())) {
                buffer.insert(current->Get());
            }

            if (current->Right()) stack.push_back(current->Right());
            if (current->Left()) stack.push_back(current->Left());
        }
    }


    void ChangerReduce(Leaf<Type> *leaf, Reducer<Type> reduce, Type *base) {
        if (leaf == nullptr) return;
        ChangerReduce(leaf->Left(), reduce, base);
        ChangerReduce(leaf->Right(), reduce, base);
        *base = reduce(leaf->Get(), *base);
    }


};


#endif
