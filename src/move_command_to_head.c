# include <minishell.h>

void	reorder_command(t_token **head, t_token *start, t_token *cmd)
{
	if (cmd->prev)
		cmd->prev->next = cmd->next;
	if (cmd->next)
		cmd->next->prev = cmd->prev;
	cmd->prev = start->prev;
	cmd->next = start;
	if (start->prev)
		start->prev->next = cmd;
	start->prev = cmd;
	if (*head == start)
		*head = cmd;
}

t_token	*get_command_node(t_token *start, t_token **pipe)
{
	t_token *cmd;

	cmd = NULL;
	*pipe = start;
	while (*pipe && (*pipe)->type != pipes)
	{
		if ((*pipe)->type == command && !cmd)
			cmd = *pipe;
		*pipe = (*pipe)->next;
	}
	return (cmd);
}

void	move_command_to_front(t_token **head)
{
	t_token *node;
	t_token *start;
	t_token *cmd;
	t_token *pipe;

	node = *head;
	while (node)
	{
		start = node;
		cmd = get_command_node(start, &pipe);
		if (cmd && cmd != start)
			reorder_command(head, start, cmd);
		if (pipe)
            node = pipe->next;
        else
            node = NULL;
	}
}

