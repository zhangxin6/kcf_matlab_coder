#include <stdio.h>
#include <stdlib.h>

void data_input(float buf[],const char name[],int count)
{
  FILE *fp;
  if((fp = fopen(name,"rb")) == NULL)
  {
     exit (1) ;
  }
  fread(buf, sizeof(float), count, fp);
  fclose(fp);
}

void data_input_short(unsigned short buf[],const char name[],int count)
{
  FILE *fp;
  if((fp = fopen(name,"rb")) == NULL)
  {
     exit (1) ;
  }
  fread(buf, sizeof(unsigned short), count, fp);
  fclose(fp);
}
/*
void data_input_short(unsigned short buf[],const char name[])
{
  FILE *fp;
  if((fp = fopen(name,"r")) == NULL)
  {
     exit (1) ;
  };
  unsigned int i=0;
  while(fscanf(fp,"%d,",&buf[i]) != EOF)
  {
      i++;
  }
  fclose(fp);
}*/
