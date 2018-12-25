#include <stdio.h>
#include <string.h>
#include "license.h"
#include <unistd.h>
#include <ctype.h>

char *keygen(char *key, char *mac) {
  char salt[]="$1$jfm3kaZ2$";
  char pos_mac[]="lfR3c67H0aq";
  char MAC[20];
  strcpy(MAC, mac);
  strcpy(key, crypt(strcat(MAC, pos_mac),salt));
  strcpy(key, &key[12]);
  return key;
}

int macok(char *mac) {
  int i;
  if (strlen(mac)!=12) return 0;
  for(i=0;i<12;i++)
    if (!(((mac[i]>=48)&&(mac[i]<=57))||((mac[i]>=97)&&(mac[i]<=102))))
      return 0;
  return 1;
}


char *strnnncpy(char *s1, const char *s2, int n) {
  int i;
  for(i=0;i<n;i++)
      s1[i]=s2[i];
  return s1;
}

int main(int argc, char **argv) {
  FILE *fs;
  int i,j,k;
  unsigned char chk;
  unsigned char mac[6];
  unsigned char key[50];
  char tmp[3];

  strcpy(tmp,"aa");
  if(argc != 2) {
    printf("Usage: ./license <mac>\n");
    return 1;
  }

  for(i = 0; argv[1][i]; i++)
      argv[1][i] = tolower(argv[1][i]);

  if(!macok(argv[1])) {
    printf("Malformed MAC address\n");
    return 1;
  }

  keygen(key,argv[1]);  
  
  for(i=0;i<6;i++) {
    tmp[0]=argv[1][2*i];
    tmp[1]=argv[1][2*i+1];
    sscanf(tmp, "%x", &mac[i]);
  }

  chk=0;
  for(i=6;i<=208;i++) {
    data[i]=~data[i]+0xc8;
    chk+=data[i];
  }

  strnnncpy(&data[7],mac,6);
  strnnncpy(&data[13],mac,6);
  strnnncpy(&data[19],mac,6);
  chk=0;
  for(i=6;i<208;i++)
    chk+=data[i];
  data[208]=~chk+1;
  for(i=6;i<=208;i++)
    data[i]=~data[i]+0xc8;
  chk=0;
  for(i=215;i<=9065;i++) {
    data[i]=~data[i]+0xc8;
    chk+=data[i];
  }
  strnnncpy(&data[446],mac,6);
  strnnncpy(&data[5325],key,22);
  chk=0;
  for(i=215;i<9065;i++)
    chk+=data[i];
  data[9065]=~chk+1;
  for(i=215;i<=9065;i++)
    data[i]=~data[i]+0xc8;

  fs = fopen(strcat(argv[1],".dat"), "wb");
  if(!fs) {
    printf("%s cannot be generated.\n", argv[1]);
    return 1;
  }
  fwrite(data, 1, sizeof(data), fs);
  fclose(fs);
  printf("License %s generated\n",argv[1]);
  return 0;
}
