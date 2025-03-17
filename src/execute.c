#include <minishell.h>



void execute(t_token *node, t_env *envp)
{
    while (node)
    {
        
        if (node->type == command)
        {
            // إذا كان الأمر ليس داخليًا
                if (ft_strcmp(node->word, "echo") == 0)
                    ft_echo(&node->next->word);
                else if (ft_strcmp(node->word, "exit") == 0)
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
        }
        node = node->next;
    }
}
