
#include <minishell.h>

t_token	*create(char *str)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->word = str;
	node->prev = NULL;
	node->next = NULL;
	node->type = not_defined;
	node->args = NULL;
	node->quotes = not_quoted;
	node->in_fd = 0;
	node->out_fd = 1;
	node->origin_in = -1;
	node->origin_out = -1;
	return (node);
}

void	add_back(t_token **list, t_token *new_node)
{
	t_token	*temp;

	temp = *list;
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
		new_node->prev = temp;
		new_node->next = NULL;
	}
	else
	{
		*list = new_node;
		(*list)->prev = NULL;
		(*list)->next = NULL;
	}
}

void	clear_list(t_token **list)
{
	t_token	*temp;

	while (*list)
	{
		temp = (*list);
		*list = (*list)->next;
		free(temp->word);
		temp->next = NULL;
		temp->prev = NULL;
		if(temp->type == command && temp->args)
			ft_free_split(temp->args);
		retrieve(temp);
		free(temp);
	}
}

void	delete_token(t_token **list, t_type type)
{
	t_token *lst;
	t_token *next;

	if (!list || !*list)
		return ;
	lst = *list;
	while (lst)
	{
		next = lst->next;
		if (lst->type == type)
		{
			if (lst->prev)
				lst->prev->next = lst->next;
			else
				*list = lst->next;
			if (lst->next)
				lst->next->prev = lst->prev;
			free(lst->word);
			free(lst);
		}
		lst = next;
	}
}

void	print_list(t_token *list)
{
	int	i;

	while (list)
	{
		printf("%s %d\n", list->word, list->type);
		if (list->type == command && list->args)
		{
			i = 0;
			while (list->args[i])
			{
				printf("  arg[%d]: %s\n", i, list->args[i]);
				i++;
			}
		}
		printf("\n");
		list = list->next;
	}
}

