
#include <minishell.h>

int	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror(NULL);
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}

int	cd(char *path, t_env **env)
{
	char	*current;
	t_env	*node;

	node = *env;
	if (path == NULL)
		path = search_env(node, "HOME");
	current = getcwd(NULL, 0);
	if (!current)
	{
		perror(NULL);
		return (1);
	}
	if (chdir(path) == -1)
	{
		perror(path);
		return (1);
	}
	while (node)
	{
		if (ft_strcmp(node->key, "OLDPWD") == 0)
			break ;
		node = node->next;
	}
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(current);
		free(current);
	}
	node = *env;
	while (node)
	{
		if (ft_strcmp(node->key, "PWD") == 0)
			break ;
		node = node->next;
	}
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(path);
	}
	return (0);
}

void	exits(char *str)
{
	int	n;
	int	i;

	i = 0;
	n = ft_atoi(str);
	if (n < 0)
		i = 1;
	printf("exit\n");
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_fprintf(2, "%s: numeric argument required\n", str);
			exit(2);
		}
		i++;
	}
	while (n >= 256)
		n = n - 256;
	while (n < 0)
		n = n + 256;
	exit(n);
}

void	unset(char *str, t_env **env)
{
	delete_node_env(env, str);
}

void ft_echo(t_token *args)
{
    int ne = 1;
    if (args && ft_strcmp(args->word, "-n") == 0)
    {
        ne= 0;
        args = args->next;
    }
    while (args)
    {
        printf("%s", args->word);
        args = args->next;
    }
    if (ne == 1)
        printf("\n");
}

 int	export(t_token *str, t_env **env)
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
} 

/* int	export(t_token *str, t_env **env)
{
	char	*equal;
	char	*key;
	char	*value;
	t_env	*node;

	equal = ft_strchr(str->word, '=');

	// If '=' is missing, print an error
	if (!equal)
	{
		ft_fprintf(2, "export: `%s': not a valid identifier\n", str->word);
		return (0);
	}


	key = ft_substr(str->word, 0, equal - str->word);
	value = ft_strdup(equal + 1);
	node = create_node_env(key, value);
	add_node_env(env, node, key);
	free(key);
	free(value);
	return (1);
} */

/* int main(int argc, char **argv, char **envp)
{
	int		pwdd;
	t_env	*env;

	env = NULL;
	create_list_env(&env, envp);
	pwdd = pwd();
	cd(NULL, &env);
	pwd();
	exits("2aa");
	if (pwdd)
		return (1);
	return (0);
}  */
