#include "shell.h"

/**
 * makeshift_memset - custom memset function
 * @n_ptr: pointer to string
 * @value: number of time
 * @n_num: size
 *
 * Return: prr
*/
void *makeshift_memset(void *n_ptr, int value, size_t n_num)
{
	size_t i;
	unsigned char uc_value;

	if (n_ptr == NULL)
		return (NULL);

	uc_value = (unsigned char)value;

	for (i = 0; i < n_num; ++i)
	{
		((unsigned char *)n_ptr)[i] = uc_value;
	}

	return (n_ptr);
}
