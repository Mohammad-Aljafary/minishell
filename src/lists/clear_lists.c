#include <minishell.h>

void	clear_all(t_all *all)
{
	if (all->tok_lst)
		clear_list(&all->tok_lst);
	if (all->env_lst)
		clear_list_env(&all->env_lst);
	if (all->exp_lst)
		clear_list_env(&all->exp_lst);
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
		if (temp->type == COMMAND && temp->args)
			ft_free_split(temp->args);
		retrieve(temp);
		free(temp);
	}
}

void	clear_list_env(t_env **list)
{
	t_env	*temp;

	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

int	free_return(t_token **p)
{
	clear_list(p);
	return (0);
}
