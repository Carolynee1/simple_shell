#include "shell.h"

/**
 * main - Caro simple shell
 * Description: Simple shell v1 by Caro and co
 *
 * Return: Alway 0.
 *
 **/

int main(void)
{
	char my_cmd[MAX_LENGTH];
	char *args[MAX_LENGTH / 2 + 1];
	int cmd_sta = 1;
	int i = 0;
	int pid = 0;

	while (cmd_sta)
	{
		printf("Caro_Shell> ");
		fflush(stdout);

		fgets(my_cmd, MAX_LENGTH, stdin);

		args[i] = strtok(my_cmd, " \n");
		while (args[i] != NULL)
		{
			i++;
			args[i] = strtok(NULL, " \n");
		}

		if (pid == 0)
		{
			/* Child process */
			execvp(args[0], args);
			printf("Invalid command\n");
			exit(0);
		} else if (pid < 0)
		{
			/* Error occurred */
			printf("Fork failed\n");
			exit(1);
		} else
		{
			/* Parent process */
			wait(NULL);
		}
	}

	return (0);
}
