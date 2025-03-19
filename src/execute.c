#include <minishell.h>



void execute(t_token *node, t_env *envp)
{
    while (node)
    {
        
        if (node->type == command)
        {
                if (ft_strcmp(node->word, "exit") == 0)
                    exits(node->next->word);
                else if (ft_strcmp(node->word, "cd") == 0)
                {
                    if (!node->next)
                        cd(NULL, &envp);
                    else
                        cd(node->next->word, &envp);

                }
                else if (ft_strcmp(node->word, "pwd") == 0)
                    pwd();
                else if (ft_strcmp(node->word, "env") == 0)
                    env(envp);
                else if (ft_strcmp(node->word, "unset") == 0)
                    unset(node->next->word, &envp);
                else if (ft_strcmp(node->word, "export") == 0)
                    if(!export(node->next->word, &envp))
                        ft_fprintf(2,"syntax error");
        }
        node = node->next;
    }
}
