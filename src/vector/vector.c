#include "vector.h"
#include <stdlib.h>
#include "../index.h"

m_vec* m_new_vec(int initialSize) {
	m_vec* vec = malloc(sizeof(m_vec));
	vec->size = initialSize;
	vec->array = malloc(initialSize * sizeof(char));
	vec->length = 0;
	return vec;
}

void m_push(m_vec* vec, void* elem) {
	if (vec->length + 1 > vec->size) {
		vec->array = realloc(
			vec->array,
			sizeof(void *) * (vec->size = vec->size * MONO_RESIZE_MUL)
		);
	}
	vec->array[vec->length++] = elem;
}

void m_append(m_vec* dest, m_vec* source) {

}

void m_delete_vec(m_vec* vec) {
	free(vec->array);
	free(vec);
}

int m_vec_pretty_print(m_vec * vec) {
	return 0;
}