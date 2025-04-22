#include <minishell.h>

int    ft_echo(t_token *cmd)
{
    int ne;
    int i;
    int j;

    ne = 1;
    i = 1;
    j = 2;
    if (cmd && ft_strncmp(cmd->args[2], "-n", 2) == 0)
    {
        while (cmd->args[2][j] == 'n' || cmd->args[2][j] == 'e')
            j++;
        if (cmd->args[2][j] == '\0')
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
