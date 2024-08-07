/********************************************/
/*   list.h                                 */
/*   a dynamic  linked list with a header   */
/********************************************/


#ifndef _LIST_
#define _LIST_


/*** Definitions ***/
#define		EMPTY	0x7FFFFFFF

typedef void* DATA;

typedef enum { False, True } BOOL;	// a boolean type


// Node
typedef struct node
{
	DATA			key;
	struct node* next;
}NODE;


// List
typedef struct
{
	NODE head;
}LIST;


/*** Function prototypes ***/
// create new list
BOOL L_init(LIST* pList);

// add new node after *pNode
NODE* L_insert(NODE* pNode, DATA Value);

// erase node after *pNode
BOOL L_delete(NODE* pNode, void freeFunc(void*));

// return a pointer to the node 
const NODE* L_find(const NODE* pNode, DATA Value, int compare(const void*, const void*));

// return a pointer to the node by index 
const NODE* L_find_By_Index(const NODE* pNode, int index);

// return List length
int L_length(const LIST* pList);

// free list memory
BOOL L_free(LIST* pList, void freeFunc(void*));

// print the list content
int L_print(const LIST* pList, void (*print)(const void*));

NODE* L_insert_sorted(LIST* pList, DATA Value, int(*compare)(const void*, const void*));
#endif
