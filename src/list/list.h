#ifndef MONO_LIST_H
#define MONO_LIST_H

typedef struct node {
	void* value;

	struct node* prev;
	struct node* next;
} m_list_node;

typedef struct {
	m_list_node * first;
	m_list_node * last;
	int length;
} m_list;

m_list* m_new_list();
// you have to free your own values
void m_list_push(m_list* list, void * value);
void * m_list_pop(m_list * list);
void m_list_delete(m_list* list, m_list_node* node);
// no functions for iterating over a list currently
// these can be implemented once we know how it should be used
void m_delete_list(m_list*);

#endif