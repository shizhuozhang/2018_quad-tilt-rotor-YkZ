#include "H_define.h"

/*
//DMAx�ĸ�ͨ������
//����Ĵ�����ʽ�ǹ̶���,������->�洢��ģʽ/8λ���ݿ��/�洢������ģʽ
//ʹ��ʱ���ݲ�ͬ��������޸�
//DMA_Streamx:DMA������,DMA1_Stream0~7/DMA2_Stream0~7
//chx:DMAͨ��ѡ��,��Χ:0~7
//par:�����ַ
//mar:�洢����ַ
//ndtr:���ݴ�����  
void DMA_Config_Temp(DMA_Stream_TypeDef *DMA_Streamx,u8 chx,u32 par,u32 mar,u16 ndtr)
{ 
	DMA_TypeDef *DMAx;
	u8 streamx;
	if((u32)DMA_Streamx>(u32)DMA2)//�õ���ǰstream������DMA2����DMA1
	{
		DMAx=DMA2;
		RCC->AHB1ENR|=1<<22;//DMA2ʱ��ʹ�� 
	}else 
	{
		DMAx=DMA1; 
 		RCC->AHB1ENR|=1<<21;//DMA1ʱ��ʹ�� 
	}
	while(DMA_Streamx->CR&0X01);//�ȴ�DMA������ 
	streamx=(((u32)DMA_Streamx-(u32)DMAx)-0X10)/0X18;		//�õ�streamͨ����
 	if(streamx>=6)DMAx->HIFCR|=0X3D<<(6*(streamx-6)+16);	//���֮ǰ��stream�ϵ������жϱ�־
	else if(streamx>=4)DMAx->HIFCR|=0X3D<<6*(streamx-4);    //���֮ǰ��stream�ϵ������жϱ�־
	else if(streamx>=2)DMAx->LIFCR|=0X3D<<(6*(streamx-2)+16);//���֮ǰ��stream�ϵ������жϱ�־
	else DMAx->LIFCR|=0X3D<<6*streamx;						//���֮ǰ��stream�ϵ������жϱ�־
	
	DMA_Streamx->PAR=par;		//DMA�����ַ
	DMA_Streamx->M0AR=mar;		//DMA �洢��0��ַ
	DMA_Streamx->NDTR=ndtr;		//DMA ���ݴ�����
	DMA_Streamx->CR=0;			//��ȫ����λCR�Ĵ���ֵ 
	DMA_Streamx->CR|=(u32)chx<<25;//ͨ��ѡ��
	
	DMA_Streamx->CR|=0<<6;		//���赽�洢��ģʽ//0�Ǵ����赽�洢����1�Ǵ洢�������裬2�Ǵ洢�����洢��
	DMA_Streamx->CR|=0<<8;		//��ѭ��ģʽ(��ʹ����ͨģʽ)
	DMA_Streamx->CR|=0<<9;		//���������ģʽ
	DMA_Streamx->CR|=1<<10;		//�洢������ģʽ
	DMA_Streamx->CR|=0<<11;		//�������ݳ���:8λ
	DMA_Streamx->CR|=0<<13;		//�洢�����ݳ���:8λ
	DMA_Streamx->CR|=1<<16;		//�е����ȼ�0�ǵͣ�1���У�2�Ǹߣ�3�Ƿǳ���
	DMA_Streamx->CR|=0<<21;		//����ͻ�����δ���
	DMA_Streamx->CR|=0<<23;		//�洢��ͻ�����δ���
//	DMA_Streamx->FCR=0X21;	//FIFO���ƼĴ�����������������������
	DMA_Streamx->CR|=1<<4;		//��������ж�ʹ��	
	MY_NVIC_Init(0,0,DMA1_Stream0_IRQn,2);//��Ҫ������Ҫ�޸��ж�ʸ����
	
	DMA_Streamx->CR&=~(1<<0); 	//�ر�DMA���� 
	while(DMA_Streamx->CR&0X1);	//ȷ��DMA���Ա�����  
	DMA_Streamx->CR|=1<<0;		//����DMA����
} 
void  DMA1_Stream0_IRQHandler()//������X0-3�Ĵ�������жϷ�����
{
	if(DMA1->LISR&(1<<5))//������ɱ�־λ��������0-3��Ӧ5��11��21��27
	{
		DMA1->LIFCR &=~(1<<5);//�����־λ
		
	}
}
void  DMA1_Stream4_IRQHandler()//������X4-7�Ĵ�������жϷ�����
{
	if(DMA1->HISR&(1<<5))//������ɱ�־λ��������4-7��Ӧ5��11��21��27
	{
		DMA1->HIFCR &=~(1<<5);//�����־λ
		
	}
}
*/

/*���ڽ����ⲿ���ݰ���ͨ��DMAֱ�Ӵ��䵽�ڴ�*/
#if __DMA_USART3
//DMA_Streamx:DMA������,DMAX_StreamX
//chx:DMAͨ��ѡ��,��Χ:0~7
//USART1_RX:DMA2_Stream5,CH4��USART2_RX:DMA1_Stream5,CH4��USART3_RX:DMA1_Stream1,CH4��
//UART4_RX:DMA1_Stream2,CH4��UART5_RX:DMA1_Stream0,CH4��USART6_RX:DMA2_Stream1,CH5��
//par:�����ַ
//mar:�洢����ַ
//ndtr:���ݴ�����  
//rank����ͬ���ڵĴ������ȼ�,��Чֵ0-3
void DMA_Config_USART3(DMA_Stream_TypeDef *DMA_Streamx,u8 chx,u32 par,u32 mar,u16 ndtr,u8 rank)
{ 
	DMA_TypeDef *DMAx;
	u8 streamx;
	if((u32)DMA_Streamx>(u32)DMA2)//�õ���ǰstream������DMA2����DMA1
	{
		DMAx=DMA2;
		RCC->AHB1ENR|=1<<22;//DMA2ʱ��ʹ�� 
	}else 
	{
		DMAx=DMA1; 
 		RCC->AHB1ENR|=1<<21;//DMA1ʱ��ʹ�� 
	}
	while(DMA_Streamx->CR&0X01);//�ȴ�DMA������ 
	streamx=(((u32)DMA_Streamx-(u32)DMAx)-0X10)/0X18;		//�õ�streamͨ����
 	if(streamx>=6)DMAx->HIFCR|=0X3D<<(6*(streamx-6)+16);	//���֮ǰ��stream�ϵ������жϱ�־
	else if(streamx>=4)DMAx->HIFCR|=0X3D<<6*(streamx-4);    //���֮ǰ��stream�ϵ������жϱ�־
	else if(streamx>=2)DMAx->LIFCR|=0X3D<<(6*(streamx-2)+16);//���֮ǰ��stream�ϵ������жϱ�־
	else DMAx->LIFCR|=0X3D<<6*streamx;						//���֮ǰ��stream�ϵ������жϱ�־
	
	DMA_Streamx->PAR=par;		//DMA�����ַ
	DMA_Streamx->M0AR=mar;		//DMA �洢��0��ַ
	DMA_Streamx->NDTR=ndtr;		//DMA ���ݴ�����
	DMA_Streamx->CR=0;			//��ȫ����λCR�Ĵ���ֵ 
	DMA_Streamx->CR|=(u32)chx<<25;//ͨ��ѡ��
	
	DMA_Streamx->CR|=0<<6;		//���赽�洢��ģʽ//0�Ǵ����赽�洢����1�Ǵ洢�������裬2�Ǵ洢�����洢��
	DMA_Streamx->CR|=1<<8;		//ѭ��ģʽ
	DMA_Streamx->CR|=0<<9;		//���������ģʽ
	DMA_Streamx->CR|=1<<10;		//�洢������ģʽ
	DMA_Streamx->CR|=0<<11;		//�������ݳ���:8λ
	DMA_Streamx->CR|=0<<13;		//�洢�����ݳ���:8λ
	DMA_Streamx->CR|=rank<<16;		//�е����ȼ�0�ǵͣ�1���У�2�Ǹߣ�3�Ƿǳ���
//	DMA_Streamx->CR|=0<<21;		//����ͻ�����δ���
//	DMA_Streamx->CR|=0<<23;		//�洢��ͻ�����δ���
//	DMA_Streamx->FCR=0X21;	//FIFO���ƼĴ�����������������������
	DMA_Streamx->CR|=1<<4;		//��������ж�ʹ��
	
	MY_NVIC_Init(0,1,DMA1_Stream1_IRQn,2);//��Ҫ������Ҫ�޸��ж�ʸ����

	DMA_Streamx->CR&=~(1<<0); 	//�ر�DMA���� 
//	while(DMA_Streamx->CR&0X1);	//ȷ��DMA���Ա�����  
//	DMA_Streamx->CR|=1<<0;		//����DMA����
} 

u8 Sbus_OK=0;
volatile u8 Dma1_T1_Close=1;//��ʼʱ���ŵģ��������ٿ���
void  DMA1_Stream1_IRQHandler()//������X0-3�Ĵ�������жϷ�����
{
	if(DMA1->LISR&(1<<11))//������ɱ�־λ��������0-3��Ӧ5��11��21��27
	{	
		DMA1->LIFCR|=1<<11;//�����־λ
		if(0!=SBUS_DATA[24])	//0X0F!=SBUS_DATA[0])||
			Sbus_OK=0;
		else
		{
			SBUS_data_Pro();
			Sbus_OK=1;//ң�����ݽ��յ�
		}
		USART3->CR3&=~(1<<6);    //DMA��ֹ����
		DMA1_Stream1->CR&=~(1<<0); 	//�ر�DMA���� 		
		Dma1_T1_Close=1;
	}
}
#endif

#if __DMA_USART2
void DMA_Config_USART2(DMA_Stream_TypeDef *DMA_Streamx,u8 chx,u32 par,u32 mar,u16 ndtr,u8 rank)
{ 
	DMA_TypeDef *DMAx;
	u8 streamx;
	if((u32)DMA_Streamx>(u32)DMA2)//�õ���ǰstream������DMA2����DMA1
	{
		DMAx=DMA2;
		RCC->AHB1ENR|=1<<22;//DMA2ʱ��ʹ�� 
	}else 
	{
		DMAx=DMA1; 
 		RCC->AHB1ENR|=1<<21;//DMA1ʱ��ʹ�� 
	}
	while(DMA_Streamx->CR&0X01);//�ȴ�DMA������ 
	streamx=(((u32)DMA_Streamx-(u32)DMAx)-0X10)/0X18;		//�õ�streamͨ����
 	if(streamx>=6)DMAx->HIFCR|=0X3D<<(6*(streamx-6)+16);	//���֮ǰ��stream�ϵ������жϱ�־
	else if(streamx>=4)DMAx->HIFCR|=0X3D<<6*(streamx-4);    //���֮ǰ��stream�ϵ������жϱ�־
	else if(streamx>=2)DMAx->LIFCR|=0X3D<<(6*(streamx-2)+16);//���֮ǰ��stream�ϵ������жϱ�־
	else DMAx->LIFCR|=0X3D<<6*streamx;						//���֮ǰ��stream�ϵ������жϱ�־
	
	DMA_Streamx->PAR=par;		//DMA�����ַ
	DMA_Streamx->M0AR=mar;		//DMA �洢��0��ַ
	DMA_Streamx->NDTR=ndtr;		//DMA ���ݴ�����
	DMA_Streamx->CR=0;			//��ȫ����λCR�Ĵ���ֵ 
	DMA_Streamx->CR|=(u32)chx<<25;//ͨ��ѡ��
	
	DMA_Streamx->CR|=0<<6;		//���赽�洢��ģʽ//0�Ǵ����赽�洢����1�Ǵ洢�������裬2�Ǵ洢�����洢��
	DMA_Streamx->CR|=1<<8;		//ѭ��ģʽ
	DMA_Streamx->CR|=0<<9;		//���������ģʽ
	DMA_Streamx->CR|=1<<10;		//�洢������ģʽ
	DMA_Streamx->CR|=0<<11;		//�������ݳ���:8λ
	DMA_Streamx->CR|=0<<13;		//�洢�����ݳ���:8λ
	DMA_Streamx->CR|=rank<<16;		//�е����ȼ�0�ǵͣ�1���У�2�Ǹߣ�3�Ƿǳ���
	DMA_Streamx->CR|=0<<21;		//����ͻ�����δ���
//	DMA_Streamx->CR|=0<<23;		//�洢��ͻ�����δ���
//	DMA_Streamx->FCR=0X21;	//FIFO���ƼĴ�����������������������
	DMA_Streamx->CR|=1<<4;		//��������ж�ʹ��
	
	MY_NVIC_Init(0,2,DMA1_Stream5_IRQn,2);//��Ҫ������Ҫ�޸��ж�ʸ����

	DMA_Streamx->CR&=~(1<<0); 	//�ر�DMA���� 
//	while(DMA_Streamx->CR&0X1);	//ȷ��DMA���Ա�����  
//	DMA_Streamx->CR|=1<<0;		//����DMA����
} 
u8 Ahrs_OK=0;
volatile u8 Dma1_T5_Close=1;

void  DMA1_Stream5_IRQHandler()//������X4-7�Ĵ�������жϷ�����
{
	if(DMA1->HISR&(1<<11))//������ɱ�־λ��������4-7��Ӧ5��11��21��27
	{
		DMA1->HIFCR|=1<<11;//�����־λ
		
		Ahrs_Flag1=1;//������һ�����ݺ󣬿�����һ�����ݵ�֡ͷУ��
		
		USART2->CR3&=~(1<<6);    //DMA��ֹ����
		DMA1_Stream5->CR&=~(1<<0); 	//�ر�DMA����,��USART2�����жϺ����п��� 		
		Dma1_T5_Close=1;
		
		if((0X12==AHRS_DATA[0])&&(0XA1==AHRS_DATA[1])&&(0XAA==AHRS_DATA[41]))			
		{							//�ٴ��ж�֡��ʶ�ֽںͽ�βУ��
			if(AHRS_data_Pro())			
				Ahrs_OK=1;
			else
				Ahrs_OK=0;
		}
	}
}
#endif


volatile u16 ADC1_DATA[6]={0};
volatile u16 ADC_SUM[6]={0};
volatile u16 ADC_AVE[6]={0};
volatile float Voltage[6]={0.0};//�ɵ��ĵ�ѹֵ��
volatile float Current[5]={0.0};//�����ܵ�������·����ĵ�����������ѹ��ת����ϵ��40mv/A
volatile float Walte[5]={0.0};//�ܹ��ʺ���·����Ĺ���
u8 sign_Adc1=0;

//DMA2 Stream0,ch0��ӦADC1,DMA2 Stream1,ch2��ӦADC3,DMA2 Stream2,ch2��ӦADC2
#if __DMA_ADC1

void DMA_Config_ADC1(DMA_Stream_TypeDef *DMA_Streamx,u8 chx,u32 par,u32 mar,u16 ndtr,u8 rank)
{ 
	DMA_TypeDef *DMAx;
	u8 streamx;
	if((u32)DMA_Streamx>(u32)DMA2)//�õ���ǰstream������DMA2����DMA1
	{
		DMAx=DMA2;
		RCC->AHB1ENR|=1<<22;//DMA2ʱ��ʹ�� 
	}else 
	{
		DMAx=DMA1; 
 		RCC->AHB1ENR|=1<<21;//DMA1ʱ��ʹ�� 
	}
	while(DMA_Streamx->CR&0X01);//�ȴ�DMA������ 
	streamx=(((u32)DMA_Streamx-(u32)DMAx)-0X10)/0X18;		//�õ�streamͨ����
 	if(streamx>=6)DMAx->HIFCR|=0X3D<<(6*(streamx-6)+16);	//���֮ǰ��stream�ϵ������жϱ�־
	else if(streamx>=4)DMAx->HIFCR|=0X3D<<6*(streamx-4);    //���֮ǰ��stream�ϵ������жϱ�־
	else if(streamx>=2)DMAx->LIFCR|=0X3D<<(6*(streamx-2)+16);//���֮ǰ��stream�ϵ������жϱ�־
	else DMAx->LIFCR|=0X3D<<6*streamx;						//���֮ǰ��stream�ϵ������жϱ�־
	
	DMA_Streamx->PAR=par;		//DMA�����ַ
	DMA_Streamx->M0AR=mar;		//DMA �洢��0��ַ
	DMA_Streamx->NDTR=ndtr;		//DMA ���ݴ�����
	
	DMA_Streamx->CR=0;			//��ȫ����λCR�Ĵ���ֵ 
	DMA_Streamx->CR|=(u32)chx<<25;//ͨ��ѡ��
//	DMA_Streamx->CR|=1<<21;		//����ͻ�����δ���
	DMA_Streamx->CR|=(u32)rank<<16;		//�е����ȼ�0�ǵͣ�1���У�2�Ǹߣ�3�Ƿǳ���
	
	DMA_Streamx->CR|=1<<13;		//�洢�����ݳ���:16λ
	DMA_Streamx->CR|=1<<11;		//�������ݳ���:16λ	
	DMA_Streamx->CR|=1<<10;		//�洢������ģʽ	
//	DMA_Streamx->CR|=1<<9;		//���������ģʽ
	DMA_Streamx->CR|=1<<8;		//ѭ��ģʽ	
//	DMA_Streamx->CR|=1<<6;		//���赽�洢��ģʽ//0�Ǵ����赽�洢����1�Ǵ洢�������裬2�Ǵ洢�����洢��
	DMA_Streamx->CR|=1<<4;		//��������ж�ʹ��	
	MY_NVIC_Init(3,3,DMA2_Stream0_IRQn,2);//��Ҫ������Ҫ�޸��ж�ʸ����	
	
//	DMA_Streamx->FCR=0X21;	//FIFO���ƼĴ�����������������������

//	DMA_Streamx->CR&=~(1<<0); 	//�ر�DMA���� 
	while(DMA_Streamx->CR&0X1);	//ȷ��DMA���Ա�����  
	DMA_Streamx->CR|=1<<0;		//����DMA����
	
	ADC1->CR2|=1<<30;	   	//����ADC����ת��
} 


void  DMA2_Stream0_IRQHandler()//������X0-3�Ĵ�������жϷ�����
{
	u8 i=0;
	static u8 t=0;
	if(DMA2->LISR&(1<<5))//������ɱ�־λ��������0-3��Ӧ5��11��21��27
	{
		DMA2->LIFCR|=1<<5;//�����־λ
		for(i=0;i<6;i++)
			ADC_SUM[i]+=ADC1_DATA[i];
		t++;
		
		if(t>7)
		{
			t=0;
			for(i=0;i<6;i++)
			{
				ADC_AVE[i]=ADC_SUM[i]/8;//ȡ8�ξ�ֵ		
				ADC_SUM[i]=0;				
			}		
			sign_Adc1=1;
		}	
	}
}

u8 PowerOff_Flag=0;
void Power_Monitor(void)
{
	u8 i=0;
	for(i=0;i<6;i++)
		Voltage[i]=(float)(ADC_AVE[i]*3.3f/4095);//ת��Ϊ��ѹֵ					
	
	Voltage[5]=(float)(Voltage[5]*43/10);//���ݵ���ķ�ѹ��������ص�ѹ
	if(Voltage[5]<11.7f)
		PowerOff_Flag=1;
	
	for(i=1;i<5;i++)
		Current[i]=(float)((float)(Voltage[i-1]-2.5f)/0.04f);//�����������
	Current[0]=Current[1]+Current[2]+Current[3]+Current[4];//�ܵ���
	
	for(i=1;i<5;i++)
		Walte[i]=(float)(Voltage[5]*Current[i]);//��ص�ѹ���Ե���
	Walte[0]=Walte[1]+Walte[2]+Walte[3]+Walte[4];//�������ܹ���
}	
#endif


