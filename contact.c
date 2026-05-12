
/*

 Description: 
            The Address Book Management System project helps store and manage contact details such as 
            name, phone number, and email ID.It supports creating, searching, editing, deleting, and 
            listing contacts through a menu-driven interface.Input validation is implemented to avoid
            invalid data and duplicate phone numbers.File handling is used to save and retrieve contacts.
            This project improved my understanding of structures, pointers, string handling and file operations in C.
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

//validate name
    int validateName(const char *name)
{
    int i = 0;
    if(name[0] == '\0' || name[0] == ' ')
        return 0;

    while(name[i] != '\0')
    {
        if(!((name[i] >= 'A' && name[i] <= 'Z') ||
             (name[i] >= 'a' && name[i] <= 'z') ||
              name[i] == ' '))
            return 0;

        if(name[i] == ' ' && name[i + 1] == ' ')
            return 0;

        i++;
    }

    if(name[i - 1] == ' ')
        return 0;

    return 1;
}

//validate phone
        int validatePhone(const char *phone)
        {
            int i;

            if (strlen(phone) != 10)
                return 0;

            for (i = 0; phone[i] != '\0'; i++)
            {
                if (phone[i] < '0' || phone[i] > '9')
                    return 0;
            }
            return 1;
        }

//valiate email
    int validateEmail(const char *email)
    {
    int at_count = 0;
    int len = strlen(email);
    if(len < 6)
        return 0;
    if(strcmp(&email[len - 4], ".com") != 0) 
        return 0;
    if(len >= 5 && (strcmp(&email[len - 5], "@.com") == 0))
        return 0;

    for(int i = 0; email[i]; i++)
    {
        if(email[i] == '@')
            at_count++;
        else if(email[i] == ' ')
            return 0;
    }
    if(at_count != 1)
        return 0;

    return 1;
    }

//Duplicate phone number
    int Dup_Phone(AddressBook *addressBook, const char *phone)
    {
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcmp(addressBook->contacts[i].phone, phone) == 0)
                return 1;
        }
        return 0;
    }

//delete selection
    int selection(char *select)
    {
        while(1)
        {
            printf("\nDo you want to delete this contact\n");
            printf("For yes press (y or Y)\nFor no press (n or N): \n");
            scanf(" %c", select);
            if(*select == 'y' || *select == 'Y')
                return 1;
            else if(*select == 'n' || *select == 'N')
                return 0;
            else
                printf("Give valid input\n\n"); 
        }
    }

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the user input
    Contact temp;
    for(int i = 0; i < addressBook -> contactCount - 1; i++)
    {
        for(int j = 0; j < (addressBook->contactCount) - i - 1; j++)
        {
            switch(sortCriteria)
            {
                //sort by name
                case 1:
                {
                    if (strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0) 
                    {
                        temp = addressBook->contacts[j]; 
                        addressBook->contacts[j]= addressBook->contacts[j + 1];
                        addressBook->contacts[j + 1]= temp;
                    }
                    break;

                }
                //sort by phone number
                case 2:
                {
                    if (strcmp(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone) > 0) 
                    {
                        temp = addressBook->contacts[j]; 
                        addressBook->contacts[j]= addressBook->contacts[j + 1];
                        addressBook->contacts[j + 1]= temp;
                    }
                    break;
                }
                //sort by email
                case 3:
                {
                    if (strcmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email) > 0) 
                    {
                        temp = addressBook->contacts[j]; 
                        addressBook->contacts[j]= addressBook->contacts[j + 1];
                        addressBook->contacts[j + 1]= temp;
                    }
                    break;
                }
                default:
                    printf("Invalid criteria\n");
                    return;
            }
        }
    }
    printf("Sorted contact list:\n");
    printf("---------------------------------------------------------------\n"); 
    printf("| %-3s | %-15s | %-12s | %-20s |\n", "No", "NAME", " NUMBER", "EMAIL");
    printf("---------------------------------------------------------------\n");     
        for (int i = 0; i < addressBook->contactCount; i++)
        {
        printf("| %-3d | %-15s | %-12s | %-20s |\n", i+1,
       addressBook->contacts[i].name,
       addressBook->contacts[i].phone,
       addressBook->contacts[i].email);
        }
        printf("---------------------------------------------------------------\n");
        printf("\n");
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
   // populateAddressBook(addressBook);   
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

void createContact(AddressBook *addressBook)
{
	//Create contact logic
     char name[50];
     char phone[20];
     char email[50];
     int index = addressBook->contactCount;
            //Getting name from user
            while(1)
            {
                printf("Enter the Name: ");
                scanf(" %[^\n]", name);
                int check = validateName(name);
                if(check)
                {
                    strcpy(addressBook->contacts[index].name, name);
                    break;
                }
                else
                {
                    printf("Invalid name\n");
                }
            }
            //Getting phone number from user
            while(1)
            {
                printf("Enter the Mobile Number: ");
                scanf(" %s", phone);

                if(!validatePhone(phone))
                {
                    printf("Enter valid 10 digit phone number\n");
                    continue;
                }
                if(Dup_Phone(addressBook, phone))
                {
                    printf("Phone number already exists\n");
                    continue;
                }
                strcpy(addressBook->contacts[index].phone, phone);
                break;
            }
                //Getting email from user
                while (1)
                {
                    printf("Enter the Email-id: ");
                    scanf(" %s", email);
                    int check = validateEmail(email);
                    if(check)
                    {
                        strcpy(addressBook->contacts[index].email, email);
                        break;
                    }
                    else
                    {
                        printf("Invalid Email\n");
                    }              
                }
                addressBook->contactCount++;
                printf("%s\t%s\t%s\n", addressBook -> contacts[index].name, addressBook -> contacts[index].phone, 
                    addressBook -> contacts[index].email);
}

void searchContact(AddressBook *addressBook) 
{
   //Search contact logic
    printf("\n-----------------------------------------------------\n");
    printf("                 Search Contact\n");
    printf("-----------------------------------------------------\n");
    int choice;
    int found;
    printf("Enter the choice: \n1.Name\n2.Mobile Number\n3.E-mail ID\n");
    scanf("%d", &choice);
    switch(choice)
    {
        //Search by name
        case 1:
        {
            char name[50];
            found = 0;
            while(1)
            {
                printf("Enter the Name: ");
                scanf(" %[^\n]", name);
                int check = validateName(name);
                if(check)
                    break;
                 else
                    printf("Invalid name. Try again.\n");
            }
                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if(strcmp(addressBook->contacts[i].name, name) == 0)
                    {
                        printf("%s\t%s\t%s\n", addressBook -> contacts[i].name, addressBook -> contacts[i].phone, 
                        addressBook -> contacts[i].email);
                        found = 1;
                    }
                }
                if(!found)
                    printf("No contact found\n");
            break;
         }
         //Search by phone
        case 2:
        {
            char phone[20];
            found = 0;
             while(1)
                {
                    printf("Enter the Mobile Number: ");
                    scanf(" %s", phone);
                    int check = validatePhone(phone);
                if (check)
                    break;
                else
                    printf("Enter valid 10 digit phone number\n");
                }
                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if(strcmp(addressBook->contacts[i].phone, phone) == 0)
                    {
                    printf("%s\t%s\t%s\n", addressBook -> contacts[i].name, addressBook -> contacts[i].phone, 
                        addressBook -> contacts[i].email);
                        found = 1;
                    }
                }
                if(!found)
                    printf("No contact found\n");
            break;
        }
        //Search by email
        case 3:
        {      
            char email[50];
            found = 0;
           while (1)
                {
                    printf("Enter the Email-id: ");
                    scanf(" %s", email);
                    int check = validateEmail(email);
                        if (check)
                            break;
                        else
                            printf("Invalid email. Try again.\n");
                }
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].email, email) == 0)
                {
                printf("%s\t%s\t%s\n", addressBook -> contacts[i].name, addressBook -> contacts[i].phone, 
                    addressBook -> contacts[i].email);
                     found = 1;
                }
            }
            if(!found)
            {
                printf("No contact found\n");
                break;
            }
            break;
        }
        default:
        {
            printf("Invalid choice..\n");
            break;
        }
    }
}

void editContact(AddressBook *addressBook)
{
    printf("\n-----------------------------------------------------\n");
    printf("                 Edit Contact\n");
    printf("-----------------------------------------------------\n");

    //Edit contact logic
    int choice, flag, count = 0, index, option;
    int arr[addressBook->contactCount];
    printf("\nEditing a contact by: \n1.Name\n2.Mobile Number\n3.Email-id\n");
    scanf("%d", &choice);  
    switch(choice)
    {
        //Edit by name
        case 1:
        {
            char name[50];
            flag=0;
            printf("Enter the name to be edited: ");
            scanf(" %[^\n]", name);
            int check = validateName(name);
                if(!check)
                {
                    printf("Invalid name. Try again.\n");
                    return;
                }
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].name, name) == 0)
                {
                    flag=1;
                    arr[count]=i;
                    count++;
                }
            }
                    if(flag == 0)
                    {
                        printf("No contact found\n");
                         return;
                    }
            // for name exsist one time
            if(count == 1)
            {
                index = arr[0];
                printf("%s\t%s\t%s\n",addressBook -> contacts[index].name, addressBook -> contacts[index].phone, 
                        addressBook -> contacts[index].email);
                 printf("\nEditing a contact by: \n1.Name\n2.Mobile Number\n3.Email-id\n");
                        scanf("%d", &option);

                     switch(option)
                    {
                        case 1:
                        {
                            char newname[50];
                            printf("Enter the updating name: ");
                            scanf(" %[^\n]", newname);
                            int check = validateName(newname);
                                if(check)
                                {
                                    strcpy(addressBook->contacts[index].name, newname);
                                    printf("Editing Successful\n");
                                    break;
                                }
                                else
                                {
                                    printf("Invalid name. Try again.\n");
                                }
                            break;
                        }
                        case 2:
                        {
                            char mobile[50];
                            printf("Enter the updating Mobile Number: ");
                            scanf("%s", mobile);

                            if(!validatePhone(mobile))
                            {
                                printf("Enter valid 10 digit phone number\n");
                                break;
                            }

                            if(Dup_Phone(addressBook, mobile))
                            {
                                printf("Phone number already exists\n");
                                break;
                            }

                            strcpy(addressBook->contacts[index].phone, mobile);
                            printf("Editing Successful\n");
                            break;
                        }

                        case 3:
                        {
                            char newEmail[50];
                            printf("Enter the updating Email: ");
                            scanf("%s", newEmail);
                            int check = validateEmail(newEmail);
                                if (check)
                                {
                                    strcpy(addressBook->contacts[index].email, newEmail);
                                    printf("Editing Successful\n");
                                    break;
                                }
                                else
                                {
                                    printf("Invalid email. Try again.\n");
                                }
                            break;
                        }
                        default:
                        {
                            printf("Invalid input");
                            break;
                        }
                    }
            }
            // for duplicate name 
            else if(count > 1)
            {

                        for(int j = 0; j < count; j++)
                        {
                            printf("%d\t%s\t%s\t%s\n", j + 1, addressBook -> contacts[arr[j]].name, addressBook -> contacts[arr[j]].phone, 
                            addressBook -> contacts[arr[j]].email);
                        }
                        int dup;
                        printf("Enter the contact index you want to edit: ");
                        scanf("%d", &dup);

                            if (dup < 1 || dup > count)
                            {
                                printf("Invalid selection\n");
                                return;
                            }
                            index = arr[dup-1];

                        printf("\nEditing a contact by: \n1.Name\n2.Mobile Number\n3.Email-id\n");
                        scanf("%d", &option);

                     switch(option)
                    {
                        case 1:
                        {
                            char newname[50];
                            printf("Enter the updating name: ");
                            scanf(" %[^\n]", newname);
                            int check = validateName(newname);                           
                            if(check)
                                {
                                    strcpy(addressBook->contacts[index].name, newname);
                                    printf("Editing Successful\n");
                                    break;
                                }
                                else
                                {
                                    printf("Invalid name. Try again.\n");
                                } 
                        break;
                        }
                        case 2:
                        {
                            char mobile[50];
                            printf("Enter the updating Mobile Number: ");
                            scanf("%s", mobile);

                            if(!validatePhone(mobile))
                            {
                                printf("Enter valid 10 digit phone number\n");
                                break;
                            }

                            if(Dup_Phone(addressBook, mobile))
                            {
                                printf("Phone number already exists\n");
                                break;
                            }

                            strcpy(addressBook->contacts[index].phone, mobile);
                            printf("Editing Successful\n");
                            break;
                        }
                        case 3:
                        {
                            char newEmail[50];
                            printf("Enter the updating Email: ");
                            scanf("%s", newEmail);
                            int check = validateEmail(newEmail);
                                if (check)
                                {
                                    strcpy(addressBook->contacts[index].email, newEmail);
                                    break;
                                }
                                else
                                {
                                    printf("Invalid email. Try again.\n");
                                }                            
                        break;
                        }
                        default:
                        {
                            printf("Invalid input");
                            break;
                        }
                    }
                }
            break;
        }
            //Edit by phone number
            case 2:
            {
                char phone[20];
                flag=0;
                printf("Enter the Mobile number: ");
                scanf("%s", phone);
                int check = validatePhone(phone);
                if (!check)
                {
                    printf("Enter valid 10 digit phone number\n");
                    return;
                }
                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if((strcmp(addressBook->contacts[i].phone, phone) == 0))
                    {
                        printf("%s\t%s\t%s\n", addressBook -> contacts[i].name, addressBook -> contacts[i].phone, 
                            addressBook -> contacts[i].email);     
                        flag = 1;     
                        index = i;       
                    }
                }
                    if(flag == 0)
                    {
                        printf("No contact found\n");
                        return;
                    }
                    printf("\nEditing a contact by: \n1.Name\n2.Mobile Number\n3.Email-id\n");
                    scanf("%d", &option);

                    switch (option)
                    {
                     case 1:
                        {
                            char newname[50];
                            printf("Enter the updating name: ");
                            scanf(" %[^\n]", newname);
                            int check = validateName(newname);                           
                            if(check)
                                {
                                    strcpy(addressBook->contacts[index].name, newname);
                                    printf("Editing Successful\n");
                                    break;
                                }
                                else
                                {
                                    printf("Invalid name. Try again.\n");
                                }                             
                            break;
                        }
                        case 2:
                        {
                           char mobile[50];
                            printf("Enter the updating Mobile Number: ");
                            scanf("%s", mobile);

                            if(!validatePhone(mobile))
                            {
                                printf("Enter valid 10 digit phone number\n");
                                break;
                            }

                            if(Dup_Phone(addressBook, mobile))
                            {
                                printf("Phone number already exists\n");
                                break;
                            }

                            strcpy(addressBook->contacts[index].phone, mobile);
                            printf("Editing Successful\n");
                            break;
                        }
                        case 3:
                        {
                            char newEmail[50];
                            printf("Enter the updating Email: ");
                            scanf("%s", newEmail);
                            int check = validateEmail(newEmail);
                                if (check)
                                {
                                    strcpy(addressBook->contacts[index].email, newEmail);
                                    break;
                                }
                                else
                                {
                                    printf("Invalid email. Try again.\n");
                                }                            
                        break;
                        }
                        default:
                        {
                            printf("Invalid input");
                            break;
                        }
                    }
                        break;
            }
            //Edit by email
            case 3:
                {
                    char Email[50];
                    flag=0;
                    printf("Enter the Email: ");
                    scanf("%s", Email);
                    int check = validateEmail(Email);
                        if (!check)
                        {
                            printf("Invalid email. Try again.\n");
                            return;
                        }                    
                    for(int i = 0; i < addressBook->contactCount; i++)
                    {
                        if((strcmp(addressBook->contacts[i].email, Email) == 0))
                        {
                            printf("%s\t%s\t%s\n", addressBook -> contacts[i].name, addressBook -> contacts[i].phone, 
                            addressBook -> contacts[i].email);     
                            flag = 1;     
                            index = i;       
                        }  
                    }
                    if(flag == 0)
                    {
                        printf("No contact found\n");
                        return;
                    }
                        printf("\nEditing a contact by: \n1.Name\n2.Mobile Number\n3.Email-id\n");
                        scanf("%d", &option);
                    switch (option)
                    {
                        case 1:
                        {
                            char newname[50];
                            printf("Enter the updating name: ");
                            scanf(" %[^\n]", newname);
                           int check = validateName(newname);                           
                            if(check)
                                {
                                    strcpy(addressBook->contacts[index].name, newname);
                                    printf("Editing Successful\n");
                                    break;
                                }
                                else
                                {
                                    printf("Invalid name. Try again.\n");
                                }                            
                            break;
                        }
                        case 2:
                        {
                            char mobile[50];
                            printf("Enter the updating Mobile Number: ");
                            scanf("%s", mobile);

                            if(!validatePhone(mobile))
                            {
                                printf("Enter valid 10 digit phone number\n");
                                break;
                            }

                            if(Dup_Phone(addressBook, mobile))
                            {
                                printf("Phone number already exists\n");
                                break;
                            }

                            strcpy(addressBook->contacts[index].phone, mobile);
                            printf("Editing Successful\n");
                            break;
                        }
                        case 3:
                        {
                            char newEmail[50];
                            printf("Enter the updating Email: ");
                            scanf("%s", newEmail);
                            int check = validateEmail(newEmail);
                                if (check)
                                {
                                    strcpy(addressBook->contacts[index].email, newEmail);
                                    break;
                                }
                                else
                                {
                                    printf("Invalid email. Try again.\n");
                                }                                        
                            break;
                        }
                        default:
                        {
                            printf("Invalid input\n");
                            break;
                        }
                    }
                    break;
                }
             default:
             {
                printf("Invalid input\n");
                break;
             }
    }
}

void deleteContact(AddressBook *addressBook)
{
	//Delete contact logic
    printf("\n-----------------------------------------------------\n");
    printf("                 Delete Contact\n");
    printf("-----------------------------------------------------\n");
    int choice;
    printf("Enter the contact to be deleted by:\n1.Name\n2.Phone\n3.Email-id\n");
    scanf("%d", &choice);
    switch(choice)
    {
    //Delete by name
      case 1:
       {
            char name[50];
            int count = 0,flag = 0;
            int arr[addressBook->contactCount];
                printf("Enter the name: ");
                scanf(" %[^\n]", name);
                int check = validateName(name);
                    if(!check)
                    {
                        printf("Invalid name. Try again.\n");
                        return;
                    }          
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if((strcmp(addressBook->contacts[i].name, name) == 0))
                {
                    flag = 1;
                    arr[count] = i;
                    count++;
                }
            }
            if(flag == 0)
            {
                printf("No contact found\n");
                return;
            }
            //Name exist one time
            if(count == 1)
            {
                int index = arr[0];
                printf("%s\t%s\t%s\n",addressBook -> contacts[index].name, addressBook -> contacts[index].phone, 
                        addressBook -> contacts[index].email);
                        
                char select;
                int res = selection(&select);
                if(res == 1)
                {
                    for(int i = index; i < addressBook->contactCount - 1; i++)
                        {
                            addressBook->contacts[i] = addressBook->contacts[i+1];
                        }
                        addressBook->contactCount--;
                        printf("Deletion Successful\n");
                }
                else if(res == 0)
                {
                    printf("Deletion Cancelled\n");
                }  
                else
                {
                    printf("Invalid choice. Deletion aborted\n");
                }
            }
            // if duplicate name exist
            else if(count > 1)
            {            
                for(int j = 0; j < count; j++)
                {
                    printf("%d\t%s\t%s\t%s\n", j + 1, addressBook -> contacts[arr[j]].name, addressBook -> contacts[arr[j]].phone, 
                    addressBook -> contacts[arr[j]].email);
                }
                int del;
                printf("Enter the serial no you want to Delete: ");
                scanf("%d", &del);
                    if (del < 1 || del > count)
                    {
                        printf("Invalid selection\n");
                        return;
                    }
                int index = arr[del-1];
                char select;
                int res = selection(&select);
                if(res == 1)
                {
                    for(int i = index; i < addressBook->contactCount - 1; i++)
                        {
                            addressBook->contacts[i] = addressBook->contacts[i+1];
                        }
                        addressBook->contactCount--;
                        printf("Deletion Successful\n");
                }
                else if(res == 0)
                {
                    printf("Deletion Cancelled\n");
                }  
                else
                {
                    printf("Invalid choice. Deletion aborted\n");
                }
            }
            break;
         }
        //Delete by phone number
         case 2:
            {
                char phone[20];
                int flag = 0,index = 0;
                int arr[addressBook->contactCount];
                printf("Enter the Mobile Number: ");
                scanf("%s", phone);
                int check = validatePhone(phone);
                if (!check)
                {
                    printf("Enter valid 10 digit phone number\n");
                    return;
                }       
                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if((strcmp(addressBook->contacts[i].phone, phone) == 0))
                    {
                        printf("%s\t%s\t%s\n",addressBook -> contacts[i].name, addressBook -> contacts[i].phone, 
                        addressBook -> contacts[i].email);   
                        flag = 1;
                        index = i;
                        break;
                    }
                }
                if(flag == 0)
                {
                    printf("No Contact found\n");
                    return;
                }
                char select;
                int res = selection(&select);
                    if(res == 1)
                    {
                        for(int i = index; i < addressBook->contactCount - 1; i++)
                            {
                                addressBook->contacts[i] = addressBook->contacts[i+1];
                            }
                            addressBook->contactCount--;
                            printf("Deletion Successful\n");
                    }
                    else if(res == 0)
                    {
                        printf("Deletion Cancelled\n");
                    }  
                    else
                    {
                        printf("Invalid choice. Deletion aborted\n");
                    }
            break;
            }
            //Delete by email
            case 3:
            {
                char Email[50];
                int index = 0, flag = 0;
                printf("Enter the Email: ");
                scanf("%s", Email);
                 int check = validateEmail(Email);
                        if (!check)
                        {
                            printf("Invalid email. Try again.\n");
                            return;
                        }
                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if((strcmp(addressBook->contacts[i].email, Email) == 0))
                    {
                        printf("%s\t%s\t%s\n",addressBook -> contacts[i].name, addressBook -> contacts[i].phone, 
                        addressBook -> contacts[i].email);   
                        flag = 1;
                        index = i;
                        break;
                    }
                }
                if(flag == 0)
                {
                    printf("No contact found\n");
                    return;
                }
                char select;
               int res = selection(&select);
               if(res == 1)
               {
                  for(int i = index; i < addressBook->contactCount - 1; i++)
                    {
                        addressBook->contacts[i] = addressBook->contacts[i+1];
                    }
                    addressBook->contactCount--;
                    printf("Deletion Successful\n");
               }
               else if(res == 0)
               {
                printf("Deletion Cancelled\n");
               }  
               else
               {
                printf("Invalid choice. Deletion aborted\n");
               }
                break;
             }
        default:
            printf("Invalid input\n");
            break;
    }
}

