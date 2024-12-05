#ifndef DEBTTREE_H
#define DEBTTREE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TreeNode{
public:
    vector<string> name;
    double debt;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string _name, double amount){
        name.push_back(_name);
        debt = amount;
        left = nullptr;
        right = nullptr;
    }
};

class TreeBST{
private:
    TreeNode* root;

    TreeNode* insertNode(const string& name, double amount, TreeNode* roots){
        if (roots == nullptr){
            return new TreeNode(name, amount);
        }
        else if (amount < roots->debt){
            roots->left = insertNode(name, amount, roots->left);
        }
        else if (amount > roots->debt){
            roots->right = insertNode(name, amount, roots->right);
        }
        else{
            roots->name.push_back(name);
        }
        return roots;
    }
    void displayHelper(TreeNode* roots){
        if (roots == nullptr){
            return;
        }

        TreeNode* current = roots;

        displayHelper(current->left);
        cout << "Debt: $" << current->debt << " for ";
        for (auto i : current->name){
            cout << "(" << i << ")" << " ";
        }
        cout << "\n";

        displayHelper(current->right);
    }
public:
    TreeBST(){
        root = nullptr;
    }
    void insert(const string& name, double amount){
        if (root == nullptr){
            TreeNode* newNode = new TreeNode(name, amount);
            root = newNode;
        }
        else{
            insertNode(name, amount, root);
        }
    }

    void displayTree(){
        displayHelper(root);
    }
};

#endif // DEBTTREE_H
