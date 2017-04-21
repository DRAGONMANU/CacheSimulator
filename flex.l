%{
	# include "bison.tab.h"
	# include <string.h>
	char* tobinary(char*);
%} 

%%

[0-9'a''b''c''d''e''f''A''B''C''D''E''F']+	{
				
				//printf("%s\n",yytext);
				char* inst = tobinary(yytext);
				//printf("->   %s\n",inst);
				char* temp = malloc(6*sizeof(char));
				int i;
				for(i=0;i<6;i++)
					temp[i]=inst[i];
				temp[i]='\0';
				yylval.nod = malloc(32*sizeof(char));
				//for(i=0;i<26;i++)
				//	yylval.nod[i]=inst[i+6];
				//yylval.nod[i] = '\0';
				yylval.nod = inst;
				//printf("hereeeeee ::: %s\n",yylval.nod);
				if(!strcmp(temp,"100011"))
					return LW;
				else if(!strcmp(temp,"101011"))
					return SW;
				else if(!strcmp(temp,"000100"))
					return BEQ;
				else if(!strcmp(temp,"000010"))
					return J;
				else if(!strcmp(temp,"001000"))
					return ADDI;
				else if(!strcmp(temp,"001101"))
					return ORI;
				else if(!strcmp(temp,"001111"))
					return LUI;
				else if(!strcmp(temp,"001010"))
					return SLTI;
				else if(!strcmp(temp,"000111"))
					return BGTZ;
				else if(!strcmp(temp,"000110"))
					return BLEZ;
				else if(!strcmp(temp,"100000"))
					return LB;
				else if(!strcmp(temp,"101000"))
					return SB;
				else if(!strcmp(temp,"011100"))
					return MADD;
				else if(!strcmp(temp,"000001"))
					{
						char* temp1 = malloc(5*sizeof(char));
						for(i=0;i<5;i++)
							temp1[i]=inst[i+11];
						temp1[i] = '\0';

						if(!strcmp(temp1,"00001"))
							return BGEZ;
						else if(!strcmp(temp1,"00000"))
							return BLTZ;
					}
				
				else if(!strcmp(temp,"000000"))
					{
						char* temp1 = malloc(6*sizeof(char));
						for(i=0;i<6;i++)
							temp1[i]=inst[i+26];
						temp1[i] = '\0';

						if(!strcmp(temp1,"100000"))
							return ADD;
						else if(!strcmp(temp1,"100010"))
							return SUB;
						else if(!strcmp(temp1,"100100"))
							return AND;
						else if(!strcmp(temp1,"100101"))
							return OR;
						else if(!strcmp(temp1,"011000"))
							return MULT;
						else if(!strcmp(temp1,"100111"))
							return NOR;
						else if(!strcmp(temp1,"000000"))
							return SLL;
						else if(!strcmp(temp1,"000100"))
							return SLLV;
						else if(!strcmp(temp1,"101011"))
							return SLTU;
					}
				else
					{/*printf("unrecognized!!\n");*/}

			}
.			{printf("Mystery character : %c",yytext);}	
		
%%

int yywrap()
{return 1;}
