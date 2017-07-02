#ifndef MONO_VECTOR_H
#define MONO_VECTOR_H

#include <stddef.h>

typedef struct {
	void* array;
	unsigned int length;

	// Private fields
	unsigned int size;
	size_t member_size;
	unsigned int flags;
} m_vec;

m_vec* m_new_vec(unsigned int initial_size, size_t member_size, unsigned int flags);

// value must be a pointer to a value of member_size length
unsigned int m_push(m_vec* vec, void * value);
unsigned int m_get(m_vec* vec, void * buff, unsigned int index);

// index may require the vector to be resized
// the pointer is copied with memcpy by member_size into the vector
unsigned int m_set(m_vec* vec, void * buff, unsigned int index);
unsigned int m_append(m_vec* dest, m_vec* src);
void m_delete_vec(m_vec*);
unsigned int m_pretty_print(m_vec *);

unsigned int m_validate(m_vec * vec);
const char * m_vec_error(unsigned int code);

enum m_vector_errors {
	M_VECTOR_INVALID_INDEX = 1,
	M_VECTOR_INVALID_SIZE = 2,
	M_VECTOR_INVALID_MEMBER_SIZE = 3,
};

enum m_vec_flags {
	M_VECTOR_LAZY = 0x01,
	M_VECTOR_ZERO = 0x02,
	// TODO initialize new values to zero flag
};

#endif