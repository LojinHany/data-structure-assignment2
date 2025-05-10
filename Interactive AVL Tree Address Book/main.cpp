#include <iostream>

using namespace std;

struct contactInfo {
    string name;
    string phone;
    string email;
};

struct Node {
    int key;
    Node *left;
    Node *right;
    int height;
    contactInfo info;

    Node(int value, contactInfo information) {
        key = value;
        info = information;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

void inOrderTraversal(Node *node) {
    if (!node) {
        return;
    }
    inOrderTraversal(node->left);
    cout << "ID: " << node->key << ", Name: " << node->info.name
         << ", Phone: " << node->info.phone << ", Email: " << node->info.email << endl;
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

int getHeight (Node* node) {
    return node ? node->height : 0;
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
    int height = getHeight(root);
    int width = (1 << height) * 2;  // Width based on the tree height
    int capWidth = 300;  // Maximum width to prevent overflow
    width = min(width, capWidth);  // Limit the width

    // Dynamically allocate the 2D array (height * 2 x width)
    string** res = new string*[height * 2];
    for (int i = 0; i < height * 2; ++i) {
        res[i] = new string[width];
        fill(res[i], res[i] + width, " ");  // Fill the row with spaces
    }

    fillMatrix(res, root, 0, width / 2, width / 4, width);

    // Print the tree
    for (int i = 0; i < height * 2; ++i) {
        for (int j = 0; j < width; ++j) {
            cout << res[i][j];
        }
        cout << endl;
    }

    // Clean up dynamically allocated memory
    for (int i = 0; i < height * 2; ++i) {
        delete[] res[i];
    }
    delete[] res;
}

int main() {
    int choice;
    while (true) {
        cout << "Address Book Application\n"
                "------------------------\n"
                "1. Add New Contact\n"
                "2. Search for Contact\n"
                "3. Delete Contact (Optional)\n"
                "4. List All Contacts (Sorted by ID)\n"
                "5. Display Current Tree Structure\n"
                "6. Exit\n"
                "------------------------\n"
                "Enter operation (1-6):" << endl;
        cin >> choice;
        Node* root = nullptr;

        switch (choice) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                listAllContacts(root);
                cout << endl;
                break;
            case 5:
                displayCurrentTreeStructure(root);
                cout << endl;
                break;
            case 6:
                cout << "Exiting" << endl;
                return 0;

        }
    }

    return 0;
}
