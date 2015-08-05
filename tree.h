#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <QTextStream>
#include <QFile>
#include <QProcess>

class cBST
{
private:
    struct Node
    {
        int key;
        Node* left;
        Node* right;
    };
    Node* root;
    Node* createLeaf(int key);
    void AddLeafPrivate(int key, Node* Ptr);
    void PrintInOrderPrivate(Node* Ptr);
    int SmallestKeyPrivate(Node* Ptr);
    void DeleteKeyPrivate(int key, Node* parent);
    void DeleteKeyMatch(Node* parent, Node* match);
    void DeleteRootMatch();
    void WalkGraph(Node* ptr, QTextStream& stream);
    void PrepareWalk();
public:
    cBST();
    void AddLeaf(int key);
    void PrintInOrder();
    void SmallestKey();
    void DeleteKey(int key);
    void ShowPic();
};

#endif // TREE_H
