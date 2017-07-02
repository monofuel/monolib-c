#define MONO_DEBUG true

#include "../src/index.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define STRING_BUFF_SIZE 50

void testStrings() {
	printf("testing strings\n");
	printf("testing adding characters\n");
	m_string * str = m_new_string(5);
	assert(str->length == 0);
	for (int i = 0; i < 10; i++) {
		m_addc(str, 'a');
	}

	char text[STRING_BUFF_SIZE];
	assert(m_get_cstring(str, text, STRING_BUFF_SIZE) == 0);
	assert(strcmp("aaaaaaaaaa", text) == 0);
	assert(str->length == 10);
	assert(str->size == 10);
	m_str_pretty_print(str);	

	m_addc(str, 'b');
	assert(m_get_cstring(str, text, STRING_BUFF_SIZE) == 0);
	assert(strcmp("aaaaaaaaaab", text) == 0);
	assert(str->length == 11);
	assert(str->size > 10);
	m_str_pretty_print(str);

	printf("cleaning up\n");
	m_delete_string(str);

	printf("testing joining strings\n");
	memset(text, 0, STRING_BUFF_SIZE);
	str = m_new_string(5);
		for (int i = 0; i < 5; i++) {
		m_addc(str, 'a');
	}

	m_append_cstring(str, "bbbbb", 5);
	assert(m_get_cstring(str, text, 50) == 0);
	assert(strcmp("aaaaabbbbb", text) == 0);
	assert(str->length == 10);
	assert(str->size == 10);
	m_str_pretty_print(str);	

	printf("cleaning up\n");
	m_delete_string(str);
}

void testMap() {
	printf("testing map\n");
	m_map* map = m_new_map(10);
	printf("cleaning up\n");
	m_delete_map(map);
}

void testVec() {
	printf("testing vec\n");
	m_vec* vec = m_new_vec(10, sizeof(int), 0);
	m_pretty_print(vec);
	for (int i = 0; i < 15; i++) {
		m_push(vec,(void *) &i);
	}
	m_pretty_print(vec);
	assert(vec->length == 15);
	assert(vec->size > 15);
	for (int i = 0; i < 15; i++) {
		int val = 0;
		m_get(vec,(void *) &val,i);
		assert(val == i);
	}

	m_vec* vec2 = m_new_vec(10, sizeof(int), 0);

	for (int i = 0; i < 20; i++) {
		m_push(vec2,(void *) &i);
	}

	assert(m_append(vec, vec2) == 0);
	m_pretty_print(vec);
	for (int i = 0; i < 15; i++) {
		int val = 0;
		assert(m_get(vec,(void *) &val, i) == 0);
		assert(val == i);

		assert(m_get(vec,(void *) &val, i + 15) == 0);
		assert(val == i);
	}

	printf("cleaning up\n");
	m_delete_vec(vec);
	m_delete_vec(vec2);
}

void testList() {
	printf("testing list\n");
	m_list* list = m_new_list();
	printf("cleaning up\n");
	m_delete_list(list);
}

void testJSON() {

}

int main(int argc, char * argv[]) {
	printf("=======================\n");
	printf("tests starting\n");
	printf("=======================\n");
	testStrings();
	testMap();
	testVec();
	printf("=======================\n");
	printf("tests complete\n");
	printf("=======================\n");
}