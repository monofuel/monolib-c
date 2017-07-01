#include "vector.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../index.h"

#ifdef NDEBUG
#define m_vec_validate(vec) ((void) 0)
#else
#define m_vec_validate(vec) {\
	int code = m_validate(vec); \
	if (code != 0) { \
		m_pretty_print(vec); \
		fprintf(stderr, "%s\n", m_vec_error(code)); \
		abort(); \
	} \
}
#endif

m_vec* m_new_vec(int initial_size, int member_size, int flags) {
	m_vec* vec = malloc(sizeof(m_vec));
	vec->member_size = member_size;
	vec->flags = flags;
	vec->size = initial_size;
	vec->array = malloc(initial_size * member_size);
	vec->length = 0;
	m_vec_validate(vec);
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
	m_vec_validate(vec);
	return 0;
}

int m_set(m_vec* vec, void * buff, int index) {
	if (index >= vec->size) {
		if (vec->flags & M_VECTOR_LAZY) {
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
	m_vec_validate(vec);
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
	m_vec_validate(dest);
	m_vec_validate(src);
	return 0;
}

void m_delete_vec(m_vec* vec) {
	m_vec_validate(vec);
	free(vec->array);
	free(vec);
}

int m_validate(m_vec* vec) {
	// TODO add check for canary in debug mode
	if (vec->size < vec->length) {
		return M_VECTOR_INVALID_SIZE;
	}
	if (vec->member_size < 1) {
		return M_VECTOR_INVALID_MEMBER_SIZE;
	}
	return 0;
}

int m_pretty_print(m_vec * vec) {
	printf("{ length: %d, size: %d, member_size: %d, flags; %d }\n",
		vec->length,
		vec->size,
		vec->member_size,
		vec->flags);
	return 0;
}

const char * m_vec_error(int code) {
	switch(code) {
		case M_VECTOR_INVALID_INDEX:
			return "invalid index passed to vector";
		case M_VECTOR_INVALID_SIZE:
			return "invalid size on vector";
		case M_VECTOR_INVALID_MEMBER_SIZE:
			return "invalid member size for vector";
		default:
			return "bad error code";
	}
}