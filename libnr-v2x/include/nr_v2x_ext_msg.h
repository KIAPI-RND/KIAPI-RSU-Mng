/*
 * Copyright (c) 2025 Korea Intelligent Automotive Parts Promotion Institute (KIAPI). All rights reserved.
 * Project : KIAPI 5G-NR-V2X
 * Author: WooChang Seo (wcseo@kiapi.or.kr) 
 * Date: 2025-08-29
 */ 


#ifndef _NR_V2X_KIAPI_MSG_H_ 
#define _NR_V2X_KIAPI_MSG_H_
 
#include <string> 
#include <cpp-framework/common/endian.h>
#include <stdint.h> 

// Little Endian base format ! 


#define KIAPI_MAGIC_NUMBER 0x4B494150 // KIAP
  
typedef enum{
    KIAPI_RTT_NUMBER = 0x4B525454, // KRTT 
    KIAPI_RTT_ACK_NUMBER = 0x4B525455, // KRTT (ACK) 
    KIAPI_DEV_POS_DATA = 0x4B525450, // KRTP (POSITION) 
    // KIAPI_OBU_RTT_NUMBER = 0x4B525456
}nr_v2x_kiapi_msg_tag_t;
    
struct nr_v2x_rtt_position_t{
    int latitude;
    int longitude;
    int elevation;
    uint16_t heading;
    uint16_t speed;
    uint8_t dop;
}__attribute__((packed)); 

struct nr_v2x_rtt_base_msg_t
{   
    // tx rtt data 
    uint64_t timestamp; // 최초 RTT 메시지를 송출한 시간
    uint64_t rtt_id;
    uint32_t seq;
    uint32_t dev_id; 
    uint8_t type;
    uint16_t cnt;    
    uint16_t interval;
    uint16_t size;

    bool burst_mode;
    uint8_t reserved_1; // 예비2
    uint8_t reserved_2; // 예비2
    uint8_t reserved_3; // 예비3

    nr_v2x_rtt_position_t pos; 
    nr_v2x_rtt_position_t rx_pos; // 수신한 위치    

    // rx rtt data
    uint32_t recv_id;          // 수신한 장치의 ID
    uint8_t recv_type; 
    uint8_t pps;
    uint8_t rcpi;
    int8_t rssi;
    uint64_t tx_rf_timestamp;  // RF 모듈 RTT 메시지 전송 시간 (전송 시 채우지 않고 수신 시 확인 가능함)   
    int32_t rx_rf_tick;       // RF 모듈 RTT 메시지 수신 시간 (전송 시간을 기점으로 지난 시간)
    uint64_t rx_timestamp;     // 수신한 종단 장치의 시간 (장치간 시간이 다를 수 있어 별개 timestamp로 둠)
    uint64_t throughput;     // 수신 쓰르풋 정보
       
} __attribute__((packed));


struct nr_v2x_rtt_ack_msg_t
{ 
    nr_v2x_rtt_base_msg_t base;
    // rx rtt ack data
    uint64_t tx_ack_rf_timestamp;   // RF 모듈 RTT 메시지 수신 시간
    int32_t rx_ack_rf_tick;   // RF 모듈 RTT 메시지 수신 시간
    uint64_t rx_ack_timestamp; // 수신한 종단 장치의 시간
    nr_v2x_rtt_position_t pos; // 수신한 위치    
    uint8_t ack_rcpi;
    int8_t ack_rssi;

} __attribute__((packed));


struct nr_v2x_dev_pos_data_t{

    uint64_t seq;
    uint64_t tx_tick;
    uint32_t dev_id;
    int lat;
    int lon;
    int elev;
    uint16_t heading;
    int speed; 

} __attribute__((packed));




#endif