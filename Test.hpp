#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>

#include "Tree.hpp"
#include <cassert>


void testTree() {
    // Create
    auto *tree1 = new BinaryTree<int>;
    assert(tree1->Size() == 0);

    std::cout << "Create tests were passed!" << std::endl;

    // Insert
    tree1->Insert(1);
    tree1->Insert(2);
    tree1->Insert(3);
    tree1->Insert(4);
    tree1->Insert(5);
    assert(tree1->Size() == 5);
    assert(tree1->Find(1));
    assert(tree1->Find(2));
    assert(tree1->Find(3));
    assert(tree1->Find(4));
    assert(tree1->Find(5));

    std::cout << "Insert tests were passed!" << std::endl;

    // Where
    auto IsOdd = [](int &val) { return val % 2 == 1; };
    tree1->Where(IsOdd);
    assert(tree1->Size() == 3);
    assert(tree1->Find(1));
    assert(tree1->Find(3));
    assert(tree1->Find(5));

    std::cout << "Where tests were passed!" << std::endl;

    // Map
    auto makeDouble = [](int &val) { return val * 2; };
    tree1->Map(makeDouble);
    assert(tree1->Size() == 3);
    assert(tree1->Find(2));
    assert(tree1->Find(6));
    assert(tree1->Find(10));

    std::cout << "Map tests were passed!" << std::endl;

    // Reduce
    auto Sum = [](const int &a, const int &b) -> int { return a + b; };
    tree1->Reduce(Sum);
    assert(tree1->Root()->Get() == 18);

    std::cout << "Reduce tests were passed!" << std::endl;

    delete tree1;

    std::cout << "Tree tests were passed!" << std::endl;
}



#endif
