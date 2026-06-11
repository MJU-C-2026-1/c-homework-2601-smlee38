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
int g_seat_start_infos[MAX_RESERVATIONS][ROW_COUNT] = {0};
int g_seat_count_infos[MAX_RESERVATIONS][ROW_COUNT] = {0};

// 2. 함수 원형 선언부

void show_kiosk_screen();                     // 손님용 메인 키오스크 화면을 출력하는 함수
void show_admin_menu();                       // 관리자 전용 메뉴 화면을 출력하는 함수
int check_admin_password();                   // 관리자 비밀번호를 입력받고, 비밀번호가 맞으면 1, 틀리면 0을 반환하는 함수
int run_admin_menu();                         // 관리자 인증 후 시스템 종료 또는 매출 분석 메뉴를 실행하는 함수
int get_ticket_price(char movie_code);        // 영화 코드(A, B, C)를 받아 해당 영화 타입의 티켓 가격을 반환하는 함수
const char* get_movie_name(char movie_code);  // 영화 코드(A, B, C)를 받아 상영 시간대 이름(조조, 일반, 심야)을 반환하는 함수
const char* get_time_name(int time_code);     // 시간대 코드(1, 2, 3)를 받아 상영 시간대 이름(조조, 일반, 심야)을 반환하는 함수
void update_kiosk_system(int people_count);   // 예매 성공 후 발권 번호를 증가시키고, 전체 남은 좌석 수를 감소시키는 함수
int get_row_index(char row);                  // 입력받은 좌석 열 문자(A~E)를 배열 인덱스(0~4)로 바꾸는 함수
void show_row_status();                       // A~E열의 남은 좌석 수와 자동 좌석 배정 방식을 안내하는 함수
int find_avvailable_row(int people_count);    // 일행이 같은 열에 나란히 앉을 수 있는 열을 찾아 인덱스를 반환하는 함수
void show_rows_for_group(int people_count);  // 현재 인원 수가 한 줄로 앉을 수 있는 열 목록을 출력하는 함수
void clear_seat_arrays(int seat_starts[], int seat_counts[]); //좌석 배정 임시 배열의 값을 모두 0으로 초기화하는 함수
void assign_same_row(int row_index, int people_count, int seat_starts[], int seat_counts[]);  // 특정 열에서 왼쪽부터 연속된 좌석을 자동 배정하는 함수
int select_and_assign_seats(int people_count, int seat_starts[], int seat_counts[]); // 원하는 열을 입력받고 상황에 따라 같은 열, 다른 열, 따로 앉기 중 하나로 좌석을 배정하는 함수
void print_seat_info(int seat_starts[], int seat_counts[]); // 좌석 배정 배열을 받아 좌석 정보를 출력하는 함수
void save_reservation(int ticket_number, char movie_code, int seat_starts[], int seat_counts[]); // 예매 성공 정보를 각각의 배열에 저장하는 함수
void make_reservation(); // 영화 코드, 인원, 시간대, 좌석 열을 입력받아 실제 예매를 진행하는 함수
void show_reservation_lst(int numbers[], char movie_codes[], int seat_starts[][ROW_COUNT])


