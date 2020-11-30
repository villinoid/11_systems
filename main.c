#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

int random_int(int file){
	int rn;
	int check = read(file, &rn, sizeof(rn));
	if (check==-1){
		printf("errno: %d\t %s\n",errno,strerror(errno));
		return check;
	}
	return rn;
}
	
int main(){
	int rf = open("/dev/random", O_RDONLY);
	if (rf==-1){
		printf("errno: %d\t %s\n",errno,strerror(errno));
		return 0;
	}
	int ray[10];
	printf("Filling and printing array: \n\n");
	int i;
	for (i=0;i<10;i++){
		ray[i]=random_int(rf);
		printf("ray[%d]: %d\n",i,ray[i]);
	}
	int wf =open("./out", O_CREAT|O_WRONLY,0755);
	if (wf==-1){
		printf("errno: %d\t %s\n",errno,strerror(errno));
		return 0;
	}
	printf("writing into a file:\n");
	int check = write(wf, ray, sizeof(ray));
	if (check==-1){
		printf("errno: %d\t %s\n",errno,strerror(errno));
		return 0;
	}
	int arr[10];
	printf("reading from a file:\n\n");
	wf=open("./out",O_RDONLY);
	check = read(wf, arr,sizeof(arr));
	if (check==-1){
		printf("errno: %d\t %s\n",errno,strerror(errno));
		return 0;
	}
	for (i=0;i<10;i++){
		printf("arr[%d]: %d\n",i,arr[i]);
	}
	return 0;
}
	
	
	
	
		
	
	