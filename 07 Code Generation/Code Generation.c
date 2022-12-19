#include <stdio.h>
#include <string.h>
#include<stdlib.h>

void main()
{
    char code[10][30], str[20], opr[10];
    int i = 0,k=0;
    FILE *fp1,*fp2;
    fp1=fopen("quadruple.txt","r");
    //printf("FILE OPENED\n");
    fp2=fopen("output.txt","w+");
    char op,fir[10],sec[10],res[10];
    while(!feof(fp1)){

    	fscanf(fp1,"%c\t%s\t%s\t%s\n",&op,fir,sec,res);
    	//printf("%c\t%s\t%s\t%s\n",op,fir,sec,res);
    
    	switch (op){
		case '+':
		    	strcpy(opr, "ADD ");
		    	i=0;
		    	break;
	    	case '-':
			strcpy(opr, "SUB");
			i=0;
			break;
		case '*':
			strcpy(opr, "MUL ");
			i=1;
			break;
		case '/' :
		    	strcpy(opr, "DIV");
			i=1;
			break;
	    }
	    if(strlen(fir)==2)
    	    {	
    	    	if (fir[1]=='1')
    	    		fprintf(fp2,"MOV AL,DH\n");
    	    	else if (fir[1]=='2')
    	    		fprintf(fp2,"MOV BL,DL\n");
    	    	else if (fir[1]=='3')
    	    		fprintf(fp2,"MOV CX,CH\n");
    	    	else if (fir[1]=='4')
    	    		fprintf(fp2,"MOV DX,CL\n");
    	    }
    	    else
    	    fprintf(fp2,"MOV AL,[%s]\n", fir);
    	    if(strlen(sec)==2)
    	    {	
    	    	if (sec[1]=='1')
    	    		fprintf(fp2,"MOV BL,DH\n");
    	    	else if (sec[1]=='2')
    	    		fprintf(fp2,"MOV BL,DL\n");
    	    	else if (sec[1]=='3')
    	    		fprintf(fp2,"MOV BL,CH\n");
    	    	else if (sec[1]=='4')
    	    		fprintf(fp2,"MOV BL,CL\n");
    	    }
    	    else
    	    	fprintf(fp2,"MOV BL,[%s]\n",sec);
    	    if (i==0)
	    fprintf(fp2,"%sAL,BL\n", opr);
	    else
	    fprintf(fp2,"%sBL\n", opr);
	    if(strlen(res)==2)
    	    {	
    	    	if (res[1]=='1')
    	    		fprintf(fp2,"MOV DH,AL\n");
    	    	else if (res[1]=='2')
    	    		fprintf(fp2,"MOV DL,AL\n");
    	    	else if (res[1]=='3')
    	    		fprintf(fp2,"MOV CH,AL\n");
    	    	else if (res[1]=='4')
    	    		fprintf(fp2,"MOV CL,AL\n");
    	    }
    	    
	    k++;
	    
    }
}
