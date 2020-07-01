#pragma once

#include <algorithm>
#include <map>

#include "TFNode.h"
#include "TFChain.h"

template<typename T>
class TFTree {

public:

    explicit TFTree(const T& rootNodeHash) {
        nodesHashMap_.emplace( std::make_pair<T, TFNode<T>>(rootNodeHash, TFNode<T>{rootNodeHash, TF{0,0,0}}) );
        existingHashes_.emplace_back(rootNodeHash);
    }

    void addTFToTree(TF tf, const T& hash, const T& parentHash) {
        if (hashExists(parentHash)) {
            nodesHashMap_.emplace( std::make_pair<T, TFNode<T>>(hash, TFNode<T>{hash, tf, nodesHashMap_.at(parentHash)}));
            nodesHashMap_.at(parentHash).addChildren(nodesHashMap_.at(hash));
            existingHashes_.emplace_back(hash);
        }
    }

    void updateTFForHash(TF tf, const T& hash) {
        if (hashExists(hash)) {
            nodesHashMap_.at(hash).setTF(tf);
        }
    }

    bool hashExists(const T& hash) {
        return std::find(existingHashes_.begin(), existingHashes_.end(), hash) != existingHashes_.end();
    }

    const TF& at(const T& hash) {
        return nodesHashMap_.at(hash).getTF();
    }

    TFChain<T> aggregatedTFBetween(const T& first, const T& second) {

        TFChain<T> output{};

        if ( !hashExists(first) || !hashExists(second)) {
            return output;
        }
        if(first == second) {
            return output;
        }

        std::vector<T> firstPath;
        firstPath.reserve(nodesHashMap_.at(first).getTreeLevel()+1);
        firstPath.push_back(first);

        std::vector<T> secondPath;
        secondPath.reserve(nodesHashMap_.at(second).getTreeLevel()+1);
        secondPath.push_back(second);

        while (true) {
            auto currentFirst = nodesHashMap_.at(firstPath.back());
            auto currentSecond = nodesHashMap_.at(secondPath.back());

            if (currentFirst.getHash() == currentSecond.getHash()) {
                break;
            }

            if(currentFirst.getTreeLevel() > currentSecond.getTreeLevel()) {
                firstPath.push_back(currentFirst.getParent().getHash());
            }
            else if(currentFirst.getTreeLevel() < currentSecond.getTreeLevel()) {
                secondPath.push_back(currentSecond.getParent().getHash());
            } else {
                firstPath.push_back(currentFirst.getParent().getHash());
                secondPath.push_back(currentSecond.getParent().getHash());
            }
        }

        if(firstPath.back() != secondPath.back()) {
            std::cerr << "Unexpected state!" << std::endl;
            return output;
        }

        for (typename std::vector<T>::iterator inverseNodeIt = firstPath.begin() ; inverseNodeIt < firstPath.end()-1 ; inverseNodeIt++) {
            output.appendInverse(nodesHashMap_.at(*inverseNodeIt));
        }

        for (typename std::vector<T>::iterator directNodeIt = secondPath.end()-2 ; directNodeIt >= secondPath.begin() ; directNodeIt--) {
            output.appendDirect(nodesHashMap_.at(*directNodeIt));
        }

        return output;
    }


private:

    std::vector<T> existingHashes_;
    std::map<T, TFNode<T>> nodesHashMap_;
};