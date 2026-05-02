/* 
  파일이름: main.c
  작 성 자: 60242399_이승민
  하 는 일: 영화 예매 프로그램
*/

#include <stdio.h>

int main()
{
  // [1단계] 변수 선언하기
  char movie_code;            // 영화 코드  (예 : A, B, C)
  char seat_row;              // 좌석 열    (예 : A ~ Z)
  int seat_num;               // 좌석 행    (번호)
  int people_count;           // 인원 수
  int ticket_price = 0;       // 1장 단가   (초기화)
  double discount_rate = 0.0; // 총 할인율
  int total_price;            // 할인 전 총액
  double final_price;         // 최종 결제 금액

  int age;                    // 관람객 나이
  int time_code;              // 시간대 코드 (1: 조조, 2: 일반, 3: 심야)
  double age_discount = 0.0;  // 나이 할인율
  double time_discount = 0.0; // 시간대 할인율

  // [2단계] 사용자에게 정보 입력받기
  printf("=== 영화 예매 시스템 ===\n");

  printf("영화 코드를 입력하세요 (A: 2D, B: 3D, C: IMAX) :");
  scanf(" %c", &movie_code);

  printf("좌석 열을 입력하세요 (A~Z) :");
  scanf(" %c", &seat_row);

  printf("")
}