#pragma once

#include <algorithm>
#include <map>

#include "TFNode.h"
#include "TFChain.h"

template<typename T>
class TFTree {

public:

    explicit TFTree(const T& rootNodeHash) {
        existingHashes_.emplace_back(rootNodeHash);
        nodesHashMap_.insert({rootNodeHash, {rootNodeHash, {0,0,0}}});
    }

    void addTFToTree(TF tf, const T& hash, const T& parentHash) {
        if (hashExists(parentHash)) {
            nodesHashMap_.insert({hash, TFNode{hash, tf, nodesHashMap_.at(parentHash)}});
            nodesHashMap_.at(parentHash).addChildren(nodesHashMap_.at(hash));
            existingHashes_.emplace_back(hash);
        }
    }

    bool hashExists(const T& hash) {
        return std::find(existingHashes_.begin(), existingHashes_.end(), hash) != existingHashes_.end();
    }

    TF operator[] (const T& hash) {
        if(hashExists(hash)) {

        }
        return {0,0,0};
    }

    TF at(const T& hash) {
        return nodesHashMap_.at(hash).getTF();
    }

    TFChain aggregatedTFBetween(const std::string& first, const std::string& second) {

        TFChain output{};

        if ( !hashExists(first) || !hashExists(second)) {
            return output;
        }
        if(first == second) {
            return output;
        }

        // build path from first to root and from second to root

        // sertch


        return output;
    }


private:

    std::vector<T> existingHashes_;
    std::map<T, TFNode> nodesHashMap_;
};