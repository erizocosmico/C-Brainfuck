#include <stdio.h>
#include <stdlib.h>
#define FILE_MAX_SIZE_CHARS 30000
#define ERR_NONE 0
#define ERR_MAX_SIZE_CHARS_EXCEEDED 1

int is_file(const char* input);
void execute_instruction(char c, char** ptr, unsigned long* i, const char* input);
void execute(const char* input);

int main(int argc, char** argv)
{
	char *input = malloc(sizeof(char) * FILE_MAX_SIZE_CHARS), c;
	FILE* file;
	unsigned long i = 0L;
	int output = ERR_NONE, j = 0;
	if (argc == 2)
	{
		while (argv[1][j++] != 0x0)
			input[j - 1] = argv[1][j - 1];
		input[j - 1] = 0x0;
		if (is_file((const char*) input))
		{
			file = fopen(input, "r");
			if (file != NULL)
			{
				input = malloc(FILE_MAX_SIZE_CHARS * sizeof(char));
				while ((c = fgetc(file)) != EOF)
					input[i++] = c;
				if (i >= FILE_MAX_SIZE_CHARS)
					output = ERR_MAX_SIZE_CHARS_EXCEEDED;
				input[i] = 0x0;
			}
			else
				printf("Error: File %s is empty.", input);
		}
		if (output == ERR_NONE)
			execute((const char*) input);
		else
			printf("Error: Max character size allowed is 30000.");
	}
	else
		printf("Error: No input file given.");
	free(input);
	return 0;
}

int is_file(const char* input)
{
	return (input[0] == 0x3E || input[0] == 0x3C || input[0] == 0x2B || input[0] == 0x2D || input[0] == 0x2C || input[0] == 0x2E || input[0] == 0x5B || input[0] == 0x5D) ? 0 : 1;
}

void execute(const char* input)
{
	char c, *mem = calloc(FILE_MAX_SIZE_CHARS, sizeof(char));
	char* ptr = mem;
	unsigned long i = 0L;
	while ((c = input[i++]) != 0x0)
		execute_instruction(c, &ptr, &i, input);
	free(mem);
}

void execute_instruction(char c, char** ptr, unsigned long* i, const char* input)
{
	int depth = 0, loop_depth;
	unsigned long prev_pos;
	char ch;
	switch (c)
	{
		case 0x3E: (*ptr)++; break;
		case 0x3C: (*ptr)--; break;
		case 0x2B: (**ptr)++; break;
		case 0x2D: (**ptr)--; break;
		case 0x2E: putchar(**ptr); break;
		case 0x2C:
		{
			**ptr = 0x0;
			while (**ptr == 0x0)
				**ptr = getchar();
		}
		break;
		case 0x5B:
		{
			depth++;
			loop_depth = depth;
			prev_pos = *i;
			while (**ptr)
			{
				while ((ch = input[*i]) != 0x0 && depth > 0)
				{
					(*i)++;
					execute_instruction(ch, ptr, i, input);
					if (ch == 0x5D)
						depth--;
				}
				if (ch == '=')
					break;
				if (!depth && **ptr)
				{
					*i = prev_pos;
					depth++;
				}
			}
		}
		break;
	}
}
