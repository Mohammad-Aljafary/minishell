#include <minishell.h>

int pwd()
{
    char    *path;

    path = getcwd(NULL, 0);
    if (!path)
    {
        perror(NULL);
        return (1);
    }
    printf("%s\n", path);
    free (path);
    return (0);
}

int cd(char *path)
{
    int valid_dir;

    valid_dir = chdir(path);
    if (valid_dir == -1)
    {
        perror(path);
        return (1);
    }
    return (0);
}

void    exits(int n)
{
    exit(n);
}  

int main()
{
    int pwdd;

    pwdd = pwd();
    cd("../");
    pwd();
    exits(127);
    if (pwdd)
        return (1);
    return (0);
} 