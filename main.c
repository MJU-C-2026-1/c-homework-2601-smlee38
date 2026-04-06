/* 
  파일이름: main.c
  작 성 자: 60242399_이승민
  하 는 일: 영화 예매 프로그램
*/
#include <stdio.h>
int main()
{
  // [1단계] 변수 선언하기(설계한 8개의 변수)
  char movie_code;          // 영화 코드 (예 : A, B, C)
  char seat_row;            // 좌석 열 (예 : A ~ Z)
  int seat_num;             // 좌석 행 (번호)
  int people_count;         // 인원 수
  int ticket_price;         // 1장 단가
  float discount_rate;       // 할인율 (예 : 0.1)
  int total_price;           // 총액
  float final_price;         // 최종 금액 (할인율이 곱해질 예정으로 실수형 변수 사용)

  // [2단계] 사용자에게 정보 입력받기 (안내 문구 --> 입력)
  printf("=== 영화 예매 시스템 ===\n");

  printf("영화 코드를 입력하세요 (A~Z): ");
  scanf(" %c", &movie_code);

  printf("좌석 열을 입력하세요 (A~Z): ");
  scanf(" %c", &seat_row);

  printf("좌석 번호를 입력하세요: ");
  scanf("%d", &seat_num);

  // [3단계] 연산 수행하기 (순차 구조)
  // 1. 총액 = 단가 * 인원수
  total_price = ticket_price * people_count;

  // 2. 최종 금액 = 총액 - (총액 * 할인율)
  final_price = total_price - (total_price * discount_rate);
  // [4단계] 결과 출력하기 (영수증 포맷팅)
  printf("====================================\n");
  printf("\t 영화 예매 영수증\n");
  printf("====================================\n");

  printf("영화 코드:\t%c\n", movie_code);
  printf("좌석 정보:\t%c열, %d번\n", seat_row, seat_num);
  printf("====================================\n");
  printf("예매가 완료되었습니다. 즐거운 관람 되세요!\n");
  return 0;
}