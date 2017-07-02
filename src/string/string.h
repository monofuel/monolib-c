#ifndef MONO_STRING_H
#define MONO_STRING_H

#include "../vector/vector.h"

// m_string is a vec with member size of 1
typedef m_vec m_string;

m_string* m_new_string(int);
m_string* m_from_cstring(char *);
void m_addc(m_string *, char);
void m_append_cstring(m_string *, char *, int);
int m_get_cstring(m_string*, char*, int);
void m_delete_string(m_string*);
int m_strcmp(m_string*, m_string*);
m_string* m_string_clone(m_string*);
const char * m_string_error(int);
int m_str_pretty_print(m_string *);

enum m_string_errors {
	M_STRING_DST_TOO_SMALL = 1,
};

#endif