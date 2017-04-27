/*
 * cache.c
 */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

void update_pointers(Pcache_line * head, Pcache_line * tail, Pcache_line item)
{
  if (item->LRU_prev==NULL) //curr is head
    return;
  else
    item->LRU_prev->LRU_next = item->LRU_next;

  if (item->LRU_next==NULL) //curr is tail
    *tail = item->LRU_prev;
  else
   item->LRU_next->LRU_prev = item->LRU_prev; 
  
  item->LRU_next = *head;
  item->LRU_prev = NULL;

  if (item->LRU_next)
    item->LRU_next->LRU_prev = item;
  else
    *tail = item;
  
  *head = item;
}

/************************************************************/
void init_cache()
{

  /* initialize the cache, and cache statistics data structures */
  if(cache_split==0)
  {
    c1.size = cache_usize;
    c1.n_sets = cache_usize / (cache_assoc * cache_block_size);
  }
  else
  {
    c1.size = cache_isize;
    c1.n_sets = cache_usize / (cache_assoc * cache_block_size);
  }

  c1.associativity = cache_assoc;
  c1.index_mask_offset = LOG2(cache_block_size);
  c1.index_mask = ((c1.n_sets - 1) << c1.index_mask_offset);
  c1.tag_mask_offset =  LOG2(c1.size);
  c1.tag_mask = (0xFFFFFFFF << (c1.tag_mask_offset));
  c1.LRU_head =(Pcache_line *)malloc(sizeof(Pcache_line)*c1.n_sets);
  c1.LRU_tail =(Pcache_line *)malloc(sizeof(Pcache_line)*c1.n_sets);
  c1.set_contents = (int)malloc(sizeof(int)*c1.n_sets);
  c1.contents = 0;
  
  c2.size = cache_dsize;
  c2.associativity = cache_assoc;
  c2.n_sets = cache_dsize / (cache_assoc * cache_block_size);;
  c2.index_mask_offset = LOG2(cache_block_size);
  c1.index_mask = ((c1.n_sets - 1) << c1.index_mask_offset);
  c2.tag_mask_offset =  LOG2(c2.size);
  c2.tag_mask = (0xFFFFFFFF << (c2.tag_mask_offset));
  c2.LRU_head =(Pcache_line *)malloc(sizeof(Pcache_line)*c2.n_sets);
  c2.LRU_tail =(Pcache_line *)malloc(sizeof(Pcache_line)*c2.n_sets);
  c2.set_contents = (int)malloc(sizeof(int)*c2.n_sets);
  c2.contents = 0;

  int i = 0;
  for (i = 0; i < c1.n_sets; i++)
  {
    c1.LRU_head[i] = NULL;
    c1.LRU_tail[i] = NULL;
    c1.set_contents[i]= 0;
  }
  for (i = 0; i < c2.n_sets; i++)
  {
    c2.LRU_head[i] = NULL;
    c2.LRU_tail[i] = NULL;
    c2.set_contents[i]= 0;
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

}
/************************************************************/

/************************************************************/
void perform_access(addr, access_type)
  unsigned addr, access_type;
{
  /* handle an access to the cache */
  int hit = 0;
  int index = 0;
  unsigned tag = (addr & c1.tag_mask);   
  unsigned addr_tag = 0;
  Pcache_line tmp_curr;

  if(cache_split==0)
  {
    index = (addr & c1.index_mask) >> c1.index_mask_offset;
    if (index >= c1.n_sets)
    {
      printf("\nThis access (%d) is not performed as index (%d) out of bounds!\n",access_type,index);
      return;
    }
    
    if(access_type==TRACE_DATA_STORE)
    {
      cache_stat_data.accesses++;
      tmp_curr = c1.LRU_head[index];
      addr_tag = (addr >> LOG2(cache_block_size * c1.n_sets));
      
      while(tmp_curr!=NULL)
      {
        if(tmp_curr->tag == addr_tag)
        {
          hit = 1;
          break;
        }
        tmp_curr = tmp_curr->LRU_next;
      }
      if(hit)
      {
        if(cache_writeback==0)
            cache_stat_data.copies_back++;
        tmp_curr->dirty = 1;  
        delete(&c1.LRU_head[index], &c1.LRU_tail[index], tmp_curr);
        insert(&c1.LRU_head[index], &c1.LRU_tail[index], tmp_curr);
      }
      else
      {
        cache_stat_data.misses++;
        if(cache_writealloc==0)
          return;
        Pcache_line tmp = malloc(sizeof(cache_line));
        tmp->dirty = 1;
        tmp->tag = addr_tag;
        cache_stat_data.demand_fetches++; //probable error
        if(c1.set_contents[index]==c1.associativity)
        {
          cache_stat_data.replacements++;
          if(cache_writeback==0)
            cache_stat_data.copies_back++;
          if(c1.LRU_tail[index]->dirty && cache_writeback)
            cache_stat_data.copies_back++;

          delete(&c1.LRU_head[index], &c1.LRU_tail[index], c1.LRU_tail[index]);
          insert(&c1.LRU_head[index], &c1.LRU_tail[index], tmp);
          
        }
        else if(c1.set_contents[index]<c1.associativity)
        {
          if(cache_writeback==0)//if WRITE-THROUGH
            cache_stat_data.copies_back++;
          c1.set_contents[index]++;
          c1.contents++;
          insert(&c1.LRU_head[index], &c1.LRU_tail[index], tmp);
        }
      }
    }

    else if(access_type==TRACE_DATA_LOAD)
    {
      cache_stat_data.accesses++;
      tmp_curr = c1.LRU_head[index];
      addr_tag = (addr >> LOG2(cache_block_size * c1.n_sets));
      while(tmp_curr!=NULL)
      {
        if(tmp_curr->tag == addr_tag)
        {
          hit = 1;
          break;
        }
        tmp_curr = tmp_curr->LRU_next;
      }
      if(hit)
      {
        delete(&c1.LRU_head[index], &c1.LRU_tail[index], tmp_curr);
        insert(&c1.LRU_head[index], &c1.LRU_tail[index], tmp_curr);
      }
      else
      {
        cache_stat_data.misses++;
        Pcache_line tmp = malloc(sizeof(cache_line));
        tmp->dirty = 0;
        tmp->tag = addr_tag;
        cache_stat_data.demand_fetches++; //probable error
        if(c1.set_contents[index]==c1.associativity)
        {
          cache_stat_data.replacements++;
          if(c1.LRU_tail[index]->dirty && cache_writeback)
            cache_stat_data.copies_back++;
          delete(&c1.LRU_head[index], &c1.LRU_tail[index], c1.LRU_tail[index]);
          insert(&c1.LRU_head[index], &c1.LRU_tail[index], tmp);
        }
        else if(c1.set_contents[index]<c1.associativity)
        {
          c1.set_contents[index]++;
          c1.contents++;
          insert(&c1.LRU_head[index], &c1.LRU_tail[index], tmp);
        }
      }
    }
    else if(access_type==TRACE_INST_LOAD)
    {
      cache_stat_inst.accesses++;
      tmp_curr = c1.LRU_head[index];
      addr_tag = (addr >> LOG2(cache_block_size * c1.n_sets));
      while(tmp_curr!=NULL)
      {
        if(tmp_curr->tag == addr_tag)
        {
          hit = 1;
          break;
        }
        tmp_curr = tmp_curr->LRU_next;
      }
      if(hit)
      {
        delete(&c1.LRU_head[index], &c1.LRU_tail[index], tmp_curr);
        insert(&c1.LRU_head[index], &c1.LRU_tail[index], tmp_curr);
      }
      else
      {
        cache_stat_inst.misses++;
        Pcache_line tmp = malloc(sizeof(cache_line));
        tmp->dirty = 0;
        tmp->tag = addr_tag;
        cache_stat_inst.demand_fetches++; //probable error
        if(c1.set_contents[index]==c1.associativity)
        {
          cache_stat_inst.replacements++;
          if(c1.LRU_tail[index]->dirty && cache_writeback)
          {
            cache_stat_inst.copies_back++;
            delete(&c1.LRU_head[index], &c1.LRU_tail[index], c1.LRU_tail[index]);
            insert(&c1.LRU_head[index], &c1.LRU_tail[index], tmp);
          }
        }
        else if(c1.set_contents[index]<c1.associativity)
        {
          c1.set_contents[index]++;
          c1.contents++;
          insert(&c1.LRU_head[index], &c1.LRU_tail[index], tmp);
        }
      }
    }
  }
  else if(cache_split==1)
  {
    printf("asdasd\n");
    if(access_type==TRACE_DATA_STORE)
    {
      index = (addr & c2.index_mask) >> c2.index_mask_offset;
      if (index >= c2.n_sets)
      {
        printf("\nThis access (%d) is not performed as index (%d) out of bounds!\n",access_type,index);
        return;
      }
      cache_stat_data.accesses++;
      tmp_curr = c2.LRU_head[index];
      addr_tag = (addr >> LOG2(cache_block_size * c2.n_sets));
      
      while(tmp_curr!=NULL)
      {
        if(tmp_curr->tag == addr_tag)
        {
          hit = 1;
          break;
        }
        tmp_curr = tmp_curr->LRU_next;
      }
      if(hit)
      {
        if(cache_writeback==0)
            cache_stat_data.copies_back++;
        tmp_curr->dirty = 1;  
        delete(&c2.LRU_head[index], &c2.LRU_tail[index], tmp_curr);
        insert(&c2.LRU_head[index], &c2.LRU_tail[index], tmp_curr);
      }
      else
      {
        cache_stat_data.misses++;
        if(cache_writealloc==0)
          return;
        Pcache_line tmp = malloc(sizeof(cache_line));
        tmp->dirty = 1;
        tmp->tag = addr_tag;
        cache_stat_data.demand_fetches++; //probable error
        if(c2.set_contents[index]==c2.associativity)
        {
          cache_stat_data.replacements++;
          if(cache_writeback==0)
            cache_stat_data.copies_back++;
          if(c2.LRU_tail[index]->dirty && cache_writeback)
            cache_stat_data.copies_back++;

          delete(&c2.LRU_head[index], &c2.LRU_tail[index], c2.LRU_tail[index]);
          insert(&c2.LRU_head[index], &c2.LRU_tail[index], tmp);
          
        }
        else if(c2.set_contents[index]<c2.associativity)
        {
          if(cache_writeback==0)//if WRITE-THROUGH
            cache_stat_data.copies_back++;
          c2.set_contents[index]++;
          c2.contents++;
          insert(&c2.LRU_head[index], &c2.LRU_tail[index], tmp);
        }
      }
    }

    else if(access_type==TRACE_DATA_LOAD)
    {
      index = (addr & c2.index_mask) >> c2.index_mask_offset;
      if (index >= c2.n_sets)
      {
        printf("\nThis access (%d) is not performed as index (%d) out of bounds!\n",access_type,index);
        return;
      }
      cache_stat_data.accesses++;
      tmp_curr = c2.LRU_head[index];
      addr_tag = (addr >> LOG2(cache_block_size * c2.n_sets));
      while(tmp_curr!=NULL)
      {
        if(tmp_curr->tag == addr_tag)
        {
          hit = 1;
          break;
        }
        tmp_curr = tmp_curr->LRU_next;
      }
      if(hit)
      {
        delete(&c2.LRU_head[index], &c2.LRU_tail[index], tmp_curr);
        insert(&c2.LRU_head[index], &c2.LRU_tail[index], tmp_curr);
      }
      else
      {
        cache_stat_data.misses++;
        Pcache_line tmp = malloc(sizeof(cache_line));
        tmp->dirty = 0;
        tmp->tag = addr_tag;
        cache_stat_data.demand_fetches++; //probable error
        if(c2.set_contents[index]==c2.associativity)
        {
          cache_stat_data.replacements++;
          if(c2.LRU_tail[index]->dirty && cache_writeback)
            cache_stat_data.copies_back++;
          delete(&c2.LRU_head[index], &c2.LRU_tail[index], c2.LRU_tail[index]);
          insert(&c2.LRU_head[index], &c2.LRU_tail[index], tmp);
        }
        else if(c2.set_contents[index]<c2.associativity)
        {
          c2.set_contents[index]++;
          c2.contents++;
          insert(&c2.LRU_head[index], &c2.LRU_tail[index], tmp);
        }
      }
    }
    else if(access_type==TRACE_INST_LOAD)
    {
      index = (addr & c1.index_mask) >> c1.index_mask_offset;
      if (index >= c1.n_sets)
      {
        printf("\nThis access (%d) is not performed as index (%d) out of bounds!\n",access_type,index);
        return;
      }
      cache_stat_inst.accesses++;
      tmp_curr = c1.LRU_head[index];
      addr_tag = (addr >> LOG2(cache_block_size * c1.n_sets));
      while(tmp_curr!=NULL)
      {
        if(tmp_curr->tag == addr_tag)
        {
          hit = 1;
          break;
        }
        tmp_curr = tmp_curr->LRU_next;
      }
      if(hit)
      {
        delete(&c1.LRU_head[index], &c1.LRU_tail[index], tmp_curr);
        insert(&c1.LRU_head[index], &c1.LRU_tail[index], tmp_curr);
      }
      else
      {
        cache_stat_inst.misses++;
        Pcache_line tmp = malloc(sizeof(cache_line));
        tmp->dirty = 0;
        tmp->tag = addr_tag;
        cache_stat_inst.demand_fetches++; //probable error
        if(c1.set_contents[index]==c1.associativity)
        {
          cache_stat_inst.replacements++;
          if(c1.LRU_tail[index]->dirty && cache_writeback)
          {
            cache_stat_inst.copies_back++;
            delete(&c1.LRU_head[index], &c1.LRU_tail[index], c1.LRU_tail[index]);
            insert(&c1.LRU_head[index], &c1.LRU_tail[index], tmp);
          }
        }
        else if(c1.set_contents[index]<c1.associativity)
        {
          c1.set_contents[index]++;
          c1.contents++;
          insert(&c1.LRU_head[index], &c1.LRU_tail[index], tmp);
        }
      }
    }
  }

}
/************************************************************/

void cleandirt()
{
  int i=0;
  if(cache_split==0)
  {
    for (i = 0; i < c1.n_sets; ++i)
      if(c1.LRU_head[i]!=NULL)
      {
        Pcache_line tmp = c1.LRU_head[i];
        while(tmp!=NULL)
        {
          if(tmp->dirty==1 && cache_writeback)
            cache_stat_data.copies_back++;
          tmp = tmp->LRU_next;

        }
      }
  }
  else if(cache_split==1)
  {
    for (i = 0; i < c1.n_sets; ++i)
      if(c1.LRU_head[i]!=NULL)
      {
        Pcache_line tmp = c1.LRU_head[i];
        while(tmp!=NULL)
        {
          if(tmp->dirty==1 && cache_writeback)
            cache_stat_inst.copies_back++;
          tmp = tmp->LRU_next;
        }
      }
    for (i = 0; i < c1.n_sets; ++i)
      if(c2.LRU_head[i]!=NULL)
      {
        Pcache_line tmp = c2.LRU_head[i];
        while(tmp!=NULL)
        {
          if(tmp->dirty==1 && cache_writeback)
            cache_stat_data.copies_back++;
          tmp = tmp->LRU_next;
        }
      }  
  }
}

/************************************************************/
void flush()
{

  /* flush the cache */
  cleandirt();


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
/* inserts at the head of the list */
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
  printf("\n*** CACHE STATISTICS ***\n");

  printf(" INSTRUCTIONS\n");
  printf("  accesses:  %d\n", cache_stat_inst.accesses);
  printf("  misses:    %d\n", cache_stat_inst.misses);
  if (!cache_stat_inst.accesses)
    printf("  miss rate: 0 (0)\n"); 
  else
    printf("  miss rate: %2.4f (hit rate %2.4f)\n", 
	 (float)cache_stat_inst.misses / (float)cache_stat_inst.accesses,
	 1.0 - (float)cache_stat_inst.misses / (float)cache_stat_inst.accesses);
  printf("  replace:   %d\n", cache_stat_inst.replacements);

  printf(" DATA\n");
  printf("  accesses:  %d\n", cache_stat_data.accesses);
  printf("  misses:    %d\n", cache_stat_data.misses);
  if (!cache_stat_data.accesses)
    printf("  miss rate: 0 (0)\n"); 
  else
    printf("  miss rate: %2.4f (hit rate %2.4f)\n", 
	 (float)cache_stat_data.misses / (float)cache_stat_data.accesses,
	 1.0 - (float)cache_stat_data.misses / (float)cache_stat_data.accesses);
  printf("  replace:   %d\n", cache_stat_data.replacements);

  printf(" TRAFFIC (in words)\n");
  printf("  demand fetch:  %d\n", WORD_SIZE*(cache_stat_inst.demand_fetches + 
	 cache_stat_data.demand_fetches));
  printf("  copies back:   %d\n", WORD_SIZE*(cache_stat_inst.copies_back +
	 cache_stat_data.copies_back));
}
/************************************************************/
