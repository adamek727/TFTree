#include <iostream>

#include "TFTree/TFTree.h"

int main() {

    TFTree<std::string> tree("origin");
    tree.addTFToTree({1.0,1.0,1.0}, "robot_1", "origin");
    tree.addTFToTree({-1.0,-1.0,-1.0}, "robot_2", "origin");
    tree.addTFToTree({0.0, 0.0, 1.0}, "robot_2_arm", "robot_2");

    auto tf = tree["robot_1"];
    if (tree.hashExists("robot_2")) {
        tf = tree.at("robot_2");
    }
    
    auto chain = tree.aggregatedTFBetween("robot_1", "robot_2");

    return 0;
}
