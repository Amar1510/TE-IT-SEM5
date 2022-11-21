#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(){
	FILE *fp;
	int fd1,fd2, l=1,w=1,c=0,i;
	char *myfifo1 = "file1",str1[100],ch;
	char *myfifo2 = "file2",str2[100];
	
	//Read sentences from first myfifo1 file
	fd1 = open(myfifo1, O_RDONLY);
	read(fd1,str1,100);
	printf("\n Pipe1 : %s", str1);
	
	//Count number of lines characters and words in sentence
	i=0;
	while(str1[i] != '\0')
	{
		if(str1[i]=='.' || str1[i]=='\n')
			l++;
		else if(str1[i] == ' ')
			w++;
		else 
			c++;
		i++;
	}
	
	//check the result
	printf("No of lines : %d", l);
	printf("No of words : %d", w);
	printf("No of characters : %d\n", c);
	
	fp = fopen("kp.txt","w");
	fprintf(fp,"No of lines : %d", l);
	fprintf(fp,"No of words : %d", w);
	fprintf(fp,"No of characters : %d\n", c);
	fclose(fp);
	fp = fopen("kp.txt","r");
	ch = fgetc(fp);
	i=0;
	while(ch != EOF)
	{
		str2[i] = ch;
		i++;
		ch = fgetc(fp);
	}
	str2[i] = '\0';
	fclose(fp);
	
	close(fd1);
	//Write data of text file on second FIFO pipe
	fd2 = open(myfifo2, O_WRONLY);
	write(fd2,str2,strlen(str2)+1);
	close(fd2);
}