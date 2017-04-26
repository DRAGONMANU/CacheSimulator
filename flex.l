%{
	# include "bison.tab.h"
	# include <string.h>
	int c_a = 0;
	int c_b = 0;
%} 
%s A 
%s B
%s C
%%

<INITIAL>[0-9'a''b''c''d''e''f''A''B''C''D''E''F']+	{
				
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
				if(!strcmp(temp,"000011"))
					return JAL;
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
						else if(!strcmp(temp1,"001000"))
							return JR;
						else if(!strcmp(temp1,"001001"))
							return JALR;
						else if(!strcmp(temp1,"010010"))
							return MFLO;
						else if(!strcmp(temp1,"000100"))
							return SLLV;
						else if(!strcmp(temp1,"101011"))
							return SLTU;
						else if(!strcmp(temp1,"100001"))
							return ADDU;
					}
				else
					{/*printf("unrecognized!!\n");*/}

			}
<INITIAL>.			{printf("Mystery character : %c",yytext);}
<INITIAL><<EOF>>     {BEGIN C;}

<C>"l1_icache"	{	BEGIN A;	}
<C>"l1_dcache"	{	BEGIN B;	}
<C>.					{}
<C>\n					{}
<A>"false" 				{  yylval.nod = yytext; return Q;}
<A>"true" 				{  yylval.nod = yytext; return W;}
<A>[0-9]+ 				{	
							if(c_a == 0)
							{
								
								yylval.nod = yytext; return E;
								c_a++;
							}
							else if(c_a == 1)
							{
								
								yylval.nod = yytext; return R;
								c_a++;
							}
							else if(c_a == 2)
							{
								
								yylval.nod = yytext; return T;
								c_a++;
							}
							else if(c_a == 3)
							{
								
								yylval.nod = yytext; return Y;
								c_a++;
								BEGIN C;
							}  
						}
<A>"lru" 				{ yylval.nod = yytext; return U; }
<A>.					{}
<A>\n					{}

<B>"false" 				{ yylval.nod = yytext; return QQ;}
<B>"true" 				{ yylval.nod = yytext; return WW;}
<B>[0-9]+ 				{
							if(c_b == 0)
							{
								
								yylval.nod = yytext; return EE;
								c_b++;
							}
							else if(c_b == 1)
							{
								
								yylval.nod = yytext; return RR;
								c_b++;
							}
							else if(c_b == 2)
							{
								
								yylval.nod = yytext; return TT;
								c_b++;
							}
							else if(c_b == 3)
							{
								
								yylval.nod = yytext; return YY;
								c_b++;
								BEGIN C;
							}
						}
<B>"lru" 				{  yylval.nod = yytext; return UU;}
<B>.					{}
<B>\n					{}

		
%%

int yywrap()
{return 1;}
