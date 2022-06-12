#include "stm32f4xx.h" // ע���������ļ���#define STM32F401xxΪ�Լ���оƬ�ͺ�
#include "Delay.h"
#include "Usart.h"
#include "KeyBoard.h"

void Down(u8 R, u8 L)
{
	printf("%d-%d Down\r\n", R, L);
}
void Up(u8 R, u8 L)
{
	printf("%d-%d Up\r\n", R, L);
}

int main()
{
	Usart_init();
	Key_RLreverse_init();
	// Key_Scan_init();
	while (1)
	{
		// Key_RLreverse_Action(Down, Up);
		Key_Scan_Action(Down, Up);
	}
}
