#include "shell.h"

/**
 * print_list - prints all elements of a sh_list linked list
 * @n_h: pointer to first n_node
 *
 * Return: list size
 */
size_t print_list(const sh_list *n_h)
{
	size_t _k = 0;
	char *number, *e_msg;

	number = makeshift_itoa(n_h->num);
	e_msg = n_h->str ? n_h->str : "(nil)";

	while (n_h)
	{
		makeshift_printf(number);
		makeshift_printf(": ");
		makeshift_printf(e_msg);
		makeshift_printf("\n");

		n_h = n_h->next;
		_k++;
	}

	return (_k);
}

/**
 * put_node - adds a n_node to beginning of the list
 * @n_head: pointer to n_head n_node
 * @str: str member of node struct
 * @num: index of node
 *
 * Return: list size
 */
sh_list *put_node(sh_list **n_head, const char *str, int num)
{
	sh_list *created_head_node;

	if (n_head == NULL)
		return (NULL);

	created_head_node = malloc(sizeof(sh_list));

	if (created_head_node == NULL)
		return (NULL);

	makeshift_memset((void *)created_head_node, 0, sizeof(sh_list));

	created_head_node->num = num;

	if (str != NULL)
	{
		created_head_node->str = makeshift_strdup(str);
		if (!created_head_node->str)
		{
			free(created_head_node);
			return (NULL);
		}
	}

	created_head_node->next = *n_head;
	*n_head = created_head_node;

	return (created_head_node);
}

/**
 * put_node_4_end - adds a n_node to the end of the list
 * @n_head: pointer to n_head n_node
 * @str: string field of node
 * @num: index of node
 *
 * Return: list size
 */
sh_list *put_node_4_end(sh_list **n_head, const char *str, int num)
{
	sh_list *new_node, *n_node;

	if (n_head == NULL)
		return (NULL);

	n_node = *n_head;

	new_node = malloc(sizeof(sh_list));

	if (new_node == NULL)
		return (NULL);

	makeshift_memset((void *)new_node, 0, sizeof(sh_list));

	new_node->num = num;

	if (str != NULL)
	{
		new_node->str = makeshift_strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (n_node)
	{
		while (n_node->next)
			n_node = n_node->next;
		n_node->next = new_node;
	}
	else
		*n_head = new_node;

	return (new_node);
}

/**
 * get_node_index - gets the index of a n_node
 * @n_head: pointer to list n_head
 * @n_node: pointer to the n_node
 *
 * Return: index of n_node; -1 otherwise
 */
ssize_t get_node_index(sh_list *n_head, sh_list *n_node)
{
	size_t _k = 0;

	while (n_head != NULL)
	{
		if (n_head == n_node)
			return (_k);

		n_head = n_head->next;
		_k++;
	}

	return (-1);
}

/**
 * commencement_of_node - returns n_node whose string starts with prefix
 * @n_node: pointer to list n_head
 * @prefix: string to match
 * @chr: character that follows n_node and matches
 *
 * Return: create a match
 */
sh_list *commencement_of_node(sh_list *n_node, char *prefix, char chr)
{
	char *p = NULL;

	while (n_node)
	{
		p = starts_with(n_node->str, prefix);
		if (p && ((chr == -1) || (*p == chr)))
			return (n_node);
		n_node = n_node->next;
	}
	return (NULL);
}
