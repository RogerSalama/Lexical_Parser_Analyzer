#ifndef PARSETREENODE_H
#define PARSETREENODE_H

#include <vector>
#include <string>
using namespace std;
class ParseTreeNode {
public:
    string nodeID;
    string symbol;
    ParseTreeNode* parent;  // Add this
    vector<ParseTreeNode*> children;

    ParseTreeNode(const string& id,const string& symbol, ParseTreeNode* p = nullptr,const vector<ParseTreeNode*>& c = {}) : nodeID(id),symbol(symbol),parent(p),children(c) {}
    ~ParseTreeNode() {
        for (auto child : children) delete child;
    }
};
#endif
