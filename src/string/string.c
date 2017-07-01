#include "string.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../index.h"

m_string * m_new_string(int initialSize) {
	m_string* str = malloc(sizeof(m_string));
	str->size = initialSize;
	str->array = calloc(initialSize, sizeof(char));
	str->length = 0;
	return str;
}

void m_addc(m_string * str, char c) {
	if (str-> length + 1 > str->size) {
		str->array = realloc(
			str->array,
			sizeof(char) * (str->size = str->size * MONO_RESIZE_MUL)
		);
	}
	str->array[str->length++] = c;
}

void m_append_cstring(m_string * str, char * text, int length) {
	if (str->length + length > str->size) {
		str->array = realloc(
			str->array,
			sizeof(char) * (str->size = str->length + length)
		);
	}
	memcpy(str->array + str->length, text, length);
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

void m_delete_string(m_string * str) {
	free(str->array);
	free(str);
}

int m_string_pretty_print(m_string * str) {
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