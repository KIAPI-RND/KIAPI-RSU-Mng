/*
 * Project : KIAPI-RSU-Mng
 * Author: WooChang Seo (wcseo@kiapi.or.kr) 
 * Date: 2025-08-29
 */  

#ifndef _MAIN_SERVICE_H_
#define _MAIN_SERVICE_H_
 
#include "config.h"
#include <nr-v2x/nr_v2x.h>
#include <pq-utils/pq_handler.h> 
#include "db_service.h"
#include <cpp-framework/common/time.h>


class core_service : public nr_v2x_mng_handler{
public: 
    core_service(const app_config_t &config);
    ~core_service();

protected:
    bool on_dev_connection(nr_v2x_dev_info_t *dev, const std::string &ip, uint32_t port, bool connection);
    void on_rx_msg(nr_v2x_dev_info_t *dev, const v2x_parameter_field_t &param, const std::string &msg);
    void on_rx_msg_ext(nr_v2x_dev_info_t *dev,
                       const v2x_parameter_field_t &param,
                       const std::vector<v2x_message_field_t> &msg,
                       const std::vector<nr_v2x_ext_status_msg_field_t> &status);

    void on_tx_msg(nr_v2x_dev_info_t *dev, const v2x_parameter_field_t &param, const std::string &msg);
    void on_tx_msg_ext(nr_v2x_dev_info_t *dev,
                       const v2x_parameter_field_t &param,
                       const std::vector<v2x_message_field_t> &msg,
                       const std::vector<nr_v2x_ext_status_msg_field_t> &status);

    void on_ftp_conn_req(nr_v2x_dev_info_t *dev, uint32_t psid, uint8_t unit_id, uint32_t link_id);

private:
    
    void update_dev_status();
 
    app_config_t config;
    nr_v2x_mng v2x;  
    nr_pps_mng pps;
    nr_rx_table rx_table;

    thread_handler thread;
    void progress(void *arg);
 
    struct tick_list_t{ 
        tick_timer keep; 
        uint32_t keep_cnt;

        tick_list_t(){
            keep_cnt = 0;
            keep.set(1000);
        }; 
        
    }ticks;

    uint64_t startup = get_epoch_time_msec();

};








#endif