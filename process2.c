#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int count = 0;
//Hàm xử lý được gọi khi có tín hiệu SIGUSR1 gửi tới tiến trình
void handler(int signal_number)
{
	FILE *fid ;
	fid = fopen("output.txt", "a"); //Ghi thông tin ra tệp
	fprintf(fid, "\nNhan duoc tin hieu SIGUSR1 lan thu % d", count++);
	printf("\nNhan duoc tin hieu SIGUSR1 lan thu % d", count);
	fclose(fid);
}
int main()
{
	struct sigaction sa; //Khai báo một biến cấu trúc sigaction
	printf("The  process ID is %d\n", (int)getpid());
	printf("The parent process ID is %d\n", (int)getppid());
	//Thiet lap signal handler
	memset(&sa, 0, sizeof(sa));
	//Gán con trỏ hàm xử lý signal cho trường sa_handler của biến cấu trúc sa
	sa.sa_handler = &handler;
	//Đăng ký cấu trúc sa cho xử lý tín hiệu (signal) SIGUSR1
	sigaction(SIGUSR1, &sa, NULL);
	//Chương trình chính liên tục in ra chữ A

	while (1)
	{
		printf("A\n");
		fflush(stdout);
		sleep(1);
	}
	return 0;
}
