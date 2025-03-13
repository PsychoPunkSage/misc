#include <stdio.h>
#include <stdlib.h>

// Structure for AVL tree node
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    int height;
};

// Function to get the height of a node
int getHeight(struct Node *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to get maximum of two integers
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Function to create a new node
struct Node *createNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1; // New node is initially at height 1
    return newNode;
}

// Function to right rotate subtree rooted with y
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // Return new root
    return x;
}

// Function to left rotate subtree rooted with x
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    // Return new root
    return y;
}

// Get the balance factor of a node
int getBalanceFactor(struct Node *node)
{
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to insert a value in AVL tree
struct Node *insert(struct Node *node, int value)
{
    // 1. Perform standard BST insertion
    if (node == NULL)
        return createNode(value);

    if (value < node->data)
        node->left = insert(node->left, value);
    else if (value > node->data)
        node->right = insert(node->right, value);
    else // Duplicate values not allowed
        return node;

    // 2. Update height of this ancestor node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // 3. Get the balance factor to check if this node became unbalanced
    int balance = getBalanceFactor(node);

    // If unbalanced, there are 4 cases

    // Left Left Case
    if (balance > 1 && value < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && value > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && value > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && value < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the unchanged node pointer
    return node;
}

// Function to find the node with minimum value
struct Node *findMinValueNode(struct Node *node)
{
    struct Node *current = node;

    // Loop down to find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

// Function to delete a node from AVL tree
struct Node *deleteNode(struct Node *root, int value)
{
    // 1. Perform standard BST delete
    if (root == NULL)
        return root;

    if (value < root->data)
        root->left = deleteNode(root->left, value);
    else if (value > root->data)
        root->right = deleteNode(root->right, value);
    else
    {
        // node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL))
        {
            struct Node *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else               // One child case
                *root = *temp; // Copy the contents of the non-empty child

            free(temp);
        }
        else
        {
            // Node with two children: Get the inorder successor
            struct Node *temp = findMinValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->data);
        }
    }

    // If the tree had only one node, return
    if (root == NULL)
        return root;

    // 2. Update height of current node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // 3. Get the balance factor of this node to check if it became unbalanced
    int balance = getBalanceFactor(root);

    // If unbalanced, there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalanceFactor(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalanceFactor(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to search for a value in AVL tree
struct Node *search(struct Node *root, int value)
{
    // Base cases: root is null or value is present at root
    if (root == NULL || root->data == value)
        return root;

    // Value is greater than root's data
    if (root->data < value)
        return search(root->right, value);

    // Value is smaller than root's data
    return search(root->left, value);
}

// Function for inorder traversal
void inorderTraversal(struct Node *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Function to display tree structure (with indentation)
void displayTree(struct Node *root, int level)
{
    if (root != NULL)
    {
        displayTree(root->right, level + 1);

        for (int i = 0; i < level; i++)
        {
            printf("    ");
        }

        printf("%d (BF=%d)\n", root->data, getBalanceFactor(root));

        displayTree(root->left, level + 1);
    }
}

// Function to free the memory of AVL tree
void freeAVL(struct Node *root)
{
    if (root != NULL)
    {
        freeAVL(root->left);
        freeAVL(root->right);
        free(root);
    }
}

int main()
{
    struct Node *root = NULL;
    int choice, value;

    do
    {
        printf("\n\n--- AVL Tree Operations ---\n");
        printf("1. Insert a value\n");
        printf("2. Delete a value\n");
        printf("3. Search for a value\n");
        printf("4. Display inorder traversal\n");
        printf("5. Display tree structure\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            root = insert(root, value);
            printf("Value inserted successfully!\n");
            break;

        case 2:
            printf("Enter value to delete: ");
            scanf("%d", &value);
            root = deleteNode(root, value);
            printf("Value deleted if present!\n");
            break;

        case 3:
            printf("Enter value to search: ");
            scanf("%d", &value);
            if (search(root, value) != NULL)
            {
                printf("Value %d found in the tree!\n", value);
            }
            else
            {
                printf("Value %d not found in the tree!\n", value);
            }
            break;

        case 4:
            printf("Inorder Traversal: ");
            inorderTraversal(root);
            printf("\n");
            break;

        case 5:
            printf("Tree Structure:\n");
            displayTree(root, 0);
            break;

        case 6:
            printf("Exiting program...\n");
            break;

        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    // Free the AVL tree memory before exiting
    freeAVL(root);

    return 0;
}