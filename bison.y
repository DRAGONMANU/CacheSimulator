/* simplest version of calculator */
%{

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "code.h"
#include <string.h>


char* tobinary(char* a)
{	
	char* b = (char *) malloc(32*sizeof(char));

	int i;
	for(i=0;i<8;i++)
	{
		//printf("%c\n",a[i]);
		switch (a[i])
        {
	        case '0':
	            b[i*4]='0'; b[i*4 + 1]='0'; b[i*4 + 2]='0'; b[i*4 + 3]='0';break;
	        case '1':
	            b[i*4]='0'; b[i*4 + 1]='0'; b[i*4 + 2]='0'; b[i*4 + 3]='1'; break;
	        case '2':
	            b[i*4]='0'; b[i*4 + 1]='0'; b[i*4 + 2]='1'; b[i*4 + 3]='0'; break;
	        case '3':
	            b[i*4]='0'; b[i*4 + 1]='0'; b[i*4 + 2]='1'; b[i*4 + 3]='1'; break;
	        case '4':
	            b[i*4]='0'; b[i*4 + 1]='1'; b[i*4 + 2]='0'; b[i*4 + 3]='0'; break;
	        case '5':
	            b[i*4]='0'; b[i*4 + 1]='1'; b[i*4 + 2]='0'; b[i*4 + 3]='1'; break;
	        case '6':
	            b[i*4]='0'; b[i*4 + 1]='1'; b[i*4 + 2]='1'; b[i*4 + 3]='0'; break;
	        case '7':
	            b[i*4]='0'; b[i*4 + 1]='1'; b[i*4 + 2]='1'; b[i*4 + 3]='1'; break;
	        case '8':
	            b[i*4]='1'; b[i*4 + 1]='0'; b[i*4 + 2]='0'; b[i*4 + 3]='0'; break;
	        case '9':
	            b[i*4]='1'; b[i*4 + 1]='0'; b[i*4 + 2]='0'; b[i*4 + 3]='1'; break;
	        case 'A':
	            b[i*4]='1'; b[i*4 + 1]='0'; b[i*4 + 2]='1'; b[i*4 + 3]='0'; break;
	        case 'B':
	            b[i*4]='1'; b[i*4 + 1]='0'; b[i*4 + 2]='1'; b[i*4 + 3]='1'; break;
	        case 'C':
	            b[i*4]='1'; b[i*4 + 1]='1'; b[i*4 + 2]='0'; b[i*4 + 3]='0'; break;
	        case 'D':
	            b[i*4]='1'; b[i*4 + 1]='1'; b[i*4 + 2]='0'; b[i*4 + 3]='1'; break;
	        case 'E':
	            b[i*4]='1'; b[i*4 + 1]='1'; b[i*4 + 2]='1'; b[i*4 + 3]='0'; break;
	        case 'f':
	            b[i*4]='1'; b[i*4 + 1]='1'; b[i*4 + 2]='1'; b[i*4 + 3]='1'; break;
	        case 'a':
	            b[i*4]='1'; b[i*4 + 1]='0'; b[i*4 + 2]='1'; b[i*4 + 3]='0'; break;
	        case 'b':
	            b[i*4]='1'; b[i*4 + 1]='0'; b[i*4 + 2]='1'; b[i*4 + 3]='1'; break;
	        case 'c':
	            b[i*4]='1'; b[i*4 + 1]='1'; b[i*4 + 2]='0'; b[i*4 + 3]='0'; break;
	        case 'd':
	            b[i*4]='1'; b[i*4 + 1]='1'; b[i*4 + 2]='0'; b[i*4 + 3]='1'; break;
	        case 'e':
	            b[i*4]='1'; b[i*4 + 1]='1'; b[i*4 + 2]='1'; b[i*4 + 3]='0'; break;
	        case 'F':
	            b[i*4]='1'; b[i*4 + 1]='1'; b[i*4 + 2]='1'; b[i*4 + 3]='1'; break;
	        default:
	            printf("Invalid hexa digit %c ", a[i]);
	            return 0;
        }
	}
	b[32]='\0';
	return b;
}
extern FILE *yyin;
extern FILE *yyout;

void stat(char* s, char* t)
{
    while(*s != '\0')
        *s++;
    while(*s++ = *t++)
        ;
}
 
void convertinstr()
{
    //read the if_id.name and decode into various instructions
    //get the cases Rd,RT,Rd,offset and store in char* new variable
    char tmp[20] = "";
    char tmpa[20] = "";
    char tmpb[20] = "";
    char tmpc[20] = "";
 
    
    if(!strcmp(if_id.name_write, "add") || !strcmp(if_id.name_write,"and") || !strcmp(if_id.name_write,"nor") || !strcmp(if_id.name_write,"or") || !strcmp(if_id.name_write,"sub"))
    {
        /*if_id.instr_name_read = if_id.name_read;
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.inst_data_15_11_write);
        stat(if_id.instr_name_read,tmp);
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.rf_rad1_write);
        stat(if_id.instr_name_read,tmp);
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.rf_rad2_write);
        stat(if_id.instr_name_read,tmp);
*/      //printf("case1\n");
 
        stat(tmp,if_id.name_read);
        stat(tmp," $");
        sprintf(tmpa,"%d",if_id.inst_data_15_11_write);
        stat(tmp,tmpa);
        stat(tmp," $");
        sprintf(tmpb,"%d",if_id.rf_rad1_write);
        stat(tmp,tmpb);
        stat(tmp," $");
        sprintf(tmpc,"%d",if_id.rf_rad2_write);
        stat(tmp,tmpc);
        //printf("%s\n",tmp);
        if_id.instr_name_read = tmp;
    }
    else if(!strcmp(if_id.name_write, "addi") || !strcmp(if_id.name_write,"ori") || !strcmp(if_id.name_write,"slti"))
    {
        /*if_id.instr_name_read = if_id.name_read;
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.rf_rad2_write);
        stat(if_id.instr_name_read,tmp);
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.rf_rad1_write);
        stat(if_id.instr_name_read,tmp);
        stat(if_id.instr_name_read," ");
        sprintf(tmp,"%d",if_id.inst_data_15_0_write);
        stat(if_id.instr_name_read,tmp);
        printf("case2\n");
*/
        stat(tmp,if_id.name_read);
        stat(tmp," $");
        sprintf(tmpa,"%d",if_id.rf_rad2_write);
        stat(tmp,tmpa);
        stat(tmp," $");
        sprintf(tmpb,"%d",if_id.rf_rad1_write);
        stat(tmp,tmpb);
        stat(tmp," $");
        sprintf(tmpc,"%d",if_id.inst_data_15_0_write);
        stat(tmp,tmpc);
        //printf("%s\n",tmp);
        if_id.instr_name_read = tmp;
 
 
    }
    else if(!strcmp(if_id.name_write,"mult")|| !strcmp(if_id.name_write,"madd") )
    {
        /*if_id.instr_name_read = if_id.name_read;
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.rf_rad1_write);
        stat(if_id.instr_name_read,tmp);
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.rf_rad2_write);
        stat(if_id.instr_name_read,tmp);
        stat(if_id.instr_name_read," ");
        sprintf(tmp,"%d",if_id.inst_data_15_0_write);
        stat(if_id.instr_name_read,if_id.inst_data_15_0_write);
        printf("case3\n");
*/
        stat(tmp,if_id.name_read);
        stat(tmp," $");
        sprintf(tmpa,"%d",if_id.rf_rad1_write);
        stat(tmp,tmpa);
        stat(tmp," $");
        sprintf(tmpb,"%d",if_id.rf_rad2_write);
        stat(tmp,tmpb);
        stat(tmp," $");
        sprintf(tmpc,"%d",if_id.inst_data_15_0_write);
        stat(tmp,tmpc);
        //printf("%s\n",tmp);
        if_id.instr_name_read = tmp;
 
    }
    else if(!strcmp(if_id.name_write, "lui"))
    {
        //printf("yes\n");
        /*
        if_id.instr_name_read = if_id.name_read;
        printf("no\n");
        //stat(if_id.instr_name_read," $");
        
        sprintf(tmp,"%d",if_id.rf_rad2_write);
        printf("see\n");
        printf("%s\n",tmp);
        stat(if_id.instr_name_read,tmp);
        printf("serio\n");
        stat(if_id.instr_name_read," ");
        sprintf(tmp,"%d",if_id.inst_data_15_0_write);
        stat(if_id.instr_name_read,tmp);
        printf("case4\n");
*/
        stat(tmp,if_id.name_read);
        stat(tmp," $");
        sprintf(tmpa,"%d",if_id.rf_rad2_write);
        stat(tmp,tmpa);
        stat(tmp," @");
        sprintf(tmpb,"%d",if_id.inst_data_15_0_write);
        stat(tmp,tmpb);
        //printf("%s\n",tmp);
        if_id.instr_name_read = tmp;
 
 
    }
    else if(!strcmp(if_id.name_write, "beq"))
    {
        /*if_id.instr_name_read = if_id.name_read;
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.rf_rad1_write);
        stat(if_id.instr_name_read,tmp);
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.rf_rad2_write);
        stat(if_id.instr_name_read,tmp);
        stat(if_id.instr_name_read," ");
        sprintf(tmp,"%d",if_id.inst_data_15_0_write);
        stat(if_id.instr_name_read,tmp);
        printf("case5\n");
*/
        stat(tmp,if_id.name_read);
        stat(tmp," $");
        sprintf(tmpa,"%d",if_id.rf_rad1_write);
        stat(tmp,tmpa);
        stat(tmp," $");
        sprintf(tmpb,"%d",if_id.rf_rad2_write);
        stat(tmp,tmpb);
        stat(tmp," $");
        sprintf(tmpc,"%d",if_id.inst_data_15_0_write);
        stat(tmp,tmpc);
        //printf("%s\n",tmp);
        if_id.instr_name_read = tmp;
 
    }
    else if(!strcmp(if_id.name_write, "bgez") || !strcmp(if_id.name_write,"bgtz") || !strcmp(if_id.name_write,"blez") || !strcmp(if_id.name_write,"bltz"))
    {
        /*if_id.instr_name_read = if_id.name_read;
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.rf_rad1_write);
        stat(if_id.instr_name_read,tmp);
        stat(if_id.instr_name_read," ");
        sprintf(tmp,"%d",if_id.inst_data_15_0_write);
        stat(if_id.instr_name_read,tmp);
        printf("case6\n");
*/
        stat(tmp,if_id.name_read);
        stat(tmp," $");
        sprintf(tmpa,"%d",if_id.rf_rad1_write);
        stat(tmp,tmpa);
        stat(tmp," @");
        sprintf(tmpb,"%d",if_id.inst_data_15_0_write);
        stat(tmp,tmpb);
        //printf("%s\n",tmp);
        if_id.instr_name_read = tmp;
 
    }
    else if(!strcmp(if_id.name_write, "lb") || !strcmp(if_id.name_write,"lw") || !strcmp(if_id.name_write,"sb") || !strcmp(if_id.name_write,"sw"))
    {
        /*if_id.instr_name_read = if_id.name_read;
        stat(if_id.instr_name_read," $");
        sprintf(tmp,"%d",if_id.rf_rad2_write);
        stat(if_id.instr_name_read,tmp);
        stat(if_id.instr_name_read," ");
        sprintf(tmp,"%d",if_id.inst_data_15_0_write);
        stat(if_id.instr_name_read,tmp);
        printf("case7\n");
*/
        stat(tmp,if_id.name_read);
        stat(tmp," $");
        sprintf(tmpa,"%d",if_id.rf_rad2_write);
        stat(tmp,tmpa);
        stat(tmp," @");
        sprintf(tmpb,"%d",if_id.inst_data_15_0_write);
        stat(tmp,tmpb);
        //printf("%s\n",tmp);
        if_id.instr_name_read = tmp;
    }
}


%}

%union{
	char* nod;
}

/* declare tokens */

%token AND ADD OR LW SW SUB BEQ J ADDI ORI LUI SLTI BGTZ BLEZ LB SB BGEZ BLTZ MULT NOR SLL SLLV SLTU MADD
%type<nod> AND ADD OR LW SW SUB BEQ J ADDI ORI LUI SLTI BGTZ BLEZ LB SB BGEZ BLTZ MULT NOR SLL SLLV SLTU MADD
%type<nod> exp
%%

exp: AND {im[N].name="and";im[N].instr=$1;N++;}
| ADD {im[N].name="add";im[N].instr=$1;N++;}
| OR  {im[N].name="or";im[N].instr=$1;N++;}
| LW  {im[N].name="lw";im[N].instr=$1;N++;}
| SW  {im[N].name="sw";im[N].instr=$1;N++;}
| SUB {im[N].name="sub";im[N].instr=$1;N++;}
| BEQ {im[N].name="beq";im[N].instr=$1;N++;}
| J   {im[N].name="j";im[N].instr=$1;N++;};
| ADDI   {im[N].name="addi";im[N].instr=$1;N++;}
| ORI   {im[N].name="ori";im[N].instr=$1;N++;}
| LUI   {im[N].name="lui";im[N].instr=$1;N++;}
| SLTI   {im[N].name="slti";im[N].instr=$1;N++;}
| BGTZ   {im[N].name="bgtz";im[N].instr=$1;N++;}
| BLEZ   {im[N].name="blez";im[N].instr=$1;N++;}
| LB   {im[N].name="lb";im[N].instr=$1;N++;}
| SB   {im[N].name="sb";im[N].instr=$1;N++;}
| MADD   {im[N].name="madd";im[N].instr=$1;N++;}
| BGEZ   {im[N].name="bgez";im[N].instr=$1;N++;}
| BLTZ   {im[N].name="bltz";im[N].instr=$1;N++;}
| MULT   {im[N].name="mult";im[N].instr=$1;N++;}
| NOR   {im[N].name="nor";im[N].instr=$1;N++;}
| SLL   {im[N].name="sll";im[N].instr=$1;N++;}
| SLLV   {im[N].name="sllv";im[N].instr=$1;N++;}
| SLTU   {im[N].name="sltu";im[N].instr=$1;N++;}
| exp AND {im[N].name="and";im[N].instr=$2;N++;}
| exp ADD {im[N].name="add";im[N].instr=$2;N++;}
| exp OR  {im[N].name="or";im[N].instr=$2;N++;}
| exp LW  {im[N].name="lw";im[N].instr=$2;N++;}
| exp SW  {im[N].name="sw";im[N].instr=$2;N++;}
| exp SUB {im[N].name="sub";im[N].instr=$2;N++;}
| exp BEQ {im[N].name="beq";im[N].instr=$2;N++;}
| exp J   {im[N].name="j";im[N].instr=$2;N++;};
| exp ADDI   {im[N].name="addi";im[N].instr=$2;N++;}
| exp ORI   {im[N].name="ori";im[N].instr=$2;N++;}
| exp LUI   {im[N].name="lui";im[N].instr=$2;N++;}
| exp SLTI   {im[N].name="slti";im[N].instr=$2;N++;}
| exp BGTZ   {im[N].name="bgtz";im[N].instr=$2;N++;}
| exp BLEZ   {im[N].name="blez";im[N].instr=$2;N++;}
| exp LB   {im[N].name="lb";im[N].instr=$2;N++;}
| exp SB   {im[N].name="sb";im[N].instr=$2;N++;}
| exp BGEZ   {im[N].name="bgez";im[N].instr=$2;N++;}
| exp BLTZ   {im[N].name="bltz";im[N].instr=$2;N++;}
| exp MULT   {im[N].name="mult";im[N].instr=$2;N++;}
| exp NOR   {im[N].name="nor";im[N].instr=$2;N++;}
| exp SLL   {im[N].name="sll";im[N].instr=$2;N++;}
| exp SLLV   {im[N].name="sllv";im[N].instr=$2;N++;}
| exp SLTU   {im[N].name="sltu";im[N].instr=$2;N++;}
| exp MADD   {im[N].name="madd";im[N].instr=$2;N++;}
%%


main(int argc, char **argv)
{
	int i;

	    char* wbins = "nop";
	for(i=0;i<1000;i++)
		mem[i] = 0;

	for(i=0;i<34;i++)
		rf[i] = 0;

	double max;
	/*FILE *myfile1 = fopen(argv[2], "w");
	if (!myfile1) {
		printf("can't open wr");
		return -1;
	}*/
	//yyout = myfile1;

	FILE *myfile = fopen(argv[1], "r");
	if (!myfile) {
		printf("can't open re");
		return -1;
	}
	yyin = myfile;
	do {
		yyparse();
	} 
	while (!feof(yyin));
	
	fclose(myfile);

		id_ex.rn_read = 0;
		id_ex.rn_write = 0;
		id_ex.rm_read = 0;
		id_ex.rm_write = 0;

		mem_wb.mem_data_read    = 0;
		mem_wb.bypass_data_read = 0;
		mem_wb.mux_ans_read     = 0;
		mem_wb.mem_data_write   = 0;
		mem_wb.bypass_data_write= 0;
		mem_wb.mux_ans_write    = 0;

		id_ex.sa_read = 0;
		id_ex.sa_write = 0;

		ex_mem.add_ans_read = 0;
		ex_mem.alu_ans_read = 0;
		ex_mem.rf_data_read = 0;
		ex_mem.mux_ans_read = 0;

		ex_mem.add_ans_write = 0;
		ex_mem.alu_ans_write = 0;
		ex_mem.rf_data_write = 0;
		ex_mem.mux_ans_write = 0;

		id_ex.rf_outdata1_read     = 0;
		id_ex.rf_outdata2_read     = 0;
		id_ex.inst_data_15_0_read  = 0;
		id_ex.inst_data_20_16_read = 0;
		id_ex.inst_data_15_11_read = 0;
		id_ex.rf_outdata1_write     = 0;
		id_ex.rf_outdata2_write     = 0;
		id_ex.inst_data_15_0_write  = 0;
		id_ex.inst_data_20_16_write = 0;
		id_ex.inst_data_15_11_write = 0;

		if_id.rf_rad1_write = 0;
		if_id.rf_rad2_write = 0;
		if_id.inst_data_15_0_write = 0;
		if_id.inst_data_20_16_write = 0;
		if_id.inst_data_15_11_write = 0;

		if_id.rf_rad1_read = 0;
		if_id.rf_rad2_read = 0;
		if_id.inst_data_15_0_read = 0;
		if_id.inst_data_20_16_read = 0;
		if_id.inst_data_15_11_read = 0;

		if_id.add_write = 0;
		if_id.inst_write = "0";
		if_id.name_write = "0";
		id_ex.name_write = "0";
		ex_mem.name_write = "0";
		mem_wb.name_write = "0";

		write_datag_left = 0;

		id_ex.ALUSrc_write = 0;
		id_ex.ALUOp_write = "000";
		id_ex.RegDest_write = 0;
		id_ex.RegWrite_write = 0;
		id_ex.MemWrite_write = 0;
		id_ex.MemtoReg_write = 0;
		id_ex.MemRead_write = 0;
		id_ex.Branch_write = 0;
		id_ex.readdata1_write = 0;
		id_ex.readdata2_write = 0;
		//id_ex.extender_write;
		id_ex.inst20_16_write = 0;
		id_ex.inst15_11_write = 0;
		id_ex.add_write = 0;


		ex_mem.MemWrite_write  = 0;
		ex_mem.MemRead_write   = 0;
		ex_mem.Branch_write    = 0;
		ex_mem.Zero_write      = 0;
		ex_mem.RegWrite_write  = 0;
		ex_mem.MemtoReg_write  = 0;
		ex_mem.readdata2_write = 0;
		ex_mem.addresult_write = 0;
		ex_mem.aluresult_write = 0;
		ex_mem.write_register_write = 0;


		mem_wb.RegWrite_write       = 0;
		mem_wb.MemtoReg_write       = 0;
		mem_wb.readdata_write       = 0;
		mem_wb.addressbypass_write  = 0;
		mem_wb.write_register_write = 0;


		if_id.add_read = 0;
		if_id.inst_read = "0";
		if_id.name_read = "0";
		id_ex.name_read = "0";
		ex_mem.name_read = "0";
		mem_wb.name_read = "0";

		write_datag_right = 0;

		id_ex.ALUSrc_read = 0;
		id_ex.ALUOp_read = "000";
		id_ex.RegDest_read = 0;
		id_ex.RegWrite_read = 0;
		id_ex.MemWrite_read = 0;
		id_ex.MemtoReg_read = 0;
		id_ex.MemRead_read = 0;
		id_ex.Branch_read = 0;
		id_ex.readdata1_read = 0;
		id_ex.readdata2_read = 0;
		//id_ex.extender_read;
		id_ex.inst20_16_read = 0;
		id_ex.inst15_11_read = 0;
		id_ex.add_read = 0;


		ex_mem.MemWrite_read  = 0;
		ex_mem.MemRead_read   = 0;
		ex_mem.Branch_read    = 0;
		ex_mem.Zero_read      = 0;
		ex_mem.RegWrite_read  = 0;
		ex_mem.MemtoReg_read  = 0;
		ex_mem.readdata2_read = 0;
		ex_mem.addresult_read = 0;
		ex_mem.aluresult_read = 0;
		ex_mem.write_register_read = 0;


		mem_wb.RegWrite_read       = 0;
		mem_wb.MemtoReg_read       = 0;
		mem_wb.readdata_read       = 0;
		mem_wb.addressbypass_read  = 0;
		mem_wb.write_register_read = 0;

        if_id.instr_name_read = "nop";
        if_id.instr_name_write = "nop";        
        id_ex.instr_name_read = "nop";
        id_ex.instr_name_write = "nop";
        ex_mem.instr_name_write = "nop";
        ex_mem.instr_name_read = "nop";
        mem_wb.instr_name_write = "nop";
        mem_wb.instr_name_read = "nop";

	int temp = 200;
	int flag = 0;
	//highlight(0,1,0,1,0);
	while(flag != 4)
	{	
		char* read = malloc(50*sizeof(char));
		scanf("%s",read);
		if(!strcmp(read,"step"))
		{

				//printf("------------------  %d\n",PC);
				/*int ghy = 10000;
				while(ghy--)
				{
				}
				char* sss = malloc(20*sizeof(char));
				scanf("%s",sss);
				*/
				

				//printf("((((((((((((((((((((((((((((((((((((((((  %d\n\n\n",temp);
				pthread_t IF,ID,EX,MEM,WB,DISPLAY;
				
				pthread_create(&IF,NULL,thread_IF,NULL);
				pthread_create(&ID,NULL,thread_ID,NULL);
				pthread_create(&EX,NULL,thread_EX,NULL);
				pthread_create(&MEM,NULL,thread_MEM,NULL);
				pthread_create(&WB,NULL,thread_WB,NULL);
				//pthread_create(&DISPLAY,NULL,display,NULL);

				//if(stall_left != 1)
				pthread_join(IF,NULL);
				pthread_join(ID,NULL);
				pthread_join(EX,NULL);
				pthread_join(MEM,NULL);
				pthread_join(WB,NULL);
				//pthread_join(DISPLAY,NULL);

				//printf("11111\n");
				if(stall_right != 1)
				{

					if_id.add_write =  if_id.add_read;
					if_id.inst_write = if_id.inst_read;
					if_id.name_write = if_id.name_read;
				
				

				//printf("if_id.instr : \n");
				//printf("%s\n",if_id.inst_read);
				//if(PC < N )
				//{

				char* aa = malloc(5*sizeof(char));
					for(i=6;i<11;i++)
						aa[i-6] = if_id.inst_read[i];
					aa[i-6] = '\0';
					if_id.rf_rad1_write = bin_to_dec(aa);// - bin_to_dec("01000");

				//printf("11111\n");

				char* bb = malloc(5*sizeof(char));
					for(i=11;i<16;i++)
						bb[i-11] = if_id.inst_read[i];
					bb[i-11] = '\0';
					//if(bb[0] == '0')
					if_id.rf_rad2_write = bin_to_dec(bb);// - bin_to_dec("01000");
					

				char* cc = malloc(16*sizeof(char));
				for(i=16;i<32;i++)
					cc[i-16] = if_id.inst_read[i];
				cc[i-16] = '\0';

				if(cc[0] == '0')
				if_id.inst_data_15_0_write = bin_to_dec(cc);
				else
				{
					//printf("i am hrer\n\n\n\n\n\n");
					for(i=0;i<16;i++)
						{
							if(cc[i] == '0')
								cc[i] = '1';
							else
								cc[i] = '0';
						}
							//cc[i] = '0';
							//cc[0] = '0';
							//printf("%s\n",cc);
							if_id.inst_data_15_0_write = -1*(bin_to_dec(cc)+1);
				}

				//printf("-------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>    %d\n", bin_to_dec(cc));

				char* dd= malloc(5*sizeof(char));
				for(i=11;i<16;i++)
					dd[i-11] = if_id.inst_read[i];
				dd[i-11] = '\0';

				//if(dd[0] == '0')
				if_id.inst_data_20_16_write = bin_to_dec(dd);// - bin_to_dec("01000");
				

				char* ee= malloc(5*sizeof(char));
				for(i=16;i<21;i++)
					ee[i-16] = if_id.inst_read[i];
				ee[i-16] = '\0';
				if_id.inst_data_15_11_write = bin_to_dec(ee);// - bin_to_dec("01000");

				}
				else
				{
					//printf("hiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii\n\n\n\n\\n\n\n\n\n\n\\n\n\n\n\n\n\n\n");
					//stall = 0;
				}

				//}
				//else
				//{
					/*if_id.rf_rad1_read = 0;
					if_id.rf_rad2_read = 0;
					if_id.inst_data_15_0_read = 0;
					if_id.inst_data_20_16_read = 0;
					if_id.inst_data_15_11_read  = 0;*/

					//stall_left = 0;
				//}
				
				wbins = mem_wb.name_write;
				id_ex.name_write = id_ex.name_read;
				ex_mem.name_write = ex_mem.name_read;
				mem_wb.name_write = mem_wb.name_read;
				write_datag_left = write_datag_right;
				rf_wdg_left = rf_wdg_right;
				rf_wadg_left = rf_wadg_right;


				id_ex.rf_outdata1_write     = id_ex.rf_outdata1_read    ;
				id_ex.rf_outdata2_write     = id_ex.rf_outdata2_read    ;
				id_ex.inst_data_15_0_write  = id_ex.inst_data_15_0_read ;
				id_ex.inst_data_20_16_write = id_ex.inst_data_20_16_read;
				id_ex.inst_data_15_11_write = id_ex.inst_data_15_11_read;

				id_ex.ALUSrc_write = id_ex.ALUSrc_read;
				id_ex.ALUOp_write = id_ex.ALUOp_read;
				id_ex.RegDest_write = id_ex.RegDest_read;
				id_ex.RegWrite_write = id_ex.RegWrite_read;
				id_ex.MemWrite_write = id_ex.MemWrite_read;
				id_ex.MemtoReg_write = id_ex.MemtoReg_read;
				id_ex.MemRead_write = id_ex.MemRead_read;
				id_ex.Branch_write = id_ex.Branch_read;
				id_ex.readdata1_write = id_ex.readdata1_read;
				id_ex.readdata2_write = id_ex.readdata2_read;
				//id_ex.extender_write;
				id_ex.inst20_16_write = id_ex.inst20_16_read;
				id_ex.inst15_11_write = id_ex.inst15_11_read;
				id_ex.add_write = id_ex.add_read;
				id_ex.sa_write = id_ex.sa_read;

				ex_mem.MemWrite_write  = ex_mem.MemWrite_read ;
				ex_mem.MemRead_write   = ex_mem.MemRead_read  ;
				ex_mem.Branch_write    = ex_mem.Branch_read   ;
				ex_mem.Zero_write      = ex_mem.Zero_read     ;
				ex_mem.RegWrite_write  = ex_mem.RegWrite_read ;
				ex_mem.MemtoReg_write  = ex_mem.MemtoReg_read ;
				ex_mem.readdata2_write = ex_mem.readdata2_read;
				ex_mem.addresult_write = ex_mem.addresult_read;
				ex_mem.aluresult_write = ex_mem.aluresult_read;
				ex_mem.write_register_write = ex_mem.write_register_read;

				id_ex.rn_write = id_ex.rn_read;
				id_ex.rm_write = id_ex.rm_read;

				stall_left = stall_right; stall_right = 0;

				ex_mem.add_ans_write = ex_mem.add_ans_read;
				ex_mem.alu_ans_write = ex_mem.alu_ans_read;
				ex_mem.rf_data_write = ex_mem.rf_data_read;
				ex_mem.mux_ans_write = ex_mem.mux_ans_read;


				mem_wb.mem_data_write   = mem_wb.mem_data_read    ;
				mem_wb.bypass_data_write= mem_wb.bypass_data_read ;
				mem_wb.mux_ans_write    = mem_wb.mux_ans_read     ;

				mem_wb.RegWrite_write       = mem_wb.RegWrite_read      ;
				mem_wb.MemtoReg_write       = mem_wb.MemtoReg_read      ;
				mem_wb.readdata_write       = mem_wb.readdata_read     ;
				mem_wb.addressbypass_write  = mem_wb.addressbypass_read ;
				mem_wb.write_register_write = mem_wb.write_register_read;

        //printf("manu\n");
        convertinstr();
        //printf("mitraan\n");
        //wbins = mem_wb.name_write;
        id_ex.instr_name_write = id_ex.instr_name_read;
        ex_mem.instr_name_write = ex_mem.instr_name_read;
        mem_wb.instr_name_write = mem_wb.instr_name_read;

				if(mybranch == 1)
				{	
					id_ex.name_write = "nop";
						id_ex.ALUSrc_write = 0;
						id_ex.ALUOp_write = "000";
						id_ex.RegDest_write = 0;
						id_ex.RegWrite_write = 0;
						id_ex.MemWrite_write = 0;
						id_ex.MemtoReg_write = 0;
						id_ex.MemRead_write = 0;
						id_ex.Branch_write = 0;
						id_ex.readdata1_write = 0;
						id_ex.readdata2_write = 0;
						//id_ex.extender_write;
						id_ex.inst20_16_write = 0;
						id_ex.inst15_11_write = 0;
						id_ex.add_write = 0;
						id_ex.name_read = "nop";
						id_ex.ALUSrc_read = 0;
						id_ex.ALUOp_read = "000";
						id_ex.RegDest_read = 0;
						id_ex.RegWrite_read = 0;
						id_ex.MemWrite_read = 0;
						id_ex.MemtoReg_read = 0;
						id_ex.MemRead_read = 0;
						id_ex.Branch_read = 0;
						id_ex.readdata1_read = 0;
						id_ex.readdata2_read = 0;
						//id_ex.extender_read;
						id_ex.inst20_16_read = 0;
						id_ex.inst15_11_read = 0;
						id_ex.add_read = 0;

						if_id.name_write = "nop";
						if_id.name_read = "nop";

						ex_mem.name_write = "nop";
						ex_mem.name_read = "nop";
						ex_mem.MemWrite_write  = 0;
						ex_mem.MemRead_write   = 0;
						ex_mem.Branch_write    = 0;
						ex_mem.Zero_write      = 0;
						ex_mem.RegWrite_write  = 0;
						ex_mem.MemtoReg_write  = 0;
						ex_mem.readdata2_write = 0;
						ex_mem.addresult_write = 0;
						ex_mem.aluresult_write = 0;
						ex_mem.write_register_write = 0;
						ex_mem.MemWrite_read  = 0;
						ex_mem.MemRead_read   = 0;
						ex_mem.Branch_read    = 0;
						ex_mem.Zero_read      = 0;
						ex_mem.RegWrite_read  = 0;
						ex_mem.MemtoReg_read  = 0;
						ex_mem.readdata2_read = 0;
						ex_mem.addresult_read = 0;
						ex_mem.aluresult_read = 0;
						ex_mem.write_register_read = 0;
					
                ex_mem.instr_name_read = "nop";
                ex_mem.instr_name_write = "nop";
                if_id.instr_name_write = "nop";
                if_id.instr_name_read = "nop";
                id_ex.instr_name_write ="nop";
                id_ex.instr_name_read = "nop";
					mybranch = 0;
				}
				/*
				printf("===============================================================================================================================\n");
				
				printf("%s\n",if_id.name_write);
				printf("%s\n",id_ex.name_write);
				printf("%s\n",ex_mem.name_write);
				printf("%s\n",mem_wb.name_write);	
				printf("\n\n");*/

        highlight(if_id.name_read, id_ex.name_read,ex_mem.name_read,mem_wb.name_read,wbins,argv[2]);

				if(strcmp(if_id.name_read,"nop") && strcmp(if_id.name_read,"0"))
					{	tim++;}
				else if(strcmp(id_ex.name_read,"nop") && strcmp(if_id.name_read,"0"))
					{	tim++;}
				else if(strcmp(ex_mem.name_read,"nop") && strcmp(if_id.name_read,"0"))
					{	tim++;}
				else if(strcmp(mem_wb.name_read,"nop") && strcmp(if_id.name_read,"0"))
					{	tim++;}
				else
				{
					flag++;
				}
				

				/*if( strcmpi("nop",if_id.name_write) && strcmpi("nop",id_ex.name_write) && strcmpi("nop",ex_mem.name_write) && strcmpi("nop",mem_wb.name_write))
					{}
				else if ( strcmpi("0",if_id.name_write) && strcmpi("0",id_ex.name_write) && strcmpi("0",ex_mem.name_write) && strcmpi("0",mem_wb.name_write))
					{}
				else
				{
					time++;
				}*/
				//printf("instruction : %s\n",if_id.inst_read);
				//printf("%s\n",if_id.name_read);
					/*
				printf("-> ADD : %d\n", if_id.add_write);
				printf("-> R1 : %d\n", if_id.rf_rad1_write);
				printf("-> R2 : %d\n", if_id.rf_rad2_write);
				printf("-> I1 : %d\n", if_id.inst_data_15_0_write);
				printf("-> I2 : %d\n", if_id.inst_data_20_16_write);
				printf("-> I3 : %d\n", if_id.inst_data_15_11_write);
				printf("\n\n");

				printf("%d\n",id_ex.add_write            );
				printf("%d\n",id_ex.rf_outdata1_write    );
				printf("%d\n",id_ex.rf_outdata2_write    );
				printf("%d\n",id_ex.inst_data_15_0_write );
				printf("%d\n",id_ex.inst_data_20_16_write);
				printf("%d\n",id_ex.inst_data_15_11_write);
				printf("\n\n");


				printf("%d\n",ex_mem.add_ans_write);
				printf("%d\n",ex_mem.alu_ans_write);
				printf("%d\n",ex_mem.rf_data_write);
				printf("%d\n",ex_mem.mux_ans_write);
				printf("\n\n");

				printf("%d\n",mem_wb.mem_data_write   ); 
				printf("%d\n",mem_wb.bypass_data_write); 
				printf("%d\n",mem_wb.mux_ans_write    ); 
				printf("\n\n");

				printf("%d\n",rf_wdg_right);
				printf("%d\n",rf_wdg_left);
				printf("%d\n",rf_wadg_right);
				printf("%d\n",rf_wadg_left);

				*/

				/*

				printf("->%d\n",if_id.add_read);
				printf("->%s\n",if_id.name_read);
				printf("\n\n");

				printf("%d\n",write_datag_right);
				printf("\n\n");

				printf("->%d\n",id_ex.ALUSrc_read);
				printf("->%s\n",id_ex.ALUOp_read);
				printf("->%d\n",id_ex.RegDest_read);
				printf("->%d\n",id_ex.RegWrite_write);
				printf("->%d\n",id_ex.MemWrite_write);
				printf("->%d\n",id_ex.MemtoReg_write);
				printf("->%d\n",id_ex.MemRead_write);
				printf("->%d\n",id_ex.Branch_write);
				printf("->%d\n",id_ex.readdata1_read);
				printf("->%d\n",id_ex.readdata2_read);
				printf("->%d\n",id_ex.inst15_11_read);
				printf("->%d\n",id_ex.add_read);
				printf("\n\n");


				printf("->%d\n",ex_mem.MemWrite_read );
				printf("->%d\n",ex_mem.MemRead_read  );
				printf("->%d\n",ex_mem.Branch_read   );
				printf("->%d\n",ex_mem.Zero_read     );
				printf("->%d\n",ex_mem.RegWrite_read );
				printf("->%d\n",ex_mem.MemtoReg_read );
				printf("->%d\n",ex_mem.readdata2_read);
				printf("->%d\n",ex_mem.addresult_read);
				printf("->%d\n",ex_mem.aluresult_read);
				printf("\n\n");

				printf("->%d\n",mem_wb.RegWrite_write      );
				printf("->%d\n",mem_wb.MemtoReg_write      );
				printf("->%d\n",mem_wb.readdata_write      );
				printf("->%d\n",mem_wb.addressbypass_write );
				printf("->%d\n",mem_wb.write_register_write);

				*/
				
				/*
				for(i=0;i<34;i++)
				{
					printf("####### R%d  =  %d\n",i,rf[i]);
				}
				
				for(i=0;i<20;i++)
				{
					printf("####### %d\n",mem[i]);
				}*/
				/*

				for(i=0;i<20;i++)
				{
					printf("####### %d\n",mem[i]);
				}*/
		}
		else if(!strcmp(read,"regdump"))
		{
			for(i=0;i<10;i++)
			{
				printf("$$0%d: 0x%x\n",i,rf[i]);
			}
			for(i=10;i<32;i++)
			{
				printf("$$%d: 0x%x\n",i,rf[i]);
			}

			printf("hi: 0x%x\n",rf[32]);
			printf("lo: 0x%x\n",rf[33]);
			printf("pc: 0x%x\n",PC);
		}
		else if(!strcmp(read,"memdump"))
		{
			int offset;
			int l;
			scanf("%x",&offset);
			//printf("%d",offset);
			scanf("%d",&l);
			//printf("%d\n",l);
			for(i=0;i<l;i++)
			{	
				if(offset >= 268500992)
				printf("0x%x: 0x%x\n",(offset + 4*i),mem[offset-268500992 + i]);
			}

			//printf("clear");
		}
		else if(!strcmp(read,"exit"))
		{
			break;
		}
	}

	FILE *fout = fopen(argv[3], "w");
	tim++;
	float ipc = num_inst/(float)tim;
	float t = tim/2.0;
	float it = (tim-num_inst)/2.0;
	float itp = (tim-num_inst)/(float)tim*100.0;
	fprintf(fout,"Instructions,%d\n",num_inst);
	fprintf(fout,"Cycles,%d\n",tim);
	fprintf(fout,"IPC,%.4f\n",ipc);
	fprintf(fout,"Time (ns),%.4f\n",t);
	fprintf(fout,"Idle time (ns),%.4f\n", it);
	fprintf(fout,"Idle time (%%),%.4f%%\n",itp);
	fprintf(fout,"Cache Summary\n");
	fprintf(fout,"Cache L1-I\n");
	fprintf(fout,"num cache accesses,%d\n",cachei);
	fprintf(fout,"Cache L1-D\n");
	fprintf(fout,"num cache accesses,%d\n",cached);
	
	

}

yyerror(char *s)
{
	fprintf(stderr, "error: %s\n", s);
}

/*void firststage()
{
	char* instl = im[pc].instr; char* namel = im[pc].name;

}*/
/*
void secondstage()
{

	char* inst,char* name;

	if(!strcmp(name,"add"))
	{
		RegDest = 1;
		RegWrite = 1;
		ALUSrc = 0;
		ALUOp = "010";
		Branch = 0;
		MemRead = 0;
		MemWrite = 0;
		MemtoReg = 0;
	}
	else if(!strcmp(name,"sub"))
	{
		RegDest = 1;
		RegWrite = 1;
		ALUSrc = 0;
		ALUOp = "110";
		Branch = 0;
		MemRead = 0;
		MemWrite = 0;
		MemtoReg = 0;
	}
	else if(!strcmp(name,"and"))
	{
		RegDest = 1;
		RegWrite = 1;
		ALUSrc = 0;
		ALUOp = "000";
		Branch = 0;
		MemRead = 0;
		MemWrite = 0;
		MemtoReg = 0;
	}
	else if(!strcmp(name,"or"))
	{
		RegDest = 1;
		RegWrite = 1;
		ALUSrc = 0;
		ALUOp = "001";
		Branch = 0;
		MemRead = 0;
		MemWrite = 0;
		MemtoReg = 0;
	}
	else if(!strcmp(name,"lw"))
	{
		RegDest = 0;
		RegWrite = 1;
		ALUSrc = 1;
		ALUOp = "010";
		Branch = 0;
		MemRead = 1;
		MemWrite = 0;
		MemtoReg = 1;
	}
	else if(!strcmp(name,"addi"))
	{
		RegDest = 0;
		RegWrite = 1;
		ALUSrc = 1;
		ALUOp = "010";
		Branch = 0;
		MemRead = 0;
		MemWrite = 0;
		MemtoReg = 0;
	}
	else if(!strcmp(name,"sw"))
	{
		//RegDest = 0;
		RegWrite = 0;
		ALUSrc = 1;
		ALUOp = "010";
		Branch = 0;
		MemRead = 0;
		MemWrite = 1;
		//MemtoReg = 0;	
	}
	else if(!strcmp(name,"beq"))
	{
		//RegDest = 0;
		RegWrite = 0;
		ALUSrc = 0;
		ALUOp = "110";
		Branch = 1;
		MemRead = 0;
		MemWrite = 0;
		//MemtoReg = 0;
	}
	else if(!strcmp(name,"j"))
	{
		RegDest = 1;
		RegWrite = 1;
		ALUSrc = 0;
		Branch = 0;
		MemRead = 0;
		MemWrite = 0;
		MemtoReg = 0;
	}
	else if(!strcmp(name,"slt"))
	{
		RegDest = 1;
		RegWrite = 1;
		ALUSrc = 0;
		ALUOp = "111";
		Branch = 0;
		MemRead = 0;
		MemWrite = 0;
		MemtoReg = 0;
	}
}*/