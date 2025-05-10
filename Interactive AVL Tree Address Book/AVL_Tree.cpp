#include <iostream>
#include <fstream>
#include <istream>
using namespace std;

//contact details
struct Contact {
    string name;
    string phone;
    string email;
};

struct Node {
    int key;  //key -> ID
    Contact contact;
    Node* left;
    Node* right;
    int height;

    Node(int k, Contact info) {
        key = k;
        contact = info;
        left = right = nullptr;
        height = 1;
    }
};

//Will be used in helper functions
Node* root = nullptr;


void inOrderTraversal(Node *node) {
    if (!node) {
        return;
    }
    inOrderTraversal(node->left);
    cout << "ID: " << node->key << ", Name: " << node->contact.name
         << ", Phone: " << node->contact.phone << ", Email: " << node->contact.email << endl;
    inOrderTraversal(node->right);
}

void listAllContacts(Node *root) {
    if (!root) {
        cout << "Address Book is empty." << endl;
    } else {
        cout << "Contacts in Address Book (sorted by ID):" << endl;
        inOrderTraversal(root);
    }
}

int height(Node* n) {
    return n ? n->height : 0;
}

int getBalance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
}

//Add contact
Node* insert(Node* node, int key, Contact c) {

    if (!node) return new Node(key, c);
    if (key < node->key)
        node->left = insert(node->left, key, c);
    else if (key > node->key)
        node->right = insert(node->right, key, c);
    else {
        cout << "Error: Contact with ID " << key << " already exists.\n";
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    //Balance cases
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

//Delete contact by ID
Node* deleteNode(Node* root, int key) {
    if (!root) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->contact = temp->contact;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

//Search using ID
Node* search(Node* root, int key) {
    if (!root || root->key == key)
        return root;
    if (key < root->key)
        return search(root->left, key);
    return search(root->right, key);
}

//helper function for insert
void addContact(ifstream& in) {
    Contact c;
    int id;
    in >> id >> c.name >> c.phone >> c.email;
    Node* found = search(root, id);
    if (found){
        cout << "Error: Contact with ID " << id << " already exists."<<endl;
    } else{
        root = insert(root, id, c);
        cout << "Contact added successfully."<< endl;
    }
}

//helper function for delete
void deleteContact(ifstream& in) {
    int id;
    in >> id;
    Node* found = search(root, id);
    if (found) {
        root = deleteNode(root, id);
        cout << "Contact deleted successfully."<<endl;
    } else {
        cout << "Contact not found."<<endl;
    }
}


//helper function for search
void searchContact(ifstream& in) {
    int id;
    in >> id;
    Node* found = search(root, id);
    if (found) {
        cout << "Contact found:"<<endl;
        cout << "ID: " << found->key << "\n";
        cout << "Name: " << found->contact.name << "\n";
        cout << "Phone: " << found->contact.phone << "\n";
        cout << "Email: " << found->contact.email << "\n";
    } else {
        cout << "Contact not found."<<endl;
    }
}


// Fill the tree structure in the array (2D grid-like representation)
void fillMatrix(string** res, Node* root, int row, int col, int offset, int maxWidth) {
    if (!root) return;

    // Ensure we're not writing outside the bounds of the array
    if (row < 0 || row >= maxWidth || col < 0 || col >= maxWidth) return;

    // Place the node value at the correct position
    res[row][col] = to_string(root->key);

    // Prevent offset from becoming too small
    if (offset < 1) return;

    // Place the left child branch
    if (root->left) {
        if (col - offset >= 0) res[row + 1][col - offset] = "/";
        fillMatrix(res, root->left, row + 2, col - 2 * offset, offset / 2, maxWidth);
    }

    // Place the right child branch
    if (root->right) {
        if (col + offset < maxWidth) res[row + 1][col + offset] = "\\";
        fillMatrix(res, root->right, row + 2, col + 2 * offset, offset / 2, maxWidth);
    }
}

// Main function to print the tree using raw arrays
void displayCurrentTreeStructure(Node* root) {
    if (!root) {
        cout << "Tree is empty." << endl;
        return;
    }
    int Height = height(root);
    int width = (1 << Height) * 2;  // Width based on the tree height
    int capWidth = 500;  // Maximum width to prevent overflow
    width = min(width, capWidth);  // Limit the width

    // Dynamically allocate the 2D array (height * 2 x width)
    string** res = new string*[Height * 2];
    for (int i = 0; i < Height * 2; ++i) {
        res[i] = new string[width];
        fill(res[i], res[i] + width, " ");  // Fill the row with spaces
    }

    fillMatrix(res, root, 0, width / 2, width / 4, width);

    // Print the tree
    for (int i = 0; i < Height * 2; ++i) {
        for (int j = 0; j < width; ++j) {
            cout << res[i][j];
        }
        cout << endl;
    }

    // Clean up dynamically allocated memory
    for (int i = 0; i < Height * 2; ++i) {
        delete[] res[i];
    }
    delete[] res;
}

int main() {
    ifstream in("input.txt");
    if (!in) {
        cerr << "Error opening input file.\n";
        return 1;
    }
    int choice;

    while (in >> choice) {
        cout << "Address Book Application\n"
                "------------------------\n"
                "1. Add New Contact\n"
                "2. Search for Contact\n"
                "3. Delete Contact\n"
                "4. List All Contacts\n"
                "5. Display Current Tree Structure\n"
                "------------------------\n"
                "Enter operation (1-5):" << endl;

        switch (choice) {
            case 1:
                addContact(in);
                break;
            case 2:
                searchContact(in);
                break;
            case 3:
                deleteContact(in);
                break;
            case 4:
                listAllContacts(root);
                cout << endl;
                break;
            case 5:
                displayCurrentTreeStructure(root);
                cout << endl;
                break;
            default:
                cout << "Invalid choice in file."<<endl;
        }
    }
    return 0;
}
