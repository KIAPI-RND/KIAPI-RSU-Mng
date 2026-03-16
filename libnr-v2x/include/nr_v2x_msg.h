/*
 * Copyright (c) 2025 Korea Intelligent Automotive Parts Promotion Institute (KIAPI). All rights reserved.
 * Project : KIAPI 5G-NR-V2X
 * Author: WooChang Seo (wcseo@kiapi.or.kr) 
 * Date: 2025-08-29
 */ 


#ifndef _V2X_CS_MSG_H_
#define _V2X_CS_MSG_H_

#include <string> 
#include <stdint.h>
#include <cpp-framework/common/endian.h>

 
#define V2X_MCU_MAGIC_NUMBER 0x35475658  // 5GVX
#define OVERALL_MAGIC_NUMBER 0x454D4F50  // EMOP

typedef enum{ 
    V2X_ACTION_TYPE_ADD = 0,
    V2X_ACTION_TYPE_DELETE = 1,
    V2X_ACTION_TYPE_DELETE_ALL = 2, 
}v2x_action_type;

typedef enum
{
    V2X_COMM_TYPE_V2V = 0x01,
    V2X_COMM_TYPE_V2I = 0x02,
    V2X_COMM_TYPE_I2V = 0x03
} v2x_comm_type;

typedef enum
{
    V2X_UC_DEV_TYPE_OBU_MODEM_UINT = 10,
    V2X_UC_DEV_TYPE_OBU_COMM_UINT = 11,
    V2X_UC_DEV_TYPE_RSU_MODEM_UINT = 20,
    V2X_UC_DEV_TYPE_RSU_COMM_UINT = 21,
    V2X_UC_DEV_TYPE_RSU_CTL_UINT = 22
} v2x_uc_device_type;

typedef enum{
    V2X_UC_TX = 0x00,
    V2X_UC_RX = 0x01
}v2x_uc_tx_rx_type;
 
typedef enum
{
    NR_V2X_DEV_MSG_ACK = 0x0001,       // reserved
    NR_V2X_DEV_MSG_NAK = 0x0002,       // reserved
    NR_V2X_DEV_MSG_HEARTBEAT = 0x0003, // reserved
    NR_V2X_DEV_MSG_TIME = 0x0004,      // reserved
    NR_V2X_DEV_MSG_STATUS = 0x0005,    // reserved
    NR_V2X_DEV_MSG_REPAIR = 0x0006,    // reserved
    NR_V2X_DEV_MSG_CMD = 0x0007,       // reserved
    NR_V2X_DEV_MSG_TX_MSG = 0x0010, 
    NR_V2X_DEV_MSG_RX_MSG = 0x0011,
    NR_V2X_DEV_MSG_WSR = 0x0012,
    NR_V2X_DEV_MSG_WSC = 0x0013,
    NR_V2X_DEV_MSG_FTP_CONN_REQ = 0xE380,
    NR_V2X_DEV_MSG_FTP_CONN_RES = 0xE381
} nr_v2x_mcu_msg_type;

typedef enum
{
    /*	C-ITS	*/ //	기존	V2X	메시지용
    eV2XMSG_TYPE_ETCS = 82049,
    eV2XMSG_TYPE_BSM = 82050,  //	20,
    eV2XMSG_TYPE_PVD = 82051,  //	26,
    eV2XMSG_TYPE_EVA = 82052,  //	22,
    eV2XMSG_TYPE_RSA = 82053,  //	27,
    eV2XMSG_TYPE_TIM = 82054,  //	31,
    eV2XMSG_TYPE_SPAT = 82055, //	19,
    eV2XMSG_TYPE_MAP = 82056,  //	18,

    // 1차년도 성과품에 일시적으로 사용(추후 삭제 예정)
    eV2XMSG_TYPE_KDF = 5271, //	KETI	data	frame	V2V	통신시
    eV2XMSG_TYPE_EDF = 5272, //	KETI	data	frame을	V2I	통신시
    //	확장 메시지용
    eV2XMSG_TYPE_5G_EM_V2V = 58200, //	Extensible	Message	for	V2V
    eV2XMSG_TYPE_5G_EM_V2I = 58201, //	Extensible	Message	for	V2I
    eV2XMSG_TYPE_5G_EM_I2V = 58202, //	Extensible	Message	for	I2V

    eV2XMSG_TYPE_5G_EM_I2I = 58201, // (I2I는 정식적으로 지원하지 않음 !!!! V2I 를 대신해서 사용함)
    

    //	Extensible	Message	Package	Type
    EM_PT_OVERALL = 58220,  //	overall	package
    EM_PT_RAW_DATA = 58221, //	raw	data	package
    EM_PT_SSOV = 58222,     //	SSOV	package	또는	SSOV	PSID,	cf	SSOV의	응용
                            //  서비스는 SSOV format 내부 Service ID로 구분
    EM_PT_STATUS = 58223,   //	status	package

} nr_v2x_psid_list_t;

struct nr_v2x_msg_header_t
{
    BE<uint32_t> magic_number;
    BE<uint16_t> length;
    BE<uint16_t> seq;
    BE<uint16_t> payload_id;
} __attribute__((packed));

struct nr_v2x_wsr_t{
    nr_v2x_msg_header_t header;
    uint8_t action;
    BE<uint32_t> psid;
}__attribute__((packed));
 
struct nr_v2x_wsc_t{
    nr_v2x_msg_header_t header;
    uint8_t action_result;
    BE<uint32_t> psid;
}__attribute__((packed)); 

struct nr_v2x_ftp_con_req_t{ 
    nr_v2x_msg_header_t header;   
    BE<uint32_t> psid;  // psid 58240
    uint8_t unit_id;  
    BE<uint32_t> link_id;
}__attribute__((packed));
 
struct nr_v2x_ftp_con_res_t{ 
    nr_v2x_msg_header_t header;   
    BE<uint32_t> psid;  // psid 58240
    uint8_t unit_id;  
    BE<uint32_t> link_id;
    BE<uint32_t> ip_address;
    BE<uint16_t> port;
    uint8_t id_password[]; // null terminated string (0x00) 
}__attribute__((packed));
 
struct nr_v2x_tx_msg_t
{
    nr_v2x_msg_header_t header;
    BE<uint32_t> psid;
    uint8_t message[];
} __attribute__((packed));
 
struct nr_v2x_ettifos_tx_msg_t{

    nr_v2x_msg_header_t header;
    BE<uint32_t> psid;  
    
    uint8_t cast_mode; // endian check 필요 
    uint32_t src_id;
    uint32_t dst_id;
    uint8_t reserved[8];

    uint8_t message[];
    // 뒤에 CRC 있음 하지만 0000 임

} __attribute__((packed));
 
struct nr_v2x_rx_msg_t
{
    nr_v2x_msg_header_t header;
    BE<uint32_t> psid;
    uint8_t rcpi;
    uint8_t message[];
} __attribute__((packed));

struct nr_v2x_ettifos_rx_msg_t
{
    nr_v2x_msg_header_t header;
    BE<uint32_t> psid;
    uint8_t cast_mode; // endian check 필요
    uint32_t src_id;
    uint32_t dst_id;
    uint8_t reserved[8];
    uint8_t rcpi;
    uint8_t message[];
    // 뒤에 CRC 있음 하지만 0000 임

} __attribute__((packed));

struct nr_v2x_ext_msg_overall_package_v1_t
{
    BE<uint32_t> tag;
    BE<uint16_t> len; 
    BE<uint32_t> magic_number;
    uint8_t version;
    uint8_t pack_cnt;
    BE<uint16_t> pack_len;
    BE<uint16_t> crc;
}__attribute__((packed)); 

struct nr_v2x_ext_msg_overall_package_v2_t
{
    BE<uint32_t> tag;
    BE<uint16_t> len; 
    BE<uint32_t> magic_number;
    uint8_t version;
    uint8_t pack_cnt;
    BE<uint16_t> pack_len; 
    uint8_t target;
    BE<uint16_t> crc;
}__attribute__((packed));
  
struct nr_v2x_ext_status_modem_base_data_t{ 
    uint8_t uc_device_type;
    uint8_t uc_tx_rx;
    BE<uint32_t> un_device_id;
    BE<uint16_t> us_hw_ver;
    BE<uint16_t> us_sw_ver;
    BE<uint64_t> us_timestamp;  
}__attribute__((packed));

struct nr_v2x_ext_status_modem_tx_t
{ 
    nr_v2x_ext_status_modem_base_data_t base;
    int8_t c_tx_pwr;
    BE<uint16_t> us_tx_freq;
    uint8_t us_tx_bw;
    uint8_t uc_tx_scs;
    uint8_t uc_pssch_mcs_idx;
    BE<int32_t> n_tx_latitude;
    BE<int32_t> n_tx_longitude;
    uint8_t cpu_temp;
    uint8_t peri_temp; 

} __attribute__((packed));

struct nr_v2x_ext_status_modem_rx_t
{
    nr_v2x_ext_status_modem_base_data_t base;
    int8_t c_rssi;
    uint8_t uc_rcpi;
    BE<int32_t> n_rx_latitude;
    BE<int32_t> n_rx_longitude;
    uint8_t cpu_temp;
    uint8_t peri_temp;
}__attribute__((packed));

struct nr_v2x_ext_status_comm_tx_t
{
    nr_v2x_ext_status_modem_base_data_t base;
    uint8_t cpu_temp;
    uint8_t peri_temp; 
}__attribute__((packed));
 
typedef nr_v2x_ext_status_comm_tx_t nr_v2x_ext_status_comm_rx_t;

typedef nr_v2x_ext_status_comm_tx_t nr_v2x_ext_status_ctl_tx_t;

typedef nr_v2x_ext_status_comm_tx_t nr_v2x_ext_status_ctl_rx_t;

struct nr_v2x_ext_status_msg_field_t{
    // uint32_t msg_id;
    typedef enum
    {
        UNKWON = 0,
        MODEM_TX = 1,
        MODEM_RX = 2,
        COMM_TX = 3,
        COMM_RX = 4,
        CTL_TX = 5,
        CTL_RX = 6
    }msg_id_t;
   
    msg_id_t msg_id;
    nr_v2x_ext_status_modem_tx_t modem_tx;
    nr_v2x_ext_status_modem_rx_t modem_rx;
    nr_v2x_ext_status_comm_tx_t common;
};











nr_v2x_ext_status_msg_field_t build_ext_status(std::string &out, uint8_t device_type, uint8_t tx_rx, uint32_t device_id, uint16_t hw_ver, uint16_t sw_ver, uint64_t timestamp);
nr_v2x_ext_status_msg_field_t parse_status_field(int index, const std::string &status_msg);

#endif