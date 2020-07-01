#pragma once

#include <string>
#include <vector>
#include <functional>

#include "TF.h"


template<typename T>
class TFNode {

public:

    TFNode() = delete;

    explicit TFNode(const T& hash, TF tf) :
            hash_{std::move(hash)},
            tf_{tf},
            parent_{*this},
            treeLevel_{0} {

    }

    explicit TFNode(const T& hash, TF tf, TFNode& parent) :
            hash_{std::move(hash)},
            tf_{tf},
            parent_{parent},
            treeLevel_{parent.getTreeLevel() + 1} {
        parent.addChildren(*this);
    }

    TFNode(TFNode& tfNode) :
            hash_{tfNode.getHash()},
            tf_{tfNode.getTF()},
            parent_{tfNode.getParent()},
            children_{tfNode.getChildren()},
            treeLevel_{tfNode.getTreeLevel()} {

    }


    [[nodiscard]] const T& getHash() const { return hash_;}
    [[nodiscard]] const TF& getTF() {return tf_;};
    [[nodiscard]] const TFNode& getParent() const {return treeLevel_ == 0 ? *this : parent_;};
    [[nodiscard]] std::vector<std::reference_wrapper<TFNode>> getChildren() const {return children_;};

    void addChildren(TFNode& newChild) {children_.emplace_back(newChild);}
    [[nodiscard]]bool isRoot() const {return treeLevel_ == 0;};
    uint32_t getTreeLevel() const {return treeLevel_;}

    void setTF(TF tf) {tf_ = tf;};

private:

    const T& hash_;
    TF tf_;

    const TFNode& parent_;
    std::vector<std::reference_wrapper<TFNode>> children_{};
    uint32_t treeLevel_;

};