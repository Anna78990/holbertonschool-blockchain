#include "cli.h"
#include "blockchain.h"

int cli(info_t *info, char **av);


/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = {NULL, NULL, 0, 0, 0, 0, NULL, 0, 0, NULL};
	blockchain_data_t blockchain_data[] = {NULL, NULL, NULL};

	blockchain_data->key = ec_create();
	blockchain_data->blockchain = blockchain_create();
	blockchain_data->tx_pool = llist_create(MT_SUPPORT_TRUE);
	if (!blockchain_data->key || !blockchain_data->blockchain ||
		!blockchain_data->tx_pool)
		exit(1);

	info->blockchain_data = blockchain_data;
	cli(info, av);
	return (EXIT_SUCCESS);
	(void)ac;
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;

	//printf("info->argv[0] is %s\n", info->argv[0]);
	//printf("length of info->argv[0] is %ld\n", strlen(info->argv[0]));
	//printf("length of info->argv[0][lasr] is %d\n", info->argv[0][(strlen(info->argv[0]) - 1)]);
	if (strcmp(info->argv[0], "wallet_save\n") == 0)
		wallet_save(info);
	if (strcmp(info->argv[0], "wallet_load\n") == 0)
		cmd_wallet_load(info);
	if (strcmp(info->argv[0], "quit\n") == 0 || strcmp(info->argv[0], "q\n") == 0)
		exit(0);
	if (strcmp(info->argv[0], "send\n") == 0 && info->argc == 3)
		cmd_send(info);
	return (built_in_ret);
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *info, char **av, char *r)
{
	char *cmd = NULL;

	info->fname = av[0];
	if (!av)
		return;

	info->fname = av[0];
	cmd = strtok(r, " \t");
	printf("cmd is %s\n", cmd);
	info->argv = malloc(sizeof(char *) * 2);
	if (info->argv)
	{
		info->argv[0] = strdup(cmd);
		info->argc = 1;
	}
	while (cmd = strtok(NULL, " \t"))
	{
		info->argv[info->argc++] = cmd;
	}
	info->argv[info->argc] = NULL;
}


/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
	int i;

	for (i = 0; info->argv[i]; i++);
		free(info->argv[i]);

	info->argv = NULL;
	if (all)
	{
		EC_KEY_free(info->blockchain_data->key);
		blockchain_destroy(info->blockchain_data->blockchain);
		llist_destroy(info->blockchain_data->tx_pool, 1,
			(node_dtor_t)transaction_destroy);
		free(info->arg);
		if (info->readfd > 2)
			close(info->readfd);
	}
}

/**
 * cli - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int cli(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;
	char *buffer = NULL;
	ssize_t size = 0;

	setbuf(stdout, NULL);
	while (r != -1 && builtin_ret != -2)
	{
		info->arg = NULL, info->argv = NULL, info->argc = 0;
		if (isatty(STDIN_FILENO))
			printf("> ");
		r = getline(&buffer, &size, stdin);
		if (r != -1)
		{
			set_info(info, av, buffer);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				printf("No such command. Try 'help'.\n");
		}
		else if (isatty(STDIN_FILENO))
			putchar('\n');
		free_info(info, 0);
	}
	free_info(info, 1);
	if (!isatty(STDIN_FILENO) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}