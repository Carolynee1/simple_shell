#include "shell.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_HISTORY_SIZE 10
#define HISTORY_FILE "history.txt"

typedef struct
{
	char history[MAX_HISTORY_SIZE][MAX_COMMAND_LENGTH];
	int count;
} History;

void write_history(history *history)
{
	FILE *file = fopen(HISTORY_FILE, "w");
	int i;

	if (file == NULL)
	{
		fprintf(stderr, "Error: Unable to open history file for writing.\n");
		return;
	}

	for (i = 0; i < history->count; i++)
	{
		fprintf(file, "%s\n", history->history[i]);
	}

	fclose(file);
}

void read_history(history *history);
{
	FILE *file = fopen(HISTORY_FILE, "r");
	int line_count = 0;
	char line[MAX_COMMAND_LENGTH];

	if (file == NULL)
	{
		fprintf(stderr, "Error: Unable to open history file for reading.\n");
		return;
	}

	while (fgets(line, sizeof(line), file) != NULL && line_count < MAX_HISTORY_SIZE)
	{
		line[strcspn(line, "\n")] = '\0';
		strncpy(history->history[line_count], line, MAX_COMMAND_LENGTH);
		line_count++;
	}

	fclose(file);
	history->nclude "shell.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_HISTORY_SIZE 10
#define HISTORY_FILE "history.txt"

		typedef struct

		{
			char history[MAX_HISTORY_SIZE][MAX_COMMAND_LENGTH];
			int count;
		} History;

	void write_history(history *history)
	{
		FILE *file = fopen(HISTORY_FILE, "w");
		int i;

		if (file == NULL)
		{
			fprintf(stderr, "Error: Unable to open history file for writing.\n");
			return;
		}

		for (i = 0; i < history->count; i++)
		{
			fprintf(file, "%s\n", history->history[i]);
		}

		fclose(file);
	}

	void read_history(history *history);
	{
		FILE *file = fopen(HISTORY_FILE, "r");
		int line_count = 0;
		char line[MAX_COMMAND_LENGTH];

		if (file == NULL)
		{
			fprintf(stderr, "Error: Unable to open history file for reading.\n");
			return;
		}

		while (fgets(line, sizeof(line), file) != NULL && line_count < MAX_HISTORY_SIZE)
		{
			line[strcspn(line, "\n")] = '\0';
			strncpy(history->history[line_count], line, MAX_COMMAND_LENGTH);
			line_count++;
		}

		fclose(file);
		history->count = line_count;
	}

	int main(void)

	{
		History history;

		history.count = 0;

		read_history(&history);
		write_history(&history);

		return (0);
	} count = line_count;
}

int main(void)
{
	History history;

	history.count = 0;


	read_history(&history);
	write_history(&history);

	return (0);
}
