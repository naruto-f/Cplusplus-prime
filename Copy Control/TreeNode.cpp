//
// Created by 123456 on 2021/5/7.
//

#include "TreeNode.h"


TreeNode& TreeNode::operator=(const TreeNode& t)
{
    value = t.value;
    count = t.count + 1;

}
