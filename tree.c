#include <stdio.h>
#include <stdlib.h>

// build binary tree dynamically with users inputs
struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node *createNode(int data)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct node *insertNode(struct node *root, int data)
{
    if (root == NULL)
    {
        root = createNode(data);
    }
    else if (data <= root->data)
    {
        root->left = insertNode(root->left, data);
    }
    else
    {
        root->right = insertNode(root->right, data);
    }
    return root;
}

// print binary tree in pre-order
void preOrder(struct node *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}

// search for a node in binary tree
int search(struct node *root, int data)
{
    if (root == NULL)
    {
        return 0;
    }
    else if (root->data == data)
    {
        return 1;
    }
    else if (data <= root->data)
    {
        return search(root->left, data);
    }
    else
    {
        return search(root->right, data);
    }
}

// sum of all nodes in binary tree
int sum(struct node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        return root->data + sum(root->left) + sum(root->right);
    }
}

// read input from user and build binary tree
int main()
{
    struct node *root = NULL;
    int data;

    while (1)
    {
        printf("Enter a number: ");
        scanf("%d", &data);
        if (data == -1)
        {
            break;
        }
        root = insertNode(root, data);
    }

    preOrder(root);
    printf(search(root, 5) ? "Found node 5 \n" : "Not Found \n");
    printf(search(root, 1) ? "Found node 1 \n" : "Not Found \n");
    printf(search(root, 100) ? "Found node 100 \n" : "Not Found \n");

    printf("Sum of all nodes in binary tree is %d", sum(root));
    return 0;
}
