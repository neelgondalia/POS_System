/**
 * @file tree.h
 * @author Michael Ellis/ Neel Gondalia
 * @date July 2017
 * @brief File containing the structs and functions for a self balancing tree
 */

#ifndef STUDENT_TREE_API_
#define STUDENT_TREE_API_

/**typedef for struct name*/
typedef struct BalancedBinTreeNode TreeNode;

/**typedef for struct name*/
typedef struct BalancedBinTree Tree;

struct BalancedBinTree
{
    TreeNode *root; ///< pointer to generic data that is to be stored in the tree
    int (*compareFP) (void *data1, void *data2); ///< function pointer to a comparison function for the purpose of inserting and deleting elements
    void (*destroyFP) (void *data); ///< function pointer to a function to free a single pointer that is deleted from the tree
    void *(*copyFP)(void *toBeCopy); ///< function pointer to a function that copies pointer data
};



struct BalancedBinTreeNode{
    void *data; ///< pointer to generic data that is to be stored in the heap
    TreeNode *left; ///< pointer to left tree node of current node. Null if empty.
    TreeNode *right; ///< pointer to right tree node of current node. Null if empty.
    int height; ///< height of the node in the tree
};

/**This function returns a pointer to a binary tree.  You must send pointers to the compare and destroy functions when you create the tree.
 *@param compareFP function pointer to allow for comparison between two generic data types
 *@param destroyFP function pointer to allow for pointer deletion. 
 *@param copyFP function pointer to a function that copies pointer data to a new pointer.
 *@return If successful, returns a pointer to a binary tree. Returns null if the memory allocation fails.
 **/
Tree *createBalancedBinTree(int (*compareFP) (void *data1, void *data2), void (*destroyFP) (void *toBeDeleted),void *(*copyFP)(void *toBeCopy));

/**This function creates a tree node for a self-balancing binary tree.
 *@param data pointer to data that is to be added to a self-balancing binary tree.
 **/
TreeNode *createBalancedBinNode(void *data);

/**This function destroys a binary tree and all data that is in the tree
 *when destroy is called.
 *@param toBeDeleted pointer to binary tree created via createBalancedBinTree
 **/
void destroyBalancedBinTree(Tree *toBeDeleted);

/**Function to insert a node into a self-balancing binary tree.
 *@param theTree pointer to a self-balancing binary tree
 *@param toBeInserted pointer to generic data that is to be inserted into the self-balancing binary tree
 **/
void treeInsertNode(Tree *theTree, void *toBeInserted);

/**Function to delete a node from a self-balancing binary tree.
 *@param theTree pointer to a self-balancing binary tree
 *@param toBeDeleted pointer to generic data that is to be deleted from the self-balancing binary tree
 **/
void treeDeleteNode(Tree *theTree, void *toBeDeleted);

/**Function to determine if a binary tree is empty.
 *@param theTree pointer to a self-balancing binary tree
 *@return If tree is empty, return 1. Otherwise, return 0.
 **/
int treeIsEmpty(Tree *theTree);

/**Function to determine if a binary tree node has two children.
 *@param root pointer to a self-balancing binary tree's root
 *@return If tree is empty, or does not exist, return 1. Otherwise, return 0.
 **/
int treeHasTwoChildren(TreeNode *root);

/**Function to return a given value in the tree, dependant on the compare function pointer parameters.
 *Compares nodes, until compare function returns zero, or the tree is exhausted.
 *@param theTree pointer to a self-balancing binary tree's root
 *@return pointer to the data found. If tree is empty or data is not found, return NULL.
 **/
void *treeFindNode(Tree *theTree, void *data);

/**Function to return the smallest value of a tree, dependant on the compare function pointer parameters.
 *@param theTree pointer to a self-balancing binary tree's root
 *@return pointer to the min found. If tree is empty, return NULL.
 **/
void *treeFindMin(Tree *theTree);

/**Function to return the largest value of a tree, dependant on the compare function pointer parameters.
 *@param theTree pointer to a self-balancing binary tree's root
 *@return pointer to the maximum value  found. If tree is empty, return NULL.
 **/
void *treeFindMax(Tree *theTree);

/**function to print a tree in-order. EG 
 *              A
 *            /    \
 *          B       C
 *         / \     / \
 *        D   F   G   E
 *would print nodes thusly: D->B->F->A->G->C->E
 *@param theTree pointer to a self-balancing binary tree
 *@param printNodeFP pointer to a function to print void pointer data.
 **/
void treeInOrderPrint(Tree *theTree, void (*printNodeFP) (void *data));

/**Function to print a tree pre-order. EG 
 *              A
 *            /   \
 *          B       C
 *         / \     / \
 *        D   F   G   E
 *would print nodes thusly: A->B->D->F->C->G->E
 *@param theTree pointer to a self-balancing binary tree
 *@param printNodeFP pointer to a function to print void pointer data.
 **/
void treePreOrderPrint(Tree *theTree, void (*printNodeFP) (void *data));

/**Function to print a tree in post-order. EG 
 *              A
 *            /   \
 *          B       C
 *         / \     / \
 *        D   F   G   E
 *would print nodes thusly: D->F->B->G->C->E->A
 *@param theTree pointer to a self-balancing binary tree's root
 *@param printNodeFP pointer to a function to print void pointer data.
 **/
void treePostOrderPrint(Tree *theTree, void (*printNodeFP) (void *data));

/**This function prints the tree according to the orders (pre, post or in)
 *@param i integer that represents what order the function should print in
 *@param root node pointer to the root of the tree or subtree
 *@param printNodeFP function pointer to the function that prints the data in a node
 **/
void traversal (int i, TreeNode *root, void (*printNodeFP) (void *data));

/**This function is the helper function to insert a node
 * @param root node pointer to the root of tree or subtree
 * @param data void pointer to the data to be inserted
 * @param compareFP function pointer to the compare function that compares keys
 * @return node pointer to the root of the tree 
 **/
TreeNode *insert (TreeNode *root, void *data, int (*compareFP) (void *data1, void *data2));

/**This function is the helper function to delete a node
 * @param root node pointer to the root of tree or subtree
 * @param data void pointer to the data to be deleted
 * @param compareFP function pointer to the compare function that compares keys
 * @param destroyFP function pointer to the function that deletes the data in a node
 * @param copyFP function pointer to the function that copies data
 * @return node pointer to the root of the tree 
 **/
TreeNode *delete (TreeNode *root, void *data, int (*compareFP) (void *data1, void *data2),  void (*destroyFP) (void *toBeDeleted), void *(*copyFP)(void *toBeCopy));

/**This function performs a right rotation
 *@param root node pointer to the root of the tree or subtree
 *@return node pointer to the root of the tree or subtree
 **/
TreeNode *rightRotation (TreeNode *node);

/**This function performs a left rotation
 *@param root node pointer to the root of the tree or subtree
 *@return node pointer to the root of the tree or subtree
 **/
TreeNode *leftRotation (TreeNode *node);

/**This function is a helper function to delete the entire bst
 *@param root node pointer to the root of the tree or subtree
 *@param destroyFP function pointer to the function that deletes the data in a node
 **/
void deleteEntireTree (TreeNode *root, void (*destroyFP) (void *toBeDeleted));

/**This function returns the height of the node
 * @param node pointer to the node whose height needs to be found
 * @return integer that represents the height of the node
 **/
int height (TreeNode *node);

/**This function finds the maximum height between two child nodes of a root node
 * @param x integer that represents the height of the first child
 * @param y integer that represents the height of the second child
 * @return maximum height between two nodes
 **/
int getMax (int x, int y);

/**This function returns the balance of the node
 * @param node pointer to the node whose balance needs to be found
 * @return integer that represents the balance of the node
 **/
int balance (TreeNode *node);

#endif
