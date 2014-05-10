#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include "resource.h"
#include <unistd.h>
#include <sysexits.h>
#include <string.h>
#include "mergesort.h"

/* Josh Fann
   Directory ID: jfann   UID: 109901918
   Project 6 mergetest.c
*/
/* 
   mergetest takes 3 integer arguments on its command line.  The first argument,
   n, is the number of integers that must be sorted.  The second argument, s,
   is the number that is used to seed the random number generator you will use
   to generate the array of numbers to sort. The third argument, m, is the upper
   bound on the value of the numbers you will sort.
*/

/*
   Program will dynamically allocate an array to hold the n random integers.
   After setting up the array, program will proceed to sort it using each of the
   mergesorts implemented int he mergesort.c file making sure to sort a copy
   of the original array each time, as sorting alreday sorted data will
   invalidate results.  After each sort, you should report to standard output
   the time spent sorting, in terms of wall clock time, user time, and system
   time.
*/

static int cmp(const void *a, const void *b){
  int *x = (int *) a;
  int *y = (int *) b;

  if(*x > *y)
    return 1;
  if(*x == *y)
    return 0;
  return -1;
}

int main(int argc, char *argv[]){

  struct rusage start_ru, end_ru;
  struct timeval start_wall, end_wall;
  
  int n, s, m, i;
  int *A, *temp;

  n = atoi(argv[1]);
  s = atoi(argv[2]);
  m = atoi(argv[3]);

  printf("Number of integers: %d\nSeed number: %d\nMaximum number: %d\n", n, s, m);
  A = calloc(n, sizeof(int));
  if(A == NULL){
    fprintf(stderr,"Memory allocation failed.\n");
    exit(EX_OSERR);
  }
  temp = calloc(n, sizeof(int));
  if(temp == NULL){
    fprintf(stderr,"Memory allocation failed.\n");
    exit(EX_OSERR);
  }
  srand(s);
  for(i = 0; i < n; i++)
    A[i] = rand()%m;
  /*create a copy of array*/
  memcpy(temp, A, n*sizeof(int));

  /* 0 threads*/
  gettimeofday(&start_wall, NULL);
  getrusage(RUSAGE_SELF, &start_ru);

  mergesort(temp, n, sizeof(int), cmp);

  gettimeofday(&end_wall, NULL);
  getrusage(RUSAGE_SELF, &end_ru);  
  /*Calculate difference and print results*/
  end_wall.tv_sec -= start_wall.tv_sec;
  if((end_wall.tv_usec-= start_wall.tv_usec) < 0){
    end_wall.tv_usec += 1000000;
    end_wall.tv_sec--;
  }
  printf("0 threads: %ld.%06lds wall;", end_wall.tv_sec, end_wall.tv_usec);
  end_ru.ru_utime.tv_sec -= start_ru.ru_utime.tv_sec;
  if((end_ru.ru_utime.tv_usec -= start_ru.ru_utime.tv_usec) < 0){
    end_ru.ru_utime.tv_usec += 1000000;
    end_ru.ru_utime.tv_sec--;
  }
  printf(" %ld.%06lds user;", end_ru.ru_utime.tv_sec, end_ru.ru_utime.tv_usec);
  end_ru.ru_stime.tv_sec -= start_ru.ru_stime.tv_sec;
  if((end_ru.ru_stime.tv_usec -= start_ru.ru_stime.tv_usec) < 0){
    end_ru.ru_stime.tv_usec += 1000000;
    end_ru.ru_stime.tv_sec--;
  }
  printf(" %ld.%06lds sys\n", end_ru.ru_stime.tv_sec, end_ru.ru_stime.tv_usec);
  memcpy(temp, A, n*sizeof(int));
  /*1 thread*/
  gettimeofday(&start_wall, NULL);
  getrusage(RUSAGE_SELF, &start_ru);

  mt_mergesort(temp, n, sizeof(int), cmp, 1);

  gettimeofday(&end_wall, NULL);
  getrusage(RUSAGE_SELF, &end_ru);  
  /*Calculate difference and print results*/
  end_wall.tv_sec -= start_wall.tv_sec;
  if((end_wall.tv_usec-= start_wall.tv_usec) < 0){
    end_wall.tv_usec += 1000000;
    end_wall.tv_sec--;
  }
  printf("1 threads: %ld.%06lds wall;", end_wall.tv_sec, end_wall.tv_usec);
  end_ru.ru_utime.tv_sec -= start_ru.ru_utime.tv_sec;
  if((end_ru.ru_utime.tv_usec -= start_ru.ru_utime.tv_usec) < 0){
    end_ru.ru_utime.tv_usec += 1000000;
    end_ru.ru_utime.tv_sec--;
  }
  printf(" %ld.%06lds user;", end_ru.ru_utime.tv_sec, end_ru.ru_utime.tv_usec);
  end_ru.ru_stime.tv_sec -= start_ru.ru_stime.tv_sec;
  if((end_ru.ru_stime.tv_usec -= start_ru.ru_stime.tv_usec) < 0){
    end_ru.ru_stime.tv_usec += 1000000;
    end_ru.ru_stime.tv_sec--;
  }
  printf(" %ld.%06lds sys\n", end_ru.ru_stime.tv_sec, end_ru.ru_stime.tv_usec);
  memcpy(temp, A, n*sizeof(int));
  /*2 threads*/
  gettimeofday(&start_wall, NULL);
  getrusage(RUSAGE_SELF, &start_ru);

  mt_mergesort(temp, n, sizeof(int), cmp, 2);

  gettimeofday(&end_wall, NULL);
  getrusage(RUSAGE_SELF, &end_ru);  
  /*Calculate difference and print results*/
  end_wall.tv_sec -= start_wall.tv_sec;
  if((end_wall.tv_usec-= start_wall.tv_usec) < 0){
    end_wall.tv_usec += 1000000;
    end_wall.tv_sec--;
  }
  printf("2 threads: %ld.%06lds wall;", end_wall.tv_sec, end_wall.tv_usec);
  end_ru.ru_utime.tv_sec -= start_ru.ru_utime.tv_sec;
  if((end_ru.ru_utime.tv_usec -= start_ru.ru_utime.tv_usec) < 0){
    end_ru.ru_utime.tv_usec += 1000000;
    end_ru.ru_utime.tv_sec--;
  }
  printf(" %ld.%06lds user;", end_ru.ru_utime.tv_sec, end_ru.ru_utime.tv_usec);
  end_ru.ru_stime.tv_sec -= start_ru.ru_stime.tv_sec;
  if((end_ru.ru_stime.tv_usec -= start_ru.ru_stime.tv_usec) < 0){
    end_ru.ru_stime.tv_usec += 1000000;
    end_ru.ru_stime.tv_sec--;
  }
  printf(" %ld.%06lds sys\n", end_ru.ru_stime.tv_sec, end_ru.ru_stime.tv_usec);

  memcpy(temp, A, sizeof(int));
  /*4 threads*/
  gettimeofday(&start_wall, NULL);
  getrusage(RUSAGE_SELF, &start_ru);

  mt_mergesort(temp, n, sizeof(int), cmp, 4);

  gettimeofday(&end_wall, NULL);
  getrusage(RUSAGE_SELF, &end_ru);  
  /*Calculate difference and print results*/
  end_wall.tv_sec -= start_wall.tv_sec;
  if((end_wall.tv_usec-= start_wall.tv_usec) < 0){
    end_wall.tv_usec += 1000000;
    end_wall.tv_sec--;
  }
  printf("4 threads: %ld.%06lds wall;", end_wall.tv_sec, end_wall.tv_usec);
  end_ru.ru_utime.tv_sec -= start_ru.ru_utime.tv_sec;
  if((end_ru.ru_utime.tv_usec -= start_ru.ru_utime.tv_usec) < 0){
    end_ru.ru_utime.tv_usec += 1000000;
    end_ru.ru_utime.tv_sec--;
  }
  printf(" %ld.%06lds user;", end_ru.ru_utime.tv_sec, end_ru.ru_utime.tv_usec);
  end_ru.ru_stime.tv_sec -= start_ru.ru_stime.tv_sec;
  if((end_ru.ru_stime.tv_usec -= start_ru.ru_stime.tv_usec) < 0){
    end_ru.ru_stime.tv_usec += 1000000;
    end_ru.ru_stime.tv_sec--;
  }
  printf(" %ld.%06lds sys\n", end_ru.ru_stime.tv_sec, end_ru.ru_stime.tv_usec);

  return 0;
}
