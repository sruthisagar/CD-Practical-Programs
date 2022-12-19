#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char s[100], post[100], stack[100], queue[100];
int top = -1, j = 0, front = -1;

int precedence(char c)
{
	if(c == '+' || c == '-')
		return 1;
	else if(c == '*' || c == '/')
		return 2;
	else if(c == '^')
		return 3;
	else
		return 0;
}

void postfix()
{
	int n = strlen(s), i = 0;
	while(s[i] != '\0')
	{
		if(s[i] == '(')
		{
			top++;
			stack[top] = s[i];
		}
		else if(isalpha(s[i]))
		{
			post[j++] = s[i];
		}
		else if(precedence(s[i]))
		{
			while(precedence(stack[top]) > precedence(s[i]))
				post[j++] = stack[top--];
			top++;
			stack[top] = s[i];
		}
		else if(s[i] == ')')
		{
			while(stack[top] != '(')
				post[j++] = stack[top--];
			top--;
		}
		i++;
	}
	while(top!=-1)
		post[j++] = stack[top--];
	post[j] = '\0';
}

void main()
{
	char ind = '1';
	scanf("%s", s);
	postfix();
	printf("\nPostfix: ");
	printf("%s\n", post);
	int i = 0;
	FILE *fp1, *fp2, *fp3;
	fp1 = fopen("threeaddress.txt", "w+");
	fp2 = fopen("quadruple.txt", "w+");
	fp3 = fopen("triple.txt", "w+");
	fprintf(fp2, "Operator\tOp1\tOp2\tResult\n");
	fprintf(fp3, "\tOperator\tOp1\tOp2\n");
	while(post[i] != '\0')
	{
		if(precedence(post[i]))
		{
			char a = queue[front--];
			char b = queue[front--];
			if(isdigit(a) && isdigit(b))
			{
				fprintf(fp1, "t%c = t%c %c t%c\n", ind, b, post[i], a);
				fprintf(fp2, "%c\tt%c\tt%c\tt%c\n", post[i], b, a, ind);
			}
			else if(isdigit(b))
			{
				fprintf(fp1, "t%c = t%c %c %c\n", ind, b, post[i], a);
				fprintf(fp2, "%c\tt%c\t%c\tt%c\n", post[i], b, a, ind);
			}
			else if(isdigit(a))
			{
				fprintf(fp1, "t%c = %c %c t%c\n", ind, b, post[i], a);
				fprintf(fp2, "%c\t%c\tt%c\tt%c\n", post[i], b, a, ind);
			}
			else
			{
				fprintf(fp1, "t%c = %c %c %c\n", ind, b, post[i], a);
				fprintf(fp2, "%c\t%c\t%c\tt%c\n", post[i], b, a, ind);
			}
			fprintf(fp3, "%c\t%c\t%c\t%c\n", ind, post[i], b, a);
			front++;
			queue[front] = ind;
			ind++;
		}
		else
		{
			front++;
			queue[front] = post[i];
		}
		i++;
	}
}
