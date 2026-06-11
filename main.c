/*
  파일이름 : main.c
  작 성 자 : 60242399_이승민
  하 는 일 : 영화 예매 키오스크 프로그램 마지막 주차
*/

#include <stdio.h>

#define MAX_RESERVATION 50
#define ADMIN_PASSWORD 60242399
#define ROW_COUNT 5
#define SEATS_PER_ROW 10

// 1. 전역 변수 선언부
int g_ticket_number = 1000;
int g_remaining_seats = ROW_COUNT * SEATS_PER_ROW;
int g_reservation_count = 0;

