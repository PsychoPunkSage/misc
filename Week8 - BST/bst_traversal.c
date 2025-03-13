#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure for Binary Search Tree node
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

// Structure for queue (for level order traversal)
struct QueueNode
{
    struct Node *data;
    struct QueueNode *next;
};

// Structure for queue
struct Queue
{
    struct QueueNode *front;
    struct QueueNode *rear;
};

// Structure for stack (for iterative traversals)
struct StackNode
{
    struct Node *data;
    struct StackNode *next;
};

// Structure for stack
struct Stack
{
    struct StackNode *top;
};

// Function to create a new BST node
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
    if (root == NULL)
    {
        return createNode(value);
    }

    if (value < root->data)
    {
        root->left = insert(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = insert(root->right, value);
    }

    return root;
}

// Create a new queue
struct Queue *createQueue()
{
    struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Check if queue is empty
bool isQueueEmpty(struct Queue *queue)
{
    return queue->front == NULL;
}

// Add an element to the queue
void enqueue(struct Queue *queue, struct Node *node)
{
    struct QueueNode *newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    newNode->data = node;
    newNode->next = NULL;

    if (isQueueEmpty(queue))
    {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else
    {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Remove an element from the queue
struct Node *dequeue(struct Queue *queue)
{
    if (isQueueEmpty(queue))
    {
        return NULL;
    }

    struct QueueNode *temp = queue->front;
    struct Node *node = temp->data;

    queue->front = queue->front->next;

    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }

    free(temp);
    return node;
}

// Create a new stack
struct Stack *createStack()
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

// Check if stack is empty
bool isStackEmpty(struct Stack *stack)
{
    return stack->top == NULL;
}

// Push an element onto the stack
void push(struct Stack *stack, struct Node *node)
{
    struct StackNode *newNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    newNode->data = node;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Pop an element from the stack
struct Node *pop(struct Stack *stack)
{
    if (isStackEmpty(stack))
    {
        return NULL;
    }

    struct StackNode *temp = stack->top;
    struct Node *node = temp->data;

    stack->top = stack->top->next;
    free(temp);

    return node;
}

// Function for recursive inorder traversal
void recursiveInorder(struct Node *root)
{
    if (root != NULL)
    {
        recursiveInorder(root->left);
        printf("%d ", root->data);
        recursiveInorder(root->right);
    }
}

// Function for recursive preorder traversal
void recursivePreorder(struct Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        recursivePreorder(root->left);
        recursivePreorder(root->right);
    }
}

// Function for recursive postorder traversal
void recursivePostorder(struct Node *root)
{
    if (root != NULL)
    {
        recursivePostorder(root->left);
        recursivePostorder(root->right);
        printf("%d ", root->data);
    }
}

// Function for iterative inorder traversal
void iterativeInorder(struct Node *root)
{
    if (root == NULL)
        return;

    struct Stack *stack = createStack();
    struct Node *current = root;

    while (current != NULL || !isStackEmpty(stack))
    {
        // Reach the leftmost node of the current node
        while (current != NULL)
        {
            push(stack, current);
            current = current->left;
        }

        // Current is NULL at this point
        current = pop(stack);
        printf("%d ", current->data);

        // We have visited the node and its left subtree.
        // Now, it's right subtree's turn
        current = current->right;
    }

    free(stack);
}

// Function for iterative preorder traversal
void iterativePreorder(struct Node *root)
{
    if (root == NULL)
        return;

    struct Stack *stack = createStack();
    push(stack, root);

    while (!isStackEmpty(stack))
    {
        struct Node *current = pop(stack);
        printf("%d ", current->data);

        // Push right child first, so that left is processed first
        if (current->right != NULL)
            push(stack, current->right);
        if (current->left != NULL)
            push(stack, current->left);
    }

    free(stack);
}

// Function for iterative postorder traversal using two stacks
void iterativePostorder(struct Node *root)
{
    if (root == NULL)
        return;

    struct Stack *stack1 = createStack();
    struct Stack *stack2 = createStack();

    push(stack1, root);

    // Fill stack2 in stack1's order but with right child first
    while (!isStackEmpty(stack1))
    {
        struct Node *current = pop(stack1);
        push(stack2, current);

        if (current->left != NULL)
            push(stack1, current->left);
        if (current->right != NULL)
            push(stack1, current->right);
    }

    // Pop from stack2 to get postorder traversal
    while (!isStackEmpty(stack2))
    {
        struct Node *current = pop(stack2);
        printf("%d ", current->data);
    }

    free(stack1);
    free(stack2);
}

// Function for level order traversal (breadth-first)
void levelOrder(struct Node *root)
{
    if (root == NULL)
        return;

    struct Queue *queue = createQueue();
    enqueue(queue, root);

    while (!isQueueEmpty(queue))
    {
        struct Node *current = dequeue(queue);
        printf("%d ", current->data);

        if (current->left != NULL)
            enqueue(queue, current->left);
        if (current->right != NULL)
            enqueue(queue, current->right);
    }

    free(queue);
}

// Function for level order traversal with level printing
void levelOrderWithLevels(struct Node *root)
{
    if (root == NULL)
        return;

    struct Queue *queue = createQueue();
    enqueue(queue, root);

    int level = 0;

    while (!isQueueEmpty(queue))
    {
        int nodeCount = 0; // Count of nodes at current level
        int levelSize = 0; // Number of nodes at current level

        // Get the size of current level
        struct QueueNode *temp = queue->front;
        while (temp != NULL)
        {
            levelSize++;
            temp = temp->next;
        }

        printf("Level %d: ", level);

        // Process all nodes of current level
        while (nodeCount < levelSize)
        {
            struct Node *current = dequeue(queue);
            printf("%d ", current->data);

            if (current->left != NULL)
                enqueue(queue, current->left);
            if (current->right != NULL)
                enqueue(queue, current->right);

            nodeCount++;
        }

        printf("\n");
        level++;
    }

    free(queue);
}

// Function to count the number of nodes in a tree
int countNodes(struct Node *root)
{
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Function to count leaf nodes (nodes with no children)
int countLeafNodes(struct Node *root)
{
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

// Function to free BST memory
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
        printf("\n\n--- BST Traversal Techniques ---\n");
        printf("1. Insert a value\n");
        printf("2. Recursive Inorder Traversal\n");
        printf("3. Recursive Preorder Traversal\n");
        printf("4. Recursive Postorder Traversal\n");
        printf("5. Iterative Inorder Traversal\n");
        printf("6. Iterative Preorder Traversal\n");
        printf("7. Iterative Postorder Traversal\n");
        printf("8. Level Order Traversal\n");
        printf("9. Level Order Traversal with Levels\n");
        printf("10. Count Nodes\n");
        printf("11. Count Leaf Nodes\n");
        printf("12. Exit\n");
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
            printf("Recursive Inorder Traversal: ");
            recursiveInorder(root);
            printf("\n");
            break;

        case 3:
            printf("Recursive Preorder Traversal: ");
            recursivePreorder(root);
            printf("\n");
            break;

        case 4:
            printf("Recursive Postorder Traversal: ");
            recursivePostorder(root);
            printf("\n");
            break;

        case 5:
            printf("Iterative Inorder Traversal: ");
            iterativeInorder(root);
            printf("\n");
            break;

        case 6:
            printf("Iterative Preorder Traversal: ");
            iterativePreorder(root);
            printf("\n");
            break;

        case 7:
            printf("Iterative Postorder Traversal: ");
            iterativePostorder(root);
            printf("\n");
            break;

        case 8:
            printf("Level Order Traversal: ");
            levelOrder(root);
            printf("\n");
            break;

        case 9:
            printf("Level Order Traversal with Levels:\n");
            levelOrderWithLevels(root);
            break;

        case 10:
            printf("Total number of nodes: %d\n", countNodes(root));
            break;

        case 11:
            printf("Number of leaf nodes: %d\n", countLeafNodes(root));
            break;

        case 12:
            printf("Exiting program...\n");
            break;

        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 12);

    // Free the BST memory before exiting
    freeBST(root);

    return 0;
}