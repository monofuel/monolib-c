#ifndef MONO_STRING_H
#define MONO_STRING_H

typedef struct {
	char * array;
	int size;
	int length;
} m_string;

m_string* m_new_string(int);
void m_addc(m_string*, char);
void m_append_cstring(m_string *, char *, int);
int m_get_cstring(m_string*, char*, int);
void m_delete_string(m_string*);
const char * m_string_error(int);
int m_string_pretty_print(m_string *);

enum m_string_errors {
	M_STRING_DST_TOO_SMALL = 1,
};

#endif