#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>                                      
                                            
int isKeyword(char buffer[]) 
{
	char Keyword[34][10] =
	{"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", 
	"float", "for", "goto","if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", 
	"switch", "typdef", "union", "unsigned", "void", "volitile", "while", "printf", "scanf"};
	
	int i,flag =0;
	for(i=0;i<34;i++)
	{
		if(strcmp(Keyword[i],buffer)==0)
		{
			flag=1;
			break;
		}
	}
	return flag;
}

void main()
{
	char ch,ch1, buffer[50], operator[]="+-*/%";
	FILE *fp,*fp2;
	int i, j=0, l=1, index = 1;
	char arr[1000][3];
	fp=fopen("program.txt", "r");
	fp2=fopen("symbol.txt", "w+");
	if(fp==NULL)
	{
		printf("Error while opening file\n");
		exit(0);
	}
	else
	{
		printf("Lexeme  \t L.no \t Token ");
		fprintf(fp2,"Lexeme  \t L.no \t Token ");
		while((ch=fgetc(fp))!=EOF)
		{
			for(i=0;i<5;++i)
			{
				if(ch==operator[i])
				{
					printf("\n%c \t\t %d\t Arithmetic operator, %c", ch,l,ch);
					//fprintf(fp2,"\n%c \t\t %d\t arithmetic operator ", ch,l);
					break;
				}
			}
			if(i==5)
			{
				if(isalnum(ch))
				{
					if(isdigit(ch) && j==0)
						j=0;
					else 
					{
						buffer[j++] = ch;
						ch1= fgetc(fp);
						if(isalnum(ch1))
							fseek(fp, -1, SEEK_CUR);
						else 
						{
							fseek (fp,-1,SEEK_CUR);
							buffer[j]='\0';
							if(isKeyword(buffer)==1)
							{
								if(strcmp(buffer, "printf")==0){
									while((ch=fgetc(fp))!='\n'){
										
									}
								}
								printf("\n%s \t\t %d \t Keyword ", buffer, l);
								j=0;
							}
							else
							{
									fseek(fp2, SEEK_SET, 0);
									char a[50], b[50], c[50], ch2, ch3;
									int flag1 = 0;
									while(!feof(fp2)){
										fscanf(fp2, "%s\t%s\t%s", a, b, c);
										if(strcmp(a, buffer) == 0){
										flag1 = 1;
										break;
										}
									}
									if(flag1==0){
										ch2 = fgetc(fp);
										if(ch2=='='){
										ch3 = fgetc(fp);
										fprintf(fp2,"\n%s \t\t %d\t Identifier, %c", buffer, index, ch3);
										fseek(fp,-2,SEEK_CUR);
										}
										else{
										fprintf(fp2,"\n%s \t\t %d\t Identifier", buffer, index);
										}
										printf("\n%s \t\t %d\t Identifier, %d", buffer, l, index);	
										index++;
									}
									else{
										printf("\n%s \t\t %d\t Identifier, %s", buffer, l, b);
									}
								j=0;
							}
						}
					}
				}
				if(ch=='<')
				{
					ch1= fgetc(fp);
					if(ch1=='=')
					{
						printf("\n%c%c \t\t %d \t Relational operator, LE",ch,ch1,l);
					}
					else
					{
						fseek(fp,-1,SEEK_CUR);
						printf("\n%c \t\t %d \t Relational operator", ch,l);
					}
				}
				else if(ch=='>')
				{
					ch1= fgetc(fp);
					if(ch1=='=')
					{
						printf("\n%c%c \t\t %d \t Relational operator, GE",ch,ch1,l);
					}
					else
					{
						fseek(fp,-1,SEEK_CUR);
						printf("\n%c \t\t %d \t Relational operator", ch,l);
					}
				}
				else if(ch=='=')
				{
					ch1=fgetc(fp);
					if(ch1=='=') 
					{
						printf("\n%c%c \t\t %d \t Relational operator, EQ", ch, ch1, l);
					}
					else
					{
						fseek(fp, -1, SEEK_CUR);
						printf("\n%c \t\t %d \t Assignment operator, EQ",ch,l);
					}
				}
				if(ch=='\n'){
					l++;
				}
			}
		}
	}
	printf("\n");
}
