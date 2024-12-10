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

    TreeNode* removeHelper(TreeNode* start, string& name, double amount){
        if (start == nullptr){
            return nullptr;
        }


        if (amount < start->debt){
            start->left = removeHelper(start->left, name, amount);
        }
        else if (amount > start->debt){
            start->right = removeHelper(start->right, name, amount);
        }
        else{
            //remove name from vector if it exists
            for (int i = 0; i < start->name.size(); ){
                if (start->name[i] == name){
                    start->name.erase(start->name.begin() + i);
                    if (!start->name.empty()){
                        return start;
                    }
                    break;
                }
                else{
                    i++;
                }
            }

            //No child
            if (start->left == nullptr && start->right == nullptr) {
                delete start;
                return nullptr;
            }
            //One child
            else if (start->left == nullptr) {
                //successor node
                TreeNode* temp = start->right;
                delete start;
                return temp;
            }
            else if (start->right == nullptr) {
                //successor node
                TreeNode* temp = start->left;
                delete start;
                return temp;
            }
            //Two child
            else{
                //successor node is right child, closest value to the current node
                TreeNode* successorNode = findSuccessor(start->right);

                //copy successor node
                start->debt = successorNode->debt;
                start->name = successorNode->name;

                //delete original successor node
                start->right = removeHelper(start->right, successorNode->name[0], successorNode->debt);
            }
        }
        return start;
    }

    TreeNode* findSuccessor(TreeNode* node){
        while (node != nullptr){
            node = node->left;
        }
        return node;
    }

    double getDebtHelper(TreeNode* node, string& name){
        if (node == nullptr){
            return 0.0;
        }
        //check if the name exists in the current node
        for (auto& person : node->name) {
            if (person == name) {
                return node->debt;
            }
        }

        double left = getDebtHelper(node->left, name);
        // If found in the left child, return it so it does not have to check the right
        if (left != 0.0) {
            return left;
        }

        double right = getDebtHelper(node->right, name);
        return right; // Return result from the right subtree
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

    TreeNode* getRoot(){
        return root;
    }

    double getDebt(string& name){
        if (root == nullptr){
            return 0.0;
        }
        else{
            return getDebtHelper(root, name);
        }
    }

    void remove(string& name, double debt){
        if (root == nullptr){
            return;
        }
        else{
            removeHelper(root, name, debt);
        }
    }
    void displayTree(){
        displayHelper(root);
    }
};

#endif // DEBTTREE_H
