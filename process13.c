#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
	printf("Start\n thay the tien trinh : \n\n");
	execlp("echo", "echo","tien trinh moi in ra man hinh",(char *)0);
	printf("Done.\n");
	exit(0);
}

