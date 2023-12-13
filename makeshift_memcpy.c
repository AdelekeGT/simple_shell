#include "shell.h"

/**
 * makeshift_memcpy - custom memcpy function
 * @destination: the block that receives the element to be copied
 * @source: the string to be copied
 * @n: size
 *
 * Return: void pointer
*/
void *makeshift_memcpy(void *destination, const void *source, unsigned int n)
{
	unsigned char *d;
	const unsigned char *s;

	if (destination == NULL || source == NULL)
		return (NULL);

	d = (unsigned char *)destination;
	s = (const unsigned char *)source;

	if (d < s || d >= s + n)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d += n;
		s += n;
		while (n--)
			*(--d) = *(--s);
	}

	return (destination);
}
