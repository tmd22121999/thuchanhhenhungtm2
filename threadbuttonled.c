/**********************************************************
* main: Thuc hien dieu khien led chay duoi
* thread: Thuc hien doc (polling) trang thai nut bam de thay doi toc do led
***********************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#define ON 1
#define OFF 0
/* Bien luu thoi gian delay, sẽ thay doi khi K1, K2 duoc an */
static int t = 1000; //don vi la milisecond, ban dau mac dinh la 1000 ms
//Nếu sử dụng cơ chế mutex
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
/* Ham sleep ms su dung usleep cua linux */
void sleepms(int ms)
{
	//usleep in us, sleep in second
	usleep(1000 * ms); //convert to microseconds
	return;
};
/* Cau truc du lieu se truyen tham so cho thread */
struct thread_parms
{
	char btn[6];
	int btn_fd;
};
/* Ham xu ly cua thread thuc hien doc nut K1, K2 (polling) */
void* btn_polling(void* param);
int main(int argc, char** agrv)
{
	int led_fd, button_fd; //định danh file thiết bị (led, button)
	struct thread_parms p; //Bien cau truc chua tham so se truyen cho ham xu ly cua thread
	pthread_t thread_id; //định danh luồng
	int led_no; //So hieu led 0-4
	//Mang chua gia tri trang thai 6 button se doc
	char buttons[6] = { '0', '0', '0', '0', '0', '0' };
	int i;

	//Chuan bi tham so truyen vao cho ham xu ly cua thread
	p.btn_fd = button_fd; // button device file number
	for (i = 0; i < 6; i++) p.btn[i] = '0'; //buffer to read button status (K1-K6)
	//Tao thread thuc hien polling button
	thread_id = pthread_create(&thread_id, NULL, &btn_polling, &p);;

	while (1)
	{

		//Sleep in t ms
		printf("thoi gian giua 2 lan in man hinh: %dms\n",t);
		fflush(stdout);
		sleepms(t);

	}

	return 0;
}

void* btn_polling(void* param)
{
	struct thread_parms* p = (struct thread_parms*)param;
	char cur_btn[6], old_btn[6];
	int btn_fd;
	int i;
	for (i = 0; i < 6; i++) old_btn[i] = p->btn[i];
	btn_fd = p->btn_fd;
	for (;;)//Lien tuc tham do trang thai nut bam (K1, K2 co duoc an)
	{

		scanf("%d",&i);
		//Chi can doc K1, K2 tuong ung voi tang/giam led speed
		//Doc K1
		if (i==1) //Nếu K1 được ấn
		{
			old_btn[0] = cur_btn[0];
			printf("tang thoi gian delay\n");
			//Neu dung mutex cho bien t
			pthread_mutex_lock( &mutex1 );
			t = t + 50;//tang thoi gian delay (so với t hiện tại)
			pthread_mutex_unlock( &mutex1 );
		}
		//Doc K2
		if (i==2) //Nếu K2 được ấn
		{
			old_btn[1] = cur_btn[1];
			printf("giam thoi gian delay\n");
			pthread_mutex_lock( &mutex1 );
			t = t - 50;//giam thoi gian delay (so với t hiện tại)
			if (t < 100) t = 100;
			pthread_mutex_unlock( &mutex1 );
		}
	}
	return NULL;
}
