int main(int argc, char **argv)
{
	int tok;

	if(argc < 2)
	{
		fprintf(stderr, "Call: ./a.out file_name\n");
		exit(1);
	}

	if((yyin = fopen(argv[1], "r")) == NULL)
	{
		printf("Failed to open file\n");
		exit(1);
	}

	initMe();

	while(isRunning()) 
	{
		tok = yylex();
		if(!isRunning())
		{
			break;
		}

		switch(tok)
		{
			default: printf("Achei token %d\n", tok); break;
		}
	}
	

	printf("Main done, file has %d lines\n", lineNumber);
	hashPrint();
	exit(0);
}