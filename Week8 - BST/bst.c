#include <stdio.h>
#include <stdlib.h>

// Structure for BST node
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node *createNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a value into BST
struct Node *insert(struct Node *root, int value)
{
    // If tree is empty, create a new node and return
    if (root == NULL)
    {
        return createNode(value);
    }

    // Otherwise, recur down the tree
    if (value < root->data)
    {
        root->left = insert(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = insert(root->right, value);
    }

    // Return the unchanged node pointer
    return root;
}

// Function to find the minimum value node in a BST
struct Node *findMinNode(struct Node *node)
{
    struct Node *current = node;

    // Loop to find the leftmost leaf
    while (current && current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

// Function to delete a node with given value
struct Node *deleteNode(struct Node *root, int value)
{
    // Base case: If tree is empty
    if (root == NULL)
    {
        return root;
    }

    // Recursive calls for ancestors of node to be deleted
    if (value < root->data)
    {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = deleteNode(root->right, value);
    }
    else
    {
        // Case 1: Node with only one child or no child
        if (root->left == NULL)
        {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        // Case 2: Node with two children
        // Get the inorder successor (smallest in the right subtree)
        struct Node *temp = findMinNode(root->right);

        // Copy the inorder successor's content to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to search for a value in BST
struct Node *search(struct Node *root, int value)
{
    // Base cases: root is null or value is present at root
    if (root == NULL || root->data == value)
    {
        return root;
    }

    // Value is greater than root's data
    if (root->data < value)
    {
        return search(root->right, value);
    }

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

// Function for preorder traversal
void preorderTraversal(struct Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Function for postorder traversal
void postorderTraversal(struct Node *root)
{
    if (root != NULL)
    {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// Function to find height of the tree
int height(struct Node *root)
{
    if (root == NULL)
    {
        return -1;
    }
    else
    {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        if (leftHeight > rightHeight)
        {
            return leftHeight + 1;
        }
        else
        {
            return rightHeight + 1;
        }
    }
}

// Function to count nodes in the tree
int countNodes(struct Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
}

// Function to free the memory of BST
void freeBST(struct Node *root)
{
    if (root != NULL)
    {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}

int main()
{
    struct Node *root = NULL;
    int choice, value;

    do
    {
        printf("\n\n--- Binary Search Tree Operations ---\n");
        printf("1. Insert a value\n");
        printf("2. Delete a value\n");
        printf("3. Search for a value\n");
        printf("4. Inorder Traversal\n");
        printf("5. Preorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. Find height of the tree\n");
        printf("8. Count nodes in the tree\n");
        printf("9. Exit\n");
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
            printf("Preorder Traversal: ");
            preorderTraversal(root);
            printf("\n");
            break;

        case 6:
            printf("Postorder Traversal: ");
            postorderTraversal(root);
            printf("\n");
            break;

        case 7:
            printf("Height of the tree: %d\n", height(root));
            break;

        case 8:
            printf("Number of nodes in the tree: %d\n", countNodes(root));
            break;

        case 9:
            printf("Exiting program...\n");
            break;

        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 9);

    // Free the BST memory before exiting
    freeBST(root);

    return 0;
}