#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

struct node
{
    int key;
    struct node *left, *right;
};

struct node *newNode(int item)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

void inOrder(struct node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%d \n", root->key);
        inOrder(root->right);
    }
}

void preOrder(struct node *root)
{
    if (root == NULL)
        return;

    printf("%d \n", root->key);
    preOrder(root->left);
    preOrder(root->right);
}

struct node *insert(struct node *node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return newNode(key);
    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    /* return the (unchanged) node pointer */
    return node;
}

struct node *minValueNode(struct node *node)
{
    struct node *current = node;
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

void postOrder(struct node *root)
{
    if (root == NULL)
        return;

    postOrder(root->left);

    postOrder(root->right);

    printf("%d \n", root->key);
}

struct node *ancestro(struct node *root, int n1, int n2)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (root->key > n1 && root->key > n2)
    {
        return ancestro(root->left, n1, n2);
    }

    if (root->key < n1 && root->key < n2)
    {
        return ancestro(root->right, n1, n2);
    }

    return root;
}
int distFromAncestor(struct node *root, int k, int cont)
	{
	    if(root->key == k)
            return cont;
        if(root->key > k)
            cont =distFromAncestor(root->left,k,cont+1);
        if(root->key < k)
            cont =distFromAncestor(root->right,k,cont+1);
        return cont;
	}
	
int distancia(struct node *root,int a, int b){
    return distFromAncestor(root,a,0) + distFromAncestor(root,b,0);
}



struct node *deleteNode(struct node *root, int key)
{
    // base case
    if (root == NULL)
        return root;
    // If the key to be deleted is smaller than the root's key,// then it lies in left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    // If the key to be deleted is greater than the root's key,// then it lies in right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key); // if key is same as root's key, then This is the node// to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        // node with two children: Get the inorder successor (smallest// in the right subtree)
        struct node *temp = minValueNode(root->right);
        // Copy the inorder successor's content to this node
        root->key = temp->key; // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

int main()
{
    /* Let us create following BST50/ \30 70/ \ / \20 40 60 80 */
    struct node *root = NULL;
    root = insert(root, 8);
    root = insert(root, 3);
    root = insert(root, 10);
    root = insert(root, 1);
    root = insert(root, 6);
    root = insert(root, 14);
    root = insert(root, 4);
    root = insert(root, 7);
    root = insert(root, 13);
    printf("Inorder traversal of the given tree \n");
    //inOrder(root);
    //Ejercicio 1
    cout<<ancestro(root,1,13) ->key;

    //Ejercicio 2
    cout<<distancia(ancestro(root,1,7),1,7);
    return 0;
}
