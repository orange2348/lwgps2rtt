//*****************************************************************************
// file        : lwgps2rtt.c
// porting lwgps to rt-thread
//
// Change Logs:
// Date                 Author      Note
// 2020/09/05           Cheney      First draft version
// 2020/09/13           Cheney      1. Update the comments.
//                                  2. Support gps info query interface.
// 2020/10/10           Cheney      Support macros LWGPS_CFG_STATUS
// 2020/12/15           Cheney      Configure the uart before using it.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup lwgps
//! @{
//
//*****************************************************************************
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "lwgps.h"

#ifndef GPS_MODULE_BAUD_RATE
#define GPS_MODULE_BAUD_RATE        BAUD_RATE_9600
#endif

static lwgps_t h_lwgps;

static rt_device_t serial = RT_NULL;
static struct rt_semaphore rx_sem;
static rt_thread_t lwgps_tid = RT_NULL;
static rt_mutex_t lwgps_mutex = RT_NULL;

/**
 * \brief gps uart date received callback
 *
 * \param dev: uart device
 * \param size: data size
 * \return rt_err_t: operation result.
 */
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(&rx_sem);
    return RT_EOK;
}

#if LWGPS_CFG_STATUS == 1
void lwgps_process_cbk(lwgps_statement_t res) 
{
    // TODO: give the interface to user.
}
#endif

/**
 * \brief lwgps process thread
 *
 * \param parameter: input parameters.
 */
static void lwgps_thread_entry(void *parameter)
{
    rt_uint8_t ch;

    while (RT_TRUE)
    {
        rt_sem_take(&rx_sem, RT_TICK_PER_SECOND);

        while (rt_device_read(serial, -1, &ch, 1) == 1)
        {
            rt_mutex_take(lwgps_mutex, RT_WAITING_FOREVER);
#if LWGPS_CFG_STATUS == 1
            lwgps_process(&h_lwgps, &ch, 1, lwgps_process_cbk);
#else
            lwgps_process(&h_lwgps, &ch, 1);
#endif
            rt_mutex_release(lwgps_mutex);
        }
    }
}

/**
 * \brief module init
 *
 * \param uart_dev_name: uart device name
 */
void lwgps2rtt_init(const char *uart_dev_name)
{
    serial = rt_device_find(uart_dev_name);
    if (!serial)
    {
        rt_kprintf("uart find %s failed!\n", uart_dev_name);
        return;
    }

    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    config.baud_rate = GPS_MODULE_BAUD_RATE;
    config.data_bits = DATA_BITS_8;
    config.stop_bits = STOP_BITS_1;
    config.parity    = PARITY_NONE;
    rt_device_control(serial, RT_DEVICE_CTRL_CONFIG, &config);

    lwgps_mutex = rt_mutex_create("lwgps_mutex", RT_IPC_FLAG_FIFO);

    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);
    rt_device_set_rx_indicate(serial, uart_input);

    lwgps_init(&h_lwgps);

    lwgps_tid = rt_thread_create("lwgps", lwgps_thread_entry, RT_NULL, 512, 20, 4);
    if (lwgps_tid != RT_NULL)
        rt_thread_startup(lwgps_tid);
}

/**
 * \brief get gps information
 * 
 * \param gps_info: gps information.
 */
void lwgps2rtt_get_gps_info(lwgps_t *gps_info)
{
    rt_mutex_take(lwgps_mutex, RT_WAITING_FOREVER);
    rt_memcpy(gps_info, &h_lwgps, (sizeof(h_lwgps) - sizeof(h_lwgps.p)));
    rt_mutex_release(lwgps_mutex);
}

/**
 * \brief module deinit
 *
 */
void lwgps2rtt_deinit(void)
{
    if (serial != RT_NULL)
    {
        rt_device_close(serial);
        rt_device_set_rx_indicate(serial, RT_NULL);
    }

    if (lwgps_tid != RT_NULL)
    {
        rt_thread_delete(lwgps_tid);
    }

    if (lwgps_mutex != RT_NULL)
    {
        rt_mutex_delete(lwgps_mutex);
    }

    serial = RT_NULL;
    lwgps_tid = RT_NULL;
    lwgps_mutex = RT_NULL;
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************