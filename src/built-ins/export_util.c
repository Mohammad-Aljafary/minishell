#include <minishell.h>

void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

int	add_to_export(char **key, char **value, t_env **env, t_env **exp)
{
	t_env	*node1;
	t_env	*node2;

	node1 = create_node_env(*key, *value);
	node2 = create_node_env(*key, *value);
	free(*key);
	free(*value);
	if (!node1 || !node2)
	{
		if (node1)
			free_env_node(node1);
		if (node2)
			free_env_node(node2);
		return (1);
	}
	add_node_env(env, node1, node1->key);
	add_node_env(exp, node2, node2->key);
	return (0);
}

int	split_key_value(char *arg, t_env **env, t_env **exp)
{
	char	*equal;
	char	*key;
	char	*value;

	equal = ft_strchr(arg, '=');
	if (!equal)
		return (2);
	key = ft_substr(arg, 0, equal - arg);
	if (!key)
		return (1);
	if (*(++equal) != '\0')
		value = ft_strdup(equal);
	else
		value = ft_strdup("");
	if (!value)
	{
		free(key);
		return (1);
	}
	if (add_to_export(&key, &value, env, exp))
		return (1);
	return (0);
}
