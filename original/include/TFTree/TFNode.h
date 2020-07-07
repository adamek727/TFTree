#pragma once

#include <string>
#include <vector>
#include <functional>

#include "TF.h"


using hashType = unsigned long;

class TFNode {

public:

    TFNode() = delete;

    explicit TFNode(const hashType hash, TF tf) :
            hash_{hash},
            tf_{tf},
            parent_{hash_},
            treeLevel_{0} {

    }

    explicit TFNode(const hashType& hash, TF tf, TFNode& parent) :
            hash_{hash},
            tf_{tf},
            parent_{parent.getHash()},
            treeLevel_{parent.getTreeLevel() + 1} {
        parent.addChildren(*this);
    }

    TFNode(TFNode&& tfNode) noexcept :
            hash_{tfNode.getHash()},
            tf_{tfNode.getTF()},
            parent_{tfNode.getParentHash()},
            children_{tfNode.getChildren()},
            treeLevel_{tfNode.getTreeLevel()} {

    }


    [[nodiscard]] const hashType& getHash() const { return hash_;}
    [[nodiscard]] const TF& getTF() {return tf_;};
    [[nodiscard]] const hashType& getParentHash() const {return treeLevel_ == 0 ? hash_ : parent_;};
    [[nodiscard]] std::vector<std::reference_wrapper<TFNode>> getChildren() const {return children_;};

    void addChildren(TFNode& newChild) {children_.emplace_back(newChild);}
    [[nodiscard]] bool isRoot() const {return treeLevel_ == 0;};
    [[nodiscard]] uint32_t getTreeLevel() const {return treeLevel_;}

    void setTF(TF tf) {tf_ = tf;};

private:

    const hashType hash_;
    TF tf_;

    const hashType parent_;
    std::vector<std::reference_wrapper<TFNode>> children_{};
    uint32_t treeLevel_;

};