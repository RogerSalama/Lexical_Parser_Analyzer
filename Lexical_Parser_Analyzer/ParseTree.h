#ifndef PARSETREE_H
#define PARSETREE_H
#include <vector>
#include <string>
#include "ParseTreeNode.h"
using namespace std;
class ParseTree {
public:
    ParseTreeNode* root;

    ParseTree() : root(nullptr) {}
    ~ParseTree() { delete root; }

    void addChild(ParseTreeNode* parent, ParseTreeNode* child) {
        if (parent) parent->children.push_back(child);
    }

    // Function to generate data for visualization
    vector<pair<string, string>> generateEdges() {
        vector<pair<string, string>> edges;
        traverseEdges(root, edges);
        return edges;
    }
    // Finds parent by node ID (for linking new nodes)
    ParseTreeNode* findParentById(ParseTreeNode* current, const string& targetId) {
        if (current->nodeID == targetId) return current;
        for (auto child : current->children) {
            ParseTreeNode* found = findParentById(child, targetId);
            if (found) return found;
        }
        return nullptr;
    }
    string generateNodeId(const string& symbol, int stackDepth) {
        return symbol + "_" + to_string(stackDepth);
    }

private:
    void traverseEdges(ParseTreeNode* node, vector<pair<string, string>>& edges) {
        if (!node) return;

        for (auto child : node->children) {
            edges.push_back({node->symbol, child->symbol});
            traverseEdges(child, edges);
        }
    }
};
#endif
