#include "H_define.h"
/*
 * ��������SPI1_Init
 * ����  ��SPI1��ʼ��
 * ����  ����
 * ���  ����
 */ 
 void SPI1_Init(void)
	{	 
		RCC->APB2ENR|=1<<3;       //PORTBʱ��ʹ�� 	 
		RCC->APB1ENR|=1<<14;      //SPI2ʱ��ʹ�� 
			   
		//����ֻ���SPI�ڳ�ʼ��
		GPIOB->CRH&=0X000FFFFF; 
		GPIOB->CRH|=0XBBB00000;//PB13,14,15���� 	    
		GPIOB->ODR|=0X7<<13;    //PB13,14,15����
		
		MPU6500_CS=1;
		
		SPI2->CR1|=0<<10;//ȫ˫��ģʽ	
		SPI2->CR1|=1<<9; //���nss����
		SPI2->CR1|=1<<8;  

		SPI2->CR1|=1<<2; //SPI����
		SPI2->CR1|=0<<11;//8bit���ݸ�ʽ	
			
		SPI2->CR1|=0<<1; //����ģʽ��SCKΪ1 CPOL=1
		SPI2->CR1|=0<<0; //���ݲ����ӵڶ���ʱ����ؿ�ʼ,CPHA=1 
			
		SPI2->CR1|=2<<3; //Fsck=Fcpu/128
		SPI2->CR1|=0<<7; //MSBfirst   
		SPI2->CR1|=1<<6; //SPI�豸ʹ��
		SPI1_Read_Write_Byte(0xff);//��������(��Ҫ���ã�ά��MOSIΪ��)		 
	}   
// void SPI1_Init(void)
//{
//	
//	RCC->APB2ENR|=1<<2;       //PORTAʱ��ʹ�� 	 
//	RCC->APB2ENR|=1<<12;      //SPI1ʱ��ʹ�� 
//		   
//	//����ֻ���SPI�ڳ�ʼ��	
//    GPIOA->CRL&=~(0XFFF00000);//PA5.6.7���츴����� 
//	GPIOA->CRL|=0XBBB00000;//PA5.6.7���츴����� 	    
//	GPIOA->ODR|=0X00E0;    //PA5.6.7����
//	
//	MPU6500_CS=1;
//	
//	SPI1->CR1=0;	
//	
//	SPI1->CR1|=0<<6; //SPI�豸����
//	
//	SPI1->CR1|=0<<10;//ȫ˫��ģʽ	
//	SPI1->CR1|=0<<15;//˫��˫��
////	SPI1->CR1|=1<<14;//����ģʽ�µ����ʹ��		
//	SPI1->CR1|=1<<9; //���nss����
////	SPI1->CR1|=1<<8; //����nss�ϵĵ�ƽ /////////////////////////////////////////

//	SPI1->CR1|=1<<2; //SPI����
//	SPI1->CR1|=0<<11;//8bit���ݸ�ʽ	
//	SPI1->CR1|=0<<1; //����ģʽ��SCKΪ0 CPOL=0
//	SPI1->CR1|=0<<0; //���ݲ����ӵ�1��ʱ����ؿ�ʼ,CPHA=0  
//	SPI1->CR1|=2<<3; //Fsck=Fcpu/16
//	SPI1->CR1|=0<<7; //MSB   
//	SPI1->CR1|=1<<13; //ʹ��CRCУ��	
//	SPI1->CRCPR|=7; //CRC����ʱ�õ��Ķ���ʽ
//	
//	SPI1->CR1|=1<<6; //SPI�豸ʹ��
//	
//	SPI1_Read_Write_Byte(0xff);//��������(��Ҫ���ã�ά��MOSIΪ��)		 
//}   
/*
 * ������: uint8_t MPU9250_Write_Reg
 * ����  ������������9250���ض��Ĵ���д������
 * ����  ���Ĵ����ĵ�ַ������
 * ���  ��0��ʧ��  1���ɹ�
 */ 
u8 MPU6500_Write_Reg(uint8_t reg,uint8_t value)
{
	u8 status;
	MPU6500_CS=0;  //ʹ��SPI����
	status=SPI1_Read_Write_Byte(reg); //����д����+�Ĵ�����
	SPI1_Read_Write_Byte(value);//д��Ĵ���ֵ
	MPU6500_CS=1;  //��ֹMPU9250
	return(status);//����״ֵ̬
}

/*
 * ������: u8 MPU9250_Read_Reg
 * ����  ������������9250������
 * ����  ���Ĵ����ĵ�ַ
 * ���  ���ӼĴ������õ�����
 */ 
u8 MPU6500_Read_Reg(uint8_t reg)
{
	u8 reg_val;
	MPU6500_CS=0;  //ʹ��SPI����
	SPI1_Read_Write_Byte(reg|0x80); //���Ͷ�����+�Ĵ�����
									//9250�Ĵ�����ַ�����0x7E������0x80,��ֹ����
	reg_val=SPI1_Read_Write_Byte(0xff);//��ȡ�Ĵ���ֵ
	MPU6500_CS=1;  //��ֹMPU9250
	return(reg_val);
}

/*
 * ������: u8 SPI1_ReadWriteByte
 * ����  ������������9250��д����
 * ����  ���Ĵ����ĵ�ַ
 * ���  ���ӼĴ������õ����ݻ���ʧ�ܷ���0
 */ 
//u8 SPI1_Read_Write_Byte(u8 TxData)
//{		
//	u16 retry=0;				 
//	while((SPI1->SR&1<<1)==0)//�ȴ���������	
//	{
//		retry++;
//		if(retry>0XFFFE)return 0;
//	}			  
//	SPI1->DR=TxData;	 	  //����һ��byte 
//	retry=0;
//	while((SPI1->SR&1<<0)==0) //�ȴ�������һ��byte  
//	{
//		retry++;
//		if(retry>0XFFFE)return 0;
//	}	  						    
//	return SPI1->DR;          //�����յ�������				    
//}

u8 SPI1_Read_Write_Byte(u8 TxData)
{		
	u16 retry=0;				 
	while((SPI2->SR&1<<1)==0)//�ȴ���������	
	{
		retry++;
		if(retry>0XFFFE)return 0;
	}			  
	SPI2->DR=TxData;	 	  //����һ��byte 
	retry=0;
	while((SPI2->SR&1<<0)==0) //�ȴ�������һ��byte  
	{
		retry++;
		if(retry>0XFFFE)return 0;
	}	  						    
	return SPI2->DR;          //�����յ�������				    
}


