#pragma once

#include <vector>

#include "TF.h"

template<typename T>
class TFTree;

class TFChain {

public:

    TFChain() { }

    TF aggregatedTF() const {
        auto tf = TF{0,0,0};
        for (auto const& node : chain_) {
            tf *= node.get().getTF();
        }
        return tf;
    }

protected:

    void append(const TFNode& node) { chain_.emplace_back(node); }

private:

    std::vector<std::reference_wrapper<const TFNode>> chain_{};
    friend class TFTree<std::string>;
};