#include "main_bonus.h"

int			is_door_pos(int x, int y, t_game *game)
{
	t_door_list	*list;

	list = game->data->door_list;
	while (list)
	{
		if (list->x == x && list->y == y)
			return (1);
		list = list->next;
	}
	return (0);
}

t_door_list	*create_door_list(int x, int y)
{
	t_door_list	*result;

	result = malloc(sizeof(t_door_list) * 1);
	result->x = x;
	result->y = y;
	result->next = 0;
	result->status = 0;
	return (result);
}

void		free_list(t_door_list *head)
{
	t_door_list	*pre;

	while (head)
	{
		pre = head;
		head = head->next;
		free(pre);
	}
}

void		add_list(t_door_list **head, t_door_list *new)
{
	t_door_list	*cur;

	cur = *head;
	if (!cur)
		*head = new;
	else
	{
		while ((cur)->next)
			cur = cur->next;
		cur->next = new;
	}
}