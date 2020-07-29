/**
 * @file pos.h
 * @author Neel Gondalia
 * @date August 2017
 * @brief File containing the function definitions of extra functions required for point of sale system
 */

#include "tree.h"
#ifndef _POS_API_
#define _POS_API_

typedef struct Data
{
    char *id;    ///<char pointer to the id of the game
    char *name;    ///<char pointer to the name of the game
    char *publisher;    ///<char pointer to the publisher of the game
    char *genre;    ///<char pointer to the genre of the game
    int tax;    ///<integer that represents if the game is taxable or not
    float price;    ///< price of the game
    int quantity;   ///< quantity in stock
}Data;

/**Function to copy data
 * @param toBeCopy void pointer to the data that needs to be copied
 * @return void pointer to the data that the tobeCopy data was copied to
 **/
void *copy (void *toBeCopy);

/** Function to compare two pieces of data and return an appropriate integer. Compares names of games.
 *@param first void pointer type that represents the first piece of data to be compared with the second piece of data
 *@param second void pointer type that represents the second piece of data to be compared with the first piece of data
**/
int compareName (void *first, void *second);

/** Function to compare two pieces of data and return an appropriate integer. Compares ids of games.
 *@param first void pointer type that represents the first piece of data to be compared with the second piece of data
 *@param second void pointer type that represents the second piece of data to be compared with the first piece of data
**/
int compareID (void *first, void *second);

/** Function to delete data from tree node
 *@pre data must exist
 *@param data of void pointer type that is the data to be removed from the tree node
**/
void destroy (void *data);

/** Function to print data. Used to print detailed info for games.
 *@pre toBePrinted must exist
 *@param toBePrinted of void pointer type that is the data to be printed
**/
void printDetailedStruct (void *toBePrinted);

/** Function to print data. Used to print inventory of games.
 *@pre toBePrinted must exist
 *@param toBePrinted of void pointer type that is the data to be printed
**/
void printInventory (void *toBePrinted);

/** Function to print data. Used to print customer invoice.
 *@pre toBePrinted must exist
 *@param toBePrinted of void pointer type that is the data to be printed
**/
void printInvoice (void *toBePrinted);

/**Function to load a line of data to struct
 * @param input char pointer to the line that is to be loaded to struct
 * @return pointer to struct data that is loaded
 **/
Data *parse (char *input);

/**function to get input from user
 * @return char pointer to the input from user
 **/
char *getInput();

/**Function to make a copy of the struct
 * @pre retrieved must exist and have memory allocated to it and has data stored
 * @param retrieved pointer to struct that is to be copied 
 * @return pointer to the copy version of the retrieved struct
 **/
Data *makeCopy (Data *retrieved);

/**Function to add an item to the customer invoice
 * @param retrieved pointer to the data struct that is to be added to the invoice
 * @param inventory pointer to tree that has the inventory stored
 * @param invoice pointer to the tree that has the current invoice stored
 **/
void addToInvoice (Data *retrieved, Tree *inventory, Tree *invoice);

/**Function to edit the customer invoice
 * @param inventory pointer to tree that has the inventory stored
 * @param invoice pointer to the tree that has the taxable invoice stored
 * @param invoice2 pointer to the tree that has the non-taxable invoice stored
 **/
void editInvoice (Tree *inventory, Tree *invoice, Tree *invoice2);

/**Function to change the quantity to be bought of an item on the customer invoice
 * @param searcg pointer to the data struct that is to be changed
 * @param inventory pointer to tree that has the inventory stored
 * @param invoice pointer to the tree that has the current invoice stored
 **/
void changeQuantity (Data *search, Tree *inventory, Tree *invoice);


#endif

