	int num_words = 1, num_chars = 0, num_lines = 0;
	
%%

[:space:]	++num_chars; ++num_words;
\n	++num_words; ++num_lines;
.	++num_chars;

%%

int main()
{
	yyin = fopen("input.txt", "r");
	yylex();
	printf( "Number of words = %d \nNumber of characters = %d\nNumber of lines = %d\n",num_words, num_chars, num_lines);
}