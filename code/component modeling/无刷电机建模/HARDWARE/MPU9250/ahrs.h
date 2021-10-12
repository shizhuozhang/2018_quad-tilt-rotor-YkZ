#ifndef __AHRS_H
#define __AHRS_H

#include "sys.h"

void Geographic_Coordinate_ReadValue(void);
void Prepare_Data(void);
void IMU_Update(void);
void AHRS_Date_Init(void);

#endif


