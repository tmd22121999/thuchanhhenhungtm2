#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
//Hàm xử lý của luồng thực hiện liên tục in chữ x
void* printx(void* unused)
{
	while (1)
	{
		fputc('x', stdout);
		fflush(stdout);	
		usleep(200);
	}
	return NULL;
}
int main(int argc, char** argv)
{
	pthread_t thread_id;
	//Tạo ra một luồng mới với hàm xử lý luồng là printx
	pthread_create(&thread_id, NULL, &printx, NULL);
	//Chương trình chính liên tục in chữ o
	while (1)
	{
		fputc('o', stdout);
		fflush(stdout);
		usleep(100);
	}
	return 0;
}

