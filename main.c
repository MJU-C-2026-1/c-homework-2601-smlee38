/*
  파일이름 : main.c
  작 성 자 : 60242399_이승민
  하 는 일 : 영화 예매 키오스크 프로그램 마지막 주차
*/

#include <stdio.h>

#define MAX_RESERVATIONS 50
#define ADMIN_PASSWORD 60242399
#define ROW_COUNT 5
#define SEATS_PER_ROW 10

// 1. 전역 변수 선언부
int g_ticket_number = 1000;
int g_remaining_seats = ROW_COUNT * SEATS_PER_ROW;
int g_reservation_count = 0;

// 예매 데이터를 저장하기 위한 1차원 배열
int g_reservation_numbers[MAX_RESERVATIONS];
char g_movie_codes[MAX_RESERVATIONS];
int g_people_counts[MAX_RESERVATIONS];
double g_final_prices[MAX_RESERVATIONS];

// A~E열의 남은 좌석 수 저장 배열
int g_row_remaining_seats[ROW_COUNT] = {10, 10, 10, 10, 10};

// 좌석 배정 정보를 저장하기 위한 2차원 배열
int g_seat_start_infos[MAX_RESERVATIONS][ROW_COUNT] = {0};
int g_seat_count_infos[MAX_RESERVATIONS][ROW_COUNT] = {0};

// 2. 함수 원형 선언부

void show_kiosk_screen();
// 손님용 메인 키오스크 화면을 출력하는 함수

void show_admin_menu();
// 관리자 전용 메뉴 화면을 출력하는 함수

int check_admin_password();
// 관리자 비밀번호를 입력받고, 비밀번호가 맞으면 1, 틀리면 0을 반환하는 함수

int run_admin_menu();
// 관리자 인증 후 시스템 종료 또는 매출 분석 메뉴를 실행하는 함수

int get_ticket_price(char movie_code);
// 영화 코드(A, B, C)를 받아 해당 영화 타입의 티켓 가격을 반환하는 함수

const char* get_movie_name(char movie_code);
// 영화 코드(A, B, C)를 받아 영화 타입 이름(2D, 3D, IMAX)을 반환하는 함수

const char* get_time_name(int time_code);
// 시간대 코드(1, 2, 3)를 받아 상영 시간대 이름(조조, 일반, 심야)을 반환하는 함수

void update_kiosk_system(int people_count);
// 예매 성공 후 발권 번호를 증가시키고, 전체 남은 좌석 수를 감소시키는 함수

int get_row_index(char row);
// 입력받은 좌석 열 문자(A~E)를 배열 인덱스(0~4)로 바꾸는 함수

void show_row_status();
// A~E열의 남은 좌석 수와 자동 좌석 배정 방식을 안내하는 함수

int find_available_row(int people_count);
// 일행이 같은 열에 나란히 앉을 수 있는 열을 찾아 인덱스를 반환하는 함수

void show_rows_for_group(int people_count);
// 현재 인원 수가 한 줄로 앉을 수 있는 열 목록을 출력하는 함수

void clear_seat_arrays(int seat_starts[], int seat_counts[]);
// 좌석 배정 임시 배열의 값을 모두 0으로 초기화하는 함수

void assign_same_row(int row_index, int people_count, int seat_starts[], int seat_counts[]);
// 특정 열에서 왼쪽부터 연속된 좌석을 자동 배정하는 함수

void assign_split_seats(int people_count, int seat_starts[], int seat_counts[]);
// 한 열에 같이 앉을 수 없을 때 여러 열에 나누어 좌석을 자동 배정하는 함수

int select_and_assign_seats(int people_count, int seat_starts[], int seat_counts[]);
// 원하는 열을 입력받고 상황에 따라 같은 열, 다른 열, 따로 앉기 중 하나로 좌석을 배정하는 함수

void print_seat_info(int seat_starts[], int seat_counts[]);
// 좌석 배정 배열을 받아 좌석 정보를 출력하는 함수

void save_reservation(int ticket_number, char movie_code, int seat_starts[], int seat_counts[], int people_count, double final_price);
// 예매 성공 정보를 각각의 배열에 저장하는 함수

void make_reservation();
// 영화 코드, 인원, 시간대, 좌석 열을 입력받아 실제 예매를 진행하는 함수

void show_reservation_list(int numbers[], char movie_codes[], int seat_starts[][ROW_COUNT], int seat_counts[][ROW_COUNT], int people_counts[], double final_prices[], int count);
// 배열을 매개변수로 전달받아 인덱스 방식(arr[i])으로 예매 내역을 조회하는 함수

void analyze_sales(double *final_prices, int *people_counts, int count);
// 포인터 연산(*(ptr + i))으로 배열을 순회하여 총매출과 총 관람 인원을 분석하는 함수

//3. main 함수 : 키오스크 무한 루프 메인 메뉴
int main()
{
  int choice;
  int is_program_running = 1;

  while(is_program_running)
  {
    show_kiosk_screen();
    scanf("%d", &choice);

    if(choice == 1)
    {
      make_reservation();
    }
    else if(choice == 2)
    {
      show_reservation_list(g_reservation_numbers, g_movie_codes, g_seat_start_infos, g_seat_count_infos, g_people_counts, g_final_prices, g_reservation_count);
    }
    else if(choice == 0)
    {
      is_program_running = run_admin_menu();
    }
    else
    {
      printf("\n[안내] 잘못된 입력입니다. 메뉴를 다시 선택해주세요.\n");
    }
  }
  return 0;
}

// 기능 1: 손님용 키오스크 첫 화면 출력
void show_kiosk_screen()
{
  printf("\n======================================================");
  printf("\n              MJU 영화 예매 전용 키오스크               ");
  printf("\n======================================================\n");
  printf("1. 영화 티켓 예매하기 (남은 좌석 : %d석)\n", g_remaining_seats);
  printf("2. 예매 내역 조회하기\n");
  printf("0. 관리자 메뉴\n");
  printf("========================================================\n");
  printf("메뉴 번호를 입력하세요: ");
}

// 기능 2: 관리자 메뉴 화면 출력
void show_admin_menu()
{
  printf("\n=======================================================");
  printf("\n                 [관리자 전용 메뉴                     ]");
  printf("\n1. 시스템 셧다운\n");
  printf("2. 매출 및 관람 인원 분석하기\n");
  printf("3. 손님용 메인 화면으로 돌아가기\n");
  printf("=========================================================\n");
  printf("관리자 메뉴 번호를 입력하세요 : ");
}

// 기능 3: 관리자 비밀번호 확인
int check_admin_password()
{
  int input_password;

  printf("\n[관리자 인증] 비밀번호를 입력하세요: ");
  scanf("%d", &input_password);

  if (input_password == ADMIN_PASSWORD)
  {
    printf("[관리자 인증] 인증에 성공했습니다. \n");
    return 1;
  }
  else
  {
    printf("[관리자 인증] 비밀번호가 틀렸습니다. 손님용 메인 화면으로 돌아갑니다. \n");
    return 0;
  }
}

// 기능 4: 관리자 메뉴 실행
int run_admin_menu()
{
  int admin_choice;

  if (check_admin_password() == 0)
  {
    return 1;
  }

  while (1)
  {
    show_admin_menu();
    scanf("%d", &admin_choice);

    if (admin_choice == 1)
    {
      printf("\n[시스템] 키오스크 프로그램을 종료합니다.\n");
      return 0;
    }
    else if (admin_choice == 2)
    {
      analyze_sales(g_final_prices, g_people_counts, g_reservation_count);
    }
    else if(admin_choice == 3)
    {
      printf("\n[안내] 손님용 메인 화면으로 돌아갑니다. \n");
      return 1;
    }
    else
    {
      printf("\n[안내] 잘못된 관리자 메뉴 번호입니다. 다시 선택해주세요.\n");
    }
  }
}

// 기능 5: 영화 코드를 받아 단가를 반환하는 함수
int get_ticket_price(char movie_code)
{
  switch (movie_code)
  {
    case 'A':
    case 'a':
    {
      return 10000;
    }
    case 'B':
    case 'b':
    {
      return 13000;
    }
    case 'C':
    case 'c':
    {
      return 18000;
    }
    default:
    {
      return 0;
    }
  }
}

// 기능 6: 영화 코드에 해당하는 영화 타입 이름 반환
const char* get_movie_name(char movie_code)
{
  switch (movie_code)
  {
    case 'A':
    case 'a':
    {
      return "2D";
    }
    case 'B':
    case 'b':
    {
      return "3D";
    }
    case 'C':
    case 'c':
    {
      return "IMAX";
    }
    default:
    {
      return "알 수 없음";
    }
  }
}

// 기능 7: 시간 코드에 해당하는 시간대 이름 반환
const char* get_time_name(int time_code)
{
  switch (time_code)
  {
    case 1:
    {
      return "조조";
    }
    case 2:
    {
      return "일반";
    }
    case 3:
    {
      return "심야";
    }
    default:
    {
      return "알 수 없음";
    }
  }
}

// 기능 8: 예매 성공 시 시스템 데이터 변경
void update_kiosk_system(int people_count)
{
  g_ticket_number += 1;
  g_remaining_seats -= people_count;
}

// 기능 9: 좌석 열 문자를 배열 인덱스로 변환
int get_row_index(char row)
{
  if (row >= 'A' && row <= 'E')
  {
    return row - 'A';
  }
  else if (row >= 'a' && row <= 'e')
  {
    return row - 'a';
  }
  else
  {
    return -1;
  }
}

/// 기능 10: 각 열의 남은 좌석 수 출력 
void show_row_status()
{
  int i;
  int next_seat;

  printf("\n============================================\n");
  printf("              [좌석 열 선택 안내]             \n");
  printf("============================================\n");
  printf("[안내] 본 키오스크는 좌석 번호를 직접 선택하지 않습니다.\n");
  printf("[안내] 선택한 열에서 가장 왼쪽 좌석부터 자동으로 나란히 배정됩니다.\n");
  printf("[안내] 각 열의 '(n행부터 착석)' 표시는 다음으로 배정될 시작 좌석입니다.\n");
  printf("[안내] 일행이 있는 경우 가능한 한 같은 열에 연속 좌석으로 배정됩니다.\n");
  printf("--------------------------------------------\n");

  for (i = 0; i < ROW_COUNT; i++)
  {
    if (g_row_remaining_seats[i] > 0)
    {
      next_seat = SEATS_PER_ROW - g_row_remaining_seats[i] + 1;
      printf(" %c열 남은 좌석: %d석 (%d행부터 착석)\n",
             'A' + i, g_row_remaining_seats[i], next_seat);
    }
    else
    {
      printf(" %c열 남은 좌석: 0석 (매진)\n", 'A' + i);
    }
  }

  printf("============================================\n");
}

// 기능 11: 일행이 같은 열에 앉을 수 있는 열 찾기
int find_available_row(int people_count)
{
  int i;

  for(i=0; i<ROW_COUNT; i++)
  {
    if (g_row_remaining_seats[i] >= people_count)
    {
      return i;
    }
  }

  return -1;
}

// 기능 12: 같은 열에 나란히 앉을 수 있는 열 목록 출력
void show_rows_for_group(int people_count)
{
  int i;

  printf("[안내] 현재 인원이 같은 열에 나란히 앉을 수 있는 열: ");

  for (i=0; i<ROW_COUNT; i++)
  {
    if (g_row_remaining_seats[i] >= people_count)
    {
      printf("%c열 ", 'A' + i);
    }
  }
  printf("\n");
}

// 기능 13: 좌석 배정 임시 배열 초기화
void clear_seat_arrays(int seat_starts[], int seat_counts[])
{
  int i;

  for (i=0; i<ROW_COUNT; i++)
  {
    seat_starts[i] = 0;
    seat_counts[i] = 0;
  }
}

// 기능 14: 특정 열에 연속 좌석 배정
void assign_same_row(int row_index, int people_count, int seat_starts[], int seat_counts[])
{
  int start_seat;

  start_seat = SEATS_PER_ROW - g_row_remaining_seats[row_index] + 1;

  seat_starts[row_index] = start_seat;
  seat_counts[row_index] = people_count;

  g_row_remaining_seats[row_index] -= people_count;
}

// 기능 15: 여러 열에 나누어 좌석 배정
void assign_split_seats(int people_count, int seat_starts[], int seat_counts[])
{
  int i;
  int remaining_people = people_count;
  int take_count;
  int start_seat;

  for (i=0; i<ROW_COUNT && remaining_people > 0; i++)
  {
    if (g_row_remaining_seats[i] <= 0)
    {
      continue;
    }

    if (g_row_remaining_seats[i] >= remaining_people)
    {
      take_count = remaining_people;
    }
    else
    {
      take_count = g_row_remaining_seats[i];
    }

    start_seat = SEATS_PER_ROW - g_row_remaining_seats[i] + 1;

    seat_starts[i] = start_seat;
    seat_counts[i] = take_count;

    g_row_remaining_seats[i] -= take_count;
    remaining_people -= take_count;
  }
}

//기능 16:좌석 정보 출력
void print_seat_info(int seat_starts[], int seat_counts[])
{
  int i;
  int end_seat;
  int is_first = 1;

  for (i = 0; i < ROW_COUNT; i++)
  {
    if (seat_counts[i] > 0)
    {
      if (is_first == 0)
      {
        printf(" / ");
      }

      end_seat = seat_starts[i] + seat_counts[i] - 1;

      if (seat_counts[i] == 1)
      {
        printf("%c열 %d행", 'A' + i, seat_starts[i]);
      }
      else
      {
        printf("%c열 %d행 ~ %d행", 'A' + i, seat_starts[i], end_seat);
      }

      is_first = 0;
    }
  }
}

// 기능 17: 좌석 열 선택 및 좌석 자동 배정
int select_and_assign_seats(int people_count, int seat_starts[], int seat_counts[])
{
  char seat_row;
  int row_index;
  int menu_choice;
  int available_row;

  clear_seat_arrays(seat_starts, seat_counts);
  show_row_status();

  printf("[안내] 원하는 좌석 열을 입력하세요 (A~E): ");
  scanf(" %c", &seat_row);

  row_index = get_row_index(seat_row);

  if (row_index == -1)
  {
    printf("\n[오류] 존재하지 않는 좌석 열입니다. 초기 화면으로 돌아갑니다. \n");
    return 0;
  }

  if (g_row_remaining_seats[row_index] >= people_count)
  {
    assign_same_row(row_index, people_count, seat_starts, seat_counts);
    printf("\n[좌석 배정] 선택하신 %c열에 나란히 배정되었습니다. \n", 'A' + row_index);
    return 1;
  }
 printf("\n[안내] 선택하신 %c열에는 남은 좌석이 %d석뿐입니다.\n",
         'A' + row_index, g_row_remaining_seats[row_index]);
  printf("[안내] 현재 인원 %d명이 %c열에 모두 같이 앉을 수 없습니다.\n",
         people_count, 'A' + row_index);

  available_row = find_available_row(people_count);

  if (available_row != -1)
  {
    printf("\n[안내] 다른 열에는 일행이 모두 같이 앉을 수 있는 자리가 있습니다.\n");
    show_rows_for_group(people_count);
    printf("1. 다른 열에 같이 앉기\n");
    printf("0. 예매 취소 후 메인 화면으로 돌아가기\n");
    printf("메뉴를 선택하세요: ");
    scanf("%d", &menu_choice);

    if (menu_choice == 1)
    {
      show_rows_for_group(people_count);
      printf("[안내] 같이 앉을 다른 열을 입력하세요 (A~E): ");
      scanf(" %c", &seat_row);

      row_index = get_row_index(seat_row);

      if (row_index == -1 || g_row_remaining_seats[row_index] < people_count)
      {
        printf("\n[오류] 해당 열에는 일행이 같이 앉을 수 없습니다. 초기 화면으로 돌아갑니다.\n");
        return 0;
      }

      assign_same_row(row_index, people_count, seat_starts, seat_counts);
      printf("\n[좌석 배정] 선택하신 %c열에 나란히 배정되었습니다.\n", 'A' + row_index);
      return 1;
    }
    else
    {
      printf("\n[안내] 예매를 취소하고 메인 화면으로 돌아갑니다.\n");
      return 0;
    }
  }
  else
  {
    printf("\n[안내] 현재 어느 한 열에도 %d명이 나란히 앉을 수 있는 좌석은 없습니다.\n", people_count);

    if (g_remaining_seats >= people_count)
    {
      printf("[안내] 다만 전체 남은 좌석 수는 충분하므로, 여러 열에 나누어 앉을 수 있습니다.\n");
      printf("2. 따로 앉기\n");
      printf("0. 예매 취소 후 메인 화면으로 돌아가기\n");
      printf("메뉴를 선택하세요: ");
      scanf("%d", &menu_choice);

      if (menu_choice == 2)
      {
        assign_split_seats(people_count, seat_starts, seat_counts);
        printf("\n[좌석 배정] 여러 열에 나누어 배정되었습니다.\n");
        return 1;
      }
      else
      {
        printf("\n[안내] 예매를 취소하고 메인 화면으로 돌아갑니다.\n");
        return 0;
      }
    }
    else
    {
      printf("[오류] 전체 남은 좌석 수도 부족합니다. 초기 화면으로 돌아갑니다.\n");
      return 0;
    }
  }
}

// 기능 18: 예매 성공 데이터를 배열에 저장
void save_reservation(int ticket_number, char movie_code, int seat_starts[], int seat_counts[], int people_count, double final_price)
{
  int index = g_reservation_count;
  int i;

  g_reservation_numbers[index] = ticket_number;
  g_movie_codes[index] = movie_code;
  g_people_counts[index] = people_count;
  g_final_prices[index] = final_price;

  for(i=0; i<ROW_COUNT; i++)
  {
    g_seat_start_infos[index][i] = seat_starts[i];
    g_seat_count_infos[index][i] = seat_counts[i];
  }

  g_reservation_count++;
}

// 기능 19: 실제 예매 프로세스
void make_reservation()
{
  char movie_code;
  int seat_starts[ROW_COUNT];
  int seat_counts[ROW_COUNT];
  int ticket_price = 0;
  int total_price;
  double final_price;
  double teen_total;
  double senior_total;
  double adult_total;

  int teen_count = 0, adult_count = 0, people_count = 0, senior_count = 0;
  int time_code;
  double time_discount = 0.0;
  double teen_rate = 0.0, adult_rate = 0.0, senior_rate = 0.0;

  if (g_remaining_seats <= 0)
  {
    printf("\n[안내] 죄송합니다. 해당 상영 회차는 매진되었습니다.\n");
    return;
  }

  if (g_reservation_count >= MAX_RESERVATIONS)
  {
    printf("\n[안내] 예매 저장 공간이 가득 찼습니다. 더 이상 예매 데이터를 저장할 수 없습니다.\n");
    return;
  }

  printf("\n[안내] 영화 코드를 입력하세요 (A: 2D, B: 3D, C: IMAX) : ");
  scanf(" %c", &movie_code);

  ticket_price = get_ticket_price(movie_code);
  if (ticket_price == 0)
  {
    printf("\n[오류] 존재하지 않는 영화 코드입니다. 초기 화면으로 돌아갑니다. \n");
    return;
  }
    printf("\n--- 관람 인원 선택 (현재 예매 가능 좌석 : %d석) ---\n", g_remaining_seats);
  printf("청소년(만 19세 미만) 수 : ");
  scanf("%d", &teen_count);

  printf("일반(만 19~64세) 수 : ");
  scanf("%d", &adult_count);

  printf("경로(만 65세 이상) 수 : ");
  scanf("%d", &senior_count);

  people_count = teen_count + adult_count + senior_count;

  if (people_count <= 0)
  {
    printf("\n[오류] 1명 이상 선택하셔야 예매가 가능합니다. 초기 화면으로 돌아갑니다.\n");
    return;
  }

  if (people_count > g_remaining_seats)
  {
    printf("\n[오류] 좌석이 부족합니다. (선택 인원 : %d명 / 남은 좌석 : %d석)\n", people_count, g_remaining_seats);
    printf("초기 화면으로 돌아갑니다. 인원수를 다시 조정해주세요.\n");
    return;
  }

  printf("\n[안내] 상영 시간대를 선택하세요 (1: 조조, 2: 일반, 3: 심야) : ");
  scanf("%d", &time_code);

  if (time_code < 1 || time_code > 3)
  {
    printf("\n[오류] 잘못된 시간대입니다. 초기 화면으로 돌아갑니다.\n");
    return;
  }

  if (select_and_assign_seats(people_count, seat_starts, seat_counts) == 0)
  {
    return;
  }

  switch (time_code)
  {
    case 1:
    case 3:
      time_discount = 0.2;
      break;

    case 2:
      time_discount = 0.0;
      break;
  }

  teen_rate = 0.2 + time_discount;
  senior_rate = 0.5 + time_discount;
  adult_rate = time_discount;

  if (teen_rate > 1.0)
  {
    teen_rate = 1.0;
  }
  if (senior_rate > 1.0)
  {
    senior_rate = 1.0;
  }
  if (adult_rate > 1.0)
  {
    adult_rate = 1.0;
  }

  teen_total = (ticket_price * teen_count) * (1.0 - teen_rate);
  senior_total = (ticket_price * senior_count) * (1.0 - senior_rate);
  adult_total = (ticket_price * adult_count) * (1.0 - adult_rate);

  total_price = ticket_price * people_count;
  final_price = teen_total + senior_total + adult_total;

  update_kiosk_system(people_count);
  save_reservation(g_ticket_number, movie_code, seat_starts, seat_counts, people_count, final_price);

  printf("============================================\n");
  printf("          [모바일 티켓 / 영수증]          \n");
  printf("============================================\n");
  printf(" 발권 번호:\tNO.%d\n", g_ticket_number);
  printf(" 영화 코드:\t%c 타입(%s)\n", movie_code, get_movie_name(movie_code));
  printf(" 상영 시간:\t%s\n", get_time_name(time_code));
  printf(" 좌석 정보:\t");
  print_seat_info(seat_starts, seat_counts);
  printf("\n");
  printf("--------------------------------------------\n");
  printf("[결제 세부 내역]\n");

  if (teen_count > 0)
  {
    printf("  청소년:\t%d명 (할인 %.0f%% 적용)\n", teen_count, teen_rate * 100);
  }
  if (adult_count > 0)
  {
    printf("  일 반:\t%d명 (할인 %.0f%% 적용)\n", adult_count, adult_rate * 100);
  }
  if (senior_count > 0)
  {
    printf("  경 로:\t%d명 (할인 %.0f%% 적용)\n", senior_count, senior_rate * 100);
  }

  printf("--------------------------------------------\n");
  printf(" 정상 금액:\t%d원\n", total_price);
  printf(" 최종 결제액:\t%.0f원\n", final_price);
  printf("============================================\n");
  printf(" 결제가 완료되었습니다. 티켓을 챙겨주세요.\n");
  printf(" (예매 데이터와 좌석 배정 정보가 배열에 저장되었습니다.)\n");
}

  // 기능 20: 예매 내역 조회
void show_reservation_list(int numbers[], char movie_codes[], int seat_starts[][ROW_COUNT], int seat_counts[][ROW_COUNT], int people_counts[], double final_prices[], int count)
{
  int i;

  if (count == 0)
  {
    printf("\n[조회] 아직 저장된 예매 내역이 없습니다.\n");
    return;
  }

  printf("\n============================================\n");
  printf("              [예매 내역 조회]              \n");
  printf("============================================\n");

  for (i = 0; i < count; i++)
  {
    printf("%d번째 예매\n", i + 1);
    printf("  발권 번호 : NO.%d\n", numbers[i]);
    printf("  영화 타입 : %s\n", get_movie_name(movie_codes[i]));
    printf("  좌석 정보 : ");
    print_seat_info(seat_starts[i], seat_counts[i]);
    printf("\n");
    printf("  관람 인원 : %d명\n", people_counts[i]);
    printf("  결제 금액 : %.0f원\n", final_prices[i]);
    printf("--------------------------------------------\n");
  }
}
// 기능 21: 매출 및 관람 인원 분석
void analyze_sales(double *final_prices, int *people_counts, int count)
{
  int i;
  double total_sales = 0.0;
  int total_people = 0;
  double average_sales = 0.0;

  if (count == 0)
  {
    printf("\n[분석] 아직 분석할 예매 데이터가 없습니다.\n");
    return;
  }

  for (i = 0; i < count; i++)
  {
    total_sales += *(final_prices + i);
    total_people += *(people_counts + i);
  }

  average_sales = total_sales / count;

  printf("\n============================================\n");
  printf("             [매출 및 인원 분석]             \n");
  printf("============================================\n");
  printf(" 총 예매 건수        : %d건\n", count);
  printf(" 총 관람 인원        : %d명\n", total_people);
  printf(" 총 매출액           : %.0f원\n", total_sales);
  printf(" 예매 1건당 평균 금액 : %.0f원\n", average_sales);
  printf(" 남은 전체 좌석 수    : %d석\n", g_remaining_seats);
  printf("--------------------------------------------\n");
  printf(" A열 남은 좌석       : %d석\n", g_row_remaining_seats[0]);
  printf(" B열 남은 좌석       : %d석\n", g_row_remaining_seats[1]);
  printf(" C열 남은 좌석       : %d석\n", g_row_remaining_seats[2]);
  printf(" D열 남은 좌석       : %d석\n", g_row_remaining_seats[3]);
  printf(" E열 남은 좌석       : %d석\n", g_row_remaining_seats[4]);
  printf("============================================\n");
}