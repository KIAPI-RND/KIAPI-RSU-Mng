/*
 * Project : KIAPI-RSU-Mng
 * Author: WooChang Seo (wcseo@kiapi.or.kr) 
 * Date: 2025-08-29
 */  


#include "core_service.h"
#include <cpp-framework/common/log.h>
#include <cpp-framework/text/text_tool.h>
#include <nr-v2x/nr_v2x.h> 
#include <cpp-framework/data/j2735.h>


/// @brief RSU Management 서비스 Init
/// @param config 
core_service::core_service(const app_config_t &config): 
v2x(nr_v2x_dev_type_t::V2X_DEV_TYPE_RSU,this,config.index),
thread(0,100)
{
    
    this->config = config; 
    v2x.add_dev_list(config.dev_list);                  // libnrv2x 라이브러리 사용 부분 
    v2x.set(config.is_server,config.ip,config.port);    // libnrv2x 라이브러리 사용 부분 
    v2x.set_debug(config.debug);                        // libnrv2x 라이브러리 사용 부분 
      
    thread.start(this,&core_service::progress,nullptr); 
}

/// @brief RSU Management 서비스 dispose
core_service::~core_service()
{ 
 


}

/// @brief RSU 연결 상태 변경(연결 완료, 연결 해제) 이벤트 처리
/// @param dev 연결장치 정보
/// @param ip 연결 장치 IP
/// @param port 연결 장치 Port
/// @param connection 연결 상태 (True : 연결, False : 연결 해제)
/// @return 
bool core_service::on_dev_connection(nr_v2x_dev_info_t *dev,const std::string &ip, uint32_t port, bool connection)
{   
    log_print(1,"core_service::on_dev_connection index = %d", dev->index);

    // define, OBU 연결 상태 갱신 처리 구현 
    return 0;
}

/// @brief RSU, V2X RX 메시지 수신 이벤트 처리 
/// @param dev 수신 RSU 장치 정보
/// @param param 수신 V2X 파라미터 정보 
/// @param msg 수신 Payload 메시지 
void core_service::on_rx_msg(nr_v2x_dev_info_t *dev, const v2x_parameter_field_t &param, const std::string &msg)
{  

    int id = -1;
    if (dev != nullptr)
    {
        id = dev->index; 
    }

    log_print(1, "core_service::on_rx_msg %d , pps %d ", id, param.rx.pps);

}

/// @brief RSU, V2X RX(Ext) 메시지 수신 이벤트 처리 
/// @param dev 수신 RSU 장치 정보 
/// @param param 수신 V2X 파라미터 정보
/// @param msg 수신 Payload 필드 정보 
/// @param status 수신 Status 필드 정보
void core_service::on_rx_msg_ext(nr_v2x_dev_info_t *dev, const v2x_parameter_field_t &param,
                                 const std::vector<v2x_message_field_t> &msg,
                                 const std::vector<nr_v2x_ext_status_msg_field_t> &status)
{
  
    for(auto it = msg.begin() ; it != msg.end() ; it++){

        if(it->psid == EM_PT_RAW_DATA)
        { 
            tlvc_msg_t val;
            val.parse((char *)it->data.c_str());
 
            switch (tlv_sub.tag)
            {
                // Define message progress
            }
        }  
    }
}

/// @brief RSU, 메시지 전송 결과 이벤트 처리
/// @param dev 전송 RSU 장치 정보 
/// @param param 전송 V2X 파라미터 정보 및 결과 
/// @param msg  전송 Payload 데이터
void core_service::on_tx_msg(nr_v2x_dev_info_t *dev, const v2x_parameter_field_t &param, const std::string &msg)
{
    int id = -1;
    if (dev != nullptr)
    {
        id = dev->index; 
    }
}

/// @brief RSU, Ext 메시지 전송 결과 이벤트 처리
/// @param dev 전송 RSU 장치 정보 
/// @param param 전송 V2X 파라미터 정보 및 결과 
/// @param msg 전송 결과, Payload 데이터 필드 목록
/// @param status 전송 결과, Status 데이터 필드 목록
void core_service::on_tx_msg_ext(nr_v2x_dev_info_t *dev, const v2x_parameter_field_t &param,
                                 const std::vector<v2x_message_field_t> &msg, const std::vector<nr_v2x_ext_status_msg_field_t> &status)
{  
    int id = -1;
    if (dev != nullptr)
    {
        id = dev->index; 
    } 

    for (int i = 0; i < msg.size(); i++)
    {
        tlvc_msg_t tlv;
        tlv.parse((char *)msg[i].data.c_str());

        switch (tlv.tag)
        { 
            // Define message progress
        }
    }
}

/// @brief RSU, FTP 업데이트 요청 이벤트 처리 
/// @param dev 수신 RSU 정보
/// @param psid 서비스 PSID
/// @param unit_id 업데이트 요청 UNIT ID 정보
/// @param link_id 업데이트 요청 LINK ID 정보
void core_service::on_ftp_conn_req(nr_v2x_dev_info_t *dev, uint32_t psid, uint8_t unit_id, uint32_t link_id)
{  
    log_print("core_service::on_ftp_conn_req");

    // libnrv2x 라이브러리 사용 부분
    bool res = v2x.request_tx_ftp_conn_res(dev->index, unit_id, link_id, config.ftp.ip, config.ftp.port, config.ftp.id, config.ftp.pw);
  
} 

/// @brief 디바이스 정보 갱신 프로그래스
void core_service::update_dev_status(){
 
    for(int i = 0 ; i < config.dev_list.size() ; i++){

        int id = config.dev_list[i].dev_id;

        // libnrv2x 라이브러리 사용 부분
        nr_v2x_dev_info_t *dev = v2x.get_dev_info(id);

        if (dev->fd < 0)
            continue;
  
        std::map<int, int> list;
        int cnt = rx_table.get(id, &list);
       
        dev->cnt.reset();
    } 
 
    rx_table.reset();
   
}

/// @brief RSU 상태 갱신 및 업데이트 동작 스레드 부 
/// @param arg 
void core_service::progress(void *arg)
{ 
    if (ticks.keep.timeout())
    { 
        update_dev_status();
    } 

}