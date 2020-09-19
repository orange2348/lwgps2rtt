//*****************************************************************************
// file        : lwgps2rtt.h
// porting lwgps to rt-thread
//
// Change Logs:
// Date                 Author      Note
// 2020/09/06           Cheney      First draft version
// 2020/09/13           Cheney      Support gps info query interface.
//
//*****************************************************************************
#ifndef __LWGPS2RTT_H__
#define __LWGPS2RTT_H__

//*****************************************************************************
//
//! \addtogroup lwgps
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

#include "lwgps.h"

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
void lwgps2rtt_init(const char *uart_dev_name);
void lwgps2rtt_get_gps_info(lwgps_t *gps_info);
void lwgps2rtt_deinit(void);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************

#ifdef __cplusplus
}
#endif

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
#endif //  __LWGPS2RTT_H__