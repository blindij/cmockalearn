#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "listlib.h"
#define TRAV_INIT_SIZE 8

typedef struct list_struct{
   data_t item;
   struct list_struct *next;
} list_t;

static list_t endlist;
static list_t *headptr = NULL;
static list_t *tailptr = NULL;
static list_t **travptrs = NULL;
static int travptrs_size = 0;

int accessdata(void){           // return a nonnegative key if successful
   int i;
   list_t **newptrs;
   if (headptr == NULL) {
      errno = EINVAL;
      return -1;
   }
   if (travptrs_size == 0) {
      travptrs = (list_t **)calloc(TRAV_INIT_SIZE,sizeof(list_t *));
      if (travptrs == NULL)   // couldn't allocate space for traversal keys
         return -1;
      travptrs[0] = headptr;
      travptrs_size = TRAV_INIT_SIZE;
      return 0;
   }
   for (i = 0; i < travptrs_size; i++){   // look for empty slot for key
      if (travptrs[i] == NULL) {
         travptrs[i] = headptr;
         return i;
      }
   }
   newptrs = realloc(travptrs, 2*travptrs_size*sizeof(list_t *));
   if (newptrs == NULL)      // couldn't expand the array of traversal keys
      return -1;
   travptrs = newptrs;
   travptrs[travptrs_size] = headptr;
   travptrs_size *= 2;
   return travptrs_size/2;
}

//int adddata(data_t data){   // allocate node for data and add to end of list
//   list_t *newnode;
//   int nodesize;
//
//   nodesize = sizeof(list_t) + strlen(data.string) + 1;
//   if (newnode = (list_t *) malloc(nodesize) == NULL)    // could not add node
//      return -1;
//   newnode->item.time =  data.time;
//   newnode->item.string = (char *) newnode + sizeof(list_t);
//   strcpy(newnode->item.string,data.string);
//   newnode->next = NULL;
//   if (headptr == NULL)
//      headptr = newnode;
//   else
//      tailptr->next = newnode;
//   tailptr = newnode;
//   return 0;
//}
