#include <iostream>

#include "TFTree/TFTree.h"

int main() {

//    std::string s = "Stand back! I've got jimmies!";
//    std::cout << std::hash<std::string>{}(s) << '\n';

    TFTree<std::string> tree("a");
    tree.addTFToTree(TF{1.0, 1.0, 1.0}, "b", "a");
    tree.addTFToTree(TF{-1.0, -1.0, -1.0}, "c", "a");

    tree.addTFToTree(TF{2.0, 2.0, 2.0}, "d", "b");
    tree.addTFToTree(TF{1.0, 1.0, 1.0}, "e", "b");
    tree.addTFToTree(TF{-1.0, -1.0, -1.0}, "f", "b");

    tree.addTFToTree(TF{1.0, 1.0, 1.0}, "g", "c");
    tree.addTFToTree(TF{-1.0, -1.0, -1.0}, "h", "c");

    tree.addTFToTree(TF{1.0, 1.0, 1.0}, "i", "g");
    tree.addTFToTree(TF{-1.0, -1.0, -1.0}, "j", "g");


    auto tf = tree.at("g");
    if (tree.hashExists("c")) {
        tf = tree.at("c");
    }

<<<<<<< HEAD:original/main.cpp
    auto chain = tree.aggregatedTFBetween("robot_1", "robot_2");
=======

    std::cout << tree.aggregatedTFBetween("d", "f").getTF() << std::endl;    // -3 -3 -3
    std::cout << tree.aggregatedTFBetween("d", "h").getTF() << std::endl;    // -5 -5 -5
    std::cout << tree.aggregatedTFBetween("i", "j").getTF() << std::endl;    // -2 -2 -2
    std::cout << tree.aggregatedTFBetween("j", "i").getTF() << std::endl;    //  2  2  2
    std::cout << tree.aggregatedTFBetween("a", "a").getTF() << std::endl;    //  0  0  0
    std::cout << tree.aggregatedTFBetween("c", "a").getTF() << std::endl;    //  1  1  1
    std::cout << tree.aggregatedTFBetween("a", "c").getTF() << std::endl;    // -1 -1 -1

//    auto d = tree.at("d") ;
    tree.updateTFForHash(TF{3.0, 3.0, 3.0}, "d");
    std::cout << tree.aggregatedTFBetween("d", "f").getTF() << std::endl;    // -4 -4 -4
>>>>>>> f5a811ef2e4658d1a5b5192a66d40922f1e148f2:main.cpp

    return 0;
}
