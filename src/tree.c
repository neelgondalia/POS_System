/**
 * @file tree.c
 * @author Neel Gondalia (ngondali@mail.uoguelph.ca)
 * @date July 2017
 * @brief File containing the functions of the tree
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

Tree *createBalancedBinTree(int (*compareFP) (void *data1, void *data2), void (*destroyFP) (void *toBeDeleted),void *(*copyFP)(void *toBeCopy))
{
    Tree *t = malloc (sizeof(Tree));
    t->root = NULL;
    t->compareFP = compareFP;
    t->destroyFP = destroyFP;
    t->copyFP = copyFP;
    return t;
}

TreeNode *createBalancedBinNode(void *data)
{
    TreeNode *new = malloc (sizeof(TreeNode));
    new->left = NULL;
    new->right = NULL;
    new->data = data;
    new->height = 1;
    return new;
}

void destroyBalancedBinTree(Tree *toBeDeleted)
{
    if (toBeDeleted != NULL)
    {
        if (toBeDeleted->root != NULL)
        {
            deleteEntireTree (toBeDeleted->root, toBeDeleted->destroyFP);
        }
        free (toBeDeleted);
    }
    return;
}

void treeInsertNode(Tree *theTree, void *toBeInserted)
{
    if (theTree != NULL && toBeInserted != NULL)
    {
        theTree->root = insert (theTree->root, toBeInserted, theTree->compareFP);
    }
    return;   
}

void treeDeleteNode(Tree *theTree, void *toBeDeleted)
{
    if (theTree != NULL && theTree->root != NULL && toBeDeleted != NULL)
    {
        theTree->root = delete (theTree->root, toBeDeleted, theTree->compareFP, theTree->destroyFP, theTree->copyFP);
    }
    return;
}

void *treeFindNode(Tree *theTree, void *data)
{
    if (theTree != NULL && theTree->root != NULL && data != NULL)
    {
        TreeNode *checking = theTree->root;

        while (checking != NULL)
        {
            if ((theTree->compareFP(data, checking->data)) < 0)
            {
                checking = checking->left;
            }
            else if ((theTree->compareFP(data, checking->data)) > 0)
            {
                checking = checking->right;
            }
            else
            {
                return checking->data;
            }
        }
    }
    return NULL;
}

int treeIsEmpty(Tree *theTree)
{
    if (theTree != NULL)
    {
        if (theTree->root == NULL)
        {
            return 1;
        }
    }
    return 0;
}

int treeHasTwoChildren(TreeNode *root)
{
    if (root != NULL)
    {
        if (root->left != NULL && root->right != NULL)
        {
            return 0;
        }
    }
    return 1;
}

void *treeFindMin(Tree *theTree)
{
    if (theTree != NULL && theTree->root != NULL)
    {
        TreeNode *prev = theTree->root;
        TreeNode *temp = prev->left;

        while (temp != NULL)
        {
            prev = temp;
            temp = temp->left;
        }

        return prev->data;
    }
    return NULL;
}

void *treeFindMax(Tree *theTree)
{
    if (theTree != NULL && theTree->root != NULL)
    {
        TreeNode *prev = theTree->root;
        TreeNode *temp = prev->right;

        while (temp != NULL)
        {
            prev = temp;
            temp = temp->right;
        }

        return prev->data;
    }
    return NULL;
}

void treeInOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
    if (theTree != NULL && theTree->root != NULL && printNodeFP != NULL)
    {
        traversal (1, theTree->root, printNodeFP);
    }
    return;
}

void treePreOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
    if (theTree != NULL && printNodeFP != NULL)
    {
        traversal (2, theTree->root, printNodeFP);
    }
    return;
}

void treePostOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
    if (theTree != NULL && printNodeFP != NULL)
    {
        traversal (3, theTree->root, printNodeFP);
    }
    return;
}

void traversal (int i, TreeNode *root, void (*printNodeFP) (void *data))
{
    //inorder
    if (i == 1)
    {
        if (root == NULL)
        {
            return;
        }

        traversal (1, root->left, printNodeFP);
        printNodeFP (root->data);
        traversal (1, root->right, printNodeFP);
    }
    //preorder
    else if (i == 2)
    {
        if (root == NULL)
        {
            return;
        }

        printNodeFP (root->data);
        traversal (2, root->left, printNodeFP);
        traversal (2, root->right, printNodeFP);

    }
    //postorder
    else if (i == 3)
    {
        if (root == NULL)
        {
            return;
        }

        traversal (3, root->left, printNodeFP);
        traversal (3, root->right, printNodeFP);
        printNodeFP (root->data);
    }
}

TreeNode *insert (TreeNode *root, void *data, int (*compareFP) (void *data1, void *data2))
{
    //recursion to find where to insert the node
    if (root == NULL)
    {
        return createBalancedBinNode (data);
    }
    if ((compareFP(data, root->data)) < 0)
    {
        root->left = insert (root->left, data, compareFP);
    }
    else if ((compareFP(data, root->data)) > 0)
    {
        root->right = insert (root->right, data, compareFP);
    }
    else if ((compareFP(data, root->data)) == 0)
    {
        return root;
    }

    //height update
    root->height = (getMax (height(root->left), height (root->right))) + 1;

    //self balance
    int b = balance (root);
    
    if (b > 1 && (compareFP (data, root->left->data)) < 0)
    {
        return rightRotation (root);
    }
    if (b < -1 && (compareFP (data, root->right->data)) > 0)
    {
        return leftRotation (root);
    }
    if (b > 1 && (compareFP (data, root->left->data)) > 0)
    {
        root->left = leftRotation (root->left);
        return rightRotation (root);
    }
    if (b < -1 && (compareFP (data, root->right->data)) < 0)
    {
        root->right = rightRotation (root->right);
        return leftRotation (root);
    }
    return root;
}

TreeNode *delete (TreeNode *root, void *data, int (*compareFP) (void *data1, void *data2),  void (*destroyFP) (void *toBeDeleted), void *(*copyFP)(void *toBeCopy))
{
    if (root == NULL)
    {
        return NULL;
    }

    if ((compareFP(data, root->data)) < 0)
    {
        root->left = delete (root->left, data, compareFP, destroyFP, copyFP);
    }
    else if ((compareFP(data, root->data)) > 0)
    {
        root->right = delete (root->right, data, compareFP, destroyFP, copyFP);
    }
    else
    {
        //node to be deleted has no child
        if (root->left == NULL && root->right == NULL)
        {
            destroyFP (root->data);
            free (root);
            return NULL;
        }
        //if node to be deleted has one child
        else if (root->right == NULL)
        {
            TreeNode *temp = root;
            root = root->left;
            destroyFP (temp->data);
            free (temp);
            return root;
        }
        else if (root->left == NULL)
        {
            TreeNode *temp = root;
            root = root->right;
            destroyFP (temp->data);
            free (temp);
            return root;
        }
        //if node to be deleted has two children, copies min of right side of the node to the node and recursively calls delete of right side of node so that leaf is to be deleted while maintaining bst properties
        else if ((treeHasTwoChildren (root)) == 0)
        {
            TreeNode *prev = root->right; 
            TreeNode *curr = prev->left;
            
            while (curr != NULL)
            {
                 prev = curr;
                 curr = prev->left;
            }

            root->data = copyFP (prev->data);
            root->right = delete (root->right, prev->data, compareFP, destroyFP, copyFP);            
        }
    }

    if (root == NULL)
    {
        return NULL;
    }

    //update height of tree
    root->height = (getMax (height(root->left), height (root->right))) + 1;

    //self balance the tree
    int b = balance (root);

    if (b > 1 && (compareFP (data, root->left->data)) < 0)
    {
        return rightRotation (root);
    }
    if (b < -1 && (compareFP (data, root->right->data)) > 0)
    {
        return leftRotation (root);
    }
    if (b > 1 && (compareFP (data, root->left->data)) > 0)
    {
        root->left = leftRotation (root->left);
        return rightRotation (root);
    }
    if (b < -1 && (compareFP (data, root->right->data)) < 0)
    {
        root->right = rightRotation (root->right);
        return leftRotation (root);
    }
    return root;
}

TreeNode *leftRotation (TreeNode *node)
{
    if (node != NULL)
    {
        TreeNode *a = node->right;
        TreeNode *b = a->left;

        a->left = node;
        node->right = b;
        node->height = (getMax (height(node->left), height (node->right))) + 1;
        a->height = (getMax (height(a->left), height (a->right))) + 1;
        return a;
    }
    return NULL;
}

TreeNode *rightRotation (TreeNode *node)
{
    if (node != NULL)
    {
        TreeNode *a = node->left;
        TreeNode *b = a->right;

        a->right = node;
        node->left = b;
        node->height = (getMax (height(node->left), height (node->right))) + 1;
        a->height = (getMax (height(a->left), height (a->right))) + 1;
        return a;
    }
    return NULL;

}

void deleteEntireTree (TreeNode *root, void (*destroyFP) (void *toBeDeleted))
{
    if (root == NULL)
    {
        return;
    }

    deleteEntireTree (root->left, destroyFP);
    deleteEntireTree (root->right, destroyFP);

    destroyFP (root->data);
    free (root);
}

int height (TreeNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}

int getMax (int x, int y)
{
    if (y > x)
    {
        return y;
    }
    return x;
}

int balance (TreeNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return (height(node->left) - height(node->right));
}
