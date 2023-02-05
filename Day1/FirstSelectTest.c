#include <stdio.h>
#include <mysql.h>

int main(void)
{
	MYSQL *mingMysql;
	if (mysql_library_init(0,NULL,NULL)) {
		fprintf(stderr,"could not initialize MySQL client library\n");
		exit(1);
	}
	
	mingMysql = mysql_init(NULL);
	if (mysql_errno(mingMysql)) {
		printf("%s\n",mysql_error(mingMysql));
	}
	
	if (!mysql_real_connect(mingMysql,"8.134.117.231","ming","ming","practice",0,NULL,0))
	{
		fprintf(stderr,"Failed to connect to database: Error: %s\n",
			mysql_error(mingMysql));
	}
	
	if (mysql_query(mingMysql,"SELECT * FROM test1"))
	{	
		fprintf(stderr,"Failed to select from pet: %s\n",
			mysql_error(mingMysql));
	}
	
	MYSQL_RES *result;
	result = mysql_store_result(mingMysql);
	if (mysql_errno(mingMysql)) {
		fprintf(stderr,"Failed to store result: %s\n",
			mysql_error(mingMysql));
	}
	
	MYSQL_ROW row;
	unsigned int num_fields;
	unsigned int i;	
	num_fields = mysql_num_fields(result);

	while ((row = mysql_fetch_row(result)))
	{
		unsigned long *lengths;
		lengths = mysql_fetch_lengths(result);
		for ( i = 0;i < num_fields; i++) 
		{
			printf("[%.*s] ",(int) lengths[i],
				row[i] ? row[i] : "NULL");
		}
	
		printf("\n");
	}
	
	mysql_free_result(result);
	mysql_close(mingMysql);
	mysql_library_end();
	return EXIT_SUCCESS;
}
