//
// Created by 123456 on 2021/5/7.
//

#ifndef COPY_CONTROL_TREENODE_H
#define COPY_CONTROL_TREENODE_H

#include <iostream>

class TreeNode {
public:
    TreeNode(const std::string s = std::string()) : value(s), count(1), left(nullptr), right(nullptr){}
    //TreeNode(const TreeNode &t) : value(t.value), count(t.count), left(t.left), right(t.right) { }
    TreeNode& operator=(const TreeNode&);
    ~TreeNode() { delete left; delete right; }
private:
    std::string value;
    int count;
    TreeNode *left;
    TreeNode *right;
};


#endif //COPY_CONTROL_TREENODE_H
