/*
 * cache.c
 */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "cache.h"
#include "main.h"

/* cache configuration parameters */
int cache_split = 0;
int cache_usize = DEFAULT_CACHE_SIZE;
int cache_isize = DEFAULT_CACHE_SIZE; 
int cache_dsize = DEFAULT_CACHE_SIZE;
int cache_block_size = DEFAULT_CACHE_BLOCK_SIZE;
int words_per_block = DEFAULT_CACHE_BLOCK_SIZE / WORD_SIZE;
int cache_assoc = DEFAULT_CACHE_ASSOC;
int cache_writeback = DEFAULT_CACHE_WRITEBACK;
int cache_writealloc = DEFAULT_CACHE_WRITEALLOC;
int debugging_mode = 0;
int lineno = 0;

/* cache model data structures */
Pcache icache;
Pcache dcache;
cache c1;
cache c2;
cache_stat cache_stat_inst;
cache_stat cache_stat_data;

/************************************************************/
void set_cache_param(param, value)
  int param;
  int value;
{

  switch (param) {
  case CACHE_PARAM_BLOCK_SIZE:
    cache_block_size = value;
    words_per_block = value / WORD_SIZE;
    break;
  case CACHE_PARAM_USIZE:
    cache_split = FALSE;
    cache_usize = value;
    break;
  case CACHE_PARAM_ISIZE:
    cache_split = TRUE;
    cache_isize = value;
    break;
  case CACHE_PARAM_DSIZE:
    cache_split = TRUE;
    cache_dsize = value;
    break;
  case CACHE_PARAM_ASSOC:
    cache_assoc = value;
    break;
  case CACHE_PARAM_WRITEBACK:
    cache_writeback = TRUE;
    break;
  case CACHE_PARAM_WRITETHROUGH:
    cache_writeback = FALSE;
    break;
  case CACHE_PARAM_WRITEALLOC:
    cache_writealloc = TRUE;
    break;
  case CACHE_PARAM_NOWRITEALLOC:
    cache_writealloc = FALSE;
    break;
  case CACHE_PARAM_SPLIT:
    cache_split = TRUE;
    break;
  case CACHE_PARAM_UNI:
    cache_split = FALSE;
    break;
  default:
    printf("error set_cache_param: bad parameter value\n");
    exit(-1);
  }

}

/************************************************************/

/************************************************************/
void init_cache()
{
  /* initialize the cache, and cache statistics data structures */
  if(cache_split){
    c1.size = cache_isize;
    c1.associativity = cache_assoc;
    c1.n_sets = cache_isize/(cache_block_size * cache_assoc);
    c1.index_mask = cache_block_size * (c1.n_sets-1);
    c1.index_mask_offset = LOG2(cache_block_size);
    c1.contents = 0;
    c1.set_contents = malloc(sizeof(int)*c1.n_sets);
    c1.LRU_head= malloc(sizeof(Pcache_line)*c1.n_sets);
    c1.LRU_tail = malloc(sizeof(Pcache_line)*c1.n_sets);
    for(int i = 0; i < c1.n_sets; i++){
      c1.set_contents[i] = 0;
      c1.LRU_head[i] = NULL;
      c1.LRU_tail[i] = NULL;
    }
  }
  if(cache_split){
    c2.size = cache_dsize;
    c2.n_sets = cache_dsize/(cache_block_size * cache_assoc);
  }
  else{
    c2.size = cache_usize;
    c2.n_sets = cache_usize/(cache_block_size * cache_assoc);
  }
  c2.associativity = cache_assoc;
  c2.index_mask = cache_block_size * (c2.n_sets-1);
  c2.index_mask_offset = LOG2(cache_block_size);
  c2.contents = 0;
  c2.set_contents = malloc(sizeof(int)*c2.n_sets);
  c2.LRU_head = malloc(sizeof(Pcache_line)*c2.n_sets);
  c2.LRU_tail = malloc(sizeof(Pcache_line)*c2.n_sets);
  for(int i = 0; i < c2.n_sets; i++){
    c2.set_contents[i] = 0;
    c2.LRU_head[i] = NULL;
    c2.LRU_tail[i] = NULL;
  }
  cache_stat_inst.accesses = 0;
  cache_stat_inst.misses = 0;
  cache_stat_inst.replacements = 0;
  cache_stat_inst.demand_fetches = 0;
  cache_stat_inst.copies_back = 0;
  cache_stat_data.accesses = 0;
  cache_stat_data.misses = 0;
  cache_stat_data.replacements = 0;
  cache_stat_data.demand_fetches = 0;
  cache_stat_data.copies_back = 0;
  //print_data();
}
/************************************************************/

/************************************************************/
void breakpoint(){
  printf("breakpoint\n");
  while(1)
    continue;
}

char* concat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char *convert(int dec){
    if (dec == 0){
        return "0";
    } else{
        if(dec%2==1)
          return concat(convert(dec / 2), "1");
        else
          return concat(convert(dec / 2), "0");
    }
}

int index_no(unsigned addr, cache my_cache){
  /*printf("%s\n", convert((int)addr));
  printf("%s\n", convert((int)my_cache.index_mask));
  printf("%d\n", my_cache.index_mask_offset);*/
  return (addr & my_cache.index_mask) >> my_cache.index_mask_offset;
}

//Debugger  function
void traverse(int var){
  if(cache_split){
    if(var==1)//print cache
      printf("INST\n");
    for(int i = 0; i < c1.n_sets; i++){
      if(c1.LRU_head[i]!=NULL){
        Pcache_line x = c1.LRU_head[i];
        if(var==1)
          printf("Set #%d has\n", i);
        while(x!=NULL){
          if(var==0 && x->dirty==1 && cache_writeback)
            cache_stat_inst.copies_back++;
          if(var==1)
            printf("    Tag: %s\n", convert((int)x->tag));
          x = x->LRU_next;
        }
      }
    }
    if(var==1)
      printf("DATA\n");
    for(int i = 0; i < c2.n_sets; i++){
      if(c2.LRU_head[i]!=NULL){
        Pcache_line x = c2.LRU_head[i];
        if(var==1)
          printf("Set #%d has\n", i);
        while(x!=NULL){
          if(var==0 && x->dirty==1 && cache_writeback)
            cache_stat_data.copies_back++;
          if(var==1)
            printf("    Tag: %s\n", convert((int)x->tag));
          x = x->LRU_next;
        }
      }
    }
  }else{
    if(var==1)
      printf("Unified\n");
    for(int i = 0; i < c2.n_sets; i++){
      if(c2.LRU_head[i]!=NULL){
        Pcache_line x = c2.LRU_head[i];
        if(var==1)
          printf("Set #%d has\n", i);
        while(x!=NULL){
          if(var==0 && x->dirty==1 && cache_writeback)
            cache_stat_data.copies_back++;
          if(var==1)
            printf("    Tag: %s\n", convert((int)x->tag));
          x = x->LRU_next;
        }
      }
    }
  }
}

void tracedirty(){
  traverse(0);
}

void print_data(){
  printf("***Printing cache-info :-\n");
  traverse(1);
}

void perform_access(addr, access_type)
  unsigned addr, access_type;
{
  if(debugging_mode)
    printf("%x\n", addr);
  int set_no = index_no(addr, c2);
  //INST READ
  if(access_type==2){
    cache_stat_inst.accesses++;
    if(debugging_mode)
      printf("*set_no = %d\n", set_no);
    //c1.LRU_head[set_no] of the set
    Pcache_line x = NULL;
    if(cache_split)
      x = c1.LRU_head[set_no]; 
    else
      x = c2.LRU_head[set_no]; 
    //tag value of the address 
    unsigned addr_tag = 0;
    if(cache_split)
      addr_tag = (addr >> LOG2(cache_block_size * c1.n_sets));
    else
      addr_tag = (addr >> LOG2(cache_block_size * c2.n_sets));
    if(debugging_mode)
      printf("*addr_tag = %s\n", convert((int)addr_tag));
    //search through the set for the matching tag
    int match = 0;
    while(x!=NULL){
      if(x->tag == addr_tag){
        match = 1; 
        break;
      }
        x = x->LRU_next;
    }
    if(match == 1){//READ HIT
      //Successful match. No need to access memory. 
      //Push the block to the top of the set list
      if(debugging_mode)
        printf("**tag match = %d\n", x->tag);
      if(cache_split){
        delete(&c1.LRU_head[set_no], &c1.LRU_tail[set_no], x);
        insert(&c1.LRU_head[set_no], &c1.LRU_tail[set_no], x);
      }else{
        delete(&c2.LRU_head[set_no], &c2.LRU_tail[set_no], x);
        insert(&c2.LRU_head[set_no], &c2.LRU_tail[set_no], x);
      }
      if(debugging_mode)
        print_data();
    }else{//READ MISS
      cache_stat_inst.misses++;
      //delete LRU_c1.LRU_tail[set_no] and insert new cache block from memory
      Pcache_line item = malloc(sizeof(cache_line));
      item->tag = addr_tag;
      item->dirty = 0;
      cache_stat_inst.demand_fetches++;//fetching item from memory to cache
      int a = (cache_split) ? c1.set_contents[set_no] : c2.set_contents[set_no];
      int b = (cache_split) ? c1.associativity : c2.associativity;
      if(a==b){//fully filled set
        cache_stat_inst.replacements++;
        printf("(address %x, tag = %d, index = %d)\n", addr, addr_tag, set_no);
        if(debugging_mode)
          printf("**replacing block from set\n");
        //DELETING tail from cache
        int c = (cache_split) ? c1.LRU_tail[set_no]->dirty : c2.LRU_tail[set_no]->dirty;
        if(cache_writeback && c)//WRITEBACK A DIRTY BLOCK
          cache_stat_inst.copies_back++;
        if(cache_split){
          delete(&c1.LRU_head[set_no], &c1.LRU_tail[set_no], c1.LRU_tail[set_no]);
          insert(&c1.LRU_head[set_no], &c1.LRU_tail[set_no], item);
        }else{
          delete(&c2.LRU_head[set_no], &c2.LRU_tail[set_no], c2.LRU_tail[set_no]);
          insert(&c2.LRU_head[set_no], &c2.LRU_tail[set_no], item);
        }
        if(debugging_mode)
          print_data();

      }
      else if(a<b){//partially filled set
        if(debugging_mode)
          printf("**adding cache_line to set\n");
        if(cache_split){
          c1.set_contents[set_no]++;
          c1.contents++;
          insert(&c1.LRU_head[set_no], &c1.LRU_tail[set_no], item);
        }else{
          c2.set_contents[set_no]++;
          c2.contents++;
          insert(&c2.LRU_head[set_no], &c2.LRU_tail[set_no], item);
        }
        if(debugging_mode)
          print_data();
      }
    }
  }
  // DATA READ
  else if(access_type==0){
    cache_stat_data.accesses++;
    if(debugging_mode)
      printf("*set_no = %d\n", set_no);
    //c2.LRU_head[set_no] of the set
    Pcache_line x = c2.LRU_head[set_no]; 
    //tag value of the address 
    unsigned addr_tag = (addr >> LOG2(cache_block_size * c2.n_sets));
    if(debugging_mode)
      printf("*addr_tag = %s\n", convert((int)addr_tag));
    //search through the set for the matching tag
    int match = 0;
    while(x!=NULL){
      if(x->tag == addr_tag){
        match = 1; 
        break;
      }
        x = x->LRU_next;
    }
    if(match == 1){//READ HIT
      //Successful match. No need to access memory. 
      //Push the block to the top of the set list
      if(debugging_mode)
        printf("**tag match = %d\n", x->tag);
      delete(&c2.LRU_head[set_no], &c2.LRU_tail[set_no], x);
      insert(&c2.LRU_head[set_no], &c2.LRU_tail[set_no], x);
      if(debugging_mode)
        print_data();
    }else{//READ MISS
      cache_stat_data.misses++;
      //delete LRU_c2.LRU_tail[set_no] and insert new cache block from memory
      Pcache_line item = malloc(sizeof(cache_line));
      item->tag = addr_tag;
      item->dirty = 0;
      cache_stat_data.demand_fetches++;//fetching item from memory to cache
      if(c2.set_contents[set_no]==c2.associativity){//fully filled set
        cache_stat_data.replacements++;
        if(debugging_mode)
          printf("**replacing block from set\n");
        //DELETING tail from set
        if(cache_writeback && c2.LRU_tail[set_no]->dirty)//WRITEBACK A DIRTY BLOCK
          cache_stat_data.copies_back++;
        delete(&c2.LRU_head[set_no], &c2.LRU_tail[set_no], c2.LRU_tail[set_no]);
        insert(&c2.LRU_head[set_no], &c2.LRU_tail[set_no], item);
        if(debugging_mode)
          print_data();

      }
      else if(c2.set_contents[set_no] < c2.associativity){//partially filled set
        if(debugging_mode)
          printf("**adding cache_line to set\n");
        c2.set_contents[set_no]++;
        c2.contents++;
        insert(&c2.LRU_head[set_no], &c2.LRU_tail[set_no], item);
        if(debugging_mode)
          print_data();
      }
    }
  }
  // DATA STORE/WRITE
  else if(access_type==1){
    cache_stat_data.accesses++;
    if(debugging_mode)
      printf("*set_no = %d\n", set_no);
    //c2.LRU_head[set_no] of the set
    Pcache_line x = c2.LRU_head[set_no]; 
    //tag value of the address 
    unsigned addr_tag = (addr >> LOG2(cache_block_size * c2.n_sets));
    if(debugging_mode)
      printf("*addr_tag = %s\n", convert((int)addr_tag));
    //search through the set for the matching tag
    int match = 0;
    while(x!=NULL){
      if(x->tag == addr_tag){
        match = 1; 
        break;
      }
        x = x->LRU_next;
    }
    if(match == 1){//WRITE HIT
      //Successful match. No need to access memory. 
      //Push the block to the top of the set list
      if(!cache_writeback)//if WRITE-THROUGH
        cache_stat_data.copies_back++;
      if(debugging_mode)
        printf("**tag match = %d\n", x->tag);
      x->dirty = 1;
      delete(&c2.LRU_head[set_no], &c2.LRU_tail[set_no], x);
      insert(&c2.LRU_head[set_no], &c2.LRU_tail[set_no], x);
      if(debugging_mode)
        print_data();
    }else{//WRITE MISS
      cache_stat_data.misses++;
      //delete LRU_c2.LRU_tail[set_no] and insert new cache block from memory
      if(!cache_writealloc){//block not loaded to cache but modified in the main memory itself
        if(debugging_mode)
          printf("Write No-Allocate. Block modified in memory, not loaded to cache\n");
        return;
      }
      cache_stat_data.demand_fetches++;//fetching item from memory to cache
      Pcache_line item = malloc(sizeof(cache_line));
      item->tag = addr_tag;
      item->dirty = 1;
      if(c2.set_contents[set_no]==c2.associativity){//fully filled set
        cache_stat_data.replacements++;
        //DELETING tail from set
        if(cache_writeback && c2.LRU_tail[set_no]->dirty)//WRITEBACK A DIRTY BLOCK
          cache_stat_data.copies_back++;
        if(debugging_mode)
          printf("**replacing block from set\n");
        delete(&c2.LRU_head[set_no], &c2.LRU_tail[set_no], c2.LRU_tail[set_no]);
        if(!cache_writeback)//if WRITE-THROUGH
          cache_stat_data.copies_back++;
        insert(&c2.LRU_head[set_no], &c2.LRU_tail[set_no], item);
        if(debugging_mode)
          print_data();

      }
      else if(c2.set_contents[set_no] < c2.associativity){//partially filled set
        if(debugging_mode)
          printf("**adding cache_line to set\n");
        if(!cache_writeback)//if WRITE-THROUGH
          cache_stat_data.copies_back++;
        c2.set_contents[set_no]++;
        c2.contents++;
        insert(&c2.LRU_head[set_no], &c2.LRU_tail[set_no], item);
        if(debugging_mode)
          print_data();
      }
    }
  }
}
/************************************************************/

/************************************************************/
void flush()
{
  /* flush the cache */
  tracedirty();//go through the cache and write back any dirty tagged blocks

}
/************************************************************/

/************************************************************/
void delete(head, tail, item)
  Pcache_line *head, *tail;
  Pcache_line item;
{
  if (item->LRU_prev) {
    item->LRU_prev->LRU_next = item->LRU_next;
  } else {
    /* item at head */
    *head = item->LRU_next;
  }

  if (item->LRU_next) {
    item->LRU_next->LRU_prev = item->LRU_prev;
  } else {
    /* item at tail */
    *tail = item->LRU_prev;
  }
}
/************************************************************/

/************************************************************/
/* inserts at the c2.LRU_head[set_no] of the list */
void insert(head, tail, item)
  Pcache_line *head, *tail;
  Pcache_line item;
{
  item->LRU_next = *head;
  item->LRU_prev = (Pcache_line)NULL;
  if (item->LRU_next)
    item->LRU_next->LRU_prev = item;
  else
    *tail = item;

  *head = item;
}
/************************************************************/

/************************************************************/
void dump_settings()
{
  printf("cache size = %d has", cache_usize);
  printf("*** CACHE SETTINGS ***\n");
  if (cache_split) {
    printf("  Split I- D-cache\n");
    printf("  I-cache size: \t%d\n", cache_isize);
    printf("  D-cache size: \t%d\n", cache_dsize);
  } else {
    printf("  Unified I- D-cache\n");
    printf("  Size: \t%d\n", cache_usize);
  }
  printf("  Associativity: \t%d\n", cache_assoc);
  printf("  Block size: \t%d\n", cache_block_size);
  printf("  Write policy: \t%s\n", 
	 cache_writeback ? "WRITE BACK" : "WRITE THROUGH");
  printf("  Allocation policy: \t%s\n",
	 cache_writealloc ? "WRITE ALLOCATE" : "WRITE NO ALLOCATE");
}
/************************************************************/

/************************************************************/
void print_stats()
{
  //FILE *out_file;
  //out_file = fopen("out1.txt", "a");
  //fprintf(out_file, "%d\n", cache_assoc);
  //fclose(out_file);
  printf("\n*** CACHE STATISTICS ***\n");

  printf(" INSTRUCTIONS\n");
  printf("  accesses:  %d\n", cache_stat_inst.accesses);
  printf("  misses:    %d\n", cache_stat_inst.misses);
  //out_file = fopen("out2.txt", "a");
  if (!cache_stat_inst.accesses){
    printf("  miss rate: 0 (0)\n");
    //fprintf(out_file, "0\n" );
  } 
  else{
    printf("  miss rate: %2.4f (hit rate %2.4f)\n", 
	 (float)cache_stat_inst.misses / (float)cache_stat_inst.accesses,
	 1.0 - (float)cache_stat_inst.misses / (float)cache_stat_inst.accesses);
    //fprintf(out_file, "%2.4f\n", 1.0 - (float)cache_stat_inst.misses / (float)cache_stat_inst.accesses );
  }
  //fclose(out_file);

  printf("  replace:   %d\n", cache_stat_inst.replacements);

  printf(" DATA\n");
  printf("  accesses:  %d\n", cache_stat_data.accesses);
  printf("  misses:    %d\n", cache_stat_data.misses);
  //out_file = fopen("out3.txt", "a");
  if (!cache_stat_data.accesses){
    printf("  miss rate: 0 (0)\n");
    //fprintf(out_file, "0\n" );
  }  
  else{
    printf("  miss rate: %2.4f (hit rate %2.4f)\n", 
	 (float)cache_stat_data.misses / (float)cache_stat_data.accesses,
	 1.0 - (float)cache_stat_data.misses / (float)cache_stat_data.accesses);
    //fprintf(out_file, "%2.4f\n", 1.0 - (float)cache_stat_data.misses / (float)cache_stat_data.accesses );
  }
  //fclose(out_file);
  printf("  replace:   %d\n", cache_stat_data.replacements);

  printf(" TRAFFIC (in words)\n");
  printf("  demand fetch:  %d\n", (cache_stat_inst.demand_fetches + 
	 cache_stat_data.demand_fetches)*WORD_SIZE);
  printf("  copies back:   %d\n", (cache_stat_inst.copies_back +
	 cache_stat_data.copies_back)*WORD_SIZE);
}
/************************************************************/
