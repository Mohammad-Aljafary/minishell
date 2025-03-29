
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
		if(temp->type == command)
			ft_free_split(temp->args);
		free(temp);
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

