#include <minishell.h>

int	count_args(char **args)
{
	int	i;

	i = 0;
	while(args[i])
		i++;
	return (i);
}

int	is_built_in(t_token *cmd)
{
	if (!ft_strcmp(cmd->word, "export") || !ft_strcmp(cmd->word, "echo")
		|| !ft_strcmp(cmd->word, "cd") || !ft_strcmp(cmd->word, "pwd")
		|| !ft_strcmp(cmd->word, "exit") || !ft_strcmp(cmd->word, "unset")
		|| !ft_strcmp(cmd->word, "env"))
			return (1);
	return (0);
}

void	run_built_in(t_token *cmd, int *exit_status, t_env *env, int in_child)
{
	if (!ft_strcmp(cmd->word, "export"))
		*exit_status = ft_export(cmd, env);
	else if (!ft_strcmp(cmd->word, "echo"))
		*exit_status = ft_echo(cmd);
	else if (!ft_strcmp(cmd->word, "cd"))
		*exit_status = ft_cd(cmd, &env);
	else if (!ft_strcmp(cmd->word, "pwd"))
		*exit_status = ft_pwd();
	else if (!ft_strcmp(cmd->word, "exit"))
		*exit_status = ft_exit(cmd);
	else if (!ft_strcmp(cmd->word, "unset"))
		*exit_status = ft_unset(cmd, env/*, export_list*/);
	else if (!ft_strcmp(cmd->word, "env"))
		*exit_status = ft_env(cmd, env);
	if (in_child)
		exit(*exit_status);
}

/*  int	export(t_token *str, t_env **env)
{
 	char	*equal;
	char	*temp;
	t_env	*node;
	int		i;

	i = 0;
	if(!str)
	{
		print_env_export(*env);
		return(2);
	}
	if(ft_isdigit(str->word[0]))
	{
		ft_fprintf(2, "export: `%s': not a valid identifier\n", str->word);
			return (2);
	}
	equal = ft_strchr(str->word, '=');
	if (!equal)
	{
		if (str->word[0])
		{
			while(ft_isalnum(str->word[i]))
				i++;
		}
		if(!(str->next))
		{
			if(str->word[i] == '\0')
			{
				//hereeee
				return (0);
			}
		}
		else if ((str->next->word[0] == '=') && !str->word[i])
		{
			ft_fprintf(2, "export: `%s': not a valid identifier\n", str->next->word);
			return (2);
		}
		ft_fprintf(2, "export: `%s': not a valid identifier\n", str->word);
		return (2);
	}
	while(ft_isalnum(str->word[i]) && str->word[i] != '=')
			i++;
	if(str->word[i] != '\0' && str->word[i] != '=')
	{
		ft_fprintf(2, "export: `%s': not a valid identifier\n", str->word);
		return (2);
	}
	temp = ft_substr(str->word, 0, equal - str->word);
	if (!temp || !temp[0])
		return (1);
	char*	value = ft_strdup(equal + 1);
	if (!value || !value[0])
	return (1);
		i = 0;
		while (ft_isalnum(temp[i]) && temp[i] != '\0')
			i++;
		if (temp[i] != '\0')
		{
			ft_fprintf(2, "export: `%s': not a valid identifier\n", str->word);
			free(temp);
			free(value);
			return (2);
		}
		node = create_node_env(temp, value);
		add_node_env(env, node, temp);
		free(temp);
		free(value);
		return (1);
}  */