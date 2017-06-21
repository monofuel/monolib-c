#ifndef MONO_MAP_H
#define MONO_MAP_H
#include "../vector/vector.h"

typedef struct {
	m_vec* table;
	int values;
} m_map;

m_map* m_new_map(int);
void m_delete_map(m_map*);

#endif