#include "tree.h"
#include "cstdlib"
using namespace std;

cBST::cBST()
{
    root = NULL;
}

cBST::Node* cBST::createLeaf(int key)
{
    Node* newNode = new Node();
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void cBST::AddLeaf(int key)
{
    AddLeafPrivate(key, root);
}

void cBST::AddLeafPrivate(int key, Node *Ptr)
{
    if(root == NULL)
    {
        root = createLeaf(key);
    }
    else
    {
        if(key < Ptr->key)
        {
            if(Ptr->left != NULL) AddLeafPrivate(key, Ptr->left);
            if(Ptr->left == NULL) Ptr->left = createLeaf(key);
        }
        else if(key > Ptr->key)
        {
            if(Ptr->right != NULL) AddLeafPrivate(key, Ptr->right);
            if(Ptr->right == NULL) Ptr->right = createLeaf(key);
        }
        else
            cout << "Key " << Ptr->key << " already added into tree\n";


    }
}

void cBST::PrintInOrder()
{
    PrintInOrderPrivate(root);
    cout << endl;
}

void cBST::PrintInOrderPrivate(Node *Ptr)
{
    if(root == NULL)
    {
        cout << "Tree empty\n";
        exit(0);
    }
    if(Ptr->left != NULL)
    {
        PrintInOrderPrivate(Ptr->left);
    }

    cout << Ptr->key << "  ";

    if(Ptr->right != NULL)
    {
        PrintInOrderPrivate(Ptr->right);
    }
}

void cBST::SmallestKey()
{
    SmallestKeyPrivate(root);
}

int cBST::SmallestKeyPrivate(Node *Ptr)
{
    if(Ptr->left != NULL) return SmallestKeyPrivate(Ptr->left);
    else return Ptr->key;
}

void cBST::DeleteKey(int key)
{
    DeleteKeyPrivate(key, root);
}

void cBST::DeleteKeyPrivate(int key, Node *parent)
{
    if(root!=NULL)
    {
        if(key == root->key) DeleteRootMatch();

        else if(key < parent->key && parent->left != NULL)
        {
            if(parent->left->key == key) DeleteKeyMatch(parent, parent->left);
            else DeleteKeyPrivate(key, parent->left);
        }
        else if(key > parent->key && parent->right != NULL)
        {
            if(parent->right->key == key) DeleteKeyMatch(parent, parent->right);
            else DeleteKeyPrivate(key, parent->right);
        }
        else cout << "Find not found: " << key << endl;
    }
    else
        cout << "Tree is empty\n";

}

void cBST::DeleteRootMatch()
{
    Node* Ptr = root;
    if(Ptr->left == NULL && Ptr->right == NULL)
    {
        root =  NULL;
        delete Ptr;
    }
    else if(Ptr->left!=NULL && Ptr->right == NULL)
    {
        delete Ptr;
        root = root->left;
    }
    else if(Ptr->left==NULL && Ptr->right != NULL)
    {
        delete Ptr;
        root = root->right;
    }
    else if(Ptr->left != NULL && Ptr->right !=NULL)
    {
        int smallestRightNode = SmallestKeyPrivate(root->right);
        DeleteKeyPrivate(smallestRightNode,root);
        root->key = smallestRightNode;
    }


}

void cBST::DeleteKeyMatch(Node* parent, Node* match)
{
    // 0 child vd 5,7,9->rm 5,9
    if(match->left == NULL && match->right == NULL)
    {
        match->key < parent->key ? parent->left = NULL : parent->right = NULL;
        cout << "Key delete(0 child) " << match->key << " was removed\n";
        delete match;
    }
    else if(match->left != NULL && match->right == NULL)
    {
        match->key < parent->key ? parent->left = match->left : parent->right = match->left;
        cout << "Key delete(1 left child) " << match->key << " has replaced by " << match->left->key << endl;
        match->left = NULL;
        delete match;
    }
    else if(match->left == NULL && match->right != NULL)
    {
        match->key < parent->key ? parent->left = match->right : parent->right = match->right;
        cout << "Key delete(1 r8 child) " << match->key << " has replaced by " << match->right->key << endl;
        match->right = NULL;
        delete match;
    }
    else if(match->left != NULL && match->right !=NULL)
    {
        int smallestInRightChild;
        smallestInRightChild = SmallestKeyPrivate(match->right);
        DeleteKeyPrivate(smallestInRightChild, match);
        match->key = smallestInRightChild;
     }
}

void cBST::WalkGraph(Node* ptr, QTextStream &stream)
{
    static int count = 0;
    if(ptr!=NULL)
    {
        stream << "\t" << ptr->key << "[label=\"" << ptr->key<< "\"];" << endl;
        if(ptr->left!=NULL)
        {
            stream << "\t" << ptr->key << "->" << ptr->left->key << ";" << endl;
            WalkGraph(ptr->left, stream);
        }
        else
        {
            stream << "\t" << "null" << count << "[label=\"null\",style=\"filled\"];" << endl;
            stream << "\t" << ptr->key << "->" << "null" << count << endl;
            count++;
        }
        if(ptr->right!=NULL)
        {
            stream << "\t" << ptr->key << "->" << ptr->right->key << ";" << endl;
            WalkGraph(ptr->right, stream);
        }
        else
        {
            stream << "\t" << "null" << count << "[label=\"null\",style=\"filled\"];" << endl;
            stream << "\t" << ptr->key << "->" << "null" << count << endl;
            count++;
        }

    }
}

void cBST::PrepareWalk()
{
    QString fileName = "/home/mrnix/CODE/QT/myQtTree/TreeConsole/BST";
    QFile file(fileName);
    if(file.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        QTextStream stream(&file);
        stream << "digraph{" << endl;
        this->WalkGraph(root,stream);
        stream << "\n}";
        file.close();
    }
}

void cBST::ShowPic()
{
    QProcess* process = new QProcess;
    this->PrepareWalk();
    process->start("dot -Tpng /home/mrnix/CODE/QT/myQtTree/TreeConsole/BST -o /home/mrnix/CODE/QT/myQtTree/TreeConsole/BST.png");
}











