#include "vector.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../index.h"

m_vec* m_new_vec(int initial_size, int member_size, int flags) {
	m_vec* vec = malloc(sizeof(m_vec));
	vec->member_size = member_size;
	vec->flags = flags;
	vec->size = initial_size;
	vec->array = malloc(initial_size * member_size);
	vec->length = 0;
	return vec;
}

int m_push(m_vec* vec, void* buff) {
	return m_set(vec, buff, vec->length);
}

int m_get(m_vec* vec, void * buff, int index) {
	if (index > vec->length) {
		return M_VECTOR_INVALID_INDEX;
	}
	void * value_ptr = (char *) vec->array + (index * vec->member_size);
	memcpy(buff, value_ptr, vec->member_size);
	return 0;
}

int m_set(m_vec* vec, void * buff, int index) {
	if (index >= vec->size) {
		if (vec->flags && M_VECTOR_LAZY) {
			vec->array = realloc(
				vec->array,
				vec->member_size * (vec->size++)
			);
		} else {
			vec->array = realloc(
				vec->array,
				vec->member_size * (vec->size = index * MONO_RESIZE_MUL)
			);
		}
	}
	if (index + 1 > vec->length) {
		vec->length = index + 1;
	}
	void * value_ptr = (char *) vec->array + (index * vec->member_size);
	memcpy(value_ptr, buff, vec->member_size);
	return 0;
}

int m_append(m_vec* dest, m_vec* src) {
	if (dest->member_size != src->member_size) {
		return M_VECTOR_INVALID_SIZE;
	}
	if (dest->size < dest->length + src->length) {
		dest->array = realloc(
				dest->array,
				dest->member_size * (dest->size = dest->length + src->length)
			);
	}

	void * dest_ptr = (char *) dest->array + (dest->length * dest->member_size);
	memcpy(dest_ptr, src->array, src->length * dest->member_size);
	dest->length += src->length;
	return 0;
}

void m_delete_vec(m_vec* vec) {
	free(vec->array);
	free(vec);
}

int m_pretty_print(m_vec * vec) {
	printf("{ length: %d, size: %d, member_size: %d, flags; %d }\n",
		vec->length,
		vec->size,
		vec->member_size,
		vec->flags);
	return 0;
}