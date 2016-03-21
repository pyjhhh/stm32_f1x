#ifndef __WWDG_H
#define __WWDG_H

#include "stm32f10x.h"

void WWDG_Config(void);
void Nvic_Config(void);
void WWDG_IRQHandler(void);

#endif

