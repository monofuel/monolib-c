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

m_list_node* m_list_pop(m_list* list) {
	if (list->length == 0) {
		// TODO set errno
		return 0;
	}
	m_list_node * node = list->last;
	list->last = node->prev;
	list->last->next = (void *) 0;
	list->length--;
	return node;
}

void m_delete_list(m_list* list) {
	while (list->length > 0){
		free(m_list_pop(list));
	}
	free(list);
}