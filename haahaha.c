#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void	heredoc_to_command(const char *delimiter, const char *command)
{
	int		pipe_fd[2];
	char	buffer[BUFFER_SIZE];
	pid_t	pid;
	ssize_t	bytes_read;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		// Child process: execute command with piped input
		close(pipe_fd[1]);              // Close write end
		dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to read end
		close(pipe_fd[0]);
		execlp(command, command, NULL); // Execute command
		perror("execlp");               // If exec fails
		exit(EXIT_FAILURE);
	}
	else
	{
		// Parent process: read input and write to pipe
		close(pipe_fd[0]); // Close read end
		printf("Entering heredoc mode. Type '%s' to stop.\n", delimiter);
		while (1)
		{
			printf("> ");
			bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
			if (bytes_read <= 0)
				break ;
			buffer[bytes_read] = '\0';
			// Check if the last entered line matches the delimiter
			if (strncmp(buffer, delimiter, strlen(delimiter)) == 0
				&& buffer[strlen(delimiter)] == '\n')
				break ;
			write(pipe_fd[1], buffer, bytes_read);
		}
		close(pipe_fd[1]); // Close write end
		wait(NULL);        // Wait for child process to finish
	}
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <delimiter> <command>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	heredoc_to_command(argv[1], argv[2]);
	return (EXIT_SUCCESS);
}
