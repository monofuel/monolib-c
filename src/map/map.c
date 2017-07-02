#include "map.h"
#include <stdlib.h>
#include "../index.h"

// debugging imports
#include <assert.h>
#include <stdio.h>

static unsigned int hash(m_map * map, m_string* key);

typedef struct {
	m_string * key;
	void * value;
	// linked list of records
	m_list * collisions;
	unsigned int flags;
} record;

m_map* m_new_map(unsigned int initial_size) {
	m_map* map = malloc(sizeof(m_map));
	map->table = m_new_vec(initial_size, sizeof(record), M_VECTOR_LAZY | M_VECTOR_ZERO);
	map->values = 0;
	return map;
}

void m_put(m_map* map, m_string * key, void * value, unsigned int flags) {
	unsigned int index = hash(map, key);
	printf("put hash %d\n", index);
	record existing;
	m_get(map->table, &existing, index);
	// TODO check if strings collide and add collision if so
	// set new value if strings equal
	record new_record = {
		.key = m_string_clone(key),
		.value = value,
		.collisions = 0,
		.flags = flags,
	};
	m_set(map->table, &new_record, index);
}

void * m_map_get(m_map* map, m_string * key) {
	unsigned int index = hash(map, key);
	printf("get hash %d\n", index);
	record existing;
	m_get(map->table, &existing, index);
	// TODO look up collisions
	return existing.value;
}

void m_delete_map(m_map* map) {
	// TODO would be cool to support talloc()
	for (int i = 0; i < map->table->length; i++) {
		record val;
		m_get(map->table, &val, i);
		if (val.flags & M_MAP_FREE) {
			#ifdef NDEBUG
			free(val.value);
			#else
			assert(val.value != 0);
			assert(val.key != 0);
			free(val.value);
			val.value = 0;
			#endif
		}
		if (val.key != 0) {
			m_delete_string(val.key);
			val.key = 0;
		}
		if (val.collisions != 0) {
			m_delete_list(val.collisions);
			val.collisions = 0;
		}
	}
	m_delete_vec(map->table);
	free(map);
}

static unsigned int hash(m_map * map, m_string * key) {
	unsigned int index = 512;

	for (int i = 0; i < key->length; i++) {
		index ^= ((char *) key->array)[i];
	}

	return index % map->table->size;
}