//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\depend\bsp_system_clock.h"
#include ".\mde_system_clock.h"
//-----------------------------------------------------------------------------
void mde_systemClock_cfg(void)
{
    bsp_clock_cfg();
}
sdt_int32u mde_pull_hisFrequency(void)
{
    return(24000000);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
