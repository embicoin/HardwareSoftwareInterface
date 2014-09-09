/*
Coursera HW/SW Interface
Lab 4 - Mystery Caches

Mystery Cache Geometries (for you to keep notes):
mystery0:
    block size =
    cache size =
    associativity =
mystery1:
    block size =
    cache size =
    associativity =
mystery2:
    block size =
    cache size =
    associativity =
mystery3:
    block size =
    cache size =
    associativity =
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real"
 * memory addresses. You can use any convenient integer value as a
 * memory address, you should not be able to cause a segmentation
 * fault by providing a memory address out of your programs address
 * space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  /* YOUR CODE GOES HERE */
  long long base = 0;
  long long addr = base;
  flush_cache();
  if (!access_cache(addr))
  {
    for (addr = 1; ; addr++)
    {
	if (!access_cache(addr))
	{
	  break;
	}
    }

    return addr - base;
  }
  else
  {
    printf("Error, %d", __LINE__);
  }

  return -1;
}


/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int size) {
  /* YOUR CODE GOES HERE */
  long long base = 0; 
  //long long addr = base + size;
  int i = 1, j = 0;
  
  for (i = 1; i <= 65536/size + 10; i++)
  {
    access_cache(base);

    for (j = 1; j < i + 1; j++)
    {
      access_cache(base + j * size);
    }

    j--;
    if (!access_cache(base))
	return (base + j * size);
  }

  return -1;
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int size) {
  /* YOUR CODE GOES HERE */
  long long base = 0;
  int i, j;
  for (i = 1; ; i++)
  {
    access_cache(base);
    for (j = 0; j < i; j++)
    {
      access_cache(base + j * size);
    }

    if (!access_cache(base))
      return (j-1);
  }
  return -1;
}


//// DO NOT CHANGE ANYTHING BELOW THIS POINT
int main(void) {
  int size;
  int assoc;
  int block_size;

  int i;

  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.  You can
     test your geometry paramter discovery routines by calling
     cache_init() w/ your own size and block size values. */
  cache_init(64*1024,16);
  flush_cache();
  
  /*
  for (i = 0; i < 17; i++)
  {
      if (!access_cache(addr + i))
	  printf("%lld miss\n", addr + i);
      else
	  printf("%lld hit\n", addr + i);
  }

  for (i = 0; i < 17; i++)
  {
      if (!access_cache(addr + i))
	  printf("%lld miss\n", addr + i);
      else
	  printf("%lld hit\n", addr + i);
  }

  for (i = 17; i < 34; i++)
  {
      if (!access_cache(addr + i))
	  printf("%lld miss\n", addr + i);
      else
	  printf("%lld hit\n", addr + i);
  }
  */

  block_size=get_block_size();
  size=get_cache_size(block_size);
  assoc=get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
