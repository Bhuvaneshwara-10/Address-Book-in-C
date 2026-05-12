#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
  FILE *fp = fopen("contact.csv","w");
  if(fp == NULL)
  {
    fprintf(stderr,"Memory is not successfully allocated");
    return;
  }
  for(int i = 0;i < addressBook->contactCount;i++)
  {
    fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
  }
  fclose(fp);

  for (int i = 0; i < 100; i++)
    {
        printf("\rSaving.......................................[%d]", i + 1);
        fflush(stdout);
        usleep(10000);
    }
    printf("\n");
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contact.csv", "r");
    if (fp == NULL)
    {
        printf("File not found\n");
        return;
    }

    addressBook->contactCount = 0;

    while (fscanf(fp, "%[^,],%[^,],%[^\n]\n",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;
    }
    fclose(fp);

}
    

