/*
 * Project : KIAPI-RSU-Mng
 * Author: WooChang Seo (wcseo@kiapi.or.kr) 
 * Date: 2025-08-29
 */  

#include <cpp-framework/text/json_handler.h>
#include <cpp-framework/common/option.h>
#include <cpp-framework/common/time.h>
#include <cpp-framework/common/log.h>
#include "config.h" 
#include "core_service.h"

app_config_t config;  
    
/// @brief 실행 명령 Arguement 입력
/// @param argc 실행 명령 Arguement Count 
/// @param argv 실행 명령 Arguement Value 
void parse_options(int argc , char**argv){

    auto vals = option_parser(argc, argv, "c:hv");

    for (auto it = vals.begin(); it != vals.end(); it++)
    { 
        switch (it->opt)
        {
        case 'c':
            config.path = it->arg;
            break;
        case 'v':
            config.debug = true;
            break;
        case 'h':
        default:
            printf("%s usage \n",argv[0]);
            printf("\t-c [configure file]      : set json configure file\n");
            printf("\t-v                       : set debug option \n");
            exit(0);
        }
    }
}
  
/// @brief Configure 파일(JSON) Parser 
/// @param path Configure 파일 경로
/// @return Parse 성공 유무 
int load_config_file(const std::string &path){
 
    if(path.size() <= 0)
    {
        printf("not set config file path \n");
        return -1;
    }
   
    json_handler json(path);
 
    if(!json.available())
    {
        printf("configure file json format error\n");
        return -1;
    }

    auto val = json.get({"connection"});

    config.index = (*val)["index"].GetInt();
    config.is_server = (*val)["is_server"].GetBool();
    config.ip = (*val)["ip"].GetString();
    config.port =  (*val)["port"].GetInt();

    val = json.get({"v2x","rtt"});

    config.rtt_set = (*val)["set"].GetBool();
    config.rtt_interval = (*val)["interval"].GetInt();
    config.rtt_size = (*val)["size"].GetInt();

    val = json.get({"v2x", "ftp"});
    config.ftp.ip = (*val)["ip"].GetString();
    config.ftp.port = (*val)["port"].GetInt();
    config.ftp.id = (*val)["id"].GetString();
    config.ftp.pw = (*val)["pw"].GetString();

    val = json.get({"db"}); 
    config.db.ip = (*val)["ip"].GetString();
    config.db.port = (*val)["port"].GetInt();
    config.db.id = (*val)["id"].GetString();
    config.db.pw =(*val)["pw"].GetString();
    config.db.name = (*val)["name"].GetString();

    val = json.get({"dev"});
 
    config.dev_list.clear();
    if(val->Size() > 0){

        auto array = val->GetArray();

        for (auto it = array.begin(); it != array.end(); it++)
        {
            nr_v2x_dev_info_t dev;
            dev.ip = (*it)["ip"].GetString();
            dev.serial = (*it)["serial"].GetString();
            dev.dev_type = (nr_v2x_dev_type_t)(*it)["type"].GetInt();
            dev.name = (*it)["name"].GetString();
            dev.dev_id = (*it)["devId"].GetInt();
            dev.ver = (*it)["version"].GetInt();
            dev.pos.latitude = (*it)["pos"].GetArray()[0].GetDouble();
            dev.pos.longitude = (*it)["pos"].GetArray()[1].GetDouble();
            dev.pos.altitude = (*it)["pos"].GetArray()[2].GetDouble();

            dev.rtt.set = (*it)["rtt"].GetArray()[0].GetInt() > 0;
            if (dev.rtt.set)
            {
                dev.rtt.ext = (*it)["rtt"].GetArray()[1].GetInt();
                dev.rtt.size = (*it)["rtt"].GetArray()[2].GetInt();
                dev.rtt.interval = (*it)["rtt"].GetArray()[3].GetInt();
            }

            log_print(1, "+ dev[%d] [%d] [%s/%s][%s] [%lf,%lf,%lf] ",
                      dev.dev_id, dev.dev_type, dev.ip.c_str(), dev.serial.c_str(), dev.name.c_str(),
                      dev.pos.latitude, dev.pos.longitude, dev.pos.altitude);

            config.dev_list.push_back(dev);
        }
    }

    return 0;
}


/// @brief 메인 프로그램 실행
/// @param argc 실행 명령 Arguement Count 
/// @param argv 실행 명령 Arguement Value 
/// @return 
int main(int argc , char**argv)
{ 
    parse_options(argc,argv);

    printf("set config path = %s\n",config.path.c_str());

    load_config_file(config.path);

    config.version = SW_VERSION_MAJOR * 1000000 + SW_VERSION_MINOR * 1000 + SW_VERSION_PATCH;

    core_service core(config);

    while(true){  
        sleep_for(1000);
    } 

    return 0;

}