#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>
#include<string.h>
FILE *output;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


/*make global data storage for different registers */

//IF-ID
int gy = 0;

int bin_to_dec(char* a)
{	
	//printf("in\n");
	/*int N = strlen(a);
	int ans = 0;
	int i;
	for(i=1;i <= N;i++)
	{
		ans+= a[N-i]*((int)pow(2,i-1));
	}
	//printf("out\n");
	return ans;*/

	return (int) strtol(a, NULL, 2);
}



char* dec_to_bin(long d)
{
	char* a = malloc(32*sizeof(a));

	int i;
	if(d >= 0)
	for(i = 0; i < 32;i++)
	{
		a[i] = d%2;
		d = d/2;
	}
	if(d < 0)
	{
		d = -1*d -1;
		for(i = 0; i < 32;i++)
		{
			a[i] = d%2;
			d = d/2;
		}
		for (i = 0; i < 32; i++)
		{
			a[i] = a[i] ^ 1;
		}
	}

	return a;
}

struct cache{
	char* name;
	char* instr;
}im[1000];

int mem[1000];
int mem_N = 0;
int rf[34];
int stall_left = 0;
int stall_right = 0;
int stall = 0;
int N=0;
int mybranch = 0;

struct IFID
{
	    char* instr_name_read;
    char* instr_name_write;
	int add_read;
	char* inst_read;char* name_read;
	int rf_rad1_read;
	int rf_rad2_read;
	int inst_data_15_0_read;
	int inst_data_20_16_read;
	int inst_data_15_11_read;

	int add_write;
	char* inst_write;char* name_write;
	int rf_rad1_write;
	int rf_rad2_write;
	int inst_data_15_0_write;
	int inst_data_20_16_write;
	int inst_data_15_11_write;


};
struct IFID if_id;

int PC = 0;
int step = 0;
int write_datag_left = 0;
int write_datag_right = 0;
int rf_wadg_left = 0;
int rf_wadg_right = 0;
int rf_wdg_left = 0;
int rf_wdg_right = 0;

//ID-EX
struct IDEX
{	
    char* instr_name_read;
    char* instr_name_write;
	char* name_read;
	char* name_write;

	int ALUSrc_read;
	char* ALUOp_read;
	int RegDest_read;
	int RegWrite_read;
	int MemWrite_read;
	int MemtoReg_read;
	int MemRead_read;
	int Branch_read;
	int sa_read;
	int sa_write;
	int readdata1_read;
	int readdata2_read;
	//int extender_read;
	int inst20_16_read;
	int inst15_11_read;
	int add_read            ;

	int rf_outdata1_read    ;
	int rf_outdata2_read    ;
	int inst_data_15_0_read ;
	int inst_data_20_16_read;
	int inst_data_15_11_read;


	int ALUSrc_write;
	char* ALUOp_write;
	int RegDest_write;
	int RegWrite_write;
	int MemWrite_write;
	int MemtoReg_write;
	int MemRead_write;
	int Branch_write;

	int readdata1_write;
	int readdata2_write;
	//int extender_write;
	int inst20_16_write;
	int inst15_11_write;
	int add_write;

	int rn_read;
	int rn_write;
	int rm_read;
	int rm_write;

	int rf_outdata1_write    ;
	int rf_outdata2_write    ;
	int inst_data_15_0_write ;
	int inst_data_20_16_write;
	int inst_data_15_11_write;
}id_ex;

//EX-MEM
struct EXMEM
{	
    char* instr_name_read;
    char* instr_name_write;
	char* name_read;
	char* name_write;

	int MemWrite_read;
	int MemRead_read;
	int Branch_read;
	int Zero_read;
	int RegWrite_read;
	int MemtoReg_read;
		
	int rn_read;
	int rn_write;
	int rm_read;
	int rm_write;

	int readdata2_read;
	int addresult_read;
	int aluresult_read;
	int write_register_read;

	int add_ans_read;
	int alu_ans_read;
	int rf_data_read;
	int mux_ans_read;

	int add_ans_write;
	int alu_ans_write;
	int rf_data_write;
	int mux_ans_write;


	int MemWrite_write;
	int MemRead_write;
	int Branch_write;
	int Zero_write;
	int RegWrite_write;
	int MemtoReg_write;
	
	int readdata2_write;
	int addresult_write;
	int aluresult_write;
	int write_register_write;		
}ex_mem;

//MEM-WB
struct MEMWB
{
    char* instr_name_read;
    char* instr_name_write;
	char* name_read;
	char* name_write;

	int RegWrite_read;
	int MemtoReg_read;

	int readdata_read;
	int addressbypass_read;
	int write_register_read;

	int mem_data_read    ;
	int bypass_data_read ;
	int mux_ans_read     ;



	int RegWrite_write;
	int MemtoReg_write;

	int readdata_write;
	int addressbypass_write;
	int write_register_write;

	int mem_data_write ;
	int bypass_data_write ;
	int mux_ans_write ;
}mem_wb;

/*make local data flags for each wire */
int th = 0;
int tim = 0;
int num_inst = 0;
int cachei = 0;
int cached = 0;

void* thread_IF()
{

		if(PC >= N )//|| stall_left == 1)
		{
			if_id.inst_read = "00000001010010110100100000100000";
			if_id.name_read = "nop";
			//printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++PC : %d\n",PC);
		}
		else if (stall_left == 1)
		{
			//time++;
		}
		else
		{
			char* instl; char* namel;

			if_id.add_read = PC + 1;
			instl = im[PC].instr; namel = im[PC].name;
			if_id.inst_read = instl; if_id.name_read = namel;
			cachei++;//tim++;

			PC++;
			
		}
}

void* thread_ID()
{
	//if(!strcmp(if_id.name_write,"nop"))
	//	return;
	gy = 1;
	while(gy == 0)
	{
		
	}

	gy = 0;
	int rf_rad1 = 0;
	int rf_rad2 = 0;
	int rf_wad  = 0;
	int rf_wd   = 0;

	int rf_outdata1 = 	  0;
	int rf_outdata2 =     0;
	int inst_data_15_0 =  0;
	int inst_data_20_16 = 0;
	int inst_data_15_11 = 0;


	int add = 0;
	//int RegWrite = 0;
	//int extender = 0;
	int inst20_16 = 1;
	int inst15_11 = 1;
	int write_register = 0;
	int write_data = 0;				//exception : how to store so as to access in WB stage
	int readdata1 = 0;
	int readdata2 = 0;

	char* inst;
	char* name;
	int RegDest = 0;
	int RegWrite = 0;
	int ALUSrc = 0;
	char* ALUOp = malloc(3*sizeof(char));
	ALUOp = "000";
	int Branch = 0;
	int MemRead = 0;
	int MemWrite = 0;
	int MemtoReg = 0;
	int sa = 0;
		
		pthread_mutex_lock(&mutex);

		inst = if_id.inst_write;
		name = if_id.name_write;

		add = if_id.add_write;
		RegWrite = mem_wb.RegWrite_write;
		write_register = mem_wb.write_register_write;
		//printf("3\n");
		write_data 	   = write_datag_left;

		pthread_mutex_unlock(&mutex);

		char* ty = malloc(5*sizeof(char));
		int u;
		for(u=21;u<26;u++)
		{
			ty[u-21] = inst[u];
		}
		ty[u-21] = '\0';

		//printf("%s , %s\n",name,ty);
		sa = bin_to_dec(ty);
		//printf("%s , %d\n",name,sa);
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
		if(!strcmp(name,"nop"))
		{
			RegDest = 0;
			RegWrite = 0;
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
			RegDest = 0;
			RegWrite = 0;
			ALUSrc = 1;
			ALUOp = "010";
			Branch = 0;
			MemRead = 0;
			MemWrite = 1;
			MemtoReg = 0;	
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
		else if(!strcmp(name,"ori"))
		{
			RegDest = 0;
			RegWrite = 1;
			ALUSrc = 1;
			Branch = 0;
			MemRead = 0;
			MemWrite = 0;
			MemtoReg = 0;
		}
		else if(!strcmp(name,"lui"))
		{
			RegDest = 0;
			RegWrite = 1;
			ALUSrc = 1;
			Branch = 0;
			MemRead = 0;
			MemWrite = 0;
			MemtoReg = 0;
		}
		else if(!strcmp(name,"bgtz"))
		{
			//RegDest = 0;
			RegWrite = 0;
			//ALUSrc = 1;
			Branch = 1;
			MemRead = 0;
			MemWrite = 0;
			MemtoReg = 0;
		}
		else if(!strcmp(name,"blez"))
		{
			//RegDest = 0;
			RegWrite = 0;
			//ALUSrc = 1;
			Branch = 1;
			MemRead = 0;
			MemWrite = 0;
			MemtoReg = 0;
		}
		else if(!strcmp(name,"lb"))
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

		else if(!strcmp(name,"sb"))
		{
			//RegDest = 0;
			RegWrite = 0;
			ALUSrc = 1;
			ALUOp = "010";
			Branch = 0;
			MemRead = 0;
			MemWrite = 1;
			MemtoReg = 0;	
		}
		else if(!strcmp(name,"bgez"))
		{
			//RegDest = 0;
			RegWrite = 0;
			//ALUSrc = 1;
			Branch = 1;
			MemRead = 0;
			MemWrite = 0;
			MemtoReg = 0;
		}
		else if(!strcmp(name,"bltz"))
		{
			//RegDest = 0;
			RegWrite = 0;
			//ALUSrc = 1;
			Branch = 1;
			MemRead = 0;
			MemWrite = 0;
			MemtoReg = 0;
		}
		else if(!strcmp(name,"slti"))
		{
			RegDest = 0;
			RegWrite = 1;
			ALUSrc = 1;
			ALUOp = "111";
			Branch = 0;
			MemRead = 0;
			MemWrite = 0;
			MemtoReg = 0;
		}
		else if(!strcmp(name,"mult"))
		{
			//RegDest = 0;
			RegWrite = 0;
			ALUSrc = 0;
			//ALUOp = "111";
			Branch = 0;
			MemRead = 0;
			MemWrite = 0;
			MemtoReg = 0;
		}
		else if(!strcmp(name,"madd"))
		{
			//RegDest = 0;
			RegWrite = 0;
			ALUSrc = 0;
			//ALUOp = "111";
			Branch = 0;
			MemRead = 0;
			MemWrite = 0;
			MemtoReg = 0;
		}
		if(!strcmp(name,"nor"))
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
		if(!strcmp(name,"sll"))//override alusrc
		{
			RegDest = 1;
			RegWrite = 1;
			ALUSrc = 0;
			//ALUOp = "010";
			Branch = 0;
			MemRead = 0;
			MemWrite = 0;
			MemtoReg = 0;
		}
		if(!strcmp(name,"sllv"))
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
		if(!strcmp(name,"sltu"))
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

		//tobedone
		readdata1 = 1;
		//readdata2 = ;

		if(ALUSrc == 1)
		{
			readdata2 = 0;
		}
		else
			readdata2 = 1;

		//if(id_ex.MemRead_write == 1 && (IF/ID.Rn=ID/EX.Rd or IF/ID.Rm=ID/EX.Rd))
		//if(!strcmp(if_id.name_write,"nop"))
		//	return;

		if(readdata1 == 1)
		{
			
			rf_rad1 = if_id.rf_rad1_write;
			if(rf_rad1 >= 0)
			{rf_outdata1 = rf[rf_rad1];}
		}

		if(readdata2 == 1)
		{
			rf_rad2 = if_id.rf_rad2_write;
			if(rf_rad2 >= 0)
			rf_outdata2 = rf[rf_rad2 ];
		}


		if(id_ex.MemRead_write) 
		{	
			int rdd = 0;
			pthread_mutex_lock(&mutex);
			if(id_ex.RegDest_write == 0)
			{
				rdd = id_ex.inst_data_20_16_write;
			}
			else
			{
				rdd = id_ex.inst_data_15_11_write;
			}
			pthread_mutex_unlock(&mutex);


			if(( readdata1 == 1 && if_id.rf_rad1_write ==  rdd) || (readdata2 == 1 && if_id.rf_rad2_write == rdd))
			{
				//printf("^@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
				stall_right = 1; //timei++;
			}
		}


		

		inst_data_15_0 = if_id.inst_data_15_0_write;

		inst_data_20_16 = if_id.inst_data_20_16_write;

		inst_data_15_11 = if_id.inst_data_15_11_write;



		pthread_mutex_lock(&mutex);

		if(stall_right == 1)
		{
		id_ex.name_read = "nop";
		id_ex.rn_read = rf_rad1;
		id_ex.rm_read = rf_rad2;
		id_ex.sa_read = sa;
		id_ex.ALUSrc_read = 0;
		id_ex.ALUOp_read = ALUOp;
		id_ex.RegDest_read = 0;
		id_ex.RegWrite_read = 0;
		id_ex.MemWrite_read = 0;
		id_ex.MemtoReg_read = 0;
		id_ex.MemRead_read =0;
		id_ex.Branch_read =0;

		id_ex.readdata1_read = readdata1;
		id_ex.readdata2_read = readdata2;
		id_ex.inst20_16_read = inst20_16;
		id_ex.inst15_11_read = inst15_11;

		id_ex.rf_outdata1_read    = rf_outdata1    ;
		id_ex.rf_outdata2_read    = rf_outdata2    ;
		id_ex.inst_data_15_0_read = inst_data_15_0 ;
		id_ex.inst_data_20_16_read= inst_data_20_16;
		id_ex.inst_data_15_11_read= inst_data_15_11;


		//int extender_read;
		//int inst20_16_read;
		//int inst15_11_read;
		id_ex.add_read = add;
		//printf("4\n");
		}
		else
		{

		id_ex.name_read = name;
		id_ex.rn_read = rf_rad1;
		id_ex.rm_read = rf_rad2;
		id_ex.sa_read = sa;
		id_ex.ALUSrc_read = ALUSrc;
		id_ex.ALUOp_read = ALUOp;
		id_ex.RegDest_read = RegDest;
		id_ex.RegWrite_read = RegWrite;
		id_ex.MemWrite_read = MemWrite;
		id_ex.MemtoReg_read = MemtoReg;
		id_ex.MemRead_read = MemRead;
		id_ex.Branch_read = Branch;

		id_ex.readdata1_read = readdata1;
		id_ex.readdata2_read = readdata2;
		id_ex.inst20_16_read = inst20_16;
		id_ex.inst15_11_read = inst15_11;

		id_ex.rf_outdata1_read    = rf_outdata1    ;
		id_ex.rf_outdata2_read    = rf_outdata2    ;
		id_ex.inst_data_15_0_read = inst_data_15_0 ;
		id_ex.inst_data_20_16_read= inst_data_20_16;
		id_ex.inst_data_15_11_read= inst_data_15_11;

        id_ex.instr_name_read = if_id.instr_name_write; 
		//int extender_read;
		//int inst20_16_read;
		//int inst15_11_read;
		id_ex.add_read = add;
		//printf("4\n");	
		}
		
		pthread_mutex_unlock(&mutex);		
}

void* thread_EX()
{
	//if(!strcmp(id_ex.name_write,"nop"))
	//	return;
	char* name = "0";
	int rf_outdata1 = 	  0;
	int rf_outdata2 =     0;
	int inst_data_15_0 =  0;
	int inst_data_20_16 = 0;
	int inst_data_15_11 = 0;
	int sa = 0;
	int fwda = 0;
	int fwdb = 0;

	int add_ans = 0;
	int alu_ans = 0;
	int mux_ans = 0;

	int ALUSrc = 0;
	char* ALUOp = malloc(3*sizeof(char));
	ALUOp = "000";
	int RegDest = 0;
	int RegWrite = 0;
	int MemtoReg = 0;
	int MemWrite = 0;
	int MemRead = 0;
	int Branch = 0;
	int Zero = 0;

	int readdata1 = 0;
	int readdata2 = 0;
	int mux1 = 0;
	//int extender = 0;
	int inst20_16 = 0;
	int inst15_11 = 0;
	int write_register = 0;
	int add = 0;
	int addresult = 0;
	int aluresult = 0;
	int bypass = 0;
	int shift = 0;


		pthread_mutex_lock(&mutex);
		//printf("5\n");
		add = id_ex.add_write;
		//readdata1 = id_ex.readdata1_write;
		//readdata2 = id_ex.readdata2_write;
		//extender = id_ex.extender_write;
		inst20_16 = id_ex.inst20_16_write;
		inst15_11 = id_ex.inst15_11_write;
		//bypass = id_ex.readdata2_write;
		//shift = id_ex.extender_write;
		ALUSrc = id_ex.ALUSrc_write;
		ALUOp = id_ex.ALUOp_write;
		RegDest = id_ex.RegDest_write;
		RegWrite = id_ex.RegWrite_write;
		MemWrite = id_ex.MemWrite_write;
		MemRead = id_ex.MemRead_write;
		MemtoReg = id_ex.MemtoReg_write;
		Branch = id_ex.Branch_write;
		//Zero = id_ex.Zero_write;
		name = id_ex.name_write;
		sa = id_ex.sa_write;
		rf_outdata1     = id_ex.rf_outdata1_write;
		rf_outdata2     = id_ex.rf_outdata2_write;
		inst_data_15_0  = id_ex.inst_data_15_0_write;
		inst_data_20_16 = id_ex.inst_data_20_16_write;
		inst_data_15_11 = id_ex.inst_data_15_11_write;

		pthread_mutex_unlock(&mutex);

		readdata1 = 1;

		if(MemWrite == 1)
			bypass = 1;
		else
			bypass = 0;

		if(ALUSrc==0)
		{
			readdata2 = 1; mux1 = 0;
		}
		else
			{readdata2 = 0; mux1 = 1;}

		if(Branch == 1)
		{
			shift = 1;
		}
		else
		{
			shift = 0;
		}

		if(readdata1 == 1 && (readdata2 == 1 || mux1 == 1))
			aluresult = 1;
		else
			aluresult = 0;

		if(RegDest == 1)
		{
			write_register = inst15_11;
		}
		else
			write_register = inst20_16;

		//Zero = Branch;


		addresult = add + shift;

		int alu1 = 0;
		int alu2 = 0;

		if(shift == 1)
		{
			//add_ans = inst_data_15_0*4 + add;
			add_ans =  add + inst_data_15_0 ;
		}

		pthread_mutex_lock(&mutex);		

		if (ex_mem.RegWrite_write == 1 && ex_mem.mux_ans_write == id_ex.rn_write) 
		 	fwda = 1 ;

		else if (mem_wb.RegWrite_write == 1 && ex_mem.mux_ans_write != id_ex.rn_write && mem_wb.mux_ans_write == id_ex.rn_write)
			fwda = 2 ;



		if (ex_mem.RegWrite_write == 1 && ex_mem.mux_ans_write == id_ex.rm_write) 
		 	fwdb = 1 ;

		else if (mem_wb.RegWrite_write == 1 && ex_mem.mux_ans_write != id_ex.rm_write && mem_wb.mux_ans_write == id_ex.rm_write)
			fwdb = 2 ;


		if(ALUSrc == 0)
		{

			if(fwda == 0)
			{
				alu1 = rf_outdata1;
			}
			else if(fwda == 1)
			{
				alu1 = ex_mem.alu_ans_write;
			}
			else if(fwda == 2)
			{
				
				if(mem_wb.MemtoReg_write == 0)
					alu1 = mem_wb.bypass_data_write;
				else
					alu1 = mem_wb.mem_data_write;		
			}

			if(fwdb == 0)
			{
				alu2 = rf_outdata2;
			}
			else if(fwdb == 1)
			{
				alu2 = ex_mem.alu_ans_write;
			}
			else if(fwdb == 2)
			{
				if(mem_wb.MemtoReg_write == 0)
					alu2 = mem_wb.bypass_data_write;
				else
					alu2 = mem_wb.mem_data_write;
			}
		}
		else
		{

			if(fwda == 0)
			{
				alu1 = rf_outdata1;
			}
			else if(fwda == 1)
			{
				alu1 = ex_mem.alu_ans_write;
			}
			else if(fwda == 2)
			{
				
				if(mem_wb.MemtoReg_write == 0)
					alu1 = mem_wb.bypass_data_write;
				else
					alu1 = mem_wb.mem_data_write;		
			}

			if(fwdb == 0)
			{
				alu2 = (inst_data_15_0);
			}
			else if(fwdb == 1)
			{
				alu2 = ex_mem.alu_ans_write;
			}
			else if(fwdb == 2)
			{
				if(mem_wb.MemtoReg_write == 0)
					alu2 = mem_wb.bypass_data_write;
				else
					alu2 = mem_wb.mem_data_write;
			}
		}


		if(!strcmp(id_ex.name_write,"and"))
		{
			alu_ans = alu1 & alu2 ;
		}
		else if (!strcmp(id_ex.name_write,"add"))
		{
			alu_ans = alu1 + alu2 ;
		}
		else if (!strcmp(id_ex.name_write,"or"))
		{
			alu_ans = alu1 | alu2 ;
		}
		else if (!strcmp(id_ex.name_write,"lw"))
		{
			alu_ans = alu1 + alu2 ;	
		}
		else if (!strcmp(id_ex.name_write,"sw"))
		{
			alu_ans = alu1 + alu2 ;
		}
		else if (!strcmp(id_ex.name_write,"sub"))
		{
			alu_ans = alu1 - alu2 ;
		}
		else if (!strcmp(id_ex.name_write,"beq"))
		{
			if(alu1 == alu2)
				Zero = 1;
			else
				Zero = 0;
		}
		else if (!strcmp(id_ex.name_write,"j"))
		{
				
		}
		else if (!strcmp(id_ex.name_write,"addi"))
		{
			alu_ans = alu1 + alu2 ;
		}
		else if (!strcmp(id_ex.name_write,"ori"))
		{
			alu_ans = alu1 | alu2 ;
		}
		else if (!strcmp(id_ex.name_write,"lui"))
		{
			alu_ans = alu2 << 16;
		}
		else if (!strcmp(id_ex.name_write,"madd"))
		{
			alu_ans = alu2*alu1;
		}
		else if (!strcmp(id_ex.name_write,"slti"))
		{
			if(alu1 < alu2)
				alu_ans = 1;
			else
				alu_ans = 0;
		}
		else if (!strcmp(id_ex.name_write,"bgtz"))
		{
			if(alu1 > 0)
				Zero = 1;
		}
		else if (!strcmp(id_ex.name_write,"blez"))
		{
			if(alu1 <= 0)
				Zero = 1;
		}
		else if (!strcmp(id_ex.name_write,"lb"))
		{
			alu_ans = alu1 + alu2 ;
		}
		else if (!strcmp(id_ex.name_write,"sb"))
		{
			alu_ans = alu1 + alu2 ;
		}
		else if (!strcmp(id_ex.name_write,"bgez"))
		{
			if(alu1 >= 0)
				Zero = 1;
		}
		else if (!strcmp(id_ex.name_write,"bltz"))
		{
			if(alu1 < 0)
				Zero = 1;
		}
		else if (!strcmp(id_ex.name_write,"mult"))
		{
			long temp = alu1*alu2;
			//printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee  %f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\\n",temp);
			rf[32] = (temp>>32);
			rf[33] = (temp<<32)>>32;
		}
		else if (!strcmp(id_ex.name_write,"nor"))
		{
			alu_ans = ~(alu1 | alu2);
		}
		else if (!strcmp(id_ex.name_write,"sll"))
		{	
			//printf("Shifting %d by %d\n",alu2,sa);
			alu_ans = alu2 << sa;
		}
		else if (!strcmp(id_ex.name_write,"sllv"))
		{
			alu_ans = (alu2 << alu1);
		}
		else if (!strcmp(id_ex.name_write,"sltu"))
		{
			if(abs(alu1) < abs(alu2))
				alu_ans = 1;
			else
				alu_ans = 0;
		}

		

		//printf("++++++++++++++++++++++++   %d\n",alu_ans);

		if(RegDest == 0)
		{
			mux_ans = inst_data_20_16;
		}
		else
		{
			mux_ans = inst_data_15_11;
		}


		
		ex_mem.addresult_read = addresult;
		ex_mem.aluresult_read = aluresult;
		ex_mem.readdata2_read = bypass;
		ex_mem.write_register_read = write_register;
		ex_mem.Zero_read = Zero;
		ex_mem.MemWrite_read = MemWrite;
		ex_mem.MemRead_read = MemRead;
		ex_mem.Branch_read = Branch;
		ex_mem.RegWrite_read = RegWrite;
		ex_mem.MemtoReg_read = MemtoReg;
		ex_mem.name_read = name;
		ex_mem.alu_ans_read = alu_ans;
		ex_mem.add_ans_read = add_ans;
		ex_mem.mux_ans_read = mux_ans;
		ex_mem.rf_data_read = rf_outdata2; 		
        ex_mem.instr_name_read = id_ex.instr_name_write;        
		pthread_mutex_unlock(&mutex);

		//printf("---------> fwda %d\n",fwda);
		//printf("---------> fwdb %d\n",fwdb);
}

void* thread_MEM()
{
	//if(!strcmp(ex_mem.name_write,"nop"))
	//	return;

	

	double fwdc = 0;
	char* name = "nop";
	int alu_ans = 0;
	int rf_data = 0;
	int mux_ans = 0;
	int mem_data = 0;
	int bypass_data = 0;

	int MemWrite = 0;
	int MemRead = 0;
	//int Branch = 0;
	//int Zero = 0;
	int RegWrite = 0;
	int MemtoReg = 0;
	
	int readdata = 0;
	int readdata2 = 0;
	//int addresult = 0;
	int aluresult = 0;
	int write_register = 0;
	int addressbypass = 0;


			pthread_mutex_lock(&mutex);
			MemWrite = ex_mem.MemWrite_write;
			MemRead = ex_mem.MemtoReg_write;
			//Branch = ex_mem.Branch_write;
			//Zero = ex_mem.Zero_write;
			RegWrite = ex_mem.RegWrite_write;
			name = ex_mem.name_write;
			alu_ans = ex_mem.alu_ans_write;
			mux_ans = ex_mem.mux_ans_write;
			rf_data = ex_mem.rf_data_write;

			MemtoReg = ex_mem.MemtoReg_write;

			if(MemRead == 1 || MemWrite == 1)
			{
				aluresult = 1; addressbypass = 0;
			}
			else
				{aluresult = 0;addressbypass = 1;}

			if(MemWrite == 1)
			{
				readdata2 = 1;
			}
			else
				readdata2 = 0;

			if(MemRead == 1)
			{
				readdata = 1;
			}
			else
				readdata = 0;

			write_register = ex_mem.write_register_write;
			//addressbypass = ex_mem.aluresult_write;
			//printf("7------------------- : %d\n",alu_ans);


			int fg = 0;

			if( mem_wb.RegWrite_write == 1 && mem_wb.mux_ans_write == ex_mem.mux_ans_write )
				fwdc = 1;


			//printf("%s , %d\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\\n\n\n\n\n\n\n\n\n\n\\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\\n\n\n\n\n\n\n\n\n\\nn\n",name,rf_data);

			if(fwdc == 0)
			{
				fg = rf[ex_mem.mux_ans_write];
			}
			else
			{
				//printf("come here :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::;\n\n\n\\n\n\n\n\n\n");
				if(mem_wb.MemtoReg_write == 0)
					fg = mem_wb.addressbypass_write;
				else
					fg = mem_wb.mem_data_write;

				//printf("fg %d\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n",fg);
			}

			if(MemWrite == 1)
			{
				if(alu_ans >= 268500992)
				{mem[(alu_ans - 268500992)/4] = fg;cached++;}
			}

			if(MemRead == 1)
			{	
				if(alu_ans >= 268500992)
				{
					mem_data = mem[(alu_ans - 268500992)/4];cached++;
				}
			}



			
			if(ex_mem.Branch_write == 1 && ex_mem.Zero_write == 1)
			{

				
				PC = ex_mem.add_ans_write; //printf("Branching to : %s\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n",im[PC].name);
				//time = time + 3; //timei = timei + 3;
				mybranch = 1;
			}
			else
			{
				//PC++;
			}
			


			//printf("here");

			//printf("here");

			bypass_data = alu_ans;

			pthread_mutex_unlock(&mutex);

			pthread_mutex_lock(&mutex);
			mem_wb.RegWrite_read = RegWrite;
			mem_wb.MemtoReg_read = MemtoReg;
			mem_wb.readdata_read = readdata;
			mem_wb.write_register_read = write_register;
			mem_wb.addressbypass_read = addressbypass;
			mem_wb.name_read = name;
			mem_wb.mem_data_read = mem_data;
			mem_wb.bypass_data_read = bypass_data;
			mem_wb.mux_ans_read = mux_ans;
			//printf("8\n");
			            mem_wb.instr_name_read = ex_mem.instr_name_write;
			pthread_mutex_unlock(&mutex);

			//printf("---------> fwdc %d\n",fwdc);
}

void* thread_WB()
{
	//int RegWrite = 0;
	//if(!strcmp(mem_wb.name_write,"nop"))
	//	return;
	int MemtoReg = 0;
	int readdata = 0;
	int addressbypass = 0;
	int write_register = 0;
	int RegWrite = 0;
	int mux_ans = 0;
	char* name = malloc(20*sizeof(char));
		pthread_mutex_lock(&mutex);
		//RegWrite = mem_wb.RegWrite;
		MemtoReg = mem_wb.MemtoReg_write;
		readdata = mem_wb.readdata_write;
		addressbypass = mem_wb.addressbypass_write;
		RegWrite = mem_wb.RegWrite_write;
		mux_ans = mem_wb.mux_ans_write;
		write_register = mem_wb.write_register_write;
		name = mem_wb.name_write;
		rf_wadg_right = mem_wb.mux_ans_write;

		if(strcmp(name,"nop") && strcmp(name,"0"))
			num_inst++;
		//printf("10\n");
		if(RegWrite == 1)
		{
			if(MemtoReg == 1)
			{
				write_datag_right = readdata;

				//rf_wdg_right = mem_wb.mem_data_write;
				if(mux_ans>=0)
				rf[mux_ans] = mem_wb.mem_data_write;
			}
			else
			{
				write_datag_right = addressbypass;

				//rf_wdg_right = mem_wb.bypass_data_write;
				if(mux_ans>=0)
				rf[mux_ans] = mem_wb.bypass_data_write;
			}
		}

		gy  = 1;

		pthread_mutex_unlock(&mutex);
}
 
void highlight(char* IF, char* ID, char* EX, char* MEM, char* WB,char* filename)
{
    /*printf("===========================\n");
    printf("%s\n", IF);
    printf("%s\n", ID);
    printf("%s\n", EX);
    printf("%s\n", MEM);
    printf("%s\n", WB);
    printf("===========================\n");*/
 
    char* a1 = "Active";
    char* a2 = "Active";
    char* a3 = "Active";
    char* a4 = "Active";
    char* a5 = "Active";

    if(!strcmp(IF,"nop") || !strcmp(IF,"0"))
    	a1="Inactive";
	if(!strcmp(ID,"nop") || !strcmp(ID,"0"))
    	a2="Inactive";
    if(!strcmp(EX,"nop") || !strcmp(EX,"0"))
    	a3="Inactive";
    if(!strcmp(MEM,"nop") || !strcmp(MEM,"0"))
    	a4="Inactive";
    if(!strcmp(WB,"nop") || !strcmp(WB,"0"))
    	a5="Inactive";

    output = fopen(filename,"w");
    fprintf(output,"<svg\n   xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n   xmlns:cc=\"http://creativecommons.org/ns#\"\n   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n   xmlns:svg=\"http://www.w3.org/2000/svg\"\n   xmlns=\"http://www.w3.org/2000/svg\"\n   xmlns:xlink=\"http://www.w3.org/1999/xlink\"\n   xmlns:sodipodi=\"http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd\"\n   xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\"\n   width=\"389mm\"\n   height=\"345mm\"\n   viewBox=\"0 0 389 345\"\n   version=\"1.1\"\n   id=\"svg8\"\n   inkscape:version=\"0.92.1 r15371\"\n   sodipodi:docname=\"drawing_start_color.svg\">\n  <defs\n     id=\"defs2\">\n    <linearGradient\n       inkscape:collect=\"always\"\n       id=\"linearGradient4780\">\n      <stop\n         style=\"stop-color:#0000ff;stop-opacity:1;\"\n         offset=\"0\"\n         id=\"stop4776\" />\n      <stop\n         style=\"stop-color:#0000ff;stop-opacity:0;\"\n         offset=\"1\"\n         id=\"stop4778\" />\n    </linearGradient>\n    <inkscape:perspective\n       id=\"perspective10\"\n       inkscape:persp3d-origin=\"372.04703 : 350.78736 : 1\"\n       inkscape:vp_z=\"744.09447 : 526.18101 : 1\"\n       inkscape:vp_y=\"0 : 999.99995 : 0\"\n       inkscape:vp_x=\"0 : 526.18101 : 1\"\n       sodipodi:type=\"inkscape:persp3d\" />\n    <inkscape:perspective\n       sodipodi:type=\"inkscape:persp3d\"\n       inkscape:vp_x=\"0 : 526.18101 : 1\"\n       inkscape:vp_y=\"0 : 999.99995 : 0\"\n       inkscape:vp_z=\"744.09447 : 526.18101 : 1\"\n       inkscape:persp3d-origin=\"372.04703 : 350.78736 : 1\"\n       id=\"perspective2390\" />\n    <inkscape:perspective\n       sodipodi:type=\"inkscape:persp3d\"\n       inkscape:vp_x=\"0 : 526.18101 : 1\"\n       inkscape:vp_y=\"0 : 999.99995 : 0\"\n       inkscape:vp_z=\"744.09447 : 526.18101 : 1\"\n       inkscape:persp3d-origin=\"372.04703 : 350.78736 : 1\"\n       id=\"perspective2403\" />\n    <radialGradient\n       inkscape:collect=\"always\"\n       xlink:href=\"#linearGradient4780\"\n       id=\"radialGradient4782\"\n       cx=\"329.80286\"\n       cy=\"263.45383\"\n       fx=\"329.80286\"\n       fy=\"263.45383\"\n       r=\"20.976562\"\n       gradientTransform=\"matrix(1,0,0,0.22164804,0,205.0598)\"\n       gradientUnits=\"userSpaceOnUse\" />\n  </defs>\n  <sodipodi:namedview\n     id=\"base\"\n     pagecolor=\"#ffffff\"\n     bordercolor=\"#666666\"\n     borderopacity=\"1.0\"\n     inkscape:pageopacity=\"0.0\"\n     inkscape:pageshadow=\"2\"\n     inkscape:zoom=\"2\"\n     inkscape:cx=\"979.59148\"\n     inkscape:cy=\"392.88746\"\n     inkscape:document-units=\"mm\"\n     inkscape:current-layer=\"layer1\"\n     showgrid=\"false\"\n     inkscape:window-width=\"1920\"\n     inkscape:window-height=\"1017\"\n     inkscape:window-x=\"-8\"\n     inkscape:window-y=\"-8\"\n     inkscape:window-maximized=\"1\"\n     showguides=\"false\" />\n  <metadata\n     id=\"metadata5\">\n    <rdf:RDF>\n      <cc:Work\n         rdf:about=\"\">\n        <dc:format>image/svg+xml</dc:format>\n        <dc:type\n           rdf:resource=\"http://purl.org/dc/dcmitype/StillImage\" />\n        <dc:title />\n      </cc:Work>\n    </rdf:RDF>\n  </metadata>\n  <g\n     inkscape:label=\"Layer 1\"\n     inkscape:groupmode=\"layer\"\n     id=\"layer1\"\n     transform=\"translate(0,48)\">\n    <g\n       id=\"layer1-1\"\n       inkscape:label=\"Layer 1\"\n       transform=\"matrix(0.2776759,0,0,0.34150913,59.285581,17.9824)\">\n      <g\n         id=\"g4770\"\n         transform=\"matrix(1.5592257,0,0,1.2503301,-176.7493,-227.31708)\">\n        <ellipse\n           style=\"display:inline;overflow:visible;visibility:visible;fill:#536dff;fill-opacity:0.2857143;stroke:#ff0000;stroke-width:1.99943709;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           id=\"ellipse4768\"\n           cx=\"340.57629\"\n           cy=\"286.41342\"\n           rx=\"25.040159\"\n           ry=\"37.5\" />\n        <ellipse\n           ry=\"37.5\"\n           rx=\"25.040159\"\n           cy=\"590.14545\"\n           cx=\"544.23254\"\n           id=\"ellipse4804\"\n           style=\"display:inline;overflow:visible;visibility:visible;fill:#536dff;fill-opacity:0.2857143;stroke:#ff0000;stroke-width:1.99943709;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1;marker:none;enable-background:accumulate\" />\n        <ellipse\n           style=\"display:inline;overflow:visible;visibility:visible;fill:#536dff;fill-opacity:0.2857143;stroke:#ff0000;stroke-width:3.15335703;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           id=\"ellipse7230\"\n           cx=\"564.09399\"\n           cy=\"773.55719\"\n           rx=\"63.263092\"\n           ry=\"36.918903\" />\n        <text\n           id=\"text4766\"\n           y=\"279.50275\"\n           x=\"341.19086\"\n           style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#00ff00;fill-opacity:1;stroke:#ff0000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;\"\n           xml:space=\"preserve\"><tspan\n             id=\"tspan4764\"\n             y=\"282.95071\"\n             x=\"341.19086\"\n             sodipodi:role=\"line\"\n             style=\"font-size:12px;line-height:1.25;stroke:#ff0000;stroke-opacity:1;fill:#00ff00;fill-opacity:1;\" /><tspan\n             y=\"290.45071\"\n             x=\"341.19086\"\n             sodipodi:role=\"line\"\n             style=\"font-size:12px;line-height:1.25;stroke:#ff0000;stroke-opacity:1;fill:#00ff00;fill-opacity:1;\"\n             id=\"tspan4774\">Control</tspan></text>\n        <rect\n           style=\"fill:#536dff;fill-opacity:0.2857143;stroke:#ff0000;stroke-width:1.99943709;stroke-linecap:round;stroke-linejoin:round;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n           id=\"rect4784\"\n           width=\"25.627529\"\n           height=\"18.990078\"\n           x=\"756.62341\"\n           y=\"300.10303\" />\n        <rect\n           style=\"fill:#536dff;fill-opacity:0.2857143;stroke:#ff0000;stroke-width:1.99943709;stroke-linecap:round;stroke-linejoin:round;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n           id=\"rect4786\"\n           width=\"25.238373\"\n           height=\"19.972313\"\n           x=\"591.29425\"\n           y=\"304.12076\" />\n        <rect\n           style=\"fill:#536dff;fill-opacity:0.2857143;stroke:#ff0000;stroke-width:1.99943709;stroke-linecap:round;stroke-linejoin:round;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n           id=\"rect4788\"\n           width=\"24.579874\"\n           height=\"21.363791\"\n           x=\"591.29419\"\n           y=\"282.75696\" />\n        <rect\n           style=\"fill:#536dff;fill-opacity:0.2857143;stroke:#ff0000;stroke-width:1.99943709;stroke-linecap:round;stroke-linejoin:round;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n           id=\"rect4790\"\n           width=\"23.965109\"\n           height=\"22.872925\"\n           x=\"426.62344\"\n           y=\"296.22034\" />\n        <rect\n           style=\"fill:#536dff;fill-opacity:0.2857143;stroke:#ff0000;stroke-width:1.99943709;stroke-linecap:round;stroke-linejoin:round;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n           id=\"rect4792\"\n           width=\"23.965109\"\n           height=\"22.008892\"\n           x=\"426.62344\"\n           y=\"274.21146\" />\n        <rect\n           style=\"fill:#536dff;fill-opacity:0.2857143;stroke:#ff0000;stroke-width:1.99943709;stroke-linecap:round;stroke-linejoin:round;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n           id=\"rect4794\"\n           width=\"23.965109\"\n           height=\"20.97538\"\n           x=\"426.62344\"\n           y=\"253.23607\" />\n        <ellipse\n           style=\"display:inline;overflow:visible;visibility:visible;fill:none;fill-opacity:1;stroke:#000000;stroke-width:2;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           id=\"ellipse4796\"\n           cx=\"544.23254\"\n           cy=\"590.14545\"\n           rx=\"25.040159\"\n           ry=\"37.5\" />\n        <text\n           xml:space=\"preserve\"\n           style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#00ff00;fill-opacity:1;stroke:#ff0000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;\"\n           x=\"544.1886\"\n           y=\"573.13568\"\n           id=\"text4802\"><tspan\n             style=\"font-size:12px;line-height:1.25;stroke:#ff0000;stroke-opacity:1;fill:#00ff00;fill-opacity:1;\"\n             sodipodi:role=\"line\"\n             x=\"544.1886\"\n             y=\"576.58362\"\n             id=\"tspan4798\" /><tspan\n             id=\"tspan4800\"\n             style=\"font-size:12px;line-height:1.25;stroke:#ff0000;stroke-opacity:1;fill:#00ff00;fill-opacity:1;\"\n             sodipodi:role=\"line\"\n             x=\"546.29797\"\n             y=\"584.08362\">ALU </tspan><tspan\n             style=\"font-size:12px;line-height:1.25;stroke:#ff0000;stroke-opacity:1;fill:#00ff00;fill-opacity:1;\"\n             sodipodi:role=\"line\"\n             x=\"544.1886\"\n             y=\"599.08362\"\n             id=\"tspan4806\">Control</tspan></text>\n        <text\n           xml:space=\"preserve\"\n           style=\"font-style:normal;font-weight:normal;font-size:40.46024704px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1.0115062\"\n           x=\"406.12302\"\n           y=\"771.62396\"\n           id=\"text4810\"\n           transform=\"scale(1.302035,0.76802849)\"><tspan\n             sodipodi:role=\"line\"\n             id=\"tspan4808\"\n             x=\"406.12302\"\n             y=\"808.53705\"\n             style=\"stroke-width:1.0115062\" /></text>\n        <text\n           id=\"text7228\"\n           y=\"934.35199\"\n           x=\"456.75711\"\n           style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:14.72777939px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#00ff00;fill-opacity:1;stroke:#ff0000;stroke-width:1.22731495px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;\"\n           xml:space=\"preserve\"\n           transform=\"scale(1.2348516,0.8098139)\"><tspan\n             id=\"tspan7226\"\n             y=\"938.58374\"\n             x=\"456.75711\"\n             sodipodi:role=\"line\"\n             style=\"font-size:14.72777939px;line-height:1.25;stroke:#ff0000;stroke-width:1.22731495px;stroke-opacity:1;fill:#00ff00;fill-opacity:1;\" /><tspan\n             y=\"947.78857\"\n             x=\"456.75711\"\n             sodipodi:role=\"line\"\n             style=\"font-size:14.72777939px;line-height:1.25;stroke:#ff0000;stroke-width:1.22731495px;stroke-opacity:1;fill:#00ff00;fill-opacity:1;\"\n             id=\"tspan7243\">Data</tspan><tspan\n             y=\"966.1983\"\n             x=\"456.75711\"\n             sodipodi:role=\"line\"\n             style=\"font-size:14.72777939px;line-height:1.25;stroke:#ff0000;stroke-width:1.22731495px;stroke-opacity:1;fill:#00ff00;fill-opacity:1;\"\n             id=\"tspan7239\">Forwarding</tspan></text>\n        <path\n           style=\"fill:none;stroke:#ff0000;stroke-width:1.77919829;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n           d=\"m 627.25209,774.33831 h 20.16644 V 550.65032\"\n           id=\"path7245\"\n           inkscape:connector-curvature=\"0\"\n           sodipodi:nodetypes=\"ccc\" />\n      </g>\n      <g\n         transform=\"matrix(1.5592257,0,0,1.2503301,-80.664455,140.39655)\"\n         id=\"g2657\"\n         style=\"fill:none;stroke:#000000;stroke-opacity:1\" />\n      <g\n         transform=\"matrix(1.5592257,0,0,1.2503301,-57.276071,140.39655)\"\n         id=\"g2523\" />\n      <text\n         id=\"text2410\"\n         y=\"177.72679\"\n         x=\"345.94672\"\n         style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:16.7551403px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:start;writing-mode:lr-tb;text-anchor:start;fill:none;stroke:#000000;stroke-width:1.39626157px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         xml:space=\"preserve\"\n         transform=\"scale(1.1167145,0.89548403)\"><tspan\n           style=\"font-size:16.7551403px;line-height:1;stroke-width:1.39626157px\"\n           y=\"177.72679\"\n           x=\"345.94672\"\n           id=\"tspan2412\"\n           sodipodi:role=\"line\"> </tspan></text>\n      <text\n         id=\"text2428\"\n         y=\"380.18472\"\n         x=\"415.23624\"\n         style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:16.7551403px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:start;writing-mode:lr-tb;text-anchor:start;fill:none;stroke:#000000;stroke-width:1.39626157px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         xml:space=\"preserve\"\n         transform=\"scale(1.1167145,0.89548403)\"><tspan\n           style=\"font-size:16.7551403px;line-height:1;stroke-width:1.39626157px\"\n");
    fprintf(output,"        y=\"380.18472\"\n           x=\"415.23624\"\n           id=\"tspan2430\"\n           sodipodi:role=\"line\"> </tspan></text>\n      <g\n         transform=\"matrix(1.5592257,0,0,1.2503301,-119.2506,146.6482)\"\n         id=\"g2558\" />\n      <g\n         transform=\"matrix(1.5592257,0,0,1.2503301,192.20007,-47.152962)\"\n         id=\"g2529\">\n        <rect\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#8ae234;fill-opacity:1;stroke:#000000;stroke-width:1.99999976;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           id=\"rect2531\"\n           width=\"25\"\n           height=\"350.00015\"\n           x=\"25\"\n           y=\"175\" />\n        <path\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:0.11764706;stroke:#000000;stroke-width:2;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"M 25,525 37.5,505 50,525\"\n           id=\"path2533\"\n           sodipodi:nodetypes=\"ccc\"\n           inkscape:connector-curvature=\"0\" />\n        <text\n           transform=\"rotate(90)\"\n           xml:space=\"preserve\"\n           style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n           x=\"349.76276\"\n           y=\"-33.682617\"\n           id=\"text2535\"><tspan\n             style=\"font-size:12px;line-height:1\"\n             sodipodi:role=\"line\"\n             id=\"tspan2537\"\n             x=\"349.76276\"\n             y=\"-33.682617\">IF / ID</tspan></text>\n      </g>\n      <g\n         transform=\"matrix(1.5592257,0,0,1.2503301,-149.66017,136.90356)\"\n         id=\"g2625\" />\n      <g\n         transform=\"matrix(1.5592257,0,0,1.2503301,706.74452,-40.901499)\"\n         id=\"g2641\">\n        <rect\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#8ae234;fill-opacity:1;stroke:#000000;stroke-width:1.99999976;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           id=\"rect2643\"\n           width=\"25\"\n           height=\"350.00015\"\n           x=\"25\"\n           y=\"175\" />\n        <path\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:0.11764706;stroke:#000000;stroke-width:2;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"M 25,525 37.5,505 50,525\"\n           id=\"path2645\"\n           sodipodi:nodetypes=\"ccc\"\n           inkscape:connector-curvature=\"0\" />\n        <text\n           transform=\"rotate(90)\"\n           xml:space=\"preserve\"\n           style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n           x=\"350.00006\"\n           y=\"-33.682617\"\n           id=\"text2647\"><tspan\n             style=\"font-size:12px;line-height:1\"\n             sodipodi:role=\"line\"\n             id=\"tspan2649\"\n             x=\"350.00006\"\n             y=\"-33.682617\">EX / MEM</tspan></text>\n      </g>\n      <g\n         transform=\"matrix(1.5592257,0,0,1.2503301,683.35615,202.91305)\"\n         id=\"g2662\" />\n      <g\n         transform=\"matrix(1.5592257,0,0,1.2503301,357.08818,197.91173)\"\n         id=\"g2670\" />\n      <g\n         transform=\"matrix(1.5592257,0,0,1.2503301,964.01615,-47.153149)\"\n         id=\"g2678\">\n        <rect\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#8ae234;fill-opacity:1;stroke:#000000;stroke-width:1.99999976;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           id=\"rect2680\"\n           width=\"25\"\n           height=\"350.00015\"\n           x=\"25\"\n           y=\"175\" />\n        <path\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:0.11764706;stroke:#000000;stroke-width:2;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"M 25,525 37.5,505 50,525\"\n           id=\"path2682\"\n           sodipodi:nodetypes=\"ccc\"\n           inkscape:connector-curvature=\"0\" />\n        <text\n           transform=\"rotate(90)\"\n           xml:space=\"preserve\"\n           style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n           x=\"350.00006\"\n           y=\"-33.682617\"\n           id=\"text2684\"><tspan\n             style=\"font-size:12px;line-height:1\"\n             sodipodi:role=\"line\"\n             id=\"tspan2686\"\n             x=\"350.00006\"\n             y=\"-33.682617\">MEM / WB</tspan></text>\n      </g>\n      <text\n         id=\"text2837\"\n         y=\"-177.02606\"\n         x=\"99.593727\"\n         style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:16.7551403px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1.39626157px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         xml:space=\"preserve\"\n");
    fprintf(output,"         transform=\"scale(1.1167145,0.89548403)\"><tspan\n           style=\"font-size:22.34018517px;line-height:1;stroke-width:1.39626157px\"\n           y=\"-177.02606\"\n           x=\"99.593727\"\n           id=\"tspan2839\"\n           sodipodi:role=\"line\">Instruction Fetch</tspan></text>\n      <text\n         id=\"text2845\"\n         y=\"-190.36145\"\n         x=\"339.85989\"\n         style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:16.7551403px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1.39626157px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         xml:space=\"preserve\"\n         transform=\"scale(1.1167145,0.89548403)\"><tspan\n           style=\"font-size:22.34018517px;line-height:1;stroke-width:1.39626157px\"\n           y=\"-190.36145\"\n           x=\"339.85989\"\n           id=\"tspan2847\"\n           sodipodi:role=\"line\">Instruction Decode</tspan><tspan\n           style=\"font-size:22.34018517px;line-height:1;stroke-width:1.39626157px\"\n           id=\"tspan2849\"\n           y=\"-168.02127\"\n           x=\"339.85989\"\n           sodipodi:role=\"line\">Register Fetch</tspan></text>\n      <text\n         id=\"text2851\"\n         y=\"-188.53976\"\n         x=\"571.86847\"\n         style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:16.7551403px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1.39626157px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         xml:space=\"preserve\"\n         transform=\"scale(1.1167145,0.89548403)\"><tspan\n           style=\"font-size:22.34018517px;line-height:1;stroke-width:1.39626157px\"\n           id=\"tspan2855\"\n           y=\"-188.53976\"\n           x=\"571.86847\"\n           sodipodi:role=\"line\">Execute</tspan><tspan\n           style=\"font-size:22.34018517px;line-height:1;stroke-width:1.39626157px\"\n           id=\"tspan2859\"\n           y=\"-166.19958\"\n           x=\"571.86847\"\n           sodipodi:role=\"line\">Address Calc.</tspan></text>\n      <text\n         id=\"text2861\"\n         y=\"-179.53496\"\n         x=\"800.58264\"\n         style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:16.7551403px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1.39626157px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         xml:space=\"preserve\"\n         transform=\"scale(1.1167145,0.89548403)\"><tspan\n           style=\"font-size:22.34018517px;line-height:1;stroke-width:1.39626157px\"\n           id=\"tspan2869\"\n           y=\"-179.53496\"\n           x=\"800.58264\"\n           sodipodi:role=\"line\">Memory Access</tspan></text>\n      <text\n         id=\"text2873\"\n         y=\"-180.05309\"\n         x=\"1000.7489\"\n         style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:16.7551403px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1.39626157px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         xml:space=\"preserve\"\n         transform=\"scale(1.1167145,0.89548403)\"><tspan\n           style=\"font-size:22.34018517px;line-height:1;stroke-width:1.39626157px\"\n           id=\"tspan2875\"\n           y=\"-180.05309\"\n           x=\"1000.7489\"\n           sodipodi:role=\"line\">Write Back</tspan></text>\n      <path\n         id=\"path2877\"\n         d=\"m 1023.2662,-186.24129 v 81.27139\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#cc0000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         inkscape:connector-curvature=\"0\" />\n      <path\n         id=\"path2879\"\n         d=\"m 765.99509,-186.24129 v 81.27139\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#cc0000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         inkscape:connector-curvature=\"0\" />\n      <path\n         id=\"path2881\"\n         d=\"m 508.72287,-186.24129 v 81.27139\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#cc0000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         inkscape:connector-curvature=\"0\" />\n      <path\n         id=\"path2883\"\n         d=\"m 251.45065,-186.24129 v 81.27139\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#cc0000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         inkscape:connector-curvature=\"0\" />\n      <text\n         id=\"text2885\"\n         y=\"-124.20264\"\n         x=\"87.021912\"\n         style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:16.7551403px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:start;writing-mode:lr-tb;text-anchor:start;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1.39626157px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         xml:space=\"preserve\"\n         transform=\"scale(1.1167145,0.89548403)\"><tspan\n           style=\"font-size:27.92523384px;line-height:1;stroke-width:1.39626157px\"\n           y=\"-124.20264\"\n           x=\"87.021912\"\n           id=\"tspan2887\"\n           sodipodi:role=\"line\">IF</tspan></text>\n      <text\n         id=\"text2889\"\n         y=\"-124.20264\"\n         x=\"324.9469\"\n         style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:16.7551403px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:start;writing-mode:lr-tb;text-anchor:start;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1.39626157px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         xml:space=\"preserve\"\n         transform=\"scale(1.1167145,0.89548403)\"><tspan\n           style=\"font-size:27.92523384px;line-height:1;stroke-width:1.39626157px\"\n           y=\"-124.20264\"\n           x=\"324.9469\"\n           id=\"tspan2891\"\n           sodipodi:role=\"line\">ID</tspan></text>\n      <text\n         id=\"text2893\"\n         y=\"-124.20264\"\n         x=\"551.40991\"\n         style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:16.7551403px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:start;writing-mode:lr-tb;text-anchor:start;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1.39626157px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         xml:space=\"preserve\"\n         transform=\"scale(1.1167145,0.89548403)\"><tspan\n           style=\"font-size:27.92523384px;line-height:1;stroke-width:1.39626157px\"\n           y=\"-124.20264\"\n           x=\"551.40991\"\n           id=\"tspan2895\"\n           sodipodi:role=\"line\">EX</tspan></text>\n      <text\n         id=\"text2897\"\n         y=\"-124.20264\"\n         x=\"768.18494\"\n         style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:16.7551403px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:start;writing-mode:lr-tb;text-anchor:start;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1.39626157px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         xml:space=\"preserve\"\n         transform=\"scale(1.1167145,0.89548403)\"><tspan\n           style=\"font-size:27.92523384px;line-height:1;stroke-width:1.39626157px\"\n           y=\"-124.20264\"\n           x=\"768.18494\"\n           id=\"tspan2899\"\n           sodipodi:role=\"line\">MEM</tspan></text>\n      <text\n         id=\"text2901\"\n         y=\"-124.20264\"\n         x=\"978.22382\"\n         style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:16.7551403px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:start;writing-mode:lr-tb;text-anchor:start;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1.39626157px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         xml:space=\"preserve\"\n         transform=\"scale(1.1167145,0.89548403)\"><tspan\n           style=\"font-size:27.92523384px;line-height:1;stroke-width:1.39626157px\"\n           y=\"-124.20264\"\n           x=\"978.22382\"\n           id=\"tspan2903\"\n           sodipodi:role=\"line\">WB</tspan></text>\n      <g\n         id=\"g5074\"\n         transform=\"matrix(1.5592257,0,0,2.3397352,-836.68246,-17.333622)\" />\n      <path\n         cx=\"126.63261\"\n         cy=\"421.72079\"\n         rx=\"3.8980641\"\n         ry=\"3.1258252\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         id=\"path5092\"\n         d=\"\"\n         inkscape:connector-curvature=\"0\" />\n      <g\n         id=\"g5110\"\n         transform=\"matrix(1.5592257,0,0,1.4276968,-131.55953,305.18889)\" />\n      <ellipse\n         style=\"fill:none;fill-opacity:1;stroke:none;stroke-width:2.79318476;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         id=\"path4729\"\n         cx=\"53.03735\"\n         cy=\"551.29315\"\n         rx=\"18.166456\"\n         ry=\"7.6433225\" />\n      <ellipse\n         style=\"fill:none;fill-opacity:1;stroke:none;stroke-width:2.79318476;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         id=\"path4731\"\n         cx=\"473.85895\"\n         cy=\"367.49313\"\n         rx=\"685.06097\"\n         ry=\"273.03546\" />\n      <ellipse\n         style=\"fill:none;fill-opacity:1;stroke:none;stroke-width:2.79318476;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         id=\"path4733\"\n         cx=\"471.69153\"\n         cy=\"366.67752\"\n         rx=\"715.92352\"\n         ry=\"296.9137\" />\n      <ellipse\n         style=\"fill:none;fill-opacity:1;stroke:none;stroke-width:2.79318476;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         id=\"path4735\"\n         cx=\"1031.6134\"\n         cy=\"568.86816\"\n         rx=\"192.33472\"\n         ry=\"115.88912\" />\n      <ellipse\n         style=\"fill:none;fill-opacity:1;stroke:none;stroke-width:2.79318476;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n");
    fprintf(output,"         id=\"path4737\"\n         cx=\"703.72675\"\n         cy=\"411.36154\"\n         rx=\"723.35529\"\n         ry=\"279.27527\" />\n      <ellipse\n         style=\"fill:none;fill-opacity:1;stroke:none;stroke-width:2.79318476;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         id=\"path4739\"\n         cx=\"-9.7806482\"\n         cy=\"301.28506\"\n         rx=\"302.16257\"\n         ry=\"295.01965\" />\n      <ellipse\n         style=\"fill:none;fill-opacity:1;stroke:none;stroke-width:2.79318476;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         id=\"path4741\"\n         cx=\"484.90356\"\n         cy=\"380.78827\"\n         rx=\"742.34747\"\n         ry=\"289.85834\" />\n      <ellipse\n         style=\"fill:none;fill-opacity:1;stroke:none;stroke-width:2.79318476;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         id=\"path4743\"\n         cx=\"494.8125\"\n         cy=\"390.78336\"\n         rx=\"742.34747\"\n         ry=\"313.96417\" />\n      <ellipse\n         style=\"fill:none;fill-opacity:1;stroke:none;stroke-width:2.79318476;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         id=\"path4745\"\n         cx=\"492.33533\"\n         cy=\"390.78336\"\n         rx=\"744.82471\"\n         ry=\"313.96417\" />\n      <ellipse\n         style=\"fill:none;fill-opacity:1;stroke:none;stroke-width:2.79318476;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         id=\"path4747\"\n         cx=\"484.07782\"\n         cy=\"377.26056\"\n         rx=\"736.5672\"\n         ry=\"300.44138\" />\n      <ellipse\n         style=\"fill:none;fill-opacity:1;stroke:none;stroke-width:2.79318476;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         id=\"path4749\"\n         cx=\"485.72931\"\n         cy=\"412.53745\"\n         rx=\"696.93134\"\n         ry=\"269.86807\" />\n      <ellipse\n         style=\"fill:none;fill-opacity:1;stroke:none;stroke-width:2.79318476;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         id=\"path4751\"\n         cx=\"488.20654\"\n         cy=\"407.24588\"\n         rx=\"694.4541\"\n         ry=\"272.80783\" />\n      <ellipse\n         style=\"fill:none;fill-opacity:1;stroke:none;stroke-width:2.79318476;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         id=\"path4753\"\n         cx=\"482.42633\"\n         cy=\"406.07004\"\n         rx=\"691.97687\"\n         ry=\"272.80783\" />\n      <ellipse\n         style=\"fill:none;fill-opacity:1;stroke:none;stroke-width:2.79318476;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         id=\"path4755\"\n         cx=\"486.55505\"\n         cy=\"406.07004\"\n         rx=\"696.10559\"\n         ry=\"273.98373\" />\n      <ellipse\n         style=\"fill:none;fill-opacity:1;stroke:none;stroke-width:2.79318476;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         id=\"path4757\"\n         cx=\"480.77484\"\n         cy=\"401.36646\"\n         rx=\"700.23438\"\n         ry=\"278.68732\" />\n      <flowRoot\n         xml:space=\"preserve\"\n         id=\"flowRoot4793\"\n         style=\"font-style:normal;font-weight:normal;font-size:40px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none\"\n         transform=\"matrix(2.4952232,0,0,1.7766452,-414.3359,-205.39573)\"><flowRegion\n           id=\"flowRegion4795\"><rect\n             id=\"rect4797\"\n             width=\"44.75\"\n             height=\"44.5\"\n             x=\"323.75\"\n             y=\"321.51968\" /></flowRegion><flowPara\n           id=\"flowPara4799\" /></flowRoot>      <g\n         id=\"g4827\"\n         transform=\"matrix(0.68530988,0,0,0.59351311,338.54001,82.015128)\" />\n      <flowRoot\n         xml:space=\"preserve\"\n         id=\"flowRoot4888\"\n         style=\"font-style:normal;font-weight:normal;font-size:40px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none\"\n         transform=\"translate(-90.355144)\"><flowRegion\n           id=\"flowRegion4890\"><rect\n             id=\"rect4892\"\n             width=\"446\"\n             height=\"268\"\n             x=\"-552\"\n             y=\"502.51968\" /></flowRegion><flowPara\n           id=\"flowPara4894\" /></flowRoot>      <flowRoot\n         xml:space=\"preserve\"\n         id=\"flowRoot4896\"\n         style=\"font-style:normal;font-weight:normal;font-size:40px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none\"\n         transform=\"translate(-90.355144)\"><flowRegion\n           id=\"flowRegion4898\"><rect\n             id=\"rect4900\"\n             width=\"34\"\n             height=\"446\"\n             x=\"-556\"\n             y=\"310.51968\" /></flowRegion><flowPara\n           id=\"flowPara4902\" /></flowRoot>      <flowRoot\n         xml:space=\"preserve\"\n         id=\"flowRoot4904\"\n         style=\"font-style:normal;font-weight:normal;font-size:40px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none\"\n         transform=\"translate(-90.355144)\"><flowRegion\n           id=\"flowRegion4906\"><rect\n             id=\"rect4908\"\n             width=\"420\"\n             height=\"688\"\n             x=\"-516\"\n             y=\"190.51968\" /></flowRegion><flowPara\n           id=\"flowPara4910\" /></flowRoot>      <path\n         style=\"fill:none;stroke:#fa0000;stroke-width:4.0835228;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1\"\n         d=\"m 667.51299,389.26664 v 73.52458\"\n         id=\"path4818\"\n         inkscape:connector-curvature=\"0\"\n         sodipodi:nodetypes=\"cc\" />\n      <path\n         style=\"fill:none;stroke:#ff0000;stroke-width:3.02724504;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         d=\"m 526.33334,159.1044 h 187.89763 v 0 l 0.51338,409.80554 H 669.0534 v -11.49901\"\n         id=\"path4822\"\n         inkscape:connector-curvature=\"0\"\n         sodipodi:nodetypes=\"cccccc\" />\n      <path\n         style=\"fill:none;stroke:#ff0000;stroke-width:3.01593065;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1;fill-opacity:1\"\n         d=\"m 600.80361,348.81145 v -94.4405 h 98.01421 V 166.28372 H 526.38543\"\n         id=\"path4824\"\n         inkscape:connector-curvature=\"0\" />\n      <path\n         style=\"fill:none;stroke:#f30000;stroke-width:3.54972363;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         d=\"M 526.02241,149.97127 H 727.13302 V 657.54601 H 612.42012 V 604.31592\"\n         id=\"path4826\"\n         inkscape:connector-curvature=\"0\" />\n      <path\n         style=\"fill:none;stroke:#ff0000;stroke-width:1.41232741px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         d=\"m 528.38686,128.65081 h 207.40613 v 38.36787 h 8.72748\"\n         id=\"path4828\"\n         inkscape:connector-curvature=\"0\" />\n      <path\n         style=\"fill:none;stroke:#ff0000;stroke-width:1.41232741px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         d=\"m 528.38686,104.12452 h 213.05333 v 31.56849 h 3.59367\"\n         id=\"path4830\"\n         inkscape:connector-curvature=\"0\" />\n      <path\n         style=\"fill:none;stroke:#000000;stroke-width:1.41232741px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         d=\"M 528.38686,104.12453 Z\"\n         id=\"path4832\"\n         inkscape:connector-curvature=\"0\" />\n      <path\n         style=\"fill:none;stroke:#000000;stroke-width:1.41232741px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         d=\"m 528.38686,104.12454 h -2.31021\"\n         id=\"path4834\"\n         inkscape:connector-curvature=\"0\" />\n      <path\n         style=\"fill:none;stroke:#000000;stroke-width:1.41232741px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         d=\"m 528.38686,128.65081 v 0 h -2.16024\"\n         id=\"path4838\"\n         inkscape:connector-curvature=\"0\" />\n      <path\n         id=\"path4840\"\n         d=\"m 742.39511,134.39411 v 2.22743 l 4.86313,-1.11371 -4.86313,-1.11372\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:1.16363168;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         inkscape:connector-curvature=\"0\" />\n      <path\n         id=\"path4842\"\n         d=\"m 741.17121,164.92678 v 4.42755 l 7.70581,-2.21378 -7.70581,-2.21377\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.06512141;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         inkscape:connector-curvature=\"0\" />\n      <text\n         xml:space=\"preserve\"\n         style=\"font-style:normal;font-weight:normal;font-size:56.4930954px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1.41232741\"\n         x=\"341.0661\"\n         y=\"148.57672\"\n         id=\"text4846\"\n         transform=\"scale(1.4540014,0.68775725)\"><tspan\n           sodipodi:role=\"line\"\n           id=\"tspan4844\"\n           x=\"341.0661\"\n           y=\"200.11708\"\n           style=\"stroke-width:1.41232741\" /></text>\n      <path\n         style=\"fill:none;stroke:#ff0000;stroke-width:1.41232741px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         d=\"M 784.82092,138.45525 H 984.012 v 20.88378 h 19.5083\"\n         id=\"path4858\"\n         inkscape:connector-curvature=\"0\" />\n      <path\n         style=\"fill:none;stroke:#ff0000;stroke-width:2.48213768;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         d=\"m 1042.794,159.58186 h 51.8516 V 37.621752 H 406.35507 v 0 l -2.05353,203.998398\"\n         id=\"path4860\"\n         inkscape:connector-curvature=\"0\"\n         sodipodi:nodetypes=\"cccccc\" />\n      <path\n         style=\"fill:none;stroke:#ff0000;stroke-width:1.23444784px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         d=\"m 1042.8845,167.67903 h 54.9735 v 177.87669\"\n         id=\"path4862\"\n         inkscape:connector-curvature=\"0\" />\n      <path\n         inkscape:connector-curvature=\"0\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.06512141;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         d=\"m 995.81449,157.12526 v 4.42755 l 7.70581,-2.21378 -7.70581,-2.21377\"\n         id=\"path4781\" />\n      <path\n         style=\"fill:none;stroke:#ff0000;stroke-width:2.48213768;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         d=\"m 386.43683,105.42975 c 6.16058,0 99.59601,0 99.59601,0\"\n         id=\"path4785\"\n         inkscape:connector-curvature=\"0\" />\n      <path\n         style=\"fill:none;stroke:#ff0000;stroke-width:2.48213768;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         d=\"m 393.62417,131.65589 h 92.40867\"\n         id=\"path4787\"\n         inkscape:connector-curvature=\"0\" />\n      <path\n         style=\"fill:none;stroke:#ff0000;stroke-width:2.48213768;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         d=\"M 386.43683,155.45368 H 487.0596\"\n         id=\"path4789\"\n         inkscape:connector-curvature=\"0\" />\n      <path\n         style=\"fill:none;stroke:#000000;stroke-width:1.41232741px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         d=\"m 1122.0764,371.08711 v 0 0\"\n         id=\"path4814\"\n         inkscape:connector-curvature=\"0\" />\n      <path\n         style=\"fill:none;stroke:#ff0000;stroke-width:2.48213768;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         d=\"m 786.65005,168.46475 h 92.93197 v 141.48904\"\n         id=\"path4816\"\n         inkscape:connector-curvature=\"0\" />\n      <path\n         style=\"fill:none;stroke:#ff0000;stroke-width:2.49281335;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         d=\"m 786.65005,161.31823 h 196.75443 v 350.22309 h -86.3977 v -27.69531\"\n         id=\"path4819\"\n         inkscape:connector-curvature=\"0\" />\n      <path\n         style=\"fill:none;stroke:#ff0000;stroke-width:1.51002;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;stroke-miterlimit:4;stroke-dasharray:none\"\n         d=\"m 603.09838,745.79578 h -66.0291 V 263.70612 h 109.15015 l 0,19.44793\"\n         id=\"path7297\"\n         inkscape:connector-curvature=\"0\"\n         sodipodi:nodetypes=\"cccc\" />\n      <text\n         xml:space=\"preserve\"\n         style=\"font-style:normal;font-weight:normal;font-size:13.74713562px;line-height:0;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.85919595;\"\n         x=\"-74.657913\"\n         y=\"382.36682\"\n         id=\"text7301\"\n         transform=\"scale(1.1090013,0.90171218)\"><tspan\n           sodipodi:role=\"line\"\n           id=\"tspan7299\"\n           x=\"-74.657913\"\n           y=\"382.36682\"\n           style=\"line-height:0;stroke-width:0.85919595;font-size:13.74713562px;stroke:#ff0000;stroke-opacity:1\">PCSRC</tspan></text>\n      <text\n         xml:space=\"preserve\"\n         style=\"font-style:normal;font-weight:normal;font-size:13.74713516px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.85919595\"\n         x=\"328.58102\"\n         y=\"382.38922\"\n         id=\"text7349\"\n         transform=\"scale(1.1090013,0.90171218)\"><tspan\n           sodipodi:role=\"line\"\n           id=\"tspan7347\"\n           x=\"328.58102\"\n           y=\"394.93115\"\n           style=\"stroke-width:0.85919595\" /></text>\n      <g\n         id=\"g7677\"\n         transform=\"translate(-1.613619,2.1334131e-5)\">\n        <rect\n           y=\"175\"\n           x=\"25\"\n           height=\"350.00015\"\n           width=\"25\"\n           id=\"rect2574\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#8ae234;fill-opacity:1;stroke:#000000;stroke-width:1.99999976;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           transform=\"matrix(1.5592257,0,0,1.2503301,449.4723,-47.152959)\" />\n        <path\n           inkscape:connector-curvature=\"0\"\n           sodipodi:nodetypes=\"ccc\"\n           id=\"path2576\"\n           d=\"M 25,525 37.5,505 50,525\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:0.11764706;stroke:#000000;stroke-width:2;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           transform=\"matrix(1.5592257,0,0,1.2503301,449.4723,-47.152959)\" />\n        <g\n           id=\"IDmaster\"\n           style=\"opacity:");
    if(!strcmp(ID,"nop") || !strcmp(ID,"0"))
        fprintf(output,"0.2");
    else
        fprintf(output,"1");    
    fprintf(output,"\">\n          <ellipse\n             style=\"display:inline;overflow:visible;visibility:visible;fill:#ffe700;fill-opacity:1;stroke:#000000;stroke-width:1.99839556;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             id=\"path2426\"\n             cx=\"350\"\n             cy=\"237.5\"\n             rx=\"25\"\n             ry=\"37.5\"\n             transform=\"matrix(1.5617305,0,0,1.2503301,-151.24915,174.78063)\" />\n          <path\n             transform=\"translate(2.6259631e-6)\"\n             sodipodi:nodetypes=\"cccc\"\n             id=\"path2551\"\n             d=\"M 348.12263,252.92625 H 293.54974 V 471.734 h 54.57289\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             inkscape:connector-curvature=\"0\" />\n          <path\n             transform=\"translate(2.6259631e-6)\"\n             inkscape:connector-curvature=\"0\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             d=\"M 433.88005,471.73401 H 480.6568\"\n             id=\"path2604\" />\n          <text\n             transform=\"matrix(0,-0.90171215,1.1090013,0,2.6259631e-6,6.1003735e-7)\"\n             id=\"text7339\"\n             y=\"259.63055\"\n             x=\"-455.66257\"\n             style=\"font-style:normal;font-weight:normal;font-size:13.74713516px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.85919595\"\n             xml:space=\"preserve\"><tspan\n               style=\"stroke-width:0.85919595\"\n               y=\"259.63055\"\n               x=\"-455.66257\"\n               id=\"tspan7337\"\n               sodipodi:role=\"line\">Instruction</tspan></text>\n          <rect\n             y=\"240.54799\"\n             x=\"355.91861\"\n             height=\"118.65633\"\n             width=\"93.111198\"\n             id=\"rect2418\"\n             style=\"fill:#ffe700;fill-rule:evenodd;stroke:#000000;stroke-width:2.79272516;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;stroke-miterlimit:4;stroke-dasharray:none;fill-opacity:1\" />\n          <text\n             id=\"text2420\"\n             y=\"249.22577\"\n             x=\"513.80475\"\n             style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:16.5201931px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1.37668264px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n             xml:space=\"preserve\"\n             transform=\"scale(0.81590916,1.2256266)\"><tspan\n               style=\"font-size:16.5201931px;line-height:1.25;stroke-width:1.37668264px\"\n               y=\"249.22577\"\n               x=\"513.80475\"\n               id=\"tspan2422\"\n               sodipodi:role=\"line\">Register</tspan><tspan\n               style=\"font-size:16.5201931px;line-height:1.25;stroke-width:1.37668264px\"\n               id=\"tspan2424\"\n               y=\"269.87601\"\n               x=\"513.80475\"\n               sodipodi:role=\"line\">File</tspan></text>\n          <text\n             transform=\"matrix(1.5592257,0,0,1.2503301,-119.2506,146.6482)\"\n             xml:space=\"preserve\"\n             style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n             x=\"329.99622\"\n             y=\"256.97363\"\n             id=\"text2432\"><tspan\n               style=\"font-size:12px;line-height:1.25\"\n               sodipodi:role=\"line\"\n               id=\"tspan2434\"\n               x=\"329.99622\"\n               y=\"256.97363\">Sign</tspan><tspan\n               style=\"font-size:12px;line-height:1.25\"\n               sodipodi:role=\"line\"\n               x=\"329.99622\"\n               y=\"271.97363\"\n               id=\"tspan2436\">Extend</tspan></text>\n          <path\n             id=\"path2549\"\n             d=\"m 270.16135,421.72081 h 23.38839\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             inkscape:connector-curvature=\"0\" />\n          <path\n             inkscape:connector-curvature=\"0\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             d=\"m 343.96468,469.23335 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n             id=\"use2564\" />\n          <path\n             inkscape:connector-curvature=\"0\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             d=\"m 343.44495,250.4256 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n             id=\"use2566\" />\n          <path\n             id=\"path2568\"\n             d=\"m 293.5243,284.1845 h 54.5729\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             inkscape:connector-curvature=\"0\" />\n          <path\n             inkscape:connector-curvature=\"0\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             d=\"m 343.44495,281.68385 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n             id=\"use2570\" />\n          <path\n             inkscape:connector-curvature=\"0\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             d=\"m 281.07594,419.22015 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n             id=\"use2582\" />\n          <text\n             id=\"text2584\"\n             y=\"519.81085\"\n             x=\"395.51404\"\n             style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:16.7551403px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:start;writing-mode:lr-tb;text-anchor:start;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1.39626157px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n             xml:space=\"preserve\"\n             transform=\"scale(1.1167145,0.89548403)\"><tspan\n               style=\"font-size:16.7551403px;line-height:1;stroke-width:1.39626157px\"\n               y=\"519.81085\"\n               x=\"395.51404\"\n               id=\"tspan2586\"\n               sodipodi:role=\"line\">Imm</tspan></text>\n          <path\n             sodipodi:nodetypes=\"cccc\"\n             id=\"path2588\"\n             d=\"m 448.80405,331.62992 h 16.2605 v 65.08429 h 23.38839\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:2.2525661;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             inkscape:connector-curvature=\"0\" />\n          <path\n             inkscape:connector-curvature=\"0\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             d=\"m 475.97913,394.21355 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n             id=\"use2590\" />\n          <ellipse\n             id=\"path2600\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             cx=\"293.54959\"\n             cy=\"284.18451\"\n             rx=\"3.8980641\"\n             ry=\"3.1258252\" />\n          <path\n             inkscape:connector-curvature=\"0\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             d=\"m 476.49886,469.23335 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n             id=\"use2606\" />\n          <path\n             sodipodi:nodetypes=\"cc\"\n             id=\"path2704\"\n             d=\"M 270.16135,184.1581 H 488.45294\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n");
    fprintf(output,"             inkscape:connector-curvature=\"0\" />\n          <path\n             id=\"path2706\"\n             d=\"m 448.14779,295.65276 h 41.01724\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:2.48566628;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             inkscape:connector-curvature=\"0\" />\n          <path\n             inkscape:connector-curvature=\"0\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             d=\"m 475.97913,181.65744 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n             id=\"use2725\" />\n          <path\n             id=\"path2913\"\n             d=\"M 292.38195,472.98124 V 596.30472 H 370.1955 487.28515\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             inkscape:connector-curvature=\"0\"\n             sodipodi:nodetypes=\"cccc\" />\n          <path\n             inkscape:connector-curvature=\"0\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             d=\"m 474.81135,593.80406 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n             id=\"use2915\" />\n          <ellipse\n             id=\"path2921\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             cx=\"293.54959\"\n             cy=\"471.73401\"\n             rx=\"3.8980641\"\n             ry=\"3.1258252\" />\n          <path\n             sodipodi:nodetypes=\"ccc\"\n             inkscape:connector-curvature=\"0\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:2.88952327;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             d=\"M 292.56478,549.79057 H 363.50049 488.8658\"\n             id=\"path5096\" />\n          <ellipse\n             ry=\"3.1258252\"\n             rx=\"3.8980641\"\n             cy=\"549.73602\"\n             cx=\"291.8981\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             id=\"ellipse5100\" />\n          <ellipse\n             id=\"ellipse5102\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             cx=\"292.5174\"\n             cy=\"596.18243\"\n             rx=\"3.8980641\"\n             ry=\"3.1258252\" />\n          <path\n             id=\"path4833\"\n             d=\"m 476.69123,293.1521 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             inkscape:connector-curvature=\"0\" />\n          <path\n             style=\"fill:none;stroke:#000000;stroke-width:2.48213768;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n             d=\"m 293.54975,252.92625 v -111.59167 -15.4539 h 21.18009\"\n             id=\"path4804\"\n             inkscape:connector-curvature=\"0\" />\n          <path\n             id=\"path4806\"\n             d=\"m 302.25604,123.38002 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             inkscape:connector-curvature=\"0\" />\n          <path\n             style=\"fill:none;stroke:#000000;stroke-width:2.48422647;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n             d=\"M 329.6178,252.99744 V 526.4833 h 157.69659\"\n             id=\"path7317\"\n             inkscape:connector-curvature=\"0\" />\n          <path\n             style=\"fill:none;stroke:#000000;stroke-width:2.48422647;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n             d=\"M 302.43016,284.66059 V 538.87926 H 487.79081\"\n             id=\"path7319\"\n             inkscape:connector-curvature=\"0\" />\n          <text\n             xml:space=\"preserve\"\n             style=\"font-style:normal;font-weight:normal;font-size:9.16475677px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.85919595\"\n             x=\"323.42587\"\n             y=\"283.79648\"\n             id=\"text7343\"\n             transform=\"scale(1.1090013,0.90171219)\"><tspan\n               sodipodi:role=\"line\"\n               id=\"tspan7341\"\n               x=\"323.42587\"\n               y=\"283.79648\"\n               style=\"font-size:9.16475677px;stroke-width:0.85919595\">Read </tspan><tspan\n               sodipodi:role=\"line\"\n               x=\"323.42587\"\n               y=\"295.25241\"\n               style=\"font-size:9.16475677px;stroke-width:0.85919595\"\n               id=\"tspan7345\">register 1</tspan></text>\n          <text\n             xml:space=\"preserve\"\n             style=\"font-style:normal;font-weight:normal;font-size:6.87356758px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.85919595\"\n             x=\"323.47955\"\n             y=\"386.9537\"\n             id=\"text7353\"\n             transform=\"scale(1.1090013,0.90171219)\"><tspan\n               sodipodi:role=\"line\"\n               id=\"tspan7351\"\n               x=\"323.47955\"\n               y=\"386.9537\"\n               style=\"font-size:6.87356758px;stroke-width:0.85919595\">Write Data</tspan></text>\n          <text\n             transform=\"scale(1.1090013,0.90171219)\"\n             id=\"text7357\"\n             y=\"352.80066\"\n             x=\"323.47955\"\n             style=\"font-style:normal;font-weight:normal;font-size:6.87356758px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.85919595\"\n             xml:space=\"preserve\"><tspan\n               style=\"font-size:6.87356758px;stroke-width:0.85919595\"\n               y=\"352.80066\"\n               x=\"323.47955\"\n               id=\"tspan7355\"\n               sodipodi:role=\"line\">Write </tspan><tspan\n               style=\"font-size:6.87356758px;stroke-width:0.85919595\"\n");
    fprintf(output,"               y=\"361.39261\"\n               x=\"323.47955\"\n               sodipodi:role=\"line\"\n               id=\"tspan7359\">Register</tspan></text>\n          <text\n             transform=\"scale(1.1090013,0.90171219)\"\n             id=\"text7365\"\n             y=\"308.71317\"\n             x=\"323.42587\"\n             style=\"font-style:normal;font-weight:normal;font-size:9.16475677px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.85919595\"\n             xml:space=\"preserve\"><tspan\n               style=\"font-size:9.16475677px;stroke-width:0.85919595\"\n               y=\"308.71317\"\n               x=\"323.42587\"\n               id=\"tspan7361\"\n               sodipodi:role=\"line\">Read </tspan><tspan\n               id=\"tspan7363\"\n               style=\"font-size:9.16475677px;stroke-width:0.85919595\"\n               y=\"320.1691\"\n               x=\"323.42587\"\n               sodipodi:role=\"line\">register 2</tspan></text>\n          <ellipse\n             ry=\"3.1258252\"\n             rx=\"3.8980641\"\n             cy=\"284.18451\"\n             cx=\"303.5545\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             id=\"ellipse7737\" />\n          <ellipse\n             id=\"ellipse7739\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             cx=\"329.51965\"\n             cy=\"252.41986\"\n             rx=\"3.8980641\"\n             ry=\"3.1258252\" />\n          <path\n             id=\"path7799\"\n             d=\"m 474.81135,546.69075 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             inkscape:connector-curvature=\"0\" />\n        </g>\n      </g>\n      <text\n         xml:space=\"preserve\"\n         style=\"font-style:normal;font-weight:normal;font-size:13.74713516px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#ff0000;fill-opacity:1;stroke:none;stroke-width:0.85919595;\"\n         x=\"-367.63858\"\n         y=\"982.99628\"\n         id=\"text7369\"\n         transform=\"matrix(0,-0.90171218,1.1090013,0,0,0)\"><tspan\n           sodipodi:role=\"line\"\n           id=\"tspan7367\"\n           x=\"-367.63858\"\n           y=\"982.99628\"\n           style=\"stroke-width:0.85919595;fill:#ff0000;fill-opacity:1;\">MemtoReg</tspan></text>\n      <text\n         xml:space=\"preserve\"\n         style=\"font-style:normal;font-weight:normal;font-size:9.7312355px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#ff0000;fill-opacity:1;stroke:none;stroke-width:0.60820222;\"\n         x=\"676.98615\"\n         y=\"567.20319\"\n         id=\"text7373\"\n         transform=\"scale(1.0049478,0.99507655)\"><tspan\n           sodipodi:role=\"line\"\n           x=\"676.98615\"\n           y=\"567.20319\"\n           style=\"stroke-width:0.60820222;fill:#ff0000;fill-opacity:1;\"\n           id=\"tspan7375\">ALUop</tspan></text>\n      <text\n         xml:space=\"preserve\"\n         style=\"font-style:normal;font-weight:normal;font-size:13.74713516px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#ff0000;fill-opacity:1;stroke:none;stroke-width:0.85919595;\"\n         x=\"577.99548\"\n         y=\"278.17316\"\n         id=\"text7381\"\n         transform=\"scale(1.1090013,0.90171219)\"><tspan\n           sodipodi:role=\"line\"\n           id=\"tspan7379\"\n           x=\"577.99548\"\n           y=\"278.17316\"\n           style=\"stroke-width:0.85919595;fill:#ff0000;fill-opacity:1;\">ALUsrc</tspan><tspan\n           sodipodi:role=\"line\"\n           x=\"577.99548\"\n           y=\"295.35709\"\n           style=\"stroke-width:0.85919595;fill:#ff0000;fill-opacity:1;\"\n           id=\"tspan7383\" /></text>\n      <text\n         xml:space=\"preserve\"\n         style=\"font-style:normal;font-weight:normal;font-size:13.74713516px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#ff0000;fill-opacity:1;stroke:none;stroke-width:0.85919595;\"\n         x=\"726.16016\"\n         y=\"249.46674\"\n         id=\"text7387\"\n         transform=\"scale(1.1090013,0.90171219)\"><tspan\n           sodipodi:role=\"line\"\n           id=\"tspan7385\"\n           x=\"726.16016\"\n           y=\"249.46674\"\n           style=\"stroke-width:0.85919595;fill:#ff0000;fill-opacity:1;\">Branch</tspan></text>\n      <text\n         transform=\"scale(1.1090013,0.90171219)\"\n         id=\"text7391\"\n         y=\"326.9285\"\n         x=\"794.20502\"\n         style=\"font-style:normal;font-weight:normal;font-size:13.74713516px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#ff0000;fill-opacity:1;stroke:none;stroke-width:0.85919595\"\n         xml:space=\"preserve\"><tspan\n           style=\"fill:#ff0000;fill-opacity:1;stroke-width:0.85919595\"\n           y=\"326.9285\"\n           x=\"794.20502\"\n           id=\"tspan7389\"\n           sodipodi:role=\"line\">MemWrite</tspan></text>\n      <text\n         xml:space=\"preserve\"\n         style=\"font-style:normal;font-weight:normal;font-size:13.74713516px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#ff0000;fill-opacity:1;stroke:none;stroke-width:0.85919595;\"\n         x=\"814.7854\"\n         y=\"562.3515\"\n         id=\"text7411\"\n         transform=\"scale(1.1090013,0.90171219)\"><tspan\n           sodipodi:role=\"line\"\n           id=\"tspan7409\"\n           x=\"814.7854\"\n           y=\"562.3515\"\n           style=\"stroke-width:0.85919595;fill:#ff0000;fill-opacity:1;\">MemRead</tspan></text>\n      <text\n         xml:space=\"preserve\"\n         style=\"font-style:normal;font-weight:normal;font-size:13.74713516px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#ff0000;fill-opacity:1;stroke:none;stroke-width:0.85919595\"\n         x=\"575.06287\"\n         y=\"724.02698\"\n         id=\"text7415\"\n         transform=\"scale(1.1090013,0.90171219)\"><tspan\n           sodipodi:role=\"line\"\n           id=\"tspan7413\"\n           x=\"575.06287\"\n           y=\"724.02698\"\n           style=\"fill:#ff0000;fill-opacity:1;stroke-width:0.85919595\">RegDst</tspan><tspan\n           sodipodi:role=\"line\"\n           x=\"575.06287\"\n           y=\"741.21088\"\n           style=\"fill:#ff0000;fill-opacity:1;stroke-width:0.85919595\"\n           id=\"tspan7417\" /></text>\n      <g\n         transform=\"matrix(1.5592257,0,0,1.2503301,449.4723,-47.152962)\"\n         id=\"g2572\">\n        <text\n           transform=\"rotate(90)\"\n           xml:space=\"preserve\"\n           style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n           x=\"349.60162\"\n           y=\"-33.682617\"\n           id=\"text2578\"><tspan\n             style=\"font-size:12px;line-height:1\"\n             sodipodi:role=\"line\"\n             id=\"tspan2580\"\n             x=\"349.60162\"\n             y=\"-33.682617\">ID / EX</tspan></text>\n      </g>\n    </g>\n    <path\n       style=\"fill:none;stroke:#ff0000;stroke-width:0.39041847px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n       d=\"m 255.96947,125.94667 h 10.10907\"\n       id=\"path4821\"\n       inkscape:connector-curvature=\"0\" />\n    <path\n       style=\"fill:none;stroke:#ff0000;stroke-width:0.40271571px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n       d=\"m 277.50863,125.31996 h 3.71149 V 99.921157 h 6.80439\"\n       id=\"path4823\"\n       inkscape:connector-curvature=\"0\" />\n    <path\n       style=\"fill:none;stroke:#ff0000;stroke-width:0.40271571px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n       d=\"m 277.81793,71.245258 h 3.95892 v 25.972171 h 5.93837\"\n       id=\"path4825\"\n       inkscape:connector-curvature=\"0\" />\n    <a\n       id=\"a4831\"\n       transform=\"matrix(1.737649,0,0,1.2537484,1.2294822,-73.656918)\" />\n    <path\n       style=\"fill:#506cff;stroke:#ff0000;stroke-width:0.40271571px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;fill-opacity:0.28627452\"\n       d=\"m 287.9072,95.989871 v 5.445819 h 5.81746 c 2.01203,-1.73803 2.01203,-3.533969 0,-5.387875 z\"\n       id=\"path4836\"\n       inkscape:connector-curvature=\"0\"\n       sodipodi:nodetypes=\"ccccc\" />\n    <path\n       style=\"fill:none;stroke:#ff0000;stroke-width:0.75648212;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n       d=\"m 295.26114,99.353786 h 3.28073 V 35.996778 H 34.545401 V 146.44173\"\n       id=\"path4841\"\n       inkscape:connector-curvature=\"0\"\n       sodipodi:nodetypes=\"ccccc\" />\n    <text\n       xml:space=\"preserve\"\n       style=\"font-style:normal;font-weight:normal;font-size:10.58333302px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.26458332\"\n       x=\"81.491669\"\n       y=\"-0.39166629\"\n       id=\"text4788\"><tspan\n         sodipodi:role=\"line\"\n         id=\"tspan4786\"\n         x=\"81.491669\"\n         y=\"-0.39166629\"\n         style=\"stroke-width:0.26458332\">%s</tspan></text>\n    <text\n       xml:space=\"preserve\"\n       style=\"font-style:normal;font-weight:normal;font-size:10.58333302px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.26458332\"\n       x=\"153.98737\"\n       y=\"-0.92083293\"\n       id=\"text4792\"><tspan\n         sodipodi:role=\"line\"\n         id=\"tspan4790\"\n         x=\"153.98737\"\n         y=\"-0.92083293\"\n         style=\"stroke-width:0.26458332\">%s</tspan></text>\n    <text\n       xml:space=\"preserve\"\n       style=\"font-style:normal;font-weight:normal;font-size:10.58333302px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.26458332\"\n       x=\"227.54131\"\n       y=\"-0.92083293\"\n       id=\"text4796\"><tspan\n         sodipodi:role=\"line\"\n         id=\"tspan4794\"\n         x=\"227.54131\"\n         y=\"-0.92083293\"\n         style=\"stroke-width:0.26458332\">%s</tspan></text>\n    <text\n       xml:space=\"preserve\"\n       style=\"font-style:normal;font-weight:normal;font-size:10.58333302px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.26458332\"\n       x=\"292.6297\"\n       y=\"-0.92083299\"\n       id=\"text4801\"><tspan\n         sodipodi:role=\"line\"\n         id=\"tspan4799\"\n         x=\"292.6297\"\n         y=\"-0.92083299\"\n         style=\"stroke-width:0.26458332\">%s</tspan></text>\n    <text\n       xml:space=\"preserve\"\n       style=\"font-style:normal;font-weight:normal;font-size:10.58333302px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.26458332\"\n       x=\"355.60068\"\n       y=\"-1.9791659\"\n       id=\"text4805\"><tspan\n         sodipodi:role=\"line\"\n         id=\"tspan4803\"\n         x=\"355.60068\"\n         y=\"-1.9791659\"\n         style=\"stroke-width:0.26458332\">%s</tspan></text>\n    <g\n       id=\"MEMmaster\"\n       style=\"opacity:",IF,ID,EX,MEM,WB);
    if(!strcmp(MEM,"nop") || !strcmp(MEM,"0"))
        fprintf(output,"0.2");
    else
        fprintf(output,"1");
    fprintf(output,"\">\n      <path\n         id=\"path5086\"\n         d=\"m -117.12012,451.78375 v 5.00132 l 12.47379,-2.50066 -12.47379,-2.50066\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         inkscape:connector-curvature=\"0\"\n         transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n      <g\n         id=\"MEM\">\n        <path\n           transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\"\n           id=\"path7313\"\n           d=\"m 807.63976,723.9005 v 5.00132 l -12.4738,-2.50066 12.4738,-2.50066\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           inkscape:connector-curvature=\"0\" />\n        <g\n           id=\"stageMEM\">\n          <path\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#ffe700;fill-opacity:1;stroke:#000000;stroke-width:2;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             d=\"m 618.35944,216.66885 v 50 l 20,-10 v -30 z\"\n             id=\"path7204\"\n             sodipodi:nodetypes=\"ccccc\"\n             inkscape:connector-curvature=\"0\"\n             transform=\"matrix(0.4329594,0,0,0.42699914,17.728559,64.736215)\" />\n          <text\n             xml:space=\"preserve\"\n             style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1\"\n             x=\"241.35681\"\n             y=\"-624.10944\"\n             id=\"text7208\"\n             transform=\"matrix(0,0.42699914,-0.4329594,0,17.728559,64.736215)\"><tspan\n               style=\"font-size:12px;line-height:1\"\n               sodipodi:role=\"line\"\n               id=\"tspan7206\"\n               x=\"241.35681\"\n               y=\"-624.10944\">MUX</tspan></text>\n          <rect\n             y=\"85.984718\"\n             x=\"109.77769\"\n             height=\"139.29602\"\n             width=\"75\"\n             id=\"rect2664\"\n             style=\"fill:#ffe700;fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:2.36047482;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n             transform=\"matrix(0.4329594,0,0,0.42699914,249.03712,87.279059)\" />\n          <text\n             transform=\"matrix(0.37445117,0,0,0.49371803,249.03712,87.279059)\"\n             id=\"text2666\"\n             y=\"116.00995\"\n             x=\"170.31233\"\n             style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:18.72877693px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1.56073141px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n             xml:space=\"preserve\"><tspan\n               y=\"116.00995\"\n               x=\"173.60449\"\n               id=\"tspan2668\"\n               sodipodi:role=\"line\"\n               style=\"font-size:18.72877693px;line-height:1.25;text-align:center;text-anchor:middle;stroke-width:1.56073141px\">Data </tspan><tspan\n               id=\"tspan4810\"\n               y=\"139.42091\"\n               x=\"170.31233\"\n               sodipodi:role=\"line\"\n               style=\"font-size:18.72877693px;line-height:1.25;text-align:center;text-anchor:middle;stroke-width:1.56073141px\">Memory</tspan></text>\n          <path\n             inkscape:connector-curvature=\"0\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:3.34865117;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             d=\"m 784.70581,336.41826 h 67.26302\"\n             id=\"path2757\"\n             sodipodi:nodetypes=\"cc\"\n             transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n          <path\n             id=\"use2759\"\n             d=\"m 846.33831,333.91761 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             inkscape:connector-curvature=\"0\"\n             transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n          <path\n             inkscape:connector-curvature=\"0\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:2.05525088;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             d=\"m 784.70581,453.3298 h 8.44588 16.89177\"\n             id=\"path2761\"\n             sodipodi:nodetypes=\"ccc\"\n             transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n          <path\n             id=\"use2763\"\n");
    fprintf(output,"             d=\"m 807.27149,450.82915 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             inkscape:connector-curvature=\"0\"\n             transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n          <ellipse\n             ry=\"3.1258252\"\n             rx=\"3.8980641\"\n             cy=\"336.41779\"\n             cx=\"808.09406\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             id=\"path2767\"\n             transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n          <path\n             inkscape:connector-curvature=\"0\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:2.16413951;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             d=\"m 972.3507,422.07155 h 23.2237\"\n             id=\"path2781\"\n             transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n          <path\n             id=\"use2783\"\n             d=\"m 990.52265,419.5709 v 5.00132 l 12.47365,-2.50066 -12.47365,-2.50066\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             inkscape:connector-curvature=\"0\"\n             transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n          <path\n             inkscape:connector-curvature=\"0\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             d=\"M 808.09418,265.70743 H 1002.9963\"\n             id=\"path2905\"\n             sodipodi:nodetypes=\"cc\"\n             transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n          <path\n             inkscape:connector-curvature=\"0\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             d=\"M 1002.9963,578.01207 H 784.70581\"\n             id=\"path2909\"\n             transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n          <path\n             id=\"use2919\"\n             d=\"m 990.52265,575.51141 v 5.00132 l 12.47365,-2.50066 -12.47365,-2.50066\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             inkscape:connector-curvature=\"0\"\n             transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n          <path\n             inkscape:connector-curvature=\"0\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:3.9788959;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             d=\"m 956.55265,213.52526 0.9954,-147.316087 0.2919,-62.9269669 -1156.64415,0.2005958 -0.59503,451.0023681 82.7947,0.0216\"\n             id=\"path4761\"\n             sodipodi:nodetypes=\"cccccc\"\n             transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n          <path\n             sodipodi:nodetypes=\"cc\"\n             id=\"path4870\"\n             d=\"M 785.50539,212.28401 H 957.81925\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.62571812;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             inkscape:connector-curvature=\"0\"\n             transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n          <path\n             inkscape:connector-curvature=\"0\"\n             id=\"path4874\"\n             d=\"m 808.09419,265.70744 -0.42779,67.89559\"\n             style=\"fill:none;stroke:#000000;stroke-width:3.01593065;stroke-linecap:round;stroke-linejoin:round;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n             transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n          <path\n             id=\"path7216\"\n             d=\"M 843.32445,439.876 H 853.5281\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:1.43448913;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             inkscape:connector-curvature=\"0\"\n             transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n          <path\n             inkscape:connector-curvature=\"0\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:1.85101044;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             d=\"m 851.30854,437.37535 v 5.00132 l 5.48047,-2.50066 -5.48047,-2.50066\"\n             id=\"path7218\"\n             transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n          <ellipse\n             id=\"ellipse7293\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             cx=\"797.49359\"\n             cy=\"336.41779\"\n             rx=\"3.8980641\"\n             ry=\"3.1258252\"\n             transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n          <ellipse\n             ry=\"3.1258252\"\n             rx=\"3.8980641\"\n             cy=\"578.02917\"\n             cx=\"815.03876\"\n             style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n             id=\"ellipse7309\"\n             transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n          <text\n             transform=\"matrix(0.30794293,0,0,0.30794293,59.285582,17.9824)\"\n             id=\"text7395\"\n             y=\"378.25244\"\n             x=\"776.83154\"\n             style=\"font-style:normal;font-weight:normal;font-size:13.74713516px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.85919595\"\n             xml:space=\"preserve\"><tspan\n               style=\"stroke-width:0.85919595\"\n               y=\"378.25244\"\n               x=\"776.83154\"\n               id=\"tspan7393\"\n               sodipodi:role=\"line\">Address</tspan></text>\n          <text\n             xml:space=\"preserve\"\n             style=\"font-style:normal;font-weight:normal;font-size:13.74713516px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.85919595\"\n             x=\"837.88965\"\n             y=\"467.86508\"\n             id=\"text7399\"\n             transform=\"matrix(0.30794293,0,0,0.30794293,59.285582,17.9824)\"><tspan\n               sodipodi:role=\"line\"\n               id=\"tspan7397\"\n               x=\"837.88965\"\n               y=\"467.86508\"\n               style=\"stroke-width:0.85919595\">Read </tspan><tspan\n               id=\"tspan7401\"\n               sodipodi:role=\"line\"\n               x=\"837.88965\"\n               y=\"485.04901\"\n               style=\"stroke-width:0.85919595\">Data</tspan></text>\n          <text\n             transform=\"matrix(0.30794293,0,0,0.30794293,59.285582,17.9824)\"\n             id=\"text7407\"\n             y=\"487.914\"\n             x=\"775.31268\"\n             style=\"font-style:normal;font-weight:normal;font-size:13.74713516px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.85919595\"\n             xml:space=\"preserve\"><tspan\n               style=\"stroke-width:0.85919595\"\n               y=\"487.914\"\n               x=\"775.31268\"\n               id=\"tspan7403\"\n               sodipodi:role=\"line\">Write</tspan><tspan\n               style=\"stroke-width:0.85919595\"\n               y=\"505.09793\"\n               x=\"775.31268\"\n               sodipodi:role=\"line\"\n               id=\"tspan7405\">Data</tspan></text>\n          <path\n             sodipodi:nodetypes=\"cccccc\"\n             inkscape:connector-curvature=\"0\"\n             id=\"path7249\"\n             d=\"m 280.92135,132.59453 v 115.94951 h -65.58229 v -64.17142 h 16.08962 l -0.37417,-61.178\"\n             style=\"fill:none;stroke:#000000;stroke-width:0.565;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;stroke-miterlimit:4;stroke-dasharray:none\" />\n          <path\n             inkscape:connector-curvature=\"0\"\n             id=\"path7305\"\n             d=\"m 285.75,215.37604 v 50.6677 h -5.02709\"\n             style=\"fill:none;stroke:#000000;stroke-width:0.765;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;stroke-miterlimit:4;stroke-dasharray:none\" />\n        </g>\n        <path\n           style=\"fill:none;stroke:#000000;stroke-width:0.66500109;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n           d=\"m 231.0544,123.19462 h 5.42558\"\n           id=\"path7263\"\n           inkscape:connector-curvature=\"0\" />\n        <path\n           style=\"fill:none;stroke:#000000;stroke-width:0.76500118;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n           d=\"m 231.42857,149.19996 h 5.05141\"\n           id=\"path7265\"\n           inkscape:connector-curvature=\"0\" />\n        <path\n           inkscape:connector-curvature=\"0\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:0.57264346;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 234.70557,122.38252 v 1.70799 l 1.53593,-0.854 -1.53593,-0.85399\"\n           id=\"path7267\" />\n        <path\n           id=\"path7269\"\n           d=\"m 234.70557,148.57493 v 1.708 l 1.53593,-0.854 -1.53593,-0.854\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:0.57264346;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           inkscape:connector-curvature=\"0\" />\n      </g>\n    </g>\n    <path\n       style=\"fill:none;stroke:#ff0000;stroke-width:0.465;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n       d=\"m 230.30615,263.88532 h -19.08304 v -81.19649 h 14.21874 v -18.52178 h 14.03165 v -14.21874\"\n       id=\"path7295\"\n       inkscape:connector-curvature=\"0\" />\n    <g\n       id=\"WBmaster\"\n       style=\"opacity:");
    if(!strcmp(WB,"nop") || !strcmp(WB,"0"))
        fprintf(output,"0.2");
    else
        fprintf(output,"1");
    fprintf(output,"\">\n      <path\n         transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\"\n         id=\"path7212\"\n         d=\"m 807.27149,421.77612 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n         style=\"opacity:1;display:inline;overflow:visible;visibility:visible;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         inkscape:connector-curvature=\"0\" />\n      <path\n         style=\"opacity:1;fill:none;stroke:#000000;stroke-width:0.69424659;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n         d=\"m 279.92916,236.36623 v -73.2454 h 5.95313\"\n         id=\"path7210\"\n         inkscape:connector-curvature=\"0\" />\n      <g\n         id=\"finalWB\">\n        <ellipse\n           transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\"\n           ry=\"3.1258252\"\n           rx=\"3.8980641\"\n           cy=\"640.83215\"\n           cx=\"794.96936\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           id=\"ellipse7214\" />\n        <path\n           transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\"\n           id=\"path7279\"\n           d=\"m 631.74401,357.67756 v 5.00132 l 5.53136,-2.50066 -5.53136,-2.50066\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:1.85957348;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           inkscape:connector-curvature=\"0\" />\n        <ellipse\n           transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\"\n           ry=\"3.1258252\"\n           rx=\"3.8980641\"\n           cy=\"641.28094\"\n           cx=\"577.02802\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           id=\"ellipse7289\" />\n        <path\n           transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\"\n           inkscape:connector-curvature=\"0\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 796.12434,765.31644 v 5.00132 l -12.4738,-2.50066 12.4738,-2.50066\"\n           id=\"path7315\" />\n        <path\n           transform=\"matrix(0.2776759,0,0,0.34150914,58.837518,17.982408)\"\n           id=\"use2803\"\n           d=\"m 343.44495,312.9421 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           inkscape:connector-curvature=\"0\" />\n        <path\n           transform=\"matrix(0.2776759,0,0,0.34150914,58.837518,17.982408)\"\n           id=\"use2805\"\n           d=\"m 343.44495,344.20035 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           inkscape:connector-curvature=\"0\" />\n        <path\n           style=\"fill:none;stroke:#000000;stroke-width:0.565;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;stroke-miterlimit:4;stroke-dasharray:none\"\n           d=\"m 233.39311,141.06159 h 2.99342\"\n           id=\"path7275\"\n           inkscape:connector-curvature=\"0\" />\n        <g\n           id=\"stageWB\">\n          <text\n             transform=\"matrix(0.31008471,0,0,0.30581597,59.285582,17.9824)\"\n             xml:space=\"preserve\"\n             style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:16.7551403px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1.39626157px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n             x=\"995.80469\"\n             y=\"557.59497\"\n             id=\"text2823\"><tspan\n               sodipodi:role=\"line\"\n               id=\"tspan2825\"\n               x=\"995.80469\"\n               y=\"557.59497\"\n               style=\"font-size:16.7551403px;line-height:1;stroke-width:1.39626157px\">WB Data</tspan></text>\n          <g\n             id=\"g5989\">\n            <path\n               transform=\"matrix(0.4329594,0,0,0.42699914,158.44036,85.571062)\"\n               style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#ffe700;fill-opacity:1;stroke:#000000;stroke-width:2;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;enable-background:accumulate\"\n               d=\"m 469.25,114.28064 v 50 l 20,-10 v -30 z\"\n               id=\"path2672\"\n               sodipodi:nodetypes=\"ccccc\"\n               inkscape:connector-curvature=\"0\" />\n            <text\n               xml:space=\"preserve\"\n               style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1\"\n               x=\"140.52199\"\n               y=\"-475\"\n               id=\"text2674\"\n               transform=\"matrix(0,0.42699914,-0.4329594,0,158.44036,85.571062)\"><tspan\n                 style=\"font-size:12px;line-height:1\"\n                 sodipodi:role=\"line\"\n                 id=\"tspan2676\"\n                 x=\"140.52199\"\n                 y=\"-475\">MUX</tspan></text>\n            <path\n               transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\"\n               id=\"path2785\"\n               d=\"m 1040.8182,267.34266 h 19.3386 v 86.52206 h 19.3389\"\n               style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:4.22466469;stroke-opacity:1;marker:none;enable-background:accumulate\"\n               inkscape:connector-curvature=\"0\" />\n            <path\n               transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\"\n               id=\"path2787\"\n               d=\"m 1088.7537,390.8133 h -23.3885 v 31.25825 h -23.3882\"\n               style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n               inkscape:connector-curvature=\"0\" />\n            <path\n               transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\"\n               inkscape:connector-curvature=\"0\"\n               style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n               d=\"m 1076.2798,388.31264 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n               id=\"use2789\" />\n            <path\n               transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\"\n               inkscape:connector-curvature=\"0\"\n               style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n               d=\"m 1076.2798,350.80274 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n               id=\"use2791\" />\n            <path\n               transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\"\n               style=\"fill:none;stroke:#000000;stroke-width:1.41232741px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n               d=\"m 1159.9821,371.08711 h -37.9057\"\n               id=\"path4812\"\n               inkscape:connector-curvature=\"0\" />\n            <ellipse\n               transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\"\n               ry=\"3.1258252\"\n               rx=\"3.8980641\"\n               cy=\"578.02917\"\n               cx=\"1057.5389\"\n               style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n               id=\"ellipse7311\" />\n            <path\n               transform=\"matrix(0.2776759,0,0,0.34150914,58.837518,17.982408)\"\n               inkscape:connector-curvature=\"0\"\n               style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n               d=\"m 1159.9821,371.08711 -1.0632,63.137 V 640.52857 H 309.14199 V 315.44275 h 46.77677\"\n               id=\"path2799\"\n               sodipodi:nodetypes=\"cccccc\" />\n            <path\n               transform=\"matrix(0.2776759,0,0,0.34150914,58.837518,17.982408)\"\n               inkscape:connector-curvature=\"0\"\n               style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n               d=\"M 355.91876,346.70101 H 324.73425 V 621.77362 H 1073.1615 V 578.01207 H 1041.977\"\n               id=\"path2801\"\n               sodipodi:nodetypes=\"cccccc\" />\n            <path\n               style=\"fill:none;stroke:#000000;stroke-width:0.765;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;stroke-miterlimit:4;stroke-dasharray:none\"\n               d=\"m 353.08645,215.11146 c -0.13229,0.66145 0,65.08749 0,65.08749 h -76.2\"\n               id=\"path7307\"\n               inkscape:connector-curvature=\"0\" />\n          </g>\n        </g>\n        <path\n           inkscape:connector-curvature=\"0\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:0.57264346;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 234.70557,114.35545 v 1.708 l 1.53593,-0.854 -1.53593,-0.854\"\n           id=\"path7277\" />\n        <path\n           style=\"fill:none;stroke:#000000;stroke-width:0.56500089;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n           d=\"m 219.26777,236.94453 v -47.52052 h 14.21878 v -74.2742 h 2.99342\"\n           id=\"path7273\"\n           inkscape:connector-curvature=\"0\" />\n      </g>\n    </g>\n    <g\n       id=\"EXmaster\" style=\"opacity:");
    if(!strcmp(EX,"nop") || !strcmp(EX,"0"))
        fprintf(output,"0.2");
    else
        fprintf(output,"1");
    fprintf(output,"\">\n      <path\n         inkscape:connector-curvature=\"0\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:0.85993701;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         d=\"m 262.89183,171.82489 v 1.708 l 3.46367,-0.854 -3.46367,-0.854\"\n         id=\"use2653\" />\n      <g\n         id=\"stageEX\">\n        <path\n           transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\"\n           inkscape:connector-curvature=\"0\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79277658;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 736.43055,209.32068 v 5.00132 l 12.47606,-2.50066 -12.47606,-2.50066\"\n           id=\"use2753\" />\n        <ellipse\n           transform=\"matrix(0.19029404,0,0,0.20269015,153.28998,45.991316)\"\n           style=\"display:inline;overflow:visible;visibility:visible;fill:#ffe700;fill-opacity:1;stroke:#000000;stroke-width:2.0001812;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           id=\"ellipse4825\"\n           cx=\"329.99149\"\n           cy=\"260\"\n           rx=\"25.044697\"\n           ry=\"37.5\" />\n        <path\n           transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\"\n           id=\"path7423\"\n           d=\"m 616.79123,705.27351 v 5.00132 l 12.47606,-2.50066 -12.47606,-2.50066\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79277658;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           inkscape:connector-curvature=\"0\" />\n        <path\n           transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\"\n           inkscape:connector-curvature=\"0\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79277658;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 611.38134,763.16043 v 5.00132 l 12.47606,-2.50066 -12.47606,-2.50066\"\n           id=\"path7425\" />\n        <path\n           inkscape:connector-curvature=\"0\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:0.86001718;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 262.89101,214.52481 v 1.70799 l 3.46432,-0.854 -3.46432,-0.85399\"\n           id=\"use2917\" />\n        <path\n           inkscape:connector-curvature=\"0\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:0.85844898;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 255.97003,133.27885 h 10.78654\"\n           id=\"path2651\" />\n        <path\n           id=\"use2698\"\n           d=\"m 217.42217,138.01419 v 1.70799 l 3.46429,-0.85399 -3.46429,-0.854\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:0.86001492;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           inkscape:connector-curvature=\"0\" />\n        <ellipse\n           ry=\"1.0674978\"\n           rx=\"1.0825922\"\n           cy=\"138.86812\"\n           cx=\"215.17049\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:0.8600148;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           id=\"path2719\" />\n        <path\n           inkscape:connector-curvature=\"0\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:0.67967242;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 228.0519,98.737833 v 1.819117 l 2.03155,-0.909558 -2.03155,-0.909559\"\n           id=\"path4831\" />\n        <path\n           id=\"path4866\"\n           d=\"m 263.29228,132.42486 v 1.70799 l 3.46429,-0.854 -3.46429,-0.85399\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:0.86001492;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           inkscape:connector-curvature=\"0\" />\n        <path\n           sodipodi:nodetypes=\"ccccccccc\"\n           id=\"path2619\"\n           d=\"m 243.0472,113.58837 12.9367,8.53998 v 21.34996 l -12.9367,8.53998 v -12.80997 l 3.23417,-2.135 v -8.53998 l -3.23417,-2.135 z\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#ffe700;fill-opacity:1;stroke:#000000;stroke-width:0.74323356;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           inkscape:connector-curvature=\"0\" />\n        <path\n           inkscape:connector-curvature=\"0\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#ffe700;fill-opacity:1;stroke:#000000;stroke-width:0.54963881;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 229.52147,77.04309 10.71444,5.639173 v 14.097931 l -10.71444,5.639176 v -8.458764 l 2.67861,-1.409791 v -5.639173 l -2.67861,-1.409794 z\"\n           id=\"path4767\"\n           sodipodi:nodetypes=\"ccccccccc\" />\n        <text\n           id=\"text2621\"\n           y=\"93.340317\"\n           x=\"366.54544\"\n           style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:5.38346291px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.44862196px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n           xml:space=\"preserve\"\n           transform=\"scale(0.68478313,1.4603164)\"><tspan\n             style=\"font-size:5.38346291px;line-height:1;stroke-width:0.44862196px\"\n             y=\"93.340317\"\n");
    fprintf(output,"             x=\"366.54544\"\n             id=\"tspan2623\"\n             sodipodi:role=\"line\">ALU</tspan></text>\n        <path\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#ffe700;fill-opacity:1;stroke:#000000;stroke-width:0.86001617;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 220.88631,134.76407 v 21.34996 l 8.66077,-4.26999 v -12.80997 z\"\n           id=\"path2627\"\n           sodipodi:nodetypes=\"ccccc\"\n           inkscape:connector-curvature=\"0\" />\n        <text\n           xml:space=\"preserve\"\n           style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:5.16009712px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1;stroke-width:0.43000808\"\n           x=\"146.32954\"\n           y=\"-221.81322\"\n           id=\"text2629\"\n           transform=\"matrix(0,0.99300261,-1.0070467,0,0,0)\"><tspan\n             style=\"font-size:5.16009712px;line-height:1;stroke-width:0.43000808\"\n             sodipodi:role=\"line\"\n             id=\"tspan2631\"\n             x=\"146.32954\"\n             y=\"-221.81322\">MUX</tspan></text>\n        <path\n           inkscape:connector-curvature=\"0\"\n           sodipodi:nodetypes=\"ccccc\"\n           id=\"path7251\"\n           d=\"m 236.50149,113.30808 v 12.53193 l 4.18897,-2.50639 v -7.51915 z\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#ffe700;fill-opacity:1;stroke:#000000;stroke-width:0.45823982;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;enable-background:accumulate\" />\n        <text\n           transform=\"matrix(0,1.0939186,-0.91414477,0,0,0)\"\n           id=\"text7255\"\n           y=\"-260.03085\"\n           x=\"109.23637\"\n           style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:2.74943876px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1;stroke-width:0.22911991\"\n           xml:space=\"preserve\"><tspan\n             y=\"-260.03085\"\n             x=\"109.23637\"\n             id=\"tspan7253\"\n             sodipodi:role=\"line\"\n             style=\"font-size:2.74943876px;line-height:1;stroke-width:0.22911991\">MUX</tspan></text>\n        <path\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#ffe700;fill-opacity:1;stroke:#000000;stroke-width:0.45823982;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 236.50149,139.12632 v 12.53192 l 4.18897,-2.50638 v -7.51916 z\"\n           id=\"path7257\"\n           sodipodi:nodetypes=\"ccccc\"\n           inkscape:connector-curvature=\"0\" />\n        <text\n           xml:space=\"preserve\"\n           style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:2.74943876px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1;stroke-width:0.22911991\"\n           x=\"132.838\"\n           y=\"-260.03085\"\n           id=\"text7261\"\n           transform=\"matrix(0,1.0939186,-0.91414477,0,0,0)\"><tspan\n             style=\"font-size:2.74943876px;line-height:1;stroke-width:0.22911991\"\n             sodipodi:role=\"line\"\n             id=\"tspan7259\"\n             x=\"132.838\"\n             y=\"-260.03085\">MUX</tspan></text>\n        <path\n           id=\"path2633\"\n           d=\"m 229.72029,145.27317 h 6.49558\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:0.86001611;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           inkscape:connector-curvature=\"0\" />\n        <path\n           sodipodi:nodetypes=\"cc\"\n           id=\"path2700\"\n           d=\"m 205.32199,152.49069 h 12.99114\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:0.86001611;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           inkscape:connector-curvature=\"0\" />\n        <path\n           inkscape:connector-curvature=\"0\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:0.86001623;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 217.40418,151.58882 v 1.708 l 3.46431,-0.854 -3.46431,-0.854\"\n           id=\"use2702\" />\n        <path\n           inkscape:connector-curvature=\"0\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:0.86001623;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 225.93872,80.020076 v 1.707997 l 3.4643,-0.853999 -3.4643,-0.853998\"\n           id=\"use2708\" />\n        <path\n           sodipodi:nodetypes=\"ccc\"\n           id=\"path2712\"\n           d=\"m 215.43023,178.70188 v -72.69197 0\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:1.21693027;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           inkscape:connector-curvature=\"0\" />\n        <path\n           sodipodi:nodetypes=\"cc\"\n           id=\"path2743\"\n           d=\"m 205.8308,179.36966 h 32.95332\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:1.36972201;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           inkscape:connector-curvature=\"0\" />\n        <path\n           inkscape:connector-curvature=\"0\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:0.86001623;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 236.95812,178.45702 v 1.708 l 3.4643,-0.854 -3.4643,-0.854\"\n           id=\"use2745\" />\n        <path\n");
    fprintf(output,"           id=\"path2751\"\n           d=\"m 240.26375,90.40583 h 23.81711\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:0.86001611;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           inkscape:connector-curvature=\"0\" />\n        <path\n           id=\"path2911\"\n           d=\"M 266.35533,215.3788 H 234.91919\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:0.61928999;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           inkscape:connector-curvature=\"0\" />\n        <path\n           inkscape:connector-curvature=\"0\"\n           sodipodi:nodetypes=\"ccccc\"\n           id=\"path5104\"\n           d=\"m 225.91335,202.16891 v 24.37858 l 8.66075,-4.87572 v -14.62714 z\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#ffe700;fill-opacity:1;stroke:#000000;stroke-width:0.91899312;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;enable-background:accumulate\" />\n        <text\n           transform=\"matrix(0,1.0610993,-0.94241885,0,0,0)\"\n           id=\"text5108\"\n           y=\"-242.35858\"\n           x=\"201.87161\"\n           style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:5.51395893px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1;stroke-width:0.45949653\"\n           xml:space=\"preserve\"><tspan\n             y=\"-242.35858\"\n             x=\"201.87161\"\n             id=\"tspan5106\"\n             sodipodi:role=\"line\"\n             style=\"font-size:5.51395893px;line-height:1;stroke-width:0.45949653\">MUX</tspan></text>\n        <path\n           id=\"path5098\"\n           d=\"m 222.44905,204.34354 v 1.708 l 3.46431,-0.854 -3.46431,-0.854\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:0.8602199;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           inkscape:connector-curvature=\"0\" />\n        <path\n           id=\"path5112\"\n           d=\"m 205.03911,205.19754 h 7.54316 13.33109\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:0.5506447;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           inkscape:connector-curvature=\"0\"\n           sodipodi:nodetypes=\"ccc\" />\n        <path\n           sodipodi:nodetypes=\"ccc\"\n           inkscape:connector-curvature=\"0\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:0.54988801;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 205.04858,221.50065 h 7.52244 13.29447\"\n           id=\"path5114\" />\n        <path\n           inkscape:connector-curvature=\"0\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:0.86001623;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 222.40118,220.64665 v 1.70799 l 3.46431,-0.85399 -3.46431,-0.854\"\n           id=\"path5116\" />\n        <text\n           transform=\"scale(0.97035795,1.0305475)\"\n           xml:space=\"preserve\"\n           style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:2.337533px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:start;writing-mode:lr-tb;text-anchor:start;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.19479442px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n           x=\"239.50778\"\n           y=\"86.872078\"\n           id=\"text4785\"><tspan\n             sodipodi:role=\"line\"\n             x=\"239.50778\"\n             y=\"86.872078\"\n             id=\"tspan4783\"\n             style=\"font-size:2.337533px;line-height:1;stroke-width:0.19479442px\">Add</tspan><tspan\n             sodipodi:role=\"line\"\n             x=\"239.50778\"\n             y=\"89.20961\"\n             style=\"font-size:2.337533px;line-height:1;stroke-width:0.19479442px\"\n             id=\"tspan4789\">Result</tspan><tspan\n             sodipodi:role=\"line\"\n             x=\"239.50778\"\n             y=\"90.37838\"\n             style=\"font-size:2.337533px;line-height:1;stroke-width:0.19479442px\"\n             id=\"tspan4791\" /></text>\n        <text\n           id=\"text4823\"\n           y=\"95.039574\"\n           x=\"222.98347\"\n           style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:2.35694623px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.19641218px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n           xml:space=\"preserve\"\n           transform=\"scale(0.96902684,1.0319632)\"><tspan\n             id=\"tspan4821\"\n             y=\"95.039574\"\n             x=\"223.39778\"\n             sodipodi:role=\"line\"\n             style=\"font-size:2.35694623px;line-height:1.25;stroke-width:0.19641218px\">Shift </tspan><tspan\n             y=\"97.985756\"\n             x=\"222.98347\"\n             sodipodi:role=\"line\"\n             style=\"font-size:2.35694623px;line-height:1.25;stroke-width:0.19641218px\"\n             id=\"tspan4886\">left 2</tspan></text>\n        <path\n           inkscape:connector-curvature=\"0\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:0.80719149;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 220.59095,99.651114 h 9.53689\"\n           id=\"path4829\" />\n        <path\n           inkscape:connector-curvature=\"0\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:0.86001611;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 205.58592,80.874074 h 23.8171\"\n           id=\"path4835\" />\n        <path\n           inkscape:connector-curvature=\"0\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:0.92059952;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 205.8904,119.18508 h 30.34555\"\n           id=\"path4851\" />\n        <path\n           id=\"path4868\"\n           d=\"m 234.69975,118.33108 v 1.708 l 1.5362,-0.854 -1.5362,-0.854\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:0.57269472;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           inkscape:connector-curvature=\"0\" />\n        <path\n           style=\"fill:none;stroke:#000000;stroke-width:0.96408784;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n           d=\"m 210.42187,152.35447 c 0,0 0.27799,18.30502 -0.007,20.62707 l 55.94063,-0.30265\"\n           id=\"path4872\"\n           inkscape:connector-curvature=\"0\"\n           sodipodi:nodetypes=\"ccc\" />\n        <path\n           inkscape:connector-curvature=\"0\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:0.57269472;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 234.69975,144.34205 v 1.708 l 1.5362,-0.854 -1.5362,-0.854\"\n           id=\"path7271\" />\n        <path\n           inkscape:connector-curvature=\"0\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:0.57269472;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           d=\"m 241.3817,144.69662 v 1.70799 l 1.5362,-0.85399 -1.5362,-0.854\"\n           id=\"path7281\" />\n        <path\n           id=\"path7285\"\n           d=\"m 241.3817,118.37058 v 1.70799 l 1.5362,-0.854 -1.5362,-0.85399\"\n           style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:0.57269472;stroke-opacity:1;marker:none;enable-background:accumulate\"\n           inkscape:connector-curvature=\"0\" />\n        <path\n           inkscape:connector-curvature=\"0\"\n           id=\"path7283\"\n           d=\"m 240.06889,145.62565 h 2.99396\"\n           style=\"fill:none;stroke:#000000;stroke-width:0.5650515;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\" />\n        <path\n           style=\"fill:none;stroke:#000000;stroke-width:0.5650515;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n           d=\"m 240.06889,119.29961 h 2.99396\"\n           id=\"path7287\"\n           inkscape:connector-curvature=\"0\" />\n        <path\n           style=\"fill:none;stroke:#000000;stroke-width:0.7650696;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n           d=\"m 205.83465,197.64896 h 7.80663 v 62.04478 h 20.37662\"\n           id=\"path7321\"\n           inkscape:connector-curvature=\"0\" />\n        <path\n           style=\"fill:none;stroke:#000000;stroke-width:0.7650696;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1\"\n           d=\"m 205.43772,201.48541 1.67102,0.44768 v 77.47211 h 24.79212\"\n           id=\"path7323\"\n           inkscape:connector-curvature=\"0\" />\n      </g>\n    </g>\n    <text\n       xml:space=\"preserve\"\n       style=\"font-style:normal;font-weight:normal;font-size:3.51164055px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.21947753\"\n       x=\"-118.44222\"\n       y=\"140.00989\"\n       id=\"text7327\"\n       transform=\"matrix(0,-0.82952146,1.2055143,0,0,0)\"><tspan\n         sodipodi:role=\"line\"\n         id=\"tspan7325\"\n         x=\"-118.44222\"\n         y=\"140.00989\"\n         style=\"stroke:#ff0000;stroke-width:0.21947753;stroke-opacity:1\">RegWrite</tspan></text>\n    <g\n       id=\"IFmaster\"\n       style=\"opacity:");
    if(!strcmp(IF,"nop") || !strcmp(IF,"0"))
        fprintf(output,"0.2");
    else
        fprintf(output,"1");
    fprintf(output,"\">\n      <rect\n         y=\"175\"\n         x=\"100\"\n         height=\"100\"\n         width=\"75\"\n         id=\"rect2395\"\n         style=\"fill:#ffe700;stroke:#000000;stroke-opacity:1;fill-opacity:1;fill-rule:evenodd;stroke-width:2;stroke-linecap:butt;stroke-linejoin:miter\"\n         transform=\"matrix(0.4329594,0,0,0.42699914,36.887007,65.929104)\" />\n      <text\n         id=\"text2397\"\n         y=\"223.16888\"\n         x=\"138.45026\"\n         style=\"fill:none;stroke:#000000;stroke-opacity:1;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill-opacity:1;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter\"\n         xml:space=\"preserve\"\n         transform=\"matrix(0.4329594,0,0,0.42699914,36.887007,65.929104)\"><tspan\n           y=\"223.16888\"\n           x=\"138.45026\"\n           id=\"tspan2399\"\n           sodipodi:role=\"line\"\n           style=\"font-size:12px;line-height:1.25;text-align:center;text-anchor:middle;fill:none;stroke:#000000;stroke-opacity:1\">Instruction</tspan><tspan\n           id=\"tspan4826\"\n           y=\"238.16888\"\n           x=\"138.45026\"\n           sodipodi:role=\"line\"\n           style=\"font-size:12px;line-height:1.25;text-align:center;text-anchor:middle;fill:none;stroke:#000000;stroke-opacity:1\">Memory</tspan></text>\n      <rect\n         y=\"175\"\n         x=\"25\"\n         height=\"100\"\n         width=\"25\"\n         id=\"rect2411\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#ffe700;fill-opacity:1;stroke:#000000;stroke-width:2;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         transform=\"matrix(0.4329594,0,0,0.42699914,43.381396,65.929104)\" />\n      <path\n         inkscape:connector-curvature=\"0\"\n         sodipodi:nodetypes=\"ccc\"\n         id=\"path2413\"\n         d=\"M 25,275 37.5,255 50,275\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:0.11764706;stroke:#000000;stroke-width:2;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         transform=\"matrix(0.4329594,0,0,0.42699914,43.381396,65.929104)\" />\n      <text\n         id=\"text2398\"\n         y=\"229.36816\"\n         x=\"29.425781\"\n         style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:start;writing-mode:lr-tb;text-anchor:start;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         xml:space=\"preserve\"\n         transform=\"matrix(0.4329594,0,0,0.42699914,43.381396,65.929104)\"><tspan\n           y=\"229.36816\"\n           x=\"29.425781\"\n           id=\"tspan2400\"\n           sodipodi:role=\"line\"\n           style=\"font-size:12px;line-height:1\">PC</tspan></text>\n      <path\n         inkscape:connector-curvature=\"0\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#ffe700;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         d=\"m 98.646528,171.6548 46.776772,18.75495 v 50.0132 L 98.646528,259.1779 V 221.668 l 15.592262,-6.25165 -15.592262,-6.25165 z\"\n         id=\"path2402\"\n         sodipodi:nodetypes=\"cccccccc\"\n         transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n      <text\n         xml:space=\"preserve\"\n         style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:16.7551403px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1.39626157px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         x=\"237.60242\"\n         y=\"-111.7238\"\n         id=\"text2414\"\n         transform=\"matrix(0,0.30581597,-0.31008471,0,59.285582,17.9824)\"><tspan\n           sodipodi:role=\"line\"\n           id=\"tspan2416\"\n           x=\"237.60242\"\n           y=\"-111.7238\"\n           style=\"font-size:16.7551403px;line-height:1;stroke-width:1.39626157px\">Adder</tspan></text>\n      <path\n         inkscape:connector-curvature=\"0\"\n         id=\"path2545\"\n         d=\"M 192.20007,421.72081 H 231.1807\"\n         style=\"display:inline;overflow:visible;visibility:visible;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n      <path\n         inkscape:connector-curvature=\"0\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         d=\"M 20.68521,421.72081 H 75.258146\"\n         id=\"path2438\"\n         sodipodi:nodetypes=\"cc\"\n         transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n      <path\n         inkscape:connector-curvature=\"0\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         d=\"M 36.277478,421.72081 V 240.42295 h 54.572926\"\n         id=\"path2442\"\n         sodipodi:nodetypes=\"ccc\"\n         transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n      <path\n         id=\"use2519\"\n         d=\"m 62.78433,419.22015 v 5.00132 l 12.473806,-2.50066 -12.473806,-2.50066\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n");
    fprintf(output,"         inkscape:connector-curvature=\"0\"\n         transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n      <path\n         id=\"use2521\"\n         d=\"m 86.172722,237.9223 v 5.00132 l 12.473806,-2.50066 -12.473806,-2.50066\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         inkscape:connector-curvature=\"0\"\n         transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n      <path\n         id=\"use2547\"\n         d=\"m 218.7069,419.22015 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         inkscape:connector-curvature=\"0\"\n         transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n      <ellipse\n         ry=\"3.1258252\"\n         rx=\"3.8980641\"\n         cy=\"421.72079\"\n         cx=\"36.277424\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         id=\"path2602\"\n         transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n      <path\n         id=\"use2809\"\n         d=\"m -30.769236,419.22015 v 5.00132 l 12.473805,-2.50066 -12.473805,-2.50066\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         inkscape:connector-curvature=\"0\"\n         transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n      <path\n         inkscape:connector-curvature=\"0\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         d=\"m 145.4233,215.41635 h 38.98065 V 184.1581 h 46.77675\"\n         id=\"path2811\"\n         transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n      <path\n         id=\"use2813\"\n         d=\"m 218.70691,181.65744 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         inkscape:connector-curvature=\"0\"\n         transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n      <path\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#ffe700;fill-opacity:1;stroke:#000000;stroke-width:2;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         d=\"m 469.25,164 v 50 l 20,-10 v -30 z\"\n         id=\"path5068\"\n         sodipodi:nodetypes=\"ccccc\"\n         inkscape:connector-curvature=\"0\"\n         transform=\"matrix(0.4329594,0,0,0.79904093,-173.04097,12.062811)\" />\n      <text\n         xml:space=\"preserve\"\n         style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:center;writing-mode:lr-tb;text-anchor:middle;fill:#000000;fill-opacity:1\"\n         x=\"188.6875\"\n         y=\"-475\"\n         id=\"text5072\"\n         transform=\"matrix(0,0.79904093,-0.4329594,0,-173.04097,12.062811)\"><tspan\n           style=\"font-size:12px;line-height:1\"\n           sodipodi:role=\"line\"\n           id=\"tspan5070\"\n           x=\"188.6875\"\n           y=\"-475\">MUX</tspan></text>\n      <path\n         sodipodi:nodetypes=\"cccccc\"\n         id=\"path5076\"\n         d=\"m 158.31319,211.12959 0.10165,-11.71647 V 165.6364 l -283.74205,0.10679 -0.14597,240.0975 20.31076,0.0115\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:2.96023655;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         inkscape:connector-curvature=\"0\"\n         transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n      <path\n         style=\"display:inline;overflow:visible;visibility:visible;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.91776466;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         d=\"m -74.150493,422.09016 h 42.555509\"\n         id=\"path5082\"\n         inkscape:connector-curvature=\"0\"\n         transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n      <path\n         inkscape:connector-curvature=\"0\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         d=\"m -117.63622,403.35154 v 5.00132 l 12.4738,-2.50066 -12.4738,-2.50066\"\n         id=\"path5084\"\n         transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n      <ellipse\n         cx=\"158.40596\"\n         cy=\"215.28223\"\n         rx=\"3.8980641\"\n         ry=\"3.1258252\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         id=\"ellipse5090\"\n         transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n      <path\n         id=\"path4837\"\n         d=\"M 41.22848,192.31965 H 95.801406\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:2.79252315;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         inkscape:connector-curvature=\"0\"\n         transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n      <path\n         inkscape:connector-curvature=\"0\"\n         style=\"display:inline;overflow:visible;visibility:visible;opacity:1;fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2.79252362;stroke-opacity:1;marker:none;enable-background:accumulate\"\n         d=\"m 83.3276,189.81899 v 5.00132 L 95.801406,192.31965 83.3276,189.81899\"\n         id=\"path4839\"\n         transform=\"matrix(0.2776759,0,0,0.34150914,59.285582,17.9824)\" />\n      <text\n         id=\"text4843\"\n         y=\"220.70055\"\n         x=\"13.217793\"\n         style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:16.7551403px;line-height:0%%;font-family:'DejaVu Sans';-inkscape-font-specification:'DejaVu Sans';text-align:start;writing-mode:lr-tb;text-anchor:start;fill:#000000;fill-opacity:1;stroke:none;stroke-width:1.39626157px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n         xml:space=\"preserve\"\n         transform=\"matrix(0.31008471,0,0,0.30581597,59.285582,17.9824)\"><tspan\n           id=\"tspan4845\"\n           style=\"font-size:16.7551403px;line-height:1;stroke-width:1.39626157px\"\n           y=\"220.70055\"\n           x=\"13.217793\"\n           sodipodi:role=\"line\">4</tspan><tspan\n           id=\"tspan4849\"\n           style=\"font-size:16.7551403px;line-height:1;stroke-width:1.39626157px\"\n           y=\"229.07811\"\n           x=\"13.217793\"\n           sodipodi:role=\"line\" /></text>\n      <text\n         id=\"text7331\"\n         y=\"153.59583\"\n         x=\"26.259895\"\n         style=\"font-style:normal;font-weight:normal;font-size:4.23333311px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.26458332\"\n         xml:space=\"preserve\"><tspan\n           style=\"stroke-width:0.26458332\"\n           y=\"153.59583\"\n           x=\"26.259895\"\n           id=\"tspan7329\"\n           sodipodi:role=\"line\">0</tspan></text>\n      <text\n         id=\"text7335\"\n         y=\"169.86771\"\n         x=\"26.193748\"\n         style=\"font-style:normal;font-weight:normal;font-size:4.23333311px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.26458332\"\n         xml:space=\"preserve\"><tspan\n           style=\"stroke-width:0.26458332\"\n           y=\"169.86771\"\n           x=\"26.193748\"\n           id=\"tspan7333\"\n           sodipodi:role=\"line\">1</tspan></text>\n    </g>\n    <text\n       xml:space=\"preserve\"\n       style=\"font-style:normal;font-weight:normal;font-size:4.23333311px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.26458332\"\n       x=\"9.5249996\"\n       y=\"222.91667\"\n       id=\"text7429\"><tspan\n         sodipodi:role=\"line\"\n         x=\"9.5249996\"\n         y=\"222.91667\"\n         style=\"stroke-width:0.26458332\"\n         id=\"tspan7451\">Thread 1</tspan></text>\n    <text\n       id=\"text7433\"\n       y=\"230.85406\"\n       x=\"9.5249996\"\n       style=\"font-style:normal;font-weight:normal;font-size:4.23333311px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.26458332\"\n       xml:space=\"preserve\"><tspan\n         style=\"stroke-width:0.26458332\"\n         y=\"230.85406\"\n         x=\"9.5249996\"\n         id=\"tspan7431\"\n         sodipodi:role=\"line\">Thread 2</tspan></text>\n    <text\n       xml:space=\"preserve\"\n       style=\"font-style:normal;font-weight:normal;font-size:4.23333311px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.26458332\"\n       x=\"9.5249996\"\n       y=\"237.73314\"\n       id=\"text7437\"><tspan\n         sodipodi:role=\"line\"\n         id=\"tspan7435\"\n         x=\"9.5249996\"\n         y=\"237.73314\"\n         style=\"stroke-width:0.26458332\">Thread 3</tspan></text>\n    <text\n       id=\"text7441\"\n       y=\"245.67053\"\n       x=\"9.5249996\"\n       style=\"font-style:normal;font-weight:normal;font-size:4.23333311px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.26458332\"\n       xml:space=\"preserve\"><tspan\n         style=\"stroke-width:0.26458332\"\n         y=\"245.67053\"\n         x=\"9.5249996\"\n         id=\"tspan7439\"\n         sodipodi:role=\"line\">Thread 4</tspan></text>\n    <text\n       xml:space=\"preserve\"\n       style=\"font-style:normal;font-weight:normal;font-size:4.23333311px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.26458332\"\n       x=\"9.5249996\"\n       y=\"253.07877\"\n       id=\"text7445\"><tspan\n         sodipodi:role=\"line\"\n         id=\"tspan7443\"\n         x=\"9.5249996\"\n         y=\"253.07877\"\n         style=\"stroke-width:0.26458332\">Thread 5</tspan></text>\n    <text\n       id=\"text7449\"\n       y=\"253.07877\"\n       x=\"9.5249996\"\n       style=\"font-style:normal;font-weight:normal;font-size:4.23333311px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.26458332\"\n       xml:space=\"preserve\"><tspan\n         style=\"stroke-width:0.26458332\"\n         y=\"256.94098\"\n         x=\"9.5249996\"\n         id=\"tspan7447\"\n         sodipodi:role=\"line\" /></text>\n    <text\n       xml:space=\"preserve\"\n       style=\"font-style:normal;font-weight:normal;font-size:4.23333311px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.26458332\"\n       x=\"28.250387\"\n       y=\"251.1633\"\n       id=\"text7457\"><tspan\n         sodipodi:role=\"line\"\n         id=\"tspan7455\"\n         x=\"28.250387\"\n         y=\"255.0255\"\n         style=\"stroke-width:0.26458332\" /></text>\n    <text\n       id=\"text7461\"\n       y=\"222.91667\"\n       x=\"34.395844\"\n       style=\"font-style:normal;font-weight:normal;font-size:4.23333311px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.26458332\"\n       xml:space=\"preserve\"><tspan\n         id=\"tspan7459\"\n         style=\"stroke-width:0.26458332\"\n         y=\"222.91667\"\n         x=\"34.395844\"\n         sodipodi:role=\"line\">%s</tspan></text>\n    <text\n       xml:space=\"preserve\"\n       style=\"font-style:normal;font-weight:normal;font-size:4.23333311px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.26458332\"\n       x=\"34.395844\"\n       y=\"230.85406\"\n       id=\"text7469\"><tspan\n         sodipodi:role=\"line\"\n         x=\"34.395844\"\n         y=\"230.85406\"\n         style=\"stroke-width:0.26458332\"\n         id=\"tspan7467\">%s</tspan></text>\n    <text\n       id=\"text7473\"\n       y=\"237.73314\"\n       x=\"34.395844\"\n       style=\"font-style:normal;font-weight:normal;font-size:4.23333311px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.26458332\"\n       xml:space=\"preserve\"><tspan\n         id=\"tspan7471\"\n         style=\"stroke-width:0.26458332\"\n         y=\"237.73314\"\n         x=\"34.395844\"\n         sodipodi:role=\"line\">%s</tspan></text>\n    <text\n       xml:space=\"preserve\"\n       style=\"font-style:normal;font-weight:normal;font-size:4.23333311px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.26458332\"\n       x=\"34.395844\"\n       y=\"245.67053\"\n       id=\"text7477\"><tspan\n         sodipodi:role=\"line\"\n         x=\"34.395844\"\n         y=\"245.67053\"\n         style=\"stroke-width:0.26458332\"\n         id=\"tspan7475\">%s</tspan></text>\n    <text\n       id=\"text7481\"\n       y=\"252.54961\"\n       x=\"34.395844\"\n       style=\"font-style:normal;font-weight:normal;font-size:4.23333311px;line-height:1.25;font-family:sans-serif;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;stroke-width:0.26458332\"\n       xml:space=\"preserve\"><tspan\n         id=\"tspan7479\"\n         style=\"stroke-width:0.26458332\"\n         y=\"252.54961\"\n         x=\"34.395844\"\n         sodipodi:role=\"line\">%s</tspan></text>\n  </g>\n</svg>\n",a1,a2,a3,a4,a5);
 
    fclose(output);
}
