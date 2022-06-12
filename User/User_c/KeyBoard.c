#include "KeyBoard.h"
u8 Key_OK = 0;
u16 Key_Data[2] = {0};
u8 Key_Key[6][6] = {0};
u8 Key_Scan_Dat[6] = {0};
void Key_Scan_Tim_init(void)
{
    TIM_TimeBaseInitTypeDef TIM_Init_Struct;              //声明定时器初始化结构体
    NVIC_InitTypeDef NVIC_Init_Struct;                    //声明NVIC初始化结构体
    RCC_APB1PeriphClockCmd(Key_Tim_RCC, ENABLE);          //打开时钟
    TIM_Init_Struct.TIM_ClockDivision = TIM_CKD_DIV1;     //滤波器不分频
    TIM_Init_Struct.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式

    //每次中断触发时间=[(TIM_Period+1)*(TIM_Prescaler+1)/(SystemCoreClock)] (s)
    //这里是10ms
    TIM_Init_Struct.TIM_Period = 840 - 1;
    TIM_Init_Struct.TIM_Prescaler = 1000 - 1;
    TIM_Init_Struct.TIM_RepetitionCounter = 0;     //高级定时器特有，这里写0就行
    TIM_TimeBaseInit(Key_Timx, &TIM_Init_Struct);  //调用函数初始
    TIM_ITConfig(Key_Timx, TIM_IT_Update, ENABLE); //启用溢出中断

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);         //设置NVIC中断分组2
    NVIC_Init_Struct.NVIC_IRQChannel = Tim_IRQn;            //中断名称
    NVIC_Init_Struct.NVIC_IRQChannelCmd = ENABLE;           //使能
    NVIC_Init_Struct.NVIC_IRQChannelPreemptionPriority = 2; //主优先级1
    NVIC_Init_Struct.NVIC_IRQChannelSubPriority = 3;        //副优先级1
    NVIC_Init(&NVIC_Init_Struct);                           //初始化NVIC
    TIM_Cmd(Key_Timx, ENABLE);                              //打开定时器
}
void Key_Scan_GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;                                               //声明GPIO初始化结构体
    RCC_AHB1PeriphClockCmd(Key_L_GPIO_RCC, ENABLE);                                 //打开GPIO时钟
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;                                      //设置为输出模式
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;                                     //设置为开漏输出
    GPIO_InitStruct.GPIO_Pin = Key_L0 | Key_L1 | Key_L2 | Key_L3 | Key_L4 | Key_L5; //设置引脚
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;                                       //设置为上拉
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;                                   //设置为快速模式
    GPIO_Init(Key_L_GPIOx, &GPIO_InitStruct);
    Set();
    RCC_AHB1PeriphClockCmd(Key_R_GPIO_RCC, ENABLE);                                 //打开GPIO时钟
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;                                       //设置为输入模式
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;                                     //
    GPIO_InitStruct.GPIO_Pin = Key_R0 | Key_R1 | Key_R2 | Key_R3 | Key_R4 | Key_R5; //设置引脚
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;                                       //设置为上拉
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;                                   //设置为快速模式
    GPIO_Init(Key_R_GPIOx, &GPIO_InitStruct);                                       //初始化
}
void Key_Scan_init(void)
{
    Key_Scan_GPIO_init();
    Key_Scan_Tim_init();
}
void Key_RLreverse_Tim_init(void)
{
    TIM_TimeBaseInitTypeDef TIM_Init_Struct;              //声明定时器初始化结构体
    NVIC_InitTypeDef NVIC_Init_Struct;                    //声明NVIC初始化结构体
    RCC_APB1PeriphClockCmd(Key_Tim_RCC, ENABLE);          //打开时钟
    TIM_Init_Struct.TIM_ClockDivision = TIM_CKD_DIV1;     //滤波器不分频
    TIM_Init_Struct.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式

    //每次中断触发时间=[(TIM_Period+1)*(TIM_Prescaler+1)/(SystemCoreClock)] (s)
    //这里是5ms
    TIM_Init_Struct.TIM_Period = 840 - 1;
    TIM_Init_Struct.TIM_Prescaler = 1000 - 1;
    TIM_Init_Struct.TIM_RepetitionCounter = 0;     //高级定时器特有，这里写0就行
    TIM_TimeBaseInit(Key_Timx, &TIM_Init_Struct);  //调用函数初始
    TIM_ITConfig(Key_Timx, TIM_IT_Update, ENABLE); //启用溢出中断

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);         //设置NVIC中断分组2
    NVIC_Init_Struct.NVIC_IRQChannel = Tim_IRQn;            //中断名称
    NVIC_Init_Struct.NVIC_IRQChannelCmd = ENABLE;           //使能
    NVIC_Init_Struct.NVIC_IRQChannelPreemptionPriority = 3; //主优先级1
    NVIC_Init_Struct.NVIC_IRQChannelSubPriority = 3;        //副优先级1
    NVIC_Init(&NVIC_Init_Struct);                           //初始化NVIC
    TIM_Cmd(Key_Timx, ENABLE);                              //打开定时器
}
void Key_RLreverse_GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;                                               //声明GPIO初始化结构体
    RCC_AHB1PeriphClockCmd(Key_R_GPIO_RCC, ENABLE);                                 //打开GPIO时钟
    RCC_AHB1PeriphClockCmd(Key_L_GPIO_RCC, ENABLE);                                 //打开GPIO时钟
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;                                      //设置为输出模式
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;                                     //设置为开漏输出
    GPIO_InitStruct.GPIO_Pin = Key_R0 | Key_R1 | Key_R2 | Key_R3 | Key_R4 | Key_R5; //设置引脚
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;                                       //设置为上拉
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;                                   //设置为快速模式
    GPIO_Init(Key_R_GPIOx, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;                                      //设置为输出模式
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;                                     //设置为开漏输出
    GPIO_InitStruct.GPIO_Pin = Key_L0 | Key_L1 | Key_L2 | Key_L3 | Key_L4 | Key_L5; //设置引脚
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;                                       //设置为上拉
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;                                   //设置为快速模式
    GPIO_Init(Key_L_GPIOx, &GPIO_InitStruct);                                       //初始化
}
void Key_RLreverse_init(void)
{
    Key_RLreverse_GPIO_init();
    Key_RLreverse_Tim_init();
}

void Set(void)
{
    GPIO_SetBits(Key_L_GPIOx, Key_L0 | Key_L1 | Key_L2 | Key_L3 | Key_L4 | Key_L5);
}

void Key_RLreverse_Set(u8 R_L, u8 bool)
{
    if (R_L == 1)
    {
        if (bool == 1)
            GPIO_SetBits(Key_L_GPIOx, (Key_L0 | Key_L1 | Key_L2 | Key_L3 | Key_L4 | Key_L5));
        else if (bool == 0)
            GPIO_ResetBits(Key_L_GPIOx, (Key_L0 | Key_L1 | Key_L2 | Key_L3 | Key_L4 | Key_L5));
    }
    else if (R_L == 0)
    {
        if (bool == 1)
            GPIO_SetBits(Key_R_GPIOx, (Key_R0 | Key_R1 | Key_R2 | Key_R3 | Key_R4 | Key_R5));
        else if (bool == 0)
            GPIO_ResetBits(Key_R_GPIOx, (Key_R0 | Key_R1 | Key_R2 | Key_R3 | Key_R4 | Key_R5));
    }
}
u8 Key_RLreverse_Read(u8 R_L)
{
    u8 zj = 0;
    if (R_L == 0)
    {
        zj |= GPIO_ReadInputDataBit(Key_R_GPIOx, Key_R5);
        zj <<= 1;
        zj |= GPIO_ReadInputDataBit(Key_R_GPIOx, Key_R4);
        zj <<= 1;
        zj |= GPIO_ReadInputDataBit(Key_R_GPIOx, Key_R3);
        zj <<= 1;
        zj |= GPIO_ReadInputDataBit(Key_R_GPIOx, Key_R2);
        zj <<= 1;
        zj |= GPIO_ReadInputDataBit(Key_R_GPIOx, Key_R1);
        zj <<= 1;
        zj |= GPIO_ReadInputDataBit(Key_R_GPIOx, Key_R0);
    }
    else if (R_L == 1)
    {
        zj |= GPIO_ReadInputDataBit(Key_L_GPIOx, Key_L5);
        zj <<= 1;
        zj |= GPIO_ReadInputDataBit(Key_L_GPIOx, Key_L4);
        zj <<= 1;
        zj |= GPIO_ReadInputDataBit(Key_L_GPIOx, Key_L3);
        zj <<= 1;
        zj |= GPIO_ReadInputDataBit(Key_L_GPIOx, Key_L2);
        zj <<= 1;
        zj |= GPIO_ReadInputDataBit(Key_L_GPIOx, Key_L1);
        zj <<= 1;
        zj |= GPIO_ReadInputDataBit(Key_L_GPIOx, Key_L0);
    }
    return zj;
}
u8 Key_Scan_Read_IN(void)
{
    u8 zj = 0;
    if (GPIO_ReadInputDataBit(Key_R_GPIOx, Key_R0))
        zj |= 1 << 0;
    if (GPIO_ReadInputDataBit(Key_R_GPIOx, Key_R1))
        zj |= 1 << 1;
    if (GPIO_ReadInputDataBit(Key_R_GPIOx, Key_R2))
        zj |= 1 << 2;
    if (GPIO_ReadInputDataBit(Key_R_GPIOx, Key_R3))
        zj |= 1 << 3;
    if (GPIO_ReadInputDataBit(Key_R_GPIOx, Key_R4))
        zj |= 1 << 4;
    if (GPIO_ReadInputDataBit(Key_R_GPIOx, Key_R5))
        zj |= 1 << 5;
    return (~zj) & 0x3f;
}
void Key_Scan_ReSet(u8 i)
{
    if (i == 0)
        GPIO_ResetBits(Key_L_GPIOx, Key_L0);
    else if (i == 1)
        GPIO_ResetBits(Key_L_GPIOx, Key_L1);
    else if (i == 2)
        GPIO_ResetBits(Key_L_GPIOx, Key_L2);
    else if (i == 3)
        GPIO_ResetBits(Key_L_GPIOx, Key_L3);
    else if (i == 4)
        GPIO_ResetBits(Key_L_GPIOx, Key_L4);
    else if (i == 5)
        GPIO_ResetBits(Key_L_GPIOx, Key_L5);
}
void Key_RLreverse_Decode()
{
    u8 zj_L = Key_Data[Key_L];
    u8 zj_R = Key_Data[Key_R];

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if ((((zj_R >> i) & 1) == 0) && (((zj_L >> j) & 1) == 0) && (Key_Key[i][j] == Key_Keep))
            {
                Key_Key[i][j] = Key_Down;
            }
            else if (!((((zj_R >> i) & 1) == 0) && (((zj_L >> j) & 1) == 0)) && (Key_Key[i][j] == Key_Down))
            {
                Key_Key[i][j] = Key_Up;
            }
        }
    }
}
void Key_RLreverse_Code()
{

    static u8 zj_R;
    static u8 zj_L;
    u16 zj = 0;
    static u8 Key_Code_ins;
    static u16 Bef_Dat;
    if (Key_Code_ins == 1) //去抖
    {
        zj_R = Key_RLreverse_Read(Key_R);
        Key_RLreverse_Set(Key_R, 0); //行设为
        Key_RLreverse_Set(Key_L, 1); //列设成
        Key_Code_ins = 2;
    }
    else if (Key_Code_ins == 2)
    {
        zj_L = Key_RLreverse_Read(Key_L);
        zj = zj_L | (zj_R << 8);
        if (zj != Bef_Dat)
        {
            Key_OK = 1;
            Key_Data[Key_L] = zj_L;
            Key_Data[Key_R] = zj_R;
            Key_RLreverse_Decode();
        }
        Bef_Dat = zj;
        Key_Code_ins = 0;
    }
    else
    {

        Key_RLreverse_Set(Key_L, 0); //行设为1
        Key_RLreverse_Set(Key_R, 1); //列设为0
        if (Key_RLreverse_Read(Key_R) != 0x3F)
            Key_Code_ins = 1;
        else
            Key_Code_ins = 0;
    }
}
void Key_RLreverse_Action(void (*Down)(u8 R, u8 L), void (*Up)(u8 R, u8 L))
{
    if (Key_OK)
    {
        Key_OK = 0;
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                if (Key_Key[i][j] == Key_Down)
                {

                    Down(i, j);
                }
                else if (Key_Key[i][j] == Key_Up)
                {
                    Key_Key[i][j] = Key_Keep;

                    Up(i, j);
                }
            }
        }
    }
}
void Key_Scan_Code(void)
{
    static u8 Dat1[6] = {0};
    static u8 Dat2[6] = {0};
    static u8 ins = 0;
    if (ins == 0)
    {
        for (int i = 0; i < 6; i++)
        {
            Set();
            Key_Scan_ReSet(i);
            Delay_us(1);
            Dat1[i] = Key_Scan_Read_IN();
            ins = 1;
        }
        Set();
    }
    else if (ins == 1)
    {
        for (int i = 0; i < 6; i++)
        {
            Set();
            Key_Scan_ReSet(i);
            Delay_us(1);
            Dat2[i] = Key_Scan_Read_IN();
        }
        Set();
        for (int i = 0; i < 6; i++)
        {
            if ((Dat2[i] == Dat1[i]))
            {
                if (Key_Scan_Dat[i] != Dat1[i])
                    Key_OK = 1;
                Key_Scan_Dat[i] = Dat1[i];
            }
        }
        ins = 0;
    }
}
void Key_Scan_Action(void (*Down)(u8 R, u8 L), void (*Up)(u8 R, u8 L))
{

    if (Key_OK)
    {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                if (Key_Scan_Dat[i] & (1 << j))
                {
                    Key_Key[j][i] = 1;
                    Key_OK = 0;
                    Down(j, i);
                }
                if ((Key_Key[j][i] == 1) && ((Key_Scan_Dat[i] & (1 << j)) == 0))
                {
                    Key_Key[j][i] = 0;
                    Up(j, i);
                }
            }
        }
    }
}

void TIM_IRQHandler(void)
{
    if (TIM_GetITStatus(Key_Timx, TIM_IT_Update) != RESET)
    {
        // Key_RLreverse_Code();
        Key_Scan_Code();
        TIM_ClearITPendingBit(Key_Timx, TIM_IT_Update); //将中断标志清除
    }
}
