#include <iostream>
#include <fstream>
#include <istream>
#include <iomanip>

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
    Node *left;
    Node *right;
    int height;

    Node(int k, Contact info) {
        key = k;
        contact = info;
        left = right = nullptr;
        height = 1;
    }
};


template<class T, int size = 100>
class ArrayQueue {
private:
    int first, last;
    T data[size];

public:
    ArrayQueue() {
        first = -1;
        last = -1;
    }

    bool isEmpty() {
        return first == -1;
    }

    int Size() {
        if (isEmpty()) {
            return 0;
        }
        if (last >= first) {
            return last - first + 1;
        } else {
            return size - first + last + 1;
        }
    }

    Node *front() {
        if (first == -1 || first > last) {
            cout << "empty" << endl;
            return nullptr;
        } else {
            return data[first];
        }
    }

    void enqueue(T value) {
        if (isEmpty()) {
            first = 0;
            last = 0;
        } else if (last == size - 1) {
            last = 0; // wrap around
        } else {
            last++;
        }
        data[last] = value;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. Cannot dequeue." << endl;
            return;
        }
        if (first == last) { // queue has only 1 element
            first = -1;
            last = -1;
        } else if (first == size - 1) {
            first = 0; // wrap around
        } else {
            first++;
        }
    }

};


//Will be used in helper functions
Node *root = nullptr;


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

int height(Node *n) {
    return n ? n->height : 0;
}

int getBalance(Node *n) {
    return n ? height(n->left) - height(n->right) : 0;
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
}

//Add contact
Node *insert(Node *node, int key, Contact c) {

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


Node *minValueNode(Node *node) {
    Node *current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

//Delete contact by ID
Node *deleteNode(Node *root, int key) {
    if (!root) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node *temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        } else {
            Node *temp = minValueNode(root->right);
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
Node *search(Node *root, int key) {
    if (!root || root->key == key)
        return root;
    if (key < root->key)
        return search(root->left, key);
    return search(root->right, key);
}

//helper function for insert
void addContact(ifstream &in) {
    Contact c;
    int id;
    in >> id >> c.name >> c.phone >> c.email;
    Node *found = search(root, id);
    if (found) {
        cout << "Error: Contact with ID " << id << " already exists." << endl;
    } else {
        root = insert(root, id, c);
        cout << "Contact added successfully." << endl;
    }
}

//helper function for delete
void deleteContact(ifstream &in) {
    int id;
    in >> id;
    Node *found = search(root, id);
    if (found) {
        root = deleteNode(root, id);
        cout << "Contact deleted successfully." << endl;
    } else {
        cout << "Contact not found." << endl;
    }
}


//helper function for search
void searchContact(ifstream &in) {
    int id;
    in >> id;
    Node *found = search(root, id);
    if (found) {
        cout << "Contact found:" << endl;
        cout << "ID: " << found->key << "\n";
        cout << "Name: " << found->contact.name << "\n";
        cout << "Phone: " << found->contact.phone << "\n";
        cout << "Email: " << found->contact.email << "\n";
    } else {
        cout << "Contact not found." << endl;
    }
}

void printTree(Node *root) {
    if (!root) return;

    // Step 1: Calculate tree depth and width
    int depth = height(root);
    int maxWidth = (1 << depth) * 3;  // Width of the last level

    // Step 2: Level order traversal using queue
    ArrayQueue<Node *> q;
    q.enqueue(root);

    int level = 0;
    while (!q.isEmpty()) {
        int levelNodeCount = q.Size();
        int spaceBetweenNodes = maxWidth / (levelNodeCount + 1);

        // Step 3: Print all nodes in the current level
        Node **currentLevelNodes = new Node *[levelNodeCount];
        for (int i = 0; i < levelNodeCount; ++i) {
            Node *node = q.front();
            q.dequeue();

            currentLevelNodes[i] = node;

            // If node is not null, print its value; otherwise, print a space
            if (node) {
                cout << setw(spaceBetweenNodes) << node->key;
                q.enqueue(node->left);
                q.enqueue(node->right);
            } else {
                cout << setw(spaceBetweenNodes) << " ";
                q.enqueue(nullptr);
                q.enqueue(nullptr);
            }
        }
        cout << endl;

        // Step 4: Print branches (left and right)
        if (!q.isEmpty()) {
            for (int i = 0; i < levelNodeCount; ++i) {
                Node *node = currentLevelNodes[i];
                int spaceBetweenBranches = spaceBetweenNodes / 2;

                // Left branch
                if (node && node->left) {
                    cout << setw(spaceBetweenBranches) << "/";
                } else {
                    cout << setw(spaceBetweenBranches) << " ";
                }

                // Right branch
                if (node && node->right) {
                    cout << setw(spaceBetweenBranches) << "\\";
                } else {
                    cout << setw(spaceBetweenBranches) << " ";
                }
            }
            cout << endl;
        }

        // Check if there are non-null children before going to the next level
        bool hasNonNullChildren = false;
        for (int i = 0; i < levelNodeCount; ++i) {
            Node *node = currentLevelNodes[i];
            if (node && (node->left || node->right)) {
                hasNonNullChildren = true;
                break;
            }
        }

        if (!hasNonNullChildren) {
            break;  // Stop if there are no more nodes with children
        }

        level++;

        delete[] currentLevelNodes;
    }
}


int main() {
    ifstream in("input.txt");
    if (!in) {
        cerr << "Error opening input file.\n";
        return 1;
    }
    int choice;

    while (in >> choice) {
        cout << "\nAddress Book Application\n"
                "------------------------\n"
                "1. Add New Contact\n"
                "2. Search for Contact\n"
                "3. Delete Contact\n"
                "4. List All Contacts\n"
                "5. Display Current Tree Structure\n"
                "6. Exit\n"
                "------------------------\n"
                "Enter operation (1-6):" << endl;

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
                printTree(root);
                cout << endl;
                break;
            case 6:
                cout << "Exiting" << endl;
                return 0;
            default:
                cout << "Invalid choice in file." << endl;
        }
    }
    return 0;
}

