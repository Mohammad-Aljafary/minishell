#include <minishell.h>

void	create_list_env(t_env **list, char **envp)
{
	int		i;
	char	**str;
	t_env	*node;

	i = -1;
	while (envp[++i])
	{
		str = ft_split(envp[i], '=');
		if (str && str[0])
		{
			if (str[1])
				node = create_node_env(str[0], str[1]);
			else
				node = create_node_env(str[0], "");
			if (!node)
			{
				clear_list_env(list);
				ft_free_split(str);
				return ;
			}
			add_back_env(list, node);
		}
		ft_free_split(str);
	}
}

void	create_list_exp(t_env *env, t_env **exp)
{
	t_env	*node;

	node = NULL;
	while (env)
	{
		if (env->value)
			node = create_node_env(env->key, env->value);
		else
			node = create_node_env(env->key, "");
		if (!node)
		{
			clear_list_env(exp);
			return ;
		}
		add_back_env(exp, node);
		env = env->next;
	}
}
