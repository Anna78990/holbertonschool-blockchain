#include "cli.h"
#include "blockchain.h"

int cli(info_t *info, char **av);


/**
 * main - entry point
 * @argc: number of args
 * @argv: argv
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	info_t info[] = {{NULL, NULL, 0, 0, 0, 0, NULL, 0, 0, NULL}};
	blockchain_data_t blockchain_data[] = {{NULL, NULL, NULL}};

	blockchain_data->key = ec_create();
	blockchain_data->blockchain = blockchain_create();
	blockchain_data->tx_pool = llist_create(MT_SUPPORT_TRUE);
	if (!blockchain_data->key || !blockchain_data->blockchain ||
		!blockchain_data->tx_pool)
		exit(1);

	info->blockchain_data = blockchain_data;
	cli(info, argv);
	return (EXIT_SUCCESS);
	(void)argc;
}

/**
 * find_command - finds a command
 * @info: the parameter & return info struct
 *
 * Return: -1 if command not found, 0 if executed successfully,
 */
int find_command(info_t *info)
{
	int ret = -1;

	/* printf("info->argv[0] is %s\n", info->argv[0]); */
	/* printf("length of info->argv[0] is %ld\n", strlen(info->argv[0])); */
	/**
	 * printf("length of info->argv[0][lasr] is %d\n",
	 * info->argv[0][(strlen(info->argv[0]) - 1)]);
	 */
	if (strcmp(info->argv[0], "wallet_save") == 0)
		wallet_save(info);
	if (strcmp(info->argv[0], "wallet_load") == 0)
		wallet_load(info);
	if (strcmp(info->argv[0], "quit") == 0 || strcmp(info->argv[0], "exit") == 0)
		exit(0);
	if (strcmp(info->argv[0], "info") == 0)
		show_info(info);
	if (strcmp(info->argv[0], "send") == 0 && info->argc == 3)
		send(info);
	return (ret);
}



/**
 * set_info - initializes info_t struct
 * @info: struct info
 * @argv: argument
 */
void set_info(info_t *info, char **argv)
{
	int i = 0;

	info->filename = argv[0];
	if (info->arg)
	{
		info->argv = _strtok(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
	}
}


/**
 * free_info - frees info structure fields
 * @info: structure info
 * @all: switch to check if freeing all fields
 */
void free_info(info_t *info, int all)
{
	char **tmp_argv = info->argv;

	if (tmp_argv)
	{
		while (*info->argv)
			free(*info->argv++);
		free(tmp_argv);
	}
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
 * cli - main command line loop
 * @info: structure info
 * @argv: argument
 *
 * Return: 0 on success, 1 on error, or error code
 */
int cli(info_t *info, char **argv)
{
	ssize_t r = 0;
	int exit_status = 0;

	setbuf(stdout, NULL);
	while (r != -1 && exit_status != -2)
	{
		info->arg = NULL, info->argv = NULL, info->argc = 0;
		if (isatty(STDIN_FILENO))
			printf("> ");
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, argv);
			exit_status = find_command(info);
		}
		else if (isatty(STDIN_FILENO))
			putchar('\n');
		free_info(info, 0);
	}
	free_info(info, 1);
	if (!isatty(STDIN_FILENO) && info->status)
		exit(info->status);
	if (exit_status == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (exit_status);
}
