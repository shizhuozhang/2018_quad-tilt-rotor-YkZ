#include "H_define.h"



#if __SPI1
	void SPI1_Init(void)
	{	 
	RCC->APB2ENR|=1<<2;       //PORTAʱ��ʹ�� 	 
	RCC->APB2ENR|=1<<12;      //SPI1ʱ��ʹ�� 
		   
	//����ֻ���SPI�ڳ�ʼ��
	GPIOA->CRL&=0X000FFFFF; 
	GPIOA->CRL|=0XBBB00000;//PA5.6.7���� 	    
	GPIOA->ODR|=0X7<<5;    //PA5.6.7����
		
	SPI1->CR1|=0<<10;//ȫ˫��ģʽ	
	SPI1->CR1|=1<<9; //���nss����
	SPI1->CR1|=1<<8;  

	SPI1->CR1|=1<<2; //SPI����
	SPI1->CR1|=0<<11;//8bit���ݸ�ʽ	
		
	SPI1->CR1|=1<<1; //����ģʽ��SCKΪ1 CPOL=1
	SPI1->CR1|=1<<0; //���ݲ����ӵڶ���ʱ����ؿ�ʼ,CPHA=1 
		
	SPI1->CR1|=7<<3; //Fsck=Fcpu/128
	SPI1->CR1|=0<<7; //MSBfirst   
	SPI1->CR1|=1<<6; //SPI�豸ʹ��
	SPI1_ReadWriteByte(0xff);//��������(��Ҫ���ã�ά��MOSIΪ��)		 
	}   
	//SPI1 �ٶ����ú���
	//SpeedSet:0~7
	//SPI�ٶ�=fAPB2/2^(SpeedSet+1)
	//APB2ʱ��һ��Ϊ72Mhz
	void SPI1_SetSpeed(u8 SpeedSet)
	{
		SpeedSet&=0X07;			//���Ʒ�Χ
		SPI1->CR1&=0XFFC7; 
		SPI1->CR1|=SpeedSet<<3;	//����SPI1�ٶ�  
		SPI1->CR1|=1<<6; 		//SPI�豸ʹ�� 
	} 
	//SPI1 ��дһ���ֽ�
	//TxData:Ҫд����ֽ�
	//����ֵ:��ȡ�����ֽ�
	//ȫ˫����д����ŵ�һ��
	//����ʱ����Ҫͨ�����豸д�������ṩSCK
	//д��������豸��DR�л��һ�����õ����ݣ���Ҫ�������建��
	u8 SPI1_ReadWriteByte(u8 TxData)
	{		
		u16 retry=0;				 
		while((SPI1->SR&1<<1)==0)//�ȴ���������	
		{
			retry++;
			if(retry>0XFFFE)return 0;
		}			  
		SPI1->DR=TxData;	 	  //����һ��byte 
		retry=0;
		while((SPI1->SR&1<<0)==0) //�ȴ�������һ��byte  
		{
			retry++;
			if(retry>0XFFFE)return 0;
		}	  						    
		return SPI1->DR;          //�����յ�������				    
	} 
#endif

#if __SPI2
	void SPI2_Init(void)
	{	 
		RCC->APB2ENR|=1<<3;       //PORTBʱ��ʹ�� 	 
		RCC->APB1ENR|=1<<14;      //SPI2ʱ��ʹ�� 
			   
		//����ֻ���SPI�ڳ�ʼ��
		GPIOB->CRH&=0X000FFFFF; 
		GPIOB->CRH|=0XBBB00000;//PB13,14,15���� 	    
		GPIOB->ODR|=0X7<<13;    //PB13,14,15����
			
		SPI2->CR1|=0<<10;//ȫ˫��ģʽ	
		SPI2->CR1|=1<<9; //���nss����
		SPI2->CR1|=1<<8;  

		SPI2->CR1|=1<<2; //SPI����
		SPI2->CR1|=0<<11;//8bit���ݸ�ʽ	
			
		SPI2->CR1|=1<<1; //����ģʽ��SCKΪ1 CPOL=1
		SPI2->CR1|=1<<0; //���ݲ����ӵڶ���ʱ����ؿ�ʼ,CPHA=1 
			
		SPI2->CR1|=7<<3; //Fsck=Fcpu/128
		SPI2->CR1|=0<<7; //MSBfirst   
		SPI2->CR1|=1<<6; //SPI�豸ʹ��
		SPI2_ReadWriteByte(0xff);//��������(��Ҫ���ã�ά��MOSIΪ��)		 
	}   
	//SPI2 �ٶ����ú���
	//SpeedSet:0~7
	//SPI�ٶ�=fAPB2/2^(SpeedSet+1)
	//APB1ʱ��һ��Ϊ36Mhz
	void SPI2_SetSpeed(u8 SpeedSet)
	{
		SpeedSet&=0X07;			//���Ʒ�Χ
		SPI2->CR1&=0XFFC7; 
		SPI2->CR1|=SpeedSet<<3;	//����SPI1�ٶ�  
		SPI2->CR1|=1<<6; 		//SPI�豸ʹ�� 
	} 
	//SPI2 ��дһ���ֽ�
	//TxData:Ҫд����ֽ�
	//����ֵ:��ȡ�����ֽ�
	//ȫ˫����д����ŵ�һ��
	//����ʱ����Ҫͨ�����豸д�������ṩSCK
	//д��������豸��DR�л��һ�����õ����ݣ���Ҫ�������建��
	u8 SPI2_ReadWriteByte(u8 TxData)
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
#endif

#if __SPI3
	void SPI3_Init(void)
	{	 
		RCC->APB2ENR|=1<<3;       //PORTBʱ��ʹ�� 	 
		RCC->APB1ENR|=1<<15;      //SPI3ʱ��ʹ�� 
			   
		//����ֻ���SPI�ڳ�ʼ��
		GPIOB->CRL&=0XFF000FFF; 
		GPIOB->CRL|=0X00BBB000;//PB3,4,5���� 	    
		GPIOB->ODR|=0X7<<3;    //PB3,4,5����
			
		SPI3->CR1|=0<<10;//ȫ˫��ģʽ	
		SPI3->CR1|=1<<9; //���nss����
		SPI3->CR1|=1<<8;  

		SPI3->CR1|=1<<2; //SPI����
		SPI3->CR1|=0<<11;//8bit���ݸ�ʽ	
			
		SPI3->CR1|=1<<1; //����ģʽ��SCKΪ1 CPOL=1
		SPI3->CR1|=1<<0; //���ݲ����ӵڶ���ʱ����ؿ�ʼ,CPHA=1 
			
		SPI3->CR1|=7<<3; //Fsck=Fcpu/128
		SPI3->CR1|=0<<7; //MSBfirst   
		SPI3->CR1|=1<<6; //SPI�豸ʹ��
		SPI3_ReadWriteByte(0xff);//��������(��Ҫ���ã�ά��MOSIΪ��)		 
	}   
	//SPI3 �ٶ����ú���
	//SpeedSet:0~7
	//SPI�ٶ�=fAPB2/2^(SpeedSet+1)
	//APB1ʱ��һ��Ϊ36Mhz
	void SPI3_SetSpeed(u8 SpeedSet)
	{
		SpeedSet&=0X07;			//���Ʒ�Χ
		SPI3->CR1&=0XFFC7; 
		SPI3->CR1|=SpeedSet<<3;	//����SPI1�ٶ�  
		SPI3->CR1|=1<<6; 		//SPI�豸ʹ�� 
	} 
	//SPI3 ��дһ���ֽ�
	//TxData:Ҫд����ֽ�
	//����ֵ:��ȡ�����ֽ�
	//ȫ˫����д����ŵ�һ��
	//����ʱ����Ҫͨ�����豸д�������ṩSCK
	//д��������豸��DR�л��һ�����õ����ݣ���Ҫ�������建��
	u8 SPI3_ReadWriteByte(u8 TxData)
	{		
		u16 retry=0;				 
		while((SPI3->SR&1<<1)==0)//�ȴ���������	
		{
			retry++;
			if(retry>0XFFFE)return 0;
		}			  
		SPI3->DR=TxData;	 	  //����һ��byte 
		retry=0;
		while((SPI3->SR&1<<0)==0) //�ȴ�������һ��byte  
		{
			retry++;
			if(retry>0XFFFE)return 0;
		}	  						    
		return SPI3->DR;          //�����յ�������				    
	} 
#endif















