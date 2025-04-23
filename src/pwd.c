#include <minishell.h>

int ft_pwd(void)
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
