/* ��BC31�±��� */
/* compile under Borland C++ 3.1 */

#include <stdio.h>
#include <dirent.h>
#include <alloc.h>
#include <string.h>
#include <stdlib.h>

void main(int argc, char *argv[])
 { 
   DIR *directory_pointer;  
   struct dirent *entry;
   struct FileList 
   {
     char filename[64];
     struct FileList *next;
   } start, *node, *previous, *new;
   
   
   if ((directory_pointer = opendir(argv[1])) == NULL) /*ȡargv[1]�ļ��е�ָ�븳��*/
     printf("Error opening %s\n", argv[1]);
   else
     {
        start.next = NULL;
		/*��directory_pointerָ����ļ����б�����һ����FileList����Ϊ������*/
        while (entry = readdir(directory_pointer))/*��ȡdirectory_pointerָ����ļ���*/
          { 
            // Find the correct location
            previous = &start;
            node = start.next;
            while ((node) && (strcmp(entry, node->filename) > 0))/* ���ֵ��������������д��ļ���Ӧ�ò����λ��*/
             { 
               node = node->next;
               previous = previous->next;
             }

            new = (struct FileList *) 
			malloc(sizeof(struct FileList));           
            if (new == NULL) /*�ڴ����ʧ��*/
             {
               printf("Insufficient memory to store list\n");
               exit(1);
             }
            /*��ɲ���*/
			new->next = node;
            previous->next = new;
            strcpy(new->filename, entry);
          }

        closedir(directory_pointer);
        node = start.next;
        /*����������������ļ���*/
		while (node)
          {
            printf("%s\n", node->filename);
            node = node->next;
          }
     }
     printf(" Press any key to quit...");
     getch();
     return;
 }

