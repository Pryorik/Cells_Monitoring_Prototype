
/* Includes ------------------------------------------------------------------*/
#include "CLK.h"
#include "stm8s.h"
void CLK_init(void)
{
    /* Initialization of the clock */
    /* Clock divider to HSI/1 */
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
}
