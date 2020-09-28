//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "stm32f10x.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_sysclock_cfg(void)
{
    static sdt_int32u count=0;
    
    __disable_interrupt();
    for(;count<50000;count++)
    {
        IWDG_ReloadCounter();
        __no_operation();  
    }
    RCC_DeInit();                        //ϵͳʱ�Ӹ�λ
    RCC_HSEConfig(RCC_HSE_ON);           //�򿪾�������
    if(ERROR==RCC_WaitForHSEStartUp())
    {
        while(1);                           //�������,�ȴ���λ
    }
        
    FLASH->ACR |= FLASH_ACR_PRFTBE;                          //����ָ��Ԥȡ����/* Enable Prefetch Buffer */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);  //ָ��ȴ�2���� /* Flash 2 wait state */
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    
    
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_6);  //PLL����
    RCC_PLLCmd(ENABLE);                                 //��PLL
    while((RCC->CR & RCC_CR_PLLRDY) == 0)               //�ȴ�PLL�ȶ�
    {
    }
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);          //�л���PLLʱ��
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
    {
    }                                           //�ȴ�PLL��Ϊϵͳʱ��Դ
    RCC_HCLKConfig(RCC_SYSCLK_Div1);            //AHBʱ��,
    RCC_PCLK1Config(RCC_HCLK_Div2);             //APB1ʱ��,AHBʱ��2��Ƶ
    RCC_PCLK2Config(RCC_HCLK_Div1);             //APB2ʱ��,
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define LsiFreq   40000
//-----------------------------------------------------------------------------
void bsp_watchdog_cfg(void)
{
    RCC_LSICmd(ENABLE);
  
  /* Wait till LSI is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
    {}
  
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(IWDG_Prescaler_32);

    /* Set counter reload value to obtain 1000ms IWDG TimeOut.
       Counter Reload Value = 1000ms/IWDG counter clock period
                            = 1000ms / (LSI/32)
                            = 1s / (LsiFreq/32)
                            = LsiFreq/(32 * 1)
                            = LsiFreq/32
     */
    IWDG_SetReload(LsiFreq/32);

    /* Reload IWDG counter */
    IWDG_ReloadCounter();

    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable();
}
//-----------------------------------------------------------------------------
void bsp_watchdog_reload(void)
{
    IWDG_ReloadCounter();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++