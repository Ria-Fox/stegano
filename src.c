#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	int d,i;
	char filename[260];
	char str[16];
	char sig[8];
	char sig2[3];
	char realsig2[3]={'s','t','e'};
	char length[1];
	char realsig[]={0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
	FILE *fp;
	while(1)
	{
		printf("::PNG Steganography tool::\nEncoding : 1\nDecoding : 2\nExit : 3\n>>");
		scanf("%d",&d);
		for(i=0; i<260; i++)
			filename[i]=0;
		if(d==1)
		{
			printf("insert path of file : ");
			scanf("%s",filename);
			printf("insert str to encode(MAX 16byte) :");
			scanf("%s",str);
			if((fp=fopen(filename, "r"))==NULL)
			{
				printf("File open error\n");
				continue;
			}
			fread(sig,1,8,fp);
			if(sig!=realsig)
			{
				printf("This is not PNG file.\n");
				continue;
			}
			fclose(fp);
			if((fp=fopen(filename, "w"))==NULL)
			{
				printf("File open error\n");
				continue;
			}
			fseek(fp, 41, SEEK_SET);
			fwrite("ste",1,3,fp);
			length[0]=strlen(str);
			fwrite(length,1,1,fp);
			fwrite(str,1,strlen(str),fp);
			fclose(fp);
		}
		else if(d==2)
		{
			printf("insert path of file : ");
			scanf("%s",filename);
			if((fp=fopen(filename, "r"))==NULL)
			{
				printf("File open error\n");
				continue;
			}
			fread(sig,1,8,fp);
			if(sig!=realsig)
			{
				printf("This is not PNG file.\n");
				continue;
			}
			fseek(fp, 41, SEEK_SET);
			fread(sig2,1,3,fp);
			if(strcmp(sig2, realsig2)!=0)
			{
				printf("This file didn't encoded.\n");
				continue;
			}
			fread(length,1,1,fp);
			fread(str,1,(int)length[0],fp);
			printf("Decoded string : %s\n",str);
			fclose(fp);
		}
		else if(d==3)
		{
			exit(0);
		}
		else
		{
			printf("Wrong Number.\n");
			continue;
		}
	}
}
