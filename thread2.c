#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
//Cau truc la tham so cho ham xu ly luong (ham char_print)
struct char_print_parms
{
	char character; //Ky tu muon in
	int count; //So lan in
};
//Ham xu ly cua thread
//In ky tu ra man hinh, duoc cho boi tham so la mot con tro den cau truc du lieu tren
void* char_print(void* params)
{
	//Tham so truyen vao la kieu void* duoc ep thanh kieu nhu struct da khai bao
	struct char_print_parms* p = (struct char_print_parms*) params;
	int i;
	int n = p->count; //Bien chua so lan in ra
	char c = p->character; //Bien chua ma ky tu muon in ra
	for (i = 0; i < n; i++){
		fputc(c, stdout); //Ham in 1 ky tu ra thiet ra chuan
		//fflush(stdout);
		usleep(200);
	}
	return NULL;
}
int main(int argc, char** agrv)
{
	pthread_t thread1_id, thread2_id; //Khai báo 2 biến định danh luồng
	struct char_print_parms p1, p2; //2 bien tham so truyen cho ham xu ly	cua thread
	//Tao 1 thread in 30 chu 'x'
	p1.character = 'x';
	p1.count = 30;
	pthread_create(&thread1_id, NULL, &char_print, &p1);
	//Tao 1 thread khac in ra 20 chu 'o'
	p2.character = 'o';
	p2.count = 20;
	pthread_create(&thread2_id, NULL, &char_print, &p2);
	//Dam bao thread1 da ket thuc
	pthread_join(thread1_id, NULL);
	//Dam bao thread2 da ket thuc
	pthread_join(thread2_id, NULL);
	printf("\ndam bao 2 luong da thuc hien xong\n");
	// Now we can safely return.
	return 0;
}
