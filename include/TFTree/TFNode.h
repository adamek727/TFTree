#pragma once

#include <string>
#include <vector>
#include <functional>

#include "TF.h"

class TFNode {

public:

    TFNode() = delete;

    TFNode(std::string hash, TF tf) :
            hash_{std::move(hash)},
            tf_{tf},
            parent_{*this},
            treeLevel_{0} {

    }

    TFNode(std::string hash, TF tf, TFNode& parent) :
            hash_{std::move(hash)},
            tf_{tf},
            parent_{parent},
            treeLevel_{parent.getTreeLevel() + 1} {
        parent.addChildren(*this);
    }

    TFNode(TFNode& old) :
            hash_{old.getHash()},
            tf_{old.getTF()},
            parent_{old.getParent()},
            children_{old.getChildren()},
            treeLevel_{old.getTreeLevel()} {

    }


    [[nodiscard]] const std::string& getHash() const { return hash_;}
    [[nodiscard]] const TF& getTF() {return tf_;};
    [[nodiscard]] const TFNode& getParent() const {return treeLevel_ == 0 ? *this : parent_;};
    [[nodiscard]] std::vector<std::reference_wrapper<TFNode>> getChildren() const {return children_;};

    void addChildren(TFNode& newChild) {children_.emplace_back(newChild);}
    [[nodiscard]]bool isRoot() const {return treeLevel_ == 0;};
    uint32_t getTreeLevel() const {return treeLevel_;}

    void setTF(TF tf) {tf_ = tf;};

private:

    std::string hash_;
    TF tf_;

    const TFNode& parent_;
    std::vector<std::reference_wrapper<TFNode>> children_{};
    uint32_t treeLevel_;

};