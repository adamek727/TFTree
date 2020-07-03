#pragma once

#include <algorithm>
#include <map>

#include "TFNode.h"
#include "TFChain.h"

template<typename T>
class TFTree {

public:

    explicit TFTree(const T& rootNodeHash) {
        auto hash = std::hash<T>{}(rootNodeHash);
        nodesHashMap_.emplace( hash, TFNode{hash, TF{0,0,0}} );
        existingHashes_.emplace_back(hash);
    }

    void addTFToTree(const TF& tf, const T& tfHash, const T& parentHash) {

        auto hash = std::hash<T>{}(tfHash);
        auto pHash = std::hash<T>{}(parentHash);
        if (hashExists(pHash)) {
            nodesHashMap_.emplace( hash, TFNode{hash, tf, nodesHashMap_.at(pHash)});
            nodesHashMap_.at(pHash).addChildren(nodesHashMap_.at(hash));
            existingHashes_.emplace_back(hash);
        }
    }

    void updateTFForHash(TF tf, const T& tfHash) {
        auto hash = std::hash<T>{}(tfHash);
        if (hashExists(hash)) {
            nodesHashMap_.at(hash).setTF(tf);
        }
    }

    bool hashExists(const hashType& hash) {
        return std::find(existingHashes_.begin(), existingHashes_.end(), hash) != existingHashes_.end();
    }

    bool hashExists(const T& tfHash) {
        auto hash = std::hash<T>{}(tfHash);
        return std::find(existingHashes_.begin(), existingHashes_.end(), hash) != existingHashes_.end();
    }

    const TF& at(const T& tfHash) {
        auto hash = std::hash<T>{}(tfHash);
        return nodesHashMap_.at(hash).getTF();
    }

    TFChain<T> aggregatedTFBetween(const T& first, const T& second) {

        TFChain<T> output{};

        auto fHash = std::hash<T>{}(first);
        auto sHash = std::hash<T>{}(second);

        if ( !hashExists(fHash) || !hashExists(sHash)) {
            return output;
        }
        if(fHash == sHash) {
            return output;
        }

        std::vector<hashType> firstPath;
        firstPath.reserve(nodesHashMap_.at(fHash).getTreeLevel()+1);
        firstPath.push_back(fHash);

        std::vector<hashType> secondPath;
        secondPath.reserve(nodesHashMap_.at(sHash).getTreeLevel()+1);
        secondPath.push_back(sHash);

        while (true) {

            std::cout << nodesHashMap_.at(firstPath.back()).getHash() << " " << nodesHashMap_.at(secondPath.back()).getHash() << std::endl;
            auto& currentFirst = nodesHashMap_.at(firstPath.back());
            auto& currentSecond = nodesHashMap_.at(secondPath.back());

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

        for (auto inverseNodeIt = firstPath.begin() ; inverseNodeIt < firstPath.end()-1 ; inverseNodeIt++) {
            output.appendInverse(nodesHashMap_.at(*inverseNodeIt));
        }

        for (auto directNodeIt = secondPath.end()-2 ; directNodeIt >= secondPath.begin() ; directNodeIt--) {
            output.appendDirect(nodesHashMap_.at(*directNodeIt));
        }

        return output;
    }


private:

    std::vector<hashType> existingHashes_;
    std::unordered_map<hashType, TFNode> nodesHashMap_;
};