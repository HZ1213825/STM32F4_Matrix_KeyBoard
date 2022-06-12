#include "stm32f4xx.h" // 注意更改这个文件的#define STM32F401xx为自己的芯片型号
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
