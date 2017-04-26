%{
	# include <string.h>
	
	int c_a = 0;
	int c_b = 0;
	char iperfect[20];
	//iperfect = malloc(20*sizeof(char));
	int ic_s = 0;
	int iassc = 0;
	char ireplpol[20];
	//ireplpol = malloc(20*sizeof(char));
	int iwthru = 0;
	int ib_s = 0;
	char dperfect[20];
	//dperfect = malloc(20*sizeof(char));
	int dc_s = 0;
	int dassc = 0;
	char dreplpol[20];
	//dreplpol = malloc(20*sizeof(char));
	int dwthru = 0;
	int db_s = 0;
%} 
%s A 
%s B
%%

<INITIAL>"l1_icache"	{	BEGIN A;	}
<INITIAL>"l1_dcache"	{	BEGIN B;	}
<INITIAL>.				{}
<INITIAL>\n					{}
<A>"false" 				{ strcpy(iperfect , "false");}
<A>"true" 				{ strcpy(iperfect , "true");}
<A>[0-9]+ 				{
							if(c_a == 0)
							{
								ic_s = atoi(yytext);
								c_a++;
							}
							else if(c_a == 1)
							{
								iassc = atoi(yytext);
								c_a++;
							}
							else if(c_a == 2)
							{
								iwthru = atoi(yytext);
								c_a++;
							}
							else if(c_a == 3)
							{
								ib_s = atoi(yytext);
								c_a++;
								BEGIN INITIAL;
							}  
						}
<A>"lru" 				{ strcpy(ireplpol , "lru"); }
<A>.					{}
<A>\n					{}

<B>"false" 				{ strcpy(dperfect , "false");}
<B>"true" 				{ strcpy(dperfect , "true");}
<B>[0-9]+ 				{
							if(c_b == 0)
							{
								dc_s = atoi(yytext);
								c_b++;
							}
							else if(c_b == 1)
							{
								dassc = atoi(yytext);
								c_b++;
							}
							else if(c_b == 2)
							{
								dwthru = atoi(yytext);
								c_b++;
							}
							else if(c_b == 3)
							{
								db_s = atoi(yytext);
								c_b++;
								BEGIN INITIAL;
							}
						}
<B>"lru" 				{ strcpy(dreplpol, "lru"); }
<B>.					{}
<B>\n					{}
		
%%
/*
main()
{	yyin=fopen("input.cfg","r");
	yylex();
	fclose(yyin);	

	printf("========================================================================================%s\n",iperfect);
	printf("========================================================================================%d\n",ic_s);
	printf("========================================================================================%d\n",iassc);
	printf("========================================================================================%s\n",ireplpol);
	printf("========================================================================================%d\n",iwthru);
	printf("========================================================================================%d\n",ib_s);
	

	printf("========================================================================================%s\n",dperfect);
	printf("========================================================================================%d\n",dc_s);
	printf("========================================================================================%d\n",dassc);
	printf("========================================================================================%s\n",dreplpol);
	printf("========================================================================================%d\n",dwthru);
	printf("========================================================================================%d\n",db_s);
	
	

}*/
int yywrap()
{return 1;}
