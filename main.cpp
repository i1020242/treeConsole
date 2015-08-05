#include "tree.h"
#include <vector>
int main()
{
    // add 50,76,21,4,32,64,15,52,100,83,2,3,70,87,80,10,18,8,12,17,19
    cBST myTree;
    std::vector<int> myVec = {50,76,21,4,32,64,15,52,100,83,2,3,70,87,80,10,18,8,12,17,19};
    for(auto it = myVec.begin(); it!=myVec.end(); it++)
    {
        myTree.AddLeaf(*it);
    }
    myTree.PrintInOrder();
    myTree.SmallestKey();
    myTree.DeleteKey(64);
    myTree.DeleteKey(19);
    myTree.DeleteKey(70);
//    myTree.DeleteKey(76);
//    myTree.DeleteKey(100);
//    myTree.DeleteKey(50);
//    myTree.DeleteKey(52);
//    myTree.DeleteKey(80);
//    myTree.DeleteKey(83);
    myTree.PrintInOrder();
    myTree.ShowPic();
    return 0;
}
