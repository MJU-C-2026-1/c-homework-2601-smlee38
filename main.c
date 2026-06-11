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

// 예매 데이터를 저장하기 위한 1차원 배열
int g_reservation_numbers[MAX_RESERVATIOS;
char g_movie_codes[MAX_RESERVATIONS];
int g_people_counts[MAX_RESERVATIONS];
double g_final_prices[MAX_RESERVATIONS];

// A~E열의 남은 좌석 수 저장 배열
int g_row_remaining_seats[ROW_COUNT] = {10, 10, 10, 10, 10};

// 좌석 배정 정보를 저장하기 위한 2차원 배열
// 예: g_seat_start_infos[0][2]는 1번째 예매에서 C열의 시작 행을 의미
int g_seat_start_infos[MAX_RESERVATIONS][ROW_COUNT] = {0};
int g_seat_count_infos[MAX_RESERVATIONS][ROW_COUNT] = {0};

