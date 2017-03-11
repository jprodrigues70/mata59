#include <stdio.h>
#include <time.h>

#define BUF_SIZE 2000
#define TIME_SIZE 25
#define CONTENT_D_SIZE 10

char * message;

typedef struct app_header {
  char message[BUF_SIZE];
  char date[TIME_SIZE];
  char last_modified[TIME_SIZE];
  int content_length;
  char content_type[CONTENT_D_SIZE];
} app_header;
