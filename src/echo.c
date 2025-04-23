#include <minishell.h>

int    ft_echo(t_token *cmd)
{
    int ne;
    int i;
    int j;

    ne = 1;
    i = 1;
    j = 2;
    if (cmd && cmd->args[i] && (ft_strncmp(cmd->args[i], "-n", 2) == 0 
        || ft_strncmp(cmd->args[i], "-en", 3) == 0))
    {
        while (cmd->args[i][j] && (cmd->args[i][j] == 'n' || cmd->args[i][j] == 'e'))
            j++;
        if (cmd->args[i][j] == '\0')
        {
            ne = 0;
            i = 2;
        }
    }
    while (cmd->args[i])
        printf("%s ", cmd->args[i++]);
    printf("\b");
    if (ne == 1)
        printf("\n");
    return (0);
}
