#ifndef MONO_VECTOR_H
#define MONO_VECTOR_H

typedef struct {
	void* array;
	int length;

	// Private fields
	int size;
	int member_size;
	int flags;
} m_vec;

m_vec* m_new_vec(int initial_size, int member_size, int flags);

// value must be a pointer to a value of member_size length
int m_push(m_vec* vec, void * value);
int m_get(m_vec* vec, void * buff, int index);

// index may require the vector to be resized
int m_set(m_vec* vec, void * buff, int index);
int m_append(m_vec* dest, m_vec* src);
void m_delete_vec(m_vec*);
int m_pretty_print(m_vec *);

int m_validate(m_vec * vec);
const char * m_vec_error(int code);

enum m_vector_errors {
	M_VECTOR_INVALID_INDEX = 1,
	M_VECTOR_INVALID_SIZE = 2,
	M_VECTOR_INVALID_MEMBER_SIZE = 3,
};

enum m_vec_flags {
	M_VECTOR_LAZY = 0x01,
	// TODO initialize new values to zero flag
};

#endif