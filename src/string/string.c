#include "string.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../index.h"

m_string * m_new_string(int initial_size) {
	m_string* str = m_new_vec(initial_size, sizeof(char), 0);
	return str;
}

m_string * m_from_cstring(char * cstr) {
	int length = strlen(cstr);
	m_string * str = m_new_string(length);
	m_append_cstring(str, cstr, length);
	return str;
}

void m_addc(m_string * str, char c) {
	m_push(str, &c);
}

void m_append_cstring(m_string * str, char * text, int length) {
	if (str->length + length > str->size) {
		str->array = realloc(
			str->array,
			sizeof(char) * (str->size = str->length + length)
		);
	}
	void * dest_ptr = (char *) str->array + str->length;
	memcpy(dest_ptr, text, length);
	str->length += length;
}

int m_get_cstring(m_string* str, char * dest, int length) {
	if (length < str->length + 1) {
		errno = M_STRING_DST_TOO_SMALL;
		return -1;
	}
	memcpy(dest, str-> array, str->length);
	dest[str->length] = 0;
	return 0;
}

int m_strcmp(m_string* str1, m_string* str2) {
	if (str1->length != str2->length) {
		return str1->length - str2->length;
	}
	for (int i = 0; i < str1->length && i < str2->length; i++) {
		char c1 = ((char *) str1->array)[i];
		char c2 = ((char *) str2->array)[i];
		if (c1 != c2) {
			return c1 - c2;
		}
	}
	return 0;
}

m_string* m_string_clone(m_string* src) {
	m_string * str = m_new_string(src->length);
	m_append(str, src);
	return str;
}

void m_delete_string(m_string * str) {
	free(str->array);
	free(str);
}

int m_str_pretty_print(m_string * str) {
	int buffSize = str->length + 1;
	char * text = calloc(buffSize, sizeof(char));
	int err = m_get_cstring(str, text, buffSize);
	if (err != 0) {
		return err;
	}
	printf("{ size: %d, length: %d, array: \"%s\" }\n",
		str-> size,
		str->length,
		text);
	free(text);
	return 0;
}

const char * m_string_error(int code) {
	switch(code) {
		case M_STRING_DST_TOO_SMALL:
			return "destination buffer too small";
		default:
			return "bad error code";
	}
}