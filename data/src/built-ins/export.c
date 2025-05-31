/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:37:42 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/05/08 07:37:43 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	handle_export_no_args(t_env **exp, int *exit_status)
{
	print_export_list(*exp);
	*exit_status = 0;
}

static int	process_export_arg(char *arg, t_env **env, t_env **exp)
{
	t_env	*node;
	int		ret;

	if (check_valid_arg(arg))
		return (1);
	ret = split_key_value(arg, env, exp);
	if (ret == 1)
		return (-1);
	else if (ret == 0)
		return (0);
	node = create_node_env(arg, NULL);
	if (!node)
		return (-1);
	add_node_env(exp, node, node->key);
	return (0);
}

void	ft_export(t_token *cmd, t_env **env, t_env **exp, int *exit_status)
{
	int	i;
	int	ret;

	if (args_count(cmd->args) == 1)
	{
		handle_export_no_args(exp, exit_status);
		return ;
	}
	*exit_status = 0;
	i = 1;
	while (cmd->args[i])
	{
		ret = process_export_arg(cmd->args[i], env, exp);
		if (ret == 1)
			*exit_status = 1;
		else if (ret == -1)
		{
			*exit_status = 1;
			return ;
		}
		i++;
	}
}
