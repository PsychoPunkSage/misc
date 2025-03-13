#include <stdio.h>
#include <stdlib.h>

// Color definition for Red-Black Tree
enum Color
{
    RED,
    BLACK
};

// Structure for Red-Black Tree node
struct RBNode
{
    int data;
    enum Color color;
    struct RBNode *left, *right, *parent;
};

// Global root pointer
struct RBNode *root = NULL;

// Function to create a new Red-Black Tree node
struct RBNode *createNode(int data)
{
    struct RBNode *newNode = (struct RBNode *)malloc(sizeof(struct RBNode));
    newNode->data = data;
    newNode->color = RED; // New nodes are always red
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

// Function to perform left rotation
void leftRotate(struct RBNode **root, struct RBNode *x)
{
    struct RBNode *y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Function to perform right rotation
void rightRotate(struct RBNode **root, struct RBNode *y)
{
    struct RBNode *x = y->left;
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

// Function to fix Red-Black Tree violations after insertion
void fixViolation(struct RBNode **root, struct RBNode *pt)
{
    struct RBNode *parent_pt = NULL;
    struct RBNode *grand_parent_pt = NULL;

    while ((pt != *root) && (pt->color != BLACK) && (pt->parent->color == RED))
    {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        // Case A: Parent of pt is left child of Grand-parent of pt
        if (parent_pt == grand_parent_pt->left)
        {
            struct RBNode *uncle_pt = grand_parent_pt->right;

            // Case 1: Uncle is also red, only recoloring required
            if (uncle_pt != NULL && uncle_pt->color == RED)
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }
            else
            {
                // Case 2: pt is right child of its parent, left-rotation required
                if (pt == parent_pt->right)
                {
                    leftRotate(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                // Case 3: pt is left child of its parent, right-rotation required
                rightRotate(root, grand_parent_pt);
                // Swap colors of parent and grandparent
                enum Color temp = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = temp;
                pt = parent_pt;
            }
        }
        // Case B: Parent of pt is right child of Grand-parent of pt
        else
        {
            struct RBNode *uncle_pt = grand_parent_pt->left;

            // Case 1: Uncle is also red, only recoloring required
            if (uncle_pt != NULL && uncle_pt->color == RED)
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }
            else
            {
                // Case 2: pt is left child of its parent, right-rotation required
                if (pt == parent_pt->left)
                {
                    rightRotate(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                // Case 3: pt is right child of its parent, left-rotation required
                leftRotate(root, grand_parent_pt);
                // Swap colors of parent and grandparent
                enum Color temp = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = temp;
                pt = parent_pt;
            }
        }
    }

    // Make sure root is always black
    (*root)->color = BLACK;
}

// Function to insert a new node with given data
void insert(struct RBNode **root, int data)
{
    // Allocate memory for new node
    struct RBNode *pt = createNode(data);

    // Do a standard BST insert
    struct RBNode *y = NULL;
    struct RBNode *x = *root;

    while (x != NULL)
    {
        y = x;
        if (pt->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    // y is parent of x
    pt->parent = y;

    if (y == NULL)
        *root = pt; // Tree was empty
    else if (pt->data < y->data)
        y->left = pt;
    else
        y->right = pt;

    // If root, color is black
    if (pt->parent == NULL)
    {
        pt->color = BLACK;
        return;
    }

    // If grandparent is null, return
    if (pt->parent->parent == NULL)
        return;

    // Fix Red Red violation
    fixViolation(root, pt);
}

// Function to search for a node with given data
struct RBNode *search(struct RBNode *root, int data)
{
    if (root == NULL || root->data == data)
        return root;

    if (root->data < data)
        return search(root->right, data);

    return search(root->left, data);
}

// Function to find the node with minimum value
struct RBNode *minValueNode(struct RBNode *node)
{
    struct RBNode *current = node;

    // Loop down to find the leftmost leaf
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Function for inorder traversal
void inorderTraversal(struct RBNode *root)
{
    if (root == NULL)
        return;

    inorderTraversal(root->left);
    printf("%d(%c) ", root->data, root->color == RED ? 'R' : 'B');
    inorderTraversal(root->right);
}

// Function to display tree with levels
void printTree(struct RBNode *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    printTree(root->right, space);

    // Print current node after space
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d(%c)\n", root->data, root->color == RED ? 'R' : 'B');

    // Process left child
    printTree(root->left, space);
}

// Function to free the memory of the tree
void freeTree(struct RBNode *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main()
{
    struct RBNode *root = NULL;
    int choice, value;

    do
    {
        printf("\n\n--- Red-Black Tree Operations ---\n");
        printf("1. Insert a value\n");
        printf("2. Search for a value\n");
        printf("3. Display inorder traversal\n");
        printf("4. Display tree structure\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            insert(&root, value);
            printf("Value inserted successfully!\n");
            break;

        case 2:
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

        case 3:
            printf("Inorder Traversal: ");
            inorderTraversal(root);
            printf("\n");
            break;

        case 4:
            printf("Tree Structure:\n");
            printTree(root, 0);
            break;

        case 5:
            printf("Exiting program...\n");
            break;

        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    // Free the tree memory before exiting
    freeTree(root);

    return 0;
}