#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>

using namespace std;

#include "Tree.hpp"

#define EMPTY if (tree->Root() == nullptr) {\
    cout << "Empty\n";\
    break;}

#define PRINT_PLR EMPTY cout << "Tree:\n"; \
    tree->PrintPLR(tree->Root()); \
    cout << endl;

#define PRINT_PRL EMPTY cout << "Tree:\n"; \
    tree->PrintPLR(tree->Root()); \
    cout << endl;

void talker() {
    cout << "\nSelect an option:\n"
            "1. New tree from array (empty tree already exist)\n"   //completed
            "2. Insert the note\n"  //completed
            "3. Find the key\n"     //completed
            "4. Print the tree (PLR)\n"   //completed
            "5. Print the tree (PRL)\n"   //completed
            "6. Remove the note\n"  //completed
            "7. Map()\n"    //COMPLETED
            "8. Where()\n"  //completed
            "9. Reduce()\n" //completed
            "10. Get the Size of tree\n"
            "0. Finish program\n"
            ">";
}

void menu() {
    int flag = 1, choice, value, rubbish;
    auto *tree = new BinaryTree<int>;
    auto makeDouble = [](int &val) { return val * 2; };
    auto isOdd = [](int &val) { return val % 2 == 1; };
    auto sum = [](const int &a, const int &b) -> int { return a + b; };
    while (flag) {
        talker();
        cin >> choice;

        switch (choice) {
            case 1:     // Tree from array
                cout << "Enter length of the array: ";
                cin >> rubbish;
                cout << "Enter the array: ";
                for (int i = 0; i < rubbish; i++) {
                    cin >> value;
                    tree->Insert(value);
                }
                PRINT_PLR
                break;
            case 2:     // Insert note
                cout << "Enter the key: ";
                cin >> value;
                tree->Insert(value);
                PRINT_PLR
                break;
            case 3:     //Find key
                EMPTY
                cout << "Enter the key: ";
                cin >> value;
                if (tree->Find(value)) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
                PRINT_PLR
                break;
            case 4:     // PrintPLR the tree
                EMPTY
                PRINT_PLR
                break;

            case 5:     // PrintPRL the tree
                EMPTY
                PRINT_PRL
                break;

            case 6:     // Remove note
                EMPTY
                PRINT_PLR
                cout << "Enter the key to Remove: ";
                cin >> value;
                while (!tree->Find(value)) {
                    cout << "This key isn't in the tree, try again: ";
                    cin >> value;
                }
                tree->Remove(value);
                PRINT_PLR
                break;

            case 7:     // Map()
                EMPTY
                PRINT_PLR
                tree->Map(makeDouble);
                PRINT_PLR
                break;

            case 8:     // Where()
                EMPTY
                PRINT_PLR
                tree->Where(isOdd);
                PRINT_PLR
                break;

            case 9:     // Reduce()
                EMPTY
                PRINT_PLR
                tree->Reduce(sum);
                PRINT_PLR
                break;

            case 10:
                EMPTY
                PRINT_PLR
                cout << "Size of tree: " << tree->Size() << endl;
                break;

//            case 9:     //test print
//                tree->test();

            case 0:     // Finish
                flag = 0;
                delete tree;
                break;
            default:
                break;
        }

    }
}

#endif
