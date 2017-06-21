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
void m_delete_list(m_list*);

#endif