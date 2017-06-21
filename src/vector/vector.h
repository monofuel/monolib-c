#ifndef MONO_VECTOR_H
#define MONO_VECTOR_H

typedef struct {
	void** array;
	int size;
	int length;
} m_vec;

m_vec* m_new_vec(int);
void m_push(m_vec*, void *);
void m_append(m_vec*, m_vec*);
void m_delete_vec(m_vec*);
int m_vec_pretty_print(m_vec *);

#endif