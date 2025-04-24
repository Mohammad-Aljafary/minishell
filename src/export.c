#include <minishell.h>

void	print_export_list(t_env *exp)
{
	while (exp)
	{
		if (exp->value && exp->value[0] != '\0')
			printf("export %s=\"%s\"\n", exp->key, exp->value);
		else
			printf("export %s\n", exp->key);
		exp = exp->next;
	}
}

int	check_valid_arg(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
	{
		ft_fprintf(2, "export: `%s': 1not a valid identifier\n", arg);
		return (1);
	}
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			ft_fprintf(2, "export: `%s': 2not a valid identifier\n", arg);
			return (1);
		}
		i++;
	}
	return (0);
}

int	split_key_value(char *arg, t_env **env, t_env **exp)
{
	char	*equal;
	char	*key;
	char	*value;
	t_env	*node;

	equal = ft_strchr(arg, '=');
	if (!equal)
		return (2);
	key = ft_substr(arg, 0, equal - arg);
	if (!key)
		return (1);
	if (equal + 1)
		value = ft_strdup(equal + 1);
	else
		value = ft_strdup("");
	if (!value)
	{
		free(key);
		return (1);
	}
	node = create_node_env(key, value);
	free(key);
	free(value);
	if (!node)
		return (1);
	add_node_env(env, node, node->key);
	add_node_env(exp, node, node->key);
	return (0);
}

void	ft_export(t_token *cmd, t_env **env, t_env **exp, int *exit_status)
{
	int		i;
	t_env	*node;
	int		ret;

	if (args_count(cmd->args) == 1)
	{
		print_export_list(*exp);
		*exit_status = 0;
		return ;
	}
	i = 1;
	*exit_status = 0;
	while (cmd->args[i])
	{
		if (check_valid_arg(cmd->args[i]))
		{
			*exit_status = 1;
			i++;
			continue ;
		}
		ret = split_key_value(cmd->args[i], env, exp);
		if (ret == 1)
            return ;
        else if (ret == 0)
        {
            i++;
            continue;
        }
		node = create_node_env(cmd->args[i], NULL);
		if (!node)
		{
			*exit_status = 1;
			return ;
		}
		add_node_env(exp, node, node->key);
		i++;
	}
}
