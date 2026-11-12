
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct Node {
  int value;
  Node* left = nullptr;
  Node* right = nullptr;
  
  Node(int number) : value(number) {}
};

class BinaryTree {
    private:
        Node* root = nullptr;
        
        // Destructor Recurrent deleting nodes form nodes to root
        void clearRecursive(Node* currentNode){
            if(currentNode == nullptr) return;
            
            clearRecursive(currentNode->left);
            clearRecursive(currentNode->right);
            delete(currentNode);
        }
        
        // Method to insert new value to its place on up-to-date node
        Node* insertRecursive(Node* currentNode, int value){
            if(currentNode == nullptr){
                return new Node(value);
            }
            
            if(value < currentNode->value){
                currentNode->left = insertRecursive(currentNode->left, value);
            } else {
                currentNode->right = insertRecursive(currentNode->right, value);
            }
            
            return currentNode;
        }
        
        // Recurrent Printing tree with styling
        void printTreeRecursive(Node* node, string prefix, bool isLast, string label){
            if(node == nullptr) return;
            
            cout << prefix + (isLast ? "└── " : "├── ") << label << "[ " << node->value << " ]" << endl;
            
            string childPrefix = prefix + (isLast ? "            " : "|            ");
            
            if(node->left != nullptr){
                printTreeRecursive(node->left, childPrefix, node->right == nullptr, "L (<" + to_string(node->value) + "): ");
            }
            
            if(node->right != nullptr){
                printTreeRecursive(node->right, childPrefix, true, "P (>=" + to_string(node->value) + "): ");
            }
        }
        
        // Recurrent Method to print values from nodes in order recurisve - only values
        void printInOrderRecursive(Node* node){
            if(node->left != nullptr) printInOrderRecursive(node->left);
            cout << node->value << " ";
            if(node->right != nullptr) printInOrderRecursive(node->right);
        }
  
  public:
    // Destructor call
    ~BinaryTree() {
        clearRecursive(root);
    }
    
    // Method to call inserting new value to node and returning newest node to the root variable
    void insert(int number){
        root = insertRecursive(root, number);
    }
  
    // Method to call printing tree
    void printTree(){
        if(this->root == nullptr){
            cout << "Drzewo jest puste" << endl;
            return;
        }
    
        printTreeRecursive(root, "", true, "Root: ");
    }
  
    // Method to call print in order provided numbers from tree
    void printInOrder(){
        if(root != nullptr){
            cout << "Wypisanie in-order: ";
            printInOrderRecursive(this->root);
        } else {
            cout << "Drzewo jest puste." << endl;
        }
    }
};

int main()
{
    BinaryTree root;
    string line;
    
    cout << "=== DRZEWO BINARNE ===" << endl;
    
    // Get user provided numbers
    cout << "Podaj liczby oddzielone spacjami: ";
    getline(cin, line);
    
    // Insert numbers to binary tree
    stringstream ss(line);
    int number;
    while(!ss.eof()){   // while ss doesn't reach the end of string
        if(ss >> number){   // converting to int
            root.insert(number);
        }else{
            // Validate letters
            ss.clear();
            ss.get();
        }
    }
    
    cout << "\n------- DRZEWO -------" << endl;
    root.printTree();
    cout << "\n----------------------" << endl;
    root.printInOrder();

    return 0;
}