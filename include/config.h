/*
 * Project : KIAPI-RSU-Mng
 * Author: WooChang Seo (wcseo@kiapi.or.kr)  
 * Date: 2025-08-29
 */  
   
#ifndef _APP_OPTIONS_H_
#define _APP_OPTIONS_H_
 
#include <string> 
#include <stdint.h>
#include <vector>
 
#include <nr-v2x/nr_v2x.h>
#include <pq-utils/pq_config.h>

#define SW_VERSION_MAJOR 0
#define SW_VERSION_MINOR 0
#define SW_VERSION_PATCH 1
 
struct app_config_t
{ 
    int index = 0;           // Application Index number
    std::string path = "";   // configure path 
    bool debug = false;      // set debug option

    // access port
    bool is_server = true;   // This Application run TCP Server (TRUE) , TCP Client(False)
    std::string ip = "";     // if this application running TCP Client, connect server ip  
    uint32_t port = 53670;   // TCP 서버 서비스 포트
    uint32_t version = 2;    // 5G-NR V2X Extensions Header Version 
    //  
    std::vector<nr_v2x_dev_info_t> dev_list;
    
    struct ftp_conn_info_t{ 
        std::string ip ="";  // FTP Server IP 
        uint16_t port = 0;   // FTP Server Port
        std::string id = ""; // FTP Access ID 
        std::string pw = ""; // FTP Access PW
    }ftp;
 
};

#endif