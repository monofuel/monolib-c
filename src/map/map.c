#include "map.h"
#include <stdlib.h>
#include <string.h>
#include "../index.h"

// debugging imports
#include <assert.h>
#include <stdio.h>

typedef struct {
	m_string * key;
	void * value;
	// linked list of records
	// TODO this field is not needed for records in the collisions table
	// possibly have a separate structure type for those
	m_list * collisions;
	unsigned int flags;
} record;

static unsigned int hash(m_map * map, m_string* key);

m_map* m_new_map(unsigned int initial_size) {
	m_map* map = malloc(sizeof(m_map));
	map->table = m_new_vec(initial_size, sizeof(record), M_VECTOR_LAZY | M_VECTOR_ZERO);
	map->values = 0;

	// table is intialized to zero, so blank records should be all zero.
	map->table->length = map->table->size;
	return map;
}

void m_put(m_map* map, m_string * key, void * value, unsigned int flags) {
	unsigned int index = hash(map, key);
	printf("put hash %d\n", index);
	record existing;
	m_get(map->table, &existing, index);

	// m_vec makes a copy of this
	record new_record = {
		.key = m_string_clone(key),
		.value = value,
		.collisions = 0,
		.flags = flags,
	};

	// if the field is new
	if (existing.key == 0) {

		m_set(map->table, &new_record, index);
	} else {
		if (m_strcmp(existing.key, key) == 0) {
			// update the existing key
			if (existing.flags & M_MAP_FREE) {
				free(existing.value);
			}
			existing.value = value;
			existing.flags = flags;
			m_set(map->table, &existing, index);

		} else {
			if (existing.collisions == 0) {
				existing.collisions = m_new_list();
			}
			record * record_clone = calloc(1, sizeof(record));
			memcpy(record_clone, &new_record, sizeof(record));
			m_list_push(existing.collisions, record_clone);

			// update collision table on record
			m_set(map->table, &existing, index);
		}
	}
}

// returns zero if the value was undefined
void * m_map_get(m_map* map, m_string * key) {
	unsigned int index = hash(map, key);
	printf("get hash %d\n", index);
	record existing;
	m_get(map->table, &existing, index);
	if (existing.key != 0 && m_strcmp(existing.key, key) != 0) {
		// we had a collision, and should look for the key in the list
		if (existing.collisions->first != 0) {
			for (m_list_node * node = existing.collisions->first; node != 0; node = node->next) {
				record * rec = node->value;
				if (m_strcmp(key, rec->key) == 0) {
					return rec->value;
				}
			}
		} // else was missing
	} // either the record did not exist, or it exists and the key matches
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
			// TODO we should add a flag so linked list can delete our values for us
			if (val.collisions->first != 0) {
				for (m_list_node * node = val.collisions->first; node != 0; node = node->next) {
					record * rec = node->value;
					if (val.flags & M_MAP_FREE) {
						#ifdef NDEBUG
						free(rec->key);
						free(rec->value);
						#else
						assert(rec->value != 0);
						assert(rec->key != 0);
						free(rec->value);
						#endif
					}
					m_delete_string(rec->key);
					free(rec);
				}
			} 
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