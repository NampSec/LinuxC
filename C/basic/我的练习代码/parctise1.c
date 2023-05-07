/*************************************************
Copyright © yang. 1998-2023. All rights reserved.
File name: parctise1.c
Author: yang
Version: 1.0
Description: 嵌入式C专题一练习一
Others: 
Log: 2023-04-15 1.0 yang create
*************************************************/
#include <stdio.h>
#define ONE_MOLE_WATER_MASS (3.0e-23)

int main()
{
    double mass = 950;
    double one_mole_water_mass = ONE_MOLE_WATER_MASS;
    printf("the molecule of the water is:%e\n",mass / one_mole_water_mass);

    return 0;


}