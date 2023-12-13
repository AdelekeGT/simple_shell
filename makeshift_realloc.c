#include "shell.h"

/**
 * makeshift_realloc - custom realloc function
 * @block: block passed in
 * @size: new size
 *
 * Return: new block of allocated memory
*/
void *makeshift_realloc(void *block, size_t size)
{
	void *new_block;
	size_t old_size, copy_size;

	if (block == NULL)
		return (malloc(size));

	if (size == 0)
	{
		free(block);
		return (NULL);
	}

	/* Allocate new block of memory */
	new_block = malloc(size);
	if (new_block == NULL)
		return (NULL);

	/* Copy data from the old block to the new block */
	old_size = (makeshift_strlen(block) + 1);
	copy_size = (size < old_size) ? size : old_size;
	makeshift_memcpy(new_block, block, copy_size);

	free(block);

	return (new_block);
}
