#include "list.h"
#include <stdlib.h>
#include "../index.h"

m_list * m_new_list() {
	m_list* list = malloc(sizeof(m_list));
	list->first = (void *) 0;
	list->last = (void *) 0;
	list->length = 0;
	return list;
}

void m_list_push(m_list* list, void * value) {
	m_list_node * node = malloc(sizeof(m_list));
	node->value = value;
	node->prev = list->last;
	node->next = 0;
	if (node->prev != 0) {
		node->prev->next = node;
	}
	list->last = node;
	if (list->first == 0) {
		list->first = node;
	}
	list->length++;
}

void * m_list_pop(m_list* list) {
	if (list->length == 0) {
		// TODO set errno
		return 0;
	}
	m_list_node * node = list->last;

	void * value = node->value;
	m_list_delete(list, node);
	return value;
}

void m_list_delete(m_list* list, m_list_node* node) {
	if (node->prev != 0) {
		node->prev->next = node->next;
	}
	if (node->next != 0) {
		node->next->prev = node->prev;
	}
	if (list->first == node) {
		list->first = node->next;
	}
	if (list->last == node) {
		list->last = node->prev;
	}
	free(node);
	list->length--;
}

void m_delete_list(m_list* list) {
	while (list->length > 0){
		m_list_pop(list);
	}
	free(list);
}