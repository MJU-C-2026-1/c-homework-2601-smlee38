/* 
  파일이름: main.c
  작 성 자: 60242399_이승민
  하 는 일: 영화 예매 프로그램 3주차
*/

#include <stdio.h>

//1. 전역 변수 선언부
int g_ticket_number = 1000;     // 고유 발권 번호 (예매마다 1씩 증가하게)
int g_remaining_seats = 30;     // 샹영관 잔여 좌석 수 (초기 30석으로 설정)

//2. 함수 원형 선언부
void show_kiosk_screen();
int get_ticket_price(char movie_code);
void update_kiosk_system(int people_count);
void make_reservation();

//3. main 함수 (키오스크 무한 루프 뼈대)
int main()
{
  int choice;
  while (1)
  {
    show_kiosk_screen();
    scanf("%d", &choice);

    if (choice == 1)
    {
      make_reservation();
    }
    else if (choice == 0) // 관리자용 종료 버튼
    {
      printf("\n[시스템] 키오스크 프로그램을 종료합니다.\n");
      break;
    }
    else
    {
      printf("\n[안내] 잘못된 입력입니다. 화면을 다시 터치해주세요.\n");
    }
  }
  return 0;
}

//4. 함수 정의부

//기능 1: 키오스크 첫 화면 출력(현재 잔여 좌석 현황 실시간 표시)
void show_kiosk_screen()
{
  printf("\n============================================");
  printf("\n          MJU 영화 예매 전용 키오스크         ");
  printf("\n============================================\n");
  printf("1. 영화 티켓 예매하기 (남은 좌석 : %d석)\n", g_remaining_seats);
  printf("0. 시스템 셧다운 (관리자용, 관리자 외 선택 절대 금지)\n");
  printf("============================================\n");
  printf("1번을 눌러 영화 예매를 진행하세요: ");
}

//기능 2: 영화 코드를 받아 단가를 반환하는 함수
int get_ticket_price(char movie_code)
{
  switch (movie_code)
  {
    case 'A':
    case 'a':
    {
      return 10000; //2D
    }
    case 'B':
    case 'b':
    {
      return 13000; //3D
    }
    case 'C':
    case 'c':
    {
      return 18000; //IMAX
    }
    default:
    {
      return 0; //잘못된 코드일 경우 0 반환
    }
  }
}

//기능 3: 예매 성공 시 시스템 데이터(전역 변수)들을 변경하는 함수
void update_kiosk_system(int people_count)
{
  g_ticket_number += 1;
  g_remaining_seats -= people_count;
}

//기능 4: 실제 예매 프로세스를 진행하는 메인 로직 함수
void make_reservation()
{
  //이미 매진된 경우 예매 진입 차단
  if (g_remaining_seats <= 0)
  {
    printf("\n[안내] 죄송합니다. 해당 상영 회차는 매진되었습니다.\n");
    return;
  }

  // 지역 변수 선언
  char movie_code;
  char seat_row;
  int seat_num;
  int ticket_price = 0;
  int total_price;
  double final_price;

  int teen_count = 0, adult_count = 0, senior_count = 0, people_count = 0;
  int time_code;
  double time_discount = 0.0;
  double teen_rate = 0.0, adult_rate = 0.0, senior_rate = 0.0;

  //정보 입력받기
  printf("\n[안내] 영화 코드를 입력하세요 (A: 2D, B: 3D, C: IMAX) :");
  scanf(" %c", &movie_code);

  //함수 호출로 단가 확인
  ticket_price = get_ticket_price(movie_code);
  if (ticket_price == 0)
  {
    printf("\n[오류] 존재하지 않는 영화 코드입니다. 초기 화면으로 돌아갑니다.\n");
    return;  
  }

  printf("[안내] 원하시는 좌석 열(A~Z)을 입력하세요 :");
  scanf(" %c", &seat_row);

  printf("[안내] 시작 좌석 번호를 입력하세요 : ");
  scanf("%d", &seat_num);

  printf("\n---관람 인원 선택 (현재 예매 가능 좌석 : %d석) ---\n", g_remaining_seats);
  printf("청소년(만 19세 미만) 수 :");
  scanf("%d", &teen_count);

  printf("일반(만 19~64세) 수 :");
  scanf("%d", &adult_count);

  printf("경로(만 65세 이상) 수 :");
  scanf("%d", &senior_count);

  //총 인원 확인 및 예외 처리
  people_count = teen_count + adult_count + senior_count;
  if (people_count <= 0)
  {
    printf("\n[오류] 1명 이상 선택하셔야 예매가 가능합니다. 초기 화면으로 돌아갑니다.");
    return;
  }

  //[예외 처리] 선택된 인원이 남은 좌석보다 많은 경우 예매 중단
  if (people_count > g_remaining_seats)
  {
    printf("\n[오류] 좌석이 부족합니다. (선택 인원 : %d명 / 남은 좌석 : %d석)\n", people_count, g_remaining_seats);
    printf("초기 화면으로 돌아갑니다. 인원수를 다시 조정해주세요.\n");
    return;
  }

  printf("\n[안내] 상영 시간대를 선택하세요 (1: 조조, 2: 일반, 3: 심야) :");
  scanf("%d", &time_code);

  if (time_code < 1 || time_code > 3)
  {
    printf("\n[오류] 잘못된 시간대입니다. 초기 화면으로 돌아갑니다.\n");
    return;
  }

  //할인율 연산
  switch (time_code)
  {
    case 1:
    case 3:
    {
      time_discount = 0.2;
      break;
    }
    case 2:
    {
      time_discount = 0.0;
      break;
    }
  }

  teen_rate = 0.2 + time_discount;
  senior_rate = 0.5 + time_discount;
  adult_rate = 0.0 + time_discount;

  //한도 초과 방지
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

  //최종 금액 산출
  double teen_total = (ticket_price * teen_count) * (1.0 - teen_rate);
  double senior_total = (ticket_price * senior_count) * (1.0 - senior_rate);
  double adult_total = (ticket_price * adult_count) * (1.0 - adult_rate);

  total_price = ticket_price * people_count;
  final_price = teen_total + senior_total + adult_total;

  //예매 성공 처리: 전역 변수 업데이트 함수 호출 (발권번호 증가, 좌석 차감)
  update_kiosk_system(people_count);

  //결과 출력 (종이 영수증 출력 시뮬레이션)
  printf("============================================\n");
  printf("          [모바일 티켓 / 영수증]          \n");
  printf("============================================\n");
  printf(" 발권 번호:\tNO.%d\n", g_ticket_number);
  printf(" 영화 코드:\t%c 타입\n", movie_code);
  printf(" 좌석 정보:\t%c열, %d번 ~ (총 %d석)\n", seat_row, seat_num, people_count);
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
  printf(" 최종 결재액:\t%.0f원\n", final_price);
  printf("============================================\n");
  printf(" 결제가 완료되었습니다. 티켓을 챙겨주세요.\n");
  printf(" (잠시 후 초기 화면으로 돌아갑니다...)\n");
}
//

