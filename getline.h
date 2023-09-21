#ifndef _GETLINE_H_
#define _GETLINE_H_

#include <unistd.h>
#include <stdlib.h>
#define BUFFER_SIZE 2048

/**
 * struct buff - buffer struct
 * @buffer: buffer
 * @next: pointer to the next value
 * @left_proc: remaining values to process
 */
typedef struct buff
{
	char buffer[BUFFER_SIZE];
	char *next;
	size_t left_proc;
} buff_s;

#define BUFF_TABLE_SIZE 127

/**
 * struct buff_hash_table - buffer hash table
 * @fd: file descriptor
 * @buf: associated buffer
 * @next: pointer to the next value chain
 */
typedef struct buff_hash_table
{
	int fd;
	struct buff buf;
	struct buff_hash_table *next;
} buff_hash_table_t;

typedef buff_hash_table_t *buf_node_table[BUFF_TABLE_SIZE];

/**GETLINE PROTOTYPES**/
char *my_getline(const int fd);
#endif /*GETLINE_H*/
