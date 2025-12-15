5G-NR-V2X 다중 RSU 연결관리 및 정보 연계 인터페이스 API 소프트웨어 

1. 소프트웨어 목적
   -  
 * 본 소프트웨어 코드는 5G-NR-V2X 연구과제를 위한 목적으로 개발된 소프트웨어입니다.
 * 본 소프트웨어 코드는 본 5G-NR-V2X 연구과제 내 구축되는 RSU 장치에 대하여 여러 RSU가 TCP 인터페이스로 연결 시, 연결 상태를 관리하고 연결 요청 및 해제를 처리하기 위한 소프트웨어입니다.
2. 소프트웨어 기능
   -
  * 자체 IP / 외산 IP 기반 RSU 연결 접속 (TCP 클라이언트) 방식에 대하여 IP 주소 기반 ID 맵핑 처리
  * IP 주소 기반 ID 맵핑을 위한 RSU Configure 파일 정의 (JSON)
  * Configure 파일 Load 및 파서 핸들링
  * RSU 연결/해제 시 이벤트 처리
  * RSU로부터 V2X Rx 메시지 API 이벤트 처리 
  * RSU로부터 V2X Extension Rx 메시지 API 이벤트 처리
  * RSU로 V2X 메시지 전송 결과 이벤트 처리 
  * RSU로 V2X Extension Tx 메시지 전송 결과 이벤트 처리
  * RSU업데이트 FTP 요청에 대한 이벤트 처리
  * 연결 RSU 상태 목록 조회
    
