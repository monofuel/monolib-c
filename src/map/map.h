#ifndef MONO_MAP_H
#define MONO_MAP_H
#include "../vector/vector.h"
#include "../string/string.h"
#include "../list/list.h"

typedef struct {
	// vector of records
	m_vec* table;
	int values;
} m_map;

m_map* m_new_map(unsigned int initial_size);
// void m_resize(m_map* map, int new_size);
// m_map is not responsible for free'ing your pointers
void m_put(m_map* map, m_string* key, void * value, unsigned int flags);
// TODO void m_int_put(m_map* map, int key, void * value);
void * m_map_get(m_map* map, m_string* key);
void m_delete_map(m_map*);
// int m_validate(m_map * map);

enum m_map_flags {
	M_MAP_FREE = 0x01,
};

#endif