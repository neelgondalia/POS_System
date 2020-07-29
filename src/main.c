/**
 * @file main.c
 * @author Neel Gondalia
 * @date August 2017
 * @brief File that calls the appropriate functions to process point of sale system 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pos.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf ("\nInvalid amount of arguments... The terminal command to run this program is: bin/main assets/'filename'\n\n");
        return 0;
    }
    char input[1][300];
    FILE *fptr = fopen (argv[1], "a+");
    Tree *inventory = createBalancedBinTree (&compareName, &destroy, &copy);
    Tree *invoice = createBalancedBinTree (&compareID, &destroy, &copy);
    Tree *invoice2 = createBalancedBinTree (&compareID, &destroy, &copy);
    
    while (fgets (input[0], 300, fptr))
    {
        if (input[0][0] != '\n' && input[0][0] != ',')
        {
            if (input[0][strlen(input[0]) - 1] == '\n')
                input[0][strlen(input[0]) - 1] = '\0';

            Data *temp = NULL;
            temp = parse (input[0]);
            treeInsertNode (inventory, (void *) temp);
        }
        strcpy (input[0], "\0");
    }
    fclose (fptr);

    printf ("\n###########################################################################\n");
    printf ("                   POINT OF SALE SYSTEM FOR SOCS GAME STORE                \n");
    printf ("###########################################################################\n");

    int menu = 8;
    while (menu != 7)
    {
        printf ("\n**********************\n      MAIN MENU\n**********************\n\n1. EDIT CURRENT CUSTOMER INVOICE\n2. REMOVE AN ITEM FROM INVENTORY\n3. VIEW INVENTORY\n4. VIEW INVOICE\n5. CLEAR SCREEN\n6. PRINT REPORTS AND START A NEW SALE\n7. EXIT PROGRAM\n\nYour Choice (1, 2, 3, 4, 5, or 6): ");
        menu = atoi(getInput ());

        if (menu == 7)
        {
            destroyBalancedBinTree (invoice);
            destroyBalancedBinTree (invoice2);
            destroyBalancedBinTree (inventory);
            printf ("\nEXITING...\n");
            continue;
        }
        else if (menu == 6)
        {
            printf ("\033[2J\033[1;1H");
            printf ("\n####################################################################################################################\n");
            printf ("                                               SOCS GAME STORE: REPORTS                         \n");
            printf ("####################################################################################################################\n");

            printf ("\n************************************************************************************************\n");
            printf ("                                       INVENTORY REPORT                                  \n");
            printf ("************************************************************************************************");
            treeInOrderPrint (inventory, &printInventory);
            printf ("\n************************************************************************************************\n");

            printf ("\n\n************************************************************************************************\n");
            printf ("                                      INVOICE: TAXABLE REPORT                                    \n");
            printf ("************************************************************************************************");
            treeInOrderPrint (invoice, &printInvoice);
            printf ("\n************************************************************************************************\n");

            printf ("\n\n************************************************************************************************\n");
            printf ("                                      INVOICE: NON-TAXABLE REPORT                                    \n");
            printf ("************************************************************************************************");
            treeInOrderPrint (invoice2, &printInvoice);
            printf ("\n************************************************************************************************\n");

            printf ("\nReports Printed...\n");
            char *option = "WXYSA";

            while (strcmp (option, "N") != 0 && strcmp (option, "X") != 0 && strcmp (option, "C") != 0)
            {  
                printf ("\nIf you wish to continue to with the current sale, enter 'C'. If you wish to start a new sale, enter 'N'. If you wish to exit the program, enter 'X'.\n\nYour Choice: ");
                option =  getInput ();

                if (strcmp(option, "N") == 0)
                {
                    destroyBalancedBinTree (invoice);
                    destroyBalancedBinTree (invoice2);
                    invoice = createBalancedBinTree (&compareID, &destroy, &copy);
                    invoice2 = createBalancedBinTree (&compareID, &destroy, &copy);
                    continue;
                }
                else if (strcmp(option, "X") == 0)
                {
                    destroyBalancedBinTree (invoice);
                    destroyBalancedBinTree (invoice2);
                    destroyBalancedBinTree (inventory);
                    printf ("\nEXITING...\n");
                    menu = 7;
                    continue;
                }
                else if (strcmp(option, "C") == 0)
                {
                    continue;
                }
                else
                {
                    printf ("\nInvalid choice. Try again...\n");
                }
            }
        }

        else if (menu == 2)
        {
            Data *search = malloc (sizeof(Data));
            printf ("\nEnter the name of the item you wish to remove from inventory: ");
            search->name = getInput();
            Data *retrieved = (Data *) treeFindNode (inventory, (void *) search);

            if (retrieved == NULL)
            {
                printf ("\nItem not found in inventory.\n");
                continue;
            }

            printDetailedStruct ((void *) retrieved);

            if (retrieved->tax == 1)
            {
                Data *delete1 = makeCopy (retrieved);
                treeDeleteNode (inventory, (void *) retrieved);
                treeDeleteNode (invoice, (void *) delete1);
            }
            else
            {
                Data *delete1 = makeCopy (retrieved);
                treeDeleteNode (inventory, (void *) retrieved);
                treeDeleteNode (invoice2, (void *) delete1);
            }

            printf ("\nItem removed from inventory successfully...\nNOTE: This item will also be deleted from invoice if present on the invoice as this item is no longer on sale\n");

            free (search);
        }

        else if (menu == 1)
        {
            editInvoice (inventory, invoice, invoice2);
        }

        else if (menu == 3)
        {
            printf ("\n************************************************************************************************\n");
            printf ("                                       CURRENT INVENTORY                                    \n");
            printf ("************************************************************************************************");
            treeInOrderPrint (inventory, &printInventory);
            printf ("\n************************************************************************************************\n");
        }

        else if (menu == 4)
        {
            printf ("\n************************************************************************************************\n");
            printf ("                                       CURRENT INVOICE                                    \n");
            printf ("************************************************************************************************");
            treeInOrderPrint (invoice, &printInvoice);
            treeInOrderPrint (invoice2, &printInvoice);
            printf ("\n************************************************************************************************\n");
        }

        else if (menu == 5)
        {
            printf ("\033[2J\033[1;1H");        //places the cursor to the top left
            printf ("\n###########################################################################\n");
            printf ("                   POINT OF SALE SYSTEM FOR SOCS GAME STORE                \n");
            printf ("###########################################################################\n");
        }

        else
            printf ("\nInvalid Menu Choice...\n");
    }
    return 0;
}
