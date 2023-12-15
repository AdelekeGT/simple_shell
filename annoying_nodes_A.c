#include "shell.h"


/**
 * print_list_str - print list
 * @pointer: pointer to first n_node
 *
 * Return: list size
 */
size_t print_list_str(const sh_list *pointer)
{
	size_t _j = 0;

	while (pointer)
	{
		makeshift_printf(pointer->str ? pointer->str : "(nil)");
		makeshift_printf("\n");
		pointer = pointer->next;
		_j++;
	}
	return (_j);
}

/**
 * get_strings_from_list - gets an array of strings from list
 * @n_head: pointer to first n_node
 *
 * Return: array of strings
 */
char **get_strings_from_list(sh_list *n_head)
{
	size_t _k, j;
	sh_list *n_node = n_head;
	char **arr_string, *str;

	_k = length_of_list(n_head);

	if (n_head == NULL || _k == 0)
		return (NULL);

	arr_string = malloc(sizeof(char *) * (_k + 1));

	if (arr_string == NULL)
		return (NULL);

	for (_k = 0; n_node; n_node = n_node->next, _k++)
	{
		str = malloc(makeshift_strlen(n_node->str) + 1);
		if (str == NULL)
		{
			for (j = 0; j < _k; j++)
				free(arr_string[j]);

			free(arr_string);
			return (NULL);
		}

		str = makeshift_strcpy(str, n_node->str);
		arr_string[_k] = str;
	}

	arr_string[_k] = NULL;
	return (arr_string);
}

/**
 * remove_node_4_index - deletes n_node at some index
 * @n_head: pointer to first n_node
 * @index: index of n_node to delete
 *
 * Return: 1 on success, 0 otherwise
 */
int remove_node_4_index(sh_list **n_head, unsigned int index)
{
	sh_list *n_node, *node_before;
	unsigned int _j = 0;

	if (n_head == NULL || !*n_head)
		return (0);

	if (index == 0)
	{
		n_node = *n_head;
		*n_head = (*n_head)->next;
		free(n_node->str);
		free(n_node);
		return (1);
	}

	n_node = *n_head;

	while (n_node)
	{
		if (_j == index)
		{
			node_before->next = n_node->next;
			free(n_node->str);
			free(n_node);
			return (1);
		}
		_j++;

		node_before = n_node;
		n_node = n_node->next;
	}
	return (0);
}

/**
 * do_free_list - frees the nodes in a linked list
 * @the_head: pointer to n_node
 */
void do_free_list(sh_list **the_head)
{
	sh_list *n_node, *n_next, *n_head;

	if (the_head == NULL || *the_head == NULL)
		return;

	n_head = *the_head;
	n_node = n_head;

	while (n_node != NULL)
	{
		n_next = n_node->next;
		free(n_node->str);
		free(n_node);
		n_node = n_next;
	}

	*the_head = NULL;
}

/**
 * length_of_list - gets length of linked list
 * @n_h: pointer to first n_node
 *
 * Return: list size k
 */
size_t length_of_list(const sh_list *n_h)
{
	size_t _k = 0;

	while (n_h)
	{
		n_h = n_h->next;
		_k++;
	}

	return (_k);
}
