/* 
  파일이름: main.c
  작 성 자: 60242399_이승민
  하 는 일: 영화 예매 프로그램
*/

#include <stdio.h>

int main()
{
  // 1단계 변수 선언하기
  char movie_code;
  char seat_row;
  int seat_num;
  int ticket_price = 0;              // 1장 단가 (초기화)

  int total_price;                  // 할인 전 총액
  double final_price;               // 최종 결제 금액

  int teen_count = 0;               // 청소년(만 19세 미만) 수
  int adult_count = 0;              // 일반(만 19~64세) 수
  int senior_count = 0;             // 경로(만 65세 이상) 수
  int people_count = 0;             // 총 인원 수

  // 조건 및 할인용 변수
  int time_code;                    // 시간대 코드 (1:조조, 2:일반, 3:심야)
  double time_discount = 0.0;       // 시간대 기본 할인율

  // 각 연령대별 최종 할인율
  double teen_rate = 0.0;
  double adult_rate = 0.0;
  double senior_rate = 0.0;

  // 2단계 사용자에게 정보 입력받기
  printf("=== 영화 예매 시스템 ===\n");

  printf("영화 코드를 입력하세요 (A:2D, B:3D, C:IMAX) :");
  scanf(" %c", &movie_code);

  printf("좌석 열을 입력하세요 :");
  scanf(" %c", &seat_row);

  printf("시작 좌석 번호를 입력하세요 :");
  scanf("%d", &seat_num);

  printf("\n--- 관림 인원 정보 ---\n");
  printf("청소년(만 19세 미만)은 몇명입니까? : ");
  scanf("%d", &teen_count);

  printf("일반(만 19~64세)은 몇 명입니까? :");
  scanf("%d", &adult_count);

  printf("경로(만 65세 이상)는 몇 명입니까? :");
  scanf("%d", &senior_count);

  printf("\n시간대를 선택하세요 (1:조조, 2:일반, 3:심야)");
  scanf("%d", &time_code);

  //총 인원수 계산
  people_count = teen_count + adult_count + senior_count;

  // 3단계 연산 수행하기 (조건문 흐름 제어)

  // 1. 영화 코드에 따른 기본 단가 설정
  switch  (movie_code)
  {
    case 'A':
    case 'a':
    ticket_price = 10000;
    break;
    case 'B':
    case 'b':
    ticket_price = 13000;
    break;
    case 'C':
    case 'c':
    ticket_price = 18000;
    break;
    default:
    printf("\n[오류] 잘못된 영화 코드를 입력하셨습니다.\n");
    break;
  }

  // 2. 예외 처리 : 시간대 오류 또는 인원이 0명인 경우
  if (time_code < 1 || time_code > 3)
  {
    printf("\n [오류] 잘못된 시간대를 입력하셨습니다.\n");
    ticket_price = 0;
  }
  if (people_count <= 0)
  {
    printf("\n [오류] 관람 인원이 최소 1명 이상이어야 합니다.\n");
    ticket_price = 0;
  }

  // 3. 정상적으로 예매가 진행된 경우에만 아래 코드 실행
  if (ticket_price > 0)
  {
    // 시간대에 따른 공통 할인율 설정
    switch (time_code)
    {
      case 1:
      case 3:
      time_discount = 0.2; // 조조, 심야 20%
      break;
      case 2:
      time_discount = 0.0;
      break;
    }
  // 각 그룹별 할인율 계산 (나이 할인 + 시간대 할인)
  teen_rate = 0.2 + time_discount;            // 청소년 기본 20%
  senior_rate = 0.5 + time_discount;          // 경로 기본 50%
  adult_rate = 0.0 + time_discount;           // 일반 0%

  //할인율 한도 100%(1.0) 초과 방지
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
  // 최종 금액 산출 (각 그룹별 인원 * 단가 * (1- 할인율))
  double teen_total = (ticket_price * teen_count) * (1.0 - teen_rate);
  double senior_total = (ticket_price * senior_count) * (1.0 - senior_rate);
  double adult_total = (ticket_price * adult_count) * (1.0 - adult_rate);

  total_price = ticket_price * people_count;
  final_price = teen_total + senior_total + adult_total;

  // 4단계 결과 출력하기 (영수증 포맷팅)
  printf("\n==========================================\n");
  printf("\t 영화 예매 영수증\n");
  printf("============================================\n");
  printf("영화 코드:\t%c\n", movie_code);
  printf("좌석 정보:\t%c열, %d번 ~ (총 %d석)\n", seat_row, seat_num, people_count);
  printf("--------------------------------------------\n");
  printf("[관람 인원 및 세부 내역]\n");
  if (teen_count >0)
  {
    printf(" 청소년:\t%d명 (적용 할인 %.0f%%)\n", teen_count, teen_rate * 100);
  }
  if (adult_count > 0)
  {
    printf(" 일반:\t\t%d명 (적용할인 %.0f%%)\n", adult_count, adult_rate * 100);
  }
  if (senior_count > 0)
  {
    printf(" 경로:\t\t%d명 (적용 할인 %.0f%%)\n", senior_count, senior_rate * 100);
  }
  printf("--------------------------------------------\n");
  printf("할인 전 총액:\t%d원\n", total_price);
  printf("최종 결제 금액:\t%.0f원\n", final_price);
  printf("============================================\n");
  printf("예매가 완료되었습니다. 즐거 관람 되세요!\n");
  }
  else
  {
    // 오류로 인해 ticket_price가 0이 된 경우
    printf("예매가 취소되었습니다. 처음부터 다시 시도해주세요.\n");
  }

  return 0;
}