#include "HW.h"
#include <iostream> // 추가

using namespace std; // 추가

//Battle Ship 게임 만들기
//	1.목표
//		플레이어는 컴퓨터가 숨겨놓은 적 함선을 찾아 격침시킨다.
//	2.맵 크기는 10 x 10이다.
//		각 칸에는 함선 또는 빈 칸이 위치한다.
//	3.적 함선 종류
//		총 4척: 크기 5, 4, 3, 2 (항공모함, 전함, 순양함, 구축함 등)
//	4.함선 배치
//		함선은 맵에 겹치지 않게 가로 또는 세로로 랜덤 배치된다.
//	5.플레이어의 목표
//		제한된 공격 횟수(30회) 내에 모든 적 함선을 명중시켜 격침시키는 것.
//	6.게임 진행 방식
//		플레이어는(x, y) 좌표를 입력해 공격한다.
//		공격 결과(명중 / 실패)는 바로 표시되고, 플레이어의 맵에 기록된다.
//		이미 공격한 좌표는 다시 공격할 수 없다.
//	7.함선 격침
//		한 함선의 모든 칸을 명중시키면 "격침" 메시지가 출력된다.
//	8.게임 종료 조건
//		모든 적 함선을 격침시키면 승리.
//		주어진 횟수 내에 격침하지 못하면 패배하며, 패배 시 적 함선의 실제 위치가 공개된다.
//	9.추가 정보
//		남은 공격 횟수와 남은 적 함선 수가 항상 안내된다.

//맵 정보
const int MapRows = 10;
const int MapCols = 10;

int Map[MapRows][MapCols] =
{
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0}
};


 //맵 출력
void PrintMap() {
    srand(time(0));
    PlaceShip(2);
    PlaceShip(3);
    PlaceShip(4);
    PlaceShip(5);
    int Clear = 0;
    int Hit = -1;
    while (Clear != 4)
    {
		system("cls");
        for (int h = 0; h < MapRows; h++)
        {
            for (int w = 0; w < MapCols; w++)
            {
                int temp = Map[h][w];
                //if (h == PlayerY && w == PlayerX)
                //{
                //    printf("P");
                //}
                if (Map[h][w] == 0)
                {
                    printf(".\t");
                }
                else if (Map[h][w] <= -1)
                {
                    printf("X\t");
                }
                else if (Map[h][w] == 2)
                {
                    printf("2\t");
                }
                else if (Map[h][w] == 3)
                {
                    printf("3\t");
                }
                else if (Map[h][w] == 4)
                {
                    printf("4\t");
                }
                else if (Map[h][w] == 5)
                {
                    printf("5\t");
                }
                else if (Map[h][w] >= 6)
                {
                    printf("O\t");
                }
            }
            printf("\n");
        }

        if (Hit == 0)
        {
            printf("공격 성공! 함선을 명중시켰습니다!\n");
        }
        else if (Hit == 1)
        {
            printf("공격 실패! 빈 칸을 공격했습니다.\n");
        }

        int PlayerX = 0, PlayerY = 0;


        printf("공격할 좌표를 입력하세요 (x y): ");
        cin >> PlayerX;
        cin >> PlayerY;             //진짜 좌표는(MapRows-PlayerY-1,PlayerX-1)로 변환해서 사용해야할듯
        while (1) {
            if (PlayerX >= MapCols || PlayerY >= MapRows || PlayerX < 1 || PlayerY < 1)
            {
                printf("잘못된 좌표입니다. 다시 입력해주세요.\n");
                PlayerX = 0, PlayerY = 0;

            }
            else
            {
                Hit = shipAttack(PlayerX - 1, MapRows - PlayerY, Hit);
                break;
            }
        }
    }
}


//함선 랜덤 배치
void PlaceShip(int size) {

    // 랜덤으로 함선 배치
    while (true)
    {
        int direction = rand() % 2; // 0: 가로, 1: 세로
        int x, y;
        int emptyCount = 0;


        //이미 함선이 겹치는지 확인하는 로직
        if (direction == 0) { // 가로
            x = rand() % (MapCols - size + 1);
            y = rand() % MapRows;
            for (int i = 0; i < size; i++)
            {
                if (Map[y][x + i] == 0)
                {
                    emptyCount++;
                }
            }
        }
        else { // 세로
            x = rand() % MapCols;
            y = rand() % (MapRows - size + 1);
            for (int i = 0; i < size; i++)
            {
                if (Map[y + i][x] == 0)
                {
                    emptyCount++;
                }
            }
        }


        if (emptyCount == size)
        {
            if (direction == 0) { // 가로
                for (int i = 0; i < size; i++) {
                    Map[y][x + i] = size; // 함선 위치 표시
                }
                break;
            }
            else { // 세로

                for (int i = 0; i < size; i++) {
                    Map[y + i][x] = size; // 함선 위치 표시
                }
                break;
            }
        }
    }
}

//함선 격침 여부 확인
int shipAttack(int x, int y, int Hit) {
    if (Map[y][x] == 0)
    {
        Hit = 1;
        Map[y][x] = -1; // 공격 실패 표시
        return Hit;
    }
    else if (Map[y][x] > 0)
    {
        Hit = 0;
        Map[y][x] += 6; // 공격 성공 표시
		return Hit;
    }
}