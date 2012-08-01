#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct code_struct {
	int length;
	int next;
	char *data;
} Code;

Code *init_code ();
void add_char (Code *code, char c);
void expand (Code *code);
#define MEM_SIZE 30000
typedef struct mem_struct {
	int dp;
	char data[MEM_SIZE];
} Memory;

Memory *init_mem();
void inc_cell (Memory *mem);
void dec_cell (Memory *mem);
void inc_dp (Memory *mem);
void dec_dp (Memory *mem);
char get_cell (Memory *mem);
void set_cell (Memory *mem, char c);

int interpret (Code *code, int ip, Memory *mem);

void dump (Memory *mem, int n);

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		return 1;
	}
	Code *code = init_code();
	char *file_name = argv[1];
	FILE *f = fopen(file_name, "r");
	char c;
	char allowed[] = "+-.,><[]";
	while (1)
	{
		c = fgetc(f);
		if (feof(f))
		{
			break;
		}
		if (strchr(allowed, c) != NULL)
		{
			add_char(code, c);
		}
	}
	code->next = 0;
	Memory *mem = init_mem();
	interpret(code, 0, mem);
	dump(mem, 5);
	return 0;
}

Code *init_code ()
{
	Code *code = malloc(sizeof(Code));
	code->length = 256;
	code->next = 0;
	code->data = calloc(code->length, sizeof(char));
	return code;
}

void add_char (Code *code, char c)
{
	if (code->next == code->length - 1)
	{
		expand(code);
	}
	code->data[code->next] = c;
	code->next++;
}

void expand (Code *code)
{
	char *new_data = calloc(code->length * 2, sizeof(char));
	strncpy(new_data, code->data, code->length);
	free(code->data);
	code->data = new_data;
}

Memory *init_mem()
{
	Memory *mem = malloc(sizeof(Memory));
	if (mem == NULL)
	{
		puts("Memory error");
		exit(1);
	}
	mem->dp = 0;
	memset(mem->data, 0, MEM_SIZE);
	return mem;
}
/*
void inc_cell (Memory *mem)
void dec_cell (Memory *mem);
void inc_dp (Memory *mem);
void dec_dp (Memory *mem);
char get_cell (Memory *mem);
void set_cell (Memory *mem, char c);
*/

int interpret (Code *code, int ip, Memory *mem)
{
	int new_ip;
	while (code->data[ip])
	{
		switch (code->data[ip])
		{
			case '+':
				mem->data[mem->dp]++;
				break;
			case '-':
				mem->data[mem->dp]--;
				break;
			case '.':
				putchar(mem->data[mem->dp]);
				break;
			case ',':
				mem->data[mem->dp] = getchar();
				break;
			case '>':
				mem->dp = (mem->dp + 1) % MEM_SIZE;
				if (mem->dp >= MEM_SIZE)
				{
					puts("DP incremented past memory");
					exit(1);
				}
				break;
			case '<':
				mem->dp = (mem->dp - 1 + MEM_SIZE) % MEM_SIZE;
				if (mem->dp < 0)
				{
					puts("DP decremented past memory");
				}
				break;
			case '[':
				while (mem->data[mem->dp])
				{
					new_ip = interpret(code, ip + 1, mem);
				}
				ip = new_ip;
				break;
			case ']':
				return ip;
				break;
			default:
				break;
		}
		ip++;
	}
	return ip;
}

void dump (Memory *mem, int n)
{
	printf("DP: %d\n", mem->dp);
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%02x", mem->data[i]);
	}
	puts("");
}
