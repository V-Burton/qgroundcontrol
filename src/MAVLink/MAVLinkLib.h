/****************************************************************************
 *
 * (c) 2009-2024 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#define MAVLINK_COMM_NUM_BUFFERS 16
#define MAVLINK_EXTERNAL_RX_STATUS
#define MAVLINK_USE_MESSAGE_INFO

// Inclure mavlink_types.h avant la déclaration
#include <mavlink/v2.0/mavlink_types.h>

#ifdef __cplusplus
extern "C" {
#endif
extern mavlink_status_t m_mavlink_status[MAVLINK_COMM_NUM_BUFFERS];
#ifdef __cplusplus
}
#endif

#include <stdint.h>
#include <mavlink/v2.0/all/mavlink.h>

// #define HAVE_MAVLINK_CHANNEL_T
#ifdef HAVE_MAVLINK_CHANNEL_T
typedef enum : uint8_t {
    MAVLINK_COMM_0,
    MAVLINK_COMM_1,
    MAVLINK_COMM_2,
    MAVLINK_COMM_3,
    MAVLINK_COMM_4,
    MAVLINK_COMM_5,
    MAVLINK_COMM_6,
    MAVLINK_COMM_7,
    MAVLINK_COMM_8,
    MAVLINK_COMM_9,
    MAVLINK_COMM_10,
    MAVLINK_COMM_11,
    MAVLINK_COMM_12,
    MAVLINK_COMM_13,
    MAVLINK_COMM_14,
    MAVLINK_COMM_15
} mavlink_channel_t;
#endif

// #define MAVLINK_MAX_SIGNING_STREAMS MAVLINK_COMM_NUM_BUFFERS

// #include <mavlink_types.h>

// #ifdef MAVLINK_EXTERNAL_RX_STATUS
//     extern mavlink_status_t m_mavlink_status[MAVLINK_COMM_NUM_BUFFERS];
// #endif

#define MAVLINK_GET_CHANNEL_STATUS
#ifdef MAVLINK_GET_CHANNEL_STATUS
    extern mavlink_status_t* mavlink_get_channel_status(uint8_t chan);
#endif

// Comment these two lines to increase security and integrity of the MAVLink communication
// #define MAVLINK_NO_SIGN_PACKET
// #define MAVLINK_NO_SIGNATURE_CHECK

#include <stddef.h>

// Ignore warnings from mavlink headers for both GCC/Clang and MSVC
#ifdef __GNUC__
#   if __GNUC__ > 8
#       pragma GCC diagnostic push
#       pragma GCC diagnostic ignored "-Waddress-of-packed-member"
#   else
#       pragma GCC diagnostic push
#       pragma GCC diagnostic ignored "-Wall"
#   endif
#else
#   pragma warning(push, 0)
#endif

#include <mavlink.h>

#ifdef __GNUC__
#	pragma GCC diagnostic pop
#else
#	pragma warning(pop, 0)
#endif
