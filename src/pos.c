/**
 * @file pos.c
 * @author Neel Gondalia
 * @date August 2017
 * @brief File containing functions for point of sale system
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pos.h"

Data *parse (char *input)
{
    Data *enter = NULL;
    enter = malloc (sizeof (Data));
    char tok1[50]= "\0", tok2[50]= "\0", tok3[50]= "\0", tok4[50]= "\0", tok5[50]= "\0", tok6[50]= "\0", tok7[50] = "\0";
    int i = 0, j = 0;

    while (input[i] != ',')
    {
        tok1[i] = input[i];
        i++;
    }
    i++;    
    enter->id = malloc (sizeof (char) * strlen (tok1) + 1);
    strcpy (enter->id, tok1);

    while (input[i] != ',')
    {
        tok2[j] = input[i];
        i++;
        j++;
    }
    i++;
    j=0;
    enter->name = malloc (sizeof (char) * strlen (tok2) + 1);
    strcpy (enter->name, tok2);

    while (input[i] != ',')
    {
        tok3[j] = input[i];
        i++;
        j++;
    }
    i++;
    j=0;
    enter->publisher = malloc (sizeof (char) * strlen (tok3) + 1);
    strcpy (enter->publisher, tok3);

    while (input[i] != ',')
    {
        tok4[j] = input[i];
        i++;
        j++;
    }
    i++;
    j=0;
    enter->genre = malloc (sizeof (char) * strlen (tok4) + 1);
    strcpy (enter->genre, tok4);  

    while (input[i] != ',')
    {
        tok5[j] = input[i];
        i++;
        j++;
    }
    i++;
    j=0;
    enter->tax = atoi (tok5);

    while (!isdigit (input[i]))
    {
        i++;
    }
    
    while (input[i] != ',')
    {
        tok6[j] = input[i];
        i++;
        j++;
    }
    i++;
    j=0;
    enter->price = atof (tok6);

    while (input[i] != '\0')
    {
        tok7[j] = input[i];
        i++;
        j++;
    }
    enter->quantity = atoi (tok7);

    return enter;
}

void *copy (void *toBeCopy)
{
    Data *retrieved = (Data *) toBeCopy;

    Data *update = malloc (sizeof(Data));
    update->id = malloc (strlen (retrieved->id) + 1);
    strcpy (update->id, retrieved->id);
    update->name = malloc (strlen (retrieved->name) + 1);
    strcpy (update->name, retrieved->name);
    update->publisher = malloc (strlen (retrieved->publisher) + 1);
    strcpy (update->publisher, retrieved->publisher);
    update->genre = malloc (strlen (retrieved->genre) + 1);
    strcpy (update->genre, retrieved->genre);
    update->tax = retrieved->tax;
    update->price = retrieved->price;
    update->quantity = retrieved->quantity;
    
    return (void *)update;
}

int compareName (void *first, void *second)
{
    Data *a = (Data *) first;
    Data *b = (Data *) second;

    return strcmp(a->name, b->name);
}

int compareID (void *first, void *second)
{
    Data *a = (Data *) first;
    Data *b = (Data *) second;

    return strcmp(a->id, b->id);
}

void destroy (void *data)
{
    free (((Data *) data)->id);
    free (((Data *) data)->name);
    free (((Data *) data)->publisher);
    free (((Data *) data)->genre);
    free ((Data *) data);
    return;
}

void printDetailedStruct (void *toBePrinted)
{
    Data *a = (Data *) toBePrinted;
    printf ("\nID: %s    Name: %s    Publisher: %s    Genre: %s    Taxable: %d    Price: %0.2f    Quantity: %d\n", a->id, a->name, a->publisher, a->genre, a->tax, a->price, a->quantity);
}

void printInventory (void *toBePrinted)
{
    Data *a = (Data *) toBePrinted;
    printf ("\nName: %s ------------------------------ In Stock: %d", a->name, a->quantity);
}

void printInvoice (void *toBePrinted)
{
    Data *a = (Data *) toBePrinted;
    printf ("\nID: %s    Name: %s    Price: %0.2f    Taxable: %d    Quantity purchasing: %d", a->id, a->name, a->price, a->tax, a->quantity);
}

char *getInput()
{
   
   char *input;
   int get;
   size_t i;
   input = malloc(1);
   
   i = 0;
   
   while (((get = getchar()) != '\n') && (get != EOF))
   {
        input[i++] = get;
        char *temp = realloc (input, i + 1);

        if (temp == NULL)
           break;
        else
           input = temp;
   }
   
   input[i] = '\0';
   return input;
}

void addToInvoice (Data *retrieved, Tree *inventory, Tree *invoice)
{
    Data *check = (Data *) treeFindNode (invoice, (void *) retrieved);

    if (check != NULL)
    {
        printf ("\nThis item is already on the invoice...\n");
        return;
    }
    
    if (retrieved->quantity == 0)
    {
        printf ("\nSorry. Item Out of Stock\n");
        return;
    }

    printf ("\nHow many of %s would you like to purchase? ", retrieved->name);
    int quantity = atoi (getInput());

    if (quantity == 0)
        return;

    while (quantity > retrieved->quantity)
    {
        printf ("\nSorry. Only %d are in stock (including the quantity already placed on invoice). How many of %s would you like to purchase? ", retrieved->quantity, retrieved->name);
        quantity = atoi (getInput());

        if (quantity == 0)
            return;
    }
    
    Data *delete1 = makeCopy (retrieved);
    Data *delete2 = makeCopy (retrieved);
    Data *update1 = makeCopy (retrieved);
    Data *update2 = makeCopy (retrieved);
    
    
    treeDeleteNode (inventory, (void *) delete1);
    update1->quantity -= quantity; 
    treeInsertNode (inventory, (void *) update1);

    treeDeleteNode (invoice, (void *) delete2);
    update2->quantity = quantity;
    treeInsertNode (invoice, (void *) update2);
    printf ("\nItem added to invoice successfully...\n");
    return;
}

void editInvoice (Tree *inventory, Tree *invoice, Tree *invoice2)
{
    int menu = 5;

    while (menu != 4 && menu != 3 && menu != 2 && menu != 1)
    {
        printf ("\n**********************\n    SECONDARY MENU\n**********************\n\n1. ADD TO INVOICE (BY NAME)\n2. REMOVE FROM INVOICE (BY ID)\n3. CHANGE QUANTITIES OF ITEMS IN INVOICE (BY ID)\n4. GO BACK\n\nYour Choice (1, 2, 3, or 4): ");
        menu = atoi (getInput());

        if (menu == 4)
            return;

        else if (menu == 1)
        {
           printf ("\n************************************************************************************************\n");
            printf ("                                       CURRENT INVOICE                                    \n");
            printf ("************************************************************************************************");
            treeInOrderPrint (invoice, &printInvoice);
            treeInOrderPrint (invoice2, &printInvoice);
            printf ("\n************************************************************************************************\n");
            Data *search = malloc (sizeof(Data));
            printf ("\nEnter the name of the item you wish to add to invoice: ");
            search->name = getInput();

            Data *retrieved = (Data *) treeFindNode (inventory, (void *) search);
            if (retrieved == NULL)
            {
                printf ("\nItem not found in inventory.\n");
                free(search);
                return;
            }

            printDetailedStruct ((void *) retrieved);

            if (retrieved->tax == 1)
                addToInvoice (retrieved, inventory, invoice);
            else
                addToInvoice (retrieved, inventory, invoice2);

            free(search);
        }

        else if (menu == 2)
        {
            printf ("\n************************************************************************************************\n");
            printf ("                                       CURRENT INVOICE                                    \n");
            printf ("************************************************************************************************");
            treeInOrderPrint (invoice, &printInvoice);
            treeInOrderPrint (invoice2, &printInvoice);
            printf ("\n************************************************************************************************\n");
            Data *search = malloc (sizeof(Data));
            printf ("\nEnter the id of the item you wish to remove from invoice: ");
            search->id = getInput();

            int check = 0;
            Data *retrievedInvoice = (Data *) treeFindNode (invoice, (void *) search);

            if (retrievedInvoice == NULL)
            {
                check = 1;
                Data *retrievedInvoice = (Data *) treeFindNode (invoice2, (void *) search);

                if (retrievedInvoice == NULL)
                {
                    printf ("\nThe item you wish to delete is not in the invoice...\n");
                    return;
                }
            }
            
            Data *retrieved = (Data *) treeFindNode (inventory, (void *) retrievedInvoice);

            if (retrieved == NULL)
            {
                printf ("\nThe item you wish to delete is not in the inventory therefore it is no longer on sale. This item will be removed from the invoice...\n");
                return;
            }
            printDetailedStruct ((void *) retrievedInvoice);

            if (check == 0)
            {
                int toAdd = retrievedInvoice->quantity;
                Data *delete1 = makeCopy (retrieved);
                Data *delete2 = makeCopy (retrieved);
                Data *update1 = makeCopy (retrieved);

                treeDeleteNode (invoice, (void *) delete1);
                treeDeleteNode (inventory, (void *) delete2);
                update1->quantity += toAdd; 
                treeInsertNode (inventory, (void *) update1);
            }
            else if (check == 1)
            {
                int toAdd = retrievedInvoice->quantity;
                Data *delete1 = makeCopy (retrieved);
                Data *delete2 = makeCopy (retrieved);
                Data *update1 = makeCopy (retrieved);

                treeDeleteNode (invoice2, (void *) delete1);
                treeDeleteNode (inventory, (void *) delete2);
                update1->quantity += toAdd; 
                treeInsertNode (inventory, (void *) update1);
            }
            printf ("\n\nItem removed from invoice successfully...\n");
            free (search);
        }
        else if (menu == 3)
        {
            printf ("\n************************************************************************************************\n");
            printf ("                                       CURRENT INVOICE                                    \n");
            printf ("************************************************************************************************");
            treeInOrderPrint (invoice, &printInvoice);
            treeInOrderPrint (invoice2, &printInvoice);
            printf ("\n************************************************************************************************\n");
            Data *search = malloc (sizeof(Data));
            printf ("\nEnter the id of the item you wish to change the quanitity of on the invoice: ");
            search->id = getInput();

            Data *retrieved = (Data *) treeFindNode (invoice, (void *) search);
            if (retrieved == NULL)
            {
                printf ("\nThe item you wish to change the quantity for is not on the invoice.\n");
                return;
            }
            if (retrieved->tax == 1)
                changeQuantity (search, inventory, invoice);
            else
                changeQuantity (search, inventory, invoice2);

            free (search);
            
        }
        else
            printf ("\nInvalid Menu Choice...\n");
    }
    return;
}

void changeQuantity (Data *search, Tree *inventory, Tree *invoice)
{
    Data *retrieved = (Data *) treeFindNode (invoice, (void *) search);

    if (retrieved == NULL)
    {
        printf ("\nThe item you wish to change the quantity for is not on the invoice.\n");
        return;
    }

    Data *retrievedInventory = (Data *) treeFindNode (inventory, (void *) retrieved);
    
    if (retrievedInventory == NULL)
    {
        printf ("\nThe item is no longer on the inventory, therefore it is no longer on sale. This item will be removed from the invoice.\n");
        treeDeleteNode (invoice, (void *) search);
        return;
    }

    int total = retrieved->quantity + retrievedInventory->quantity;

    Data *delete1 = makeCopy (retrievedInventory);
    Data *delete2 = makeCopy (retrievedInventory);
    Data *update1 = makeCopy (retrievedInventory);
    Data *update2 = makeCopy (retrievedInventory);

    printDetailedStruct ((void *) retrieved);
    
    printf ("\nEnter the quantity of the item you would like to purchase: ");
    int quantity = atoi(getInput());

    if (quantity == 0)
    {
        treeDeleteNode (invoice, (void *) delete1);
        treeDeleteNode (inventory, (void *) delete2);
        update1->quantity = total;
        treeInsertNode (inventory, (void *) update1);
        free (update2);
        return;
    }

    if (quantity > total)
    {
        printf ("\nSorry. Only %d are in stock (including the quantity already placed on invoice). How many of %s would you like to purchase?", total, retrievedInventory->name);
        quantity = atoi (getInput());

        if (quantity == 0)
        {
            treeDeleteNode (invoice, (void *) delete1);
            treeDeleteNode (inventory, (void *) delete2);
            update1->quantity = total;
            treeInsertNode (inventory, (void *) update1);
            free (update2);
            return;
        }
    }
    treeDeleteNode (invoice, (void *) delete1);
    treeDeleteNode (inventory, (void *) delete2);
    update1->quantity = total-quantity;
    treeInsertNode (inventory, (void *) update1);
    update2->quantity = quantity;
    treeInsertNode (invoice, (void *) update2);
    printf ("\nItem quantity changed successfully...\n");
    return;
}

Data *makeCopy (Data *retrieved)
{
    Data *update = malloc (sizeof(Data));
    update->id = malloc (strlen (retrieved->id) + 1);
    strcpy (update->id, retrieved->id);
    update->name = malloc (strlen (retrieved->name) + 1);
    strcpy (update->name, retrieved->name);
    update->publisher = malloc (strlen (retrieved->publisher) + 1);
    strcpy (update->publisher, retrieved->publisher);
    update->genre = malloc (strlen (retrieved->genre) + 1);
    strcpy (update->genre, retrieved->genre);
    update->tax = retrieved->tax;
    update->price = retrieved->price;
    update->quantity = retrieved->quantity;

    return update;
}
