#include "map.h"
#include <stdlib.h>
#include "../index.h"

m_map* m_new_map(int initialSize) {
	m_map* map = malloc(sizeof(m_map));
	map->table = m_new_vec(initialSize, sizeof(void *), M_VECTOR_LAZY);
	map->values = 0;
	return map;
}

void m_delete_map(m_map* map) {
	// note: does not free values in table.
	// should use talloc()
	m_delete_vec(map->table);
	free(map);
}