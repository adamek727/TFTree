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
        for (auto const& node : chainInverse_) {
            tf *= node.get().getTF().inverted();
        }
        for (auto const& node : chainDirect_) {
            tf *= node.get().getTF();
        }
        return tf;
    }

protected:

    void appendDirect(TFNode& node) { chainDirect_.emplace_back(node); }
    void appendInverse(TFNode& node) { chainInverse_.emplace_back(node); }

private:

    std::vector<std::reference_wrapper<TFNode>> chainDirect_{};
    std::vector<std::reference_wrapper<TFNode>> chainInverse_{};
    friend class TFTree<std::string>;
};