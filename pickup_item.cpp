/*
다음과 같은 다각형 모양 지형에서 캐릭터가 아이템을 줍기 위해 이동하려 합니다.

rect_1.png

지형은 각 변이 x축, y축과 평행한 직사각형이 겹쳐진 형태로 표현하며, 캐릭터는 이 다각형의 둘레(굵은 선)를 따라서 이동합니다.

만약 직사각형을 겹친 후 다음과 같이 중앙에 빈 공간이 생기는 경우, 다각형의 가장 바깥쪽 테두리가 캐릭터의 이동 경로가 됩니다.

rect_2.png

단, 서로 다른 두 직사각형의 x축 좌표 또는 y축 좌표가 같은 경우는 없습니다.

rect_4.png

즉, 위 그림처럼 서로 다른 두 직사각형이 꼭짓점에서 만나거나, 변이 겹치는 경우 등은 없습니다.

다음 그림과 같이 지형이 2개 이상으로 분리된 경우도 없습니다.

rect_3.png

한 직사각형이 다른 직사각형 안에 완전히 포함되는 경우 또한 없습니다.

rect_7.png

지형을 나타내는 직사각형이 담긴 2차원 배열 rectangle, 초기 캐릭터의 위치 characterX, characterY, 아이템의 위치 itemX, itemY가 solution 함수의 매개변수로 주어질 때, 캐릭터가 아이템을 줍기 위해 이동해야 하는 가장 짧은 거리를 return 하도록 solution 함수를 완성해주세요.

제한사항
rectangle의 세로(행) 길이는 1 이상 4 이하입니다.
rectangle의 원소는 각 직사각형의 [좌측 하단 x, 좌측 하단 y, 우측 상단 x, 우측 상단 y] 좌표 형태입니다.
직사각형을 나타내는 모든 좌표값은 1 이상 50 이하인 자연수입니다.
서로 다른 두 직사각형의 x축 좌표, 혹은 y축 좌표가 같은 경우는 없습니다.
문제에 주어진 조건에 맞는 직사각형만 입력으로 주어집니다.
charcterX, charcterY는 1 이상 50 이하인 자연수입니다.
지형을 나타내는 다각형 테두리 위의 한 점이 주어집니다.
itemX, itemY는 1 이상 50 이하인 자연수입니다.
지형을 나타내는 다각형 테두리 위의 한 점이 주어집니다.
캐릭터와 아이템의 처음 위치가 같은 경우는 없습니다.
전체 배점의 50%는 직사각형이 1개인 경우입니다.
전체 배점의 25%는 직사각형이 2개인 경우입니다.
전체 배점의 25%는 직사각형이 3개 또는 4개인 경우입니다.
입출력 예
rectangle	characterX	characterY	itemX	itemY	result
[[1,1,7,4],[3,2,5,5],[4,3,6,9],[2,6,8,8]]	1	3	7	8	17
[[1,1,8,4],[2,2,4,9],[3,6,9,8],[6,3,7,7]]	9	7	6	1	11
[[1,1,5,7]]	1	1	4	7	9
[[2,1,7,5],[6,4,10,10]]	3	1	7	10	15
[[2,2,5,5],[1,3,6,4],[3,1,4,6]]	1	4	6	3	10
입출력 예 설명
입출력 예 #1

rect_5.png

캐릭터 위치는 (1, 3)이며, 아이템 위치는 (7, 8)입니다. 위 그림과 같이 굵은 선을 따라 이동하는 경로가 가장 짧습니다.

입출력 예 #2

rect_6.png

캐릭터 위치는 (9, 7)이며, 아이템 위치는 (6, 1)입니다. 위 그림과 같이 굵은 선을 따라 이동하는 경로가 가장 짧습니다.

입출력 예 #3

rect_8.png

캐릭터 위치는 (1, 1)이며, 아이템 위치는 (4, 7)입니다. 위 그림과 같이 굵은 선을 따라 이동하는 경로가 가장 짧습니다.

입출력 예 #4, #5

설명 생략
*/

#include <string>
#include <vector>
#include <string.h>
#include <queue>

using namespace std;
enum DIRECTION
{
    dir_up,
    dir_right,
    dir_left,
    dir_down,
    dir_none
};
/*
up/down left/right
up,left
up,right
down,left
down,right
up,down
left,right
이런 조합들이 있음
*/

vector<DIRECTION> calculateNextPossibleDir(vector<vector<bool>> &grid, int x_pos, int y_pos)
{
    vector<DIRECTION> possibleDirections;
    bool smallGridForCheck1[2][2];
    bool smallGridForCheck2[2][2];

    // up
    if (grid[y_pos + 1][x_pos])
    {
        smallGridForCheck1[0][0] = grid[y_pos][x_pos - 1];
        smallGridForCheck1[0][1] = grid[y_pos][x_pos];
        smallGridForCheck1[1][0] = grid[y_pos + 1][x_pos - 1];
        smallGridForCheck1[1][1] = grid[y_pos + 1][x_pos];

        smallGridForCheck2[0][0] = grid[y_pos][x_pos];
        smallGridForCheck2[0][1] = grid[y_pos][x_pos + 1];
        smallGridForCheck2[1][0] = grid[y_pos + 1][x_pos];
        smallGridForCheck2[1][1] = grid[y_pos + 1][x_pos + 1];

        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                if (!(smallGridForCheck1[i][j] && smallGridForCheck2[i][j]))
                {
                    possibleDirections.push_back(DIRECTION::dir_up);
                    j = 3;
                    i = 3;
                }
            }
        }
    }

    // down
    if (grid[y_pos - 1][x_pos])
    {
        smallGridForCheck1[0][0] = grid[y_pos - 1][x_pos - 1];
        smallGridForCheck1[0][1] = grid[y_pos - 1][x_pos];
        smallGridForCheck1[1][0] = grid[y_pos][x_pos - 1];
        smallGridForCheck1[1][1] = grid[y_pos][x_pos];

        smallGridForCheck2[0][0] = grid[y_pos - 1][x_pos];
        smallGridForCheck2[0][1] = grid[y_pos - 1][x_pos + 1];
        smallGridForCheck2[1][0] = grid[y_pos][x_pos];
        smallGridForCheck2[1][1] = grid[y_pos][x_pos + 1];

        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                if (!(smallGridForCheck1[i][j] && smallGridForCheck2[i][j]))
                {
                    possibleDirections.push_back(DIRECTION::dir_down);
                    j = 3;
                    i = 3;
                }
            }
        }
    }

    // right
    if (grid[y_pos][x_pos + 1])
    {
        smallGridForCheck1[0][0] = grid[y_pos][x_pos];
        smallGridForCheck1[0][1] = grid[y_pos][x_pos + 1];
        smallGridForCheck1[1][0] = grid[y_pos + 1][x_pos];
        smallGridForCheck1[1][1] = grid[y_pos + 1][x_pos + 1];

        smallGridForCheck2[0][0] = grid[y_pos - 1][x_pos];
        smallGridForCheck2[0][1] = grid[y_pos - 1][x_pos + 1];
        smallGridForCheck2[1][0] = grid[y_pos][x_pos];
        smallGridForCheck2[1][1] = grid[y_pos][x_pos + 1];

        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                if (!(smallGridForCheck1[i][j] && smallGridForCheck2[i][j]))
                {
                    possibleDirections.push_back(DIRECTION::dir_right);
                    j = 3;
                    i = 3;
                }
            }
        }
    }

    // left
    if (grid[y_pos][x_pos - 1])
    {
        smallGridForCheck1[0][0] = grid[y_pos][x_pos - 1];
        smallGridForCheck1[0][1] = grid[y_pos][x_pos];
        smallGridForCheck1[1][0] = grid[y_pos + 1][x_pos - 1];
        smallGridForCheck1[1][1] = grid[y_pos + 1][x_pos];

        smallGridForCheck2[0][0] = grid[y_pos - 1][x_pos - 1];
        smallGridForCheck2[0][1] = grid[y_pos - 1][x_pos];
        smallGridForCheck2[1][0] = grid[y_pos][x_pos - 1];
        smallGridForCheck2[1][1] = grid[y_pos][x_pos];

        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                if (!(smallGridForCheck1[i][j] && smallGridForCheck2[i][j]))
                {
                    possibleDirections.push_back(DIRECTION::dir_left);
                    j = 3;
                    i = 3;
                }
            }
        }
    }

    return possibleDirections;
}

DIRECTION getReverseDirection(DIRECTION direction)
{
    switch (direction)
    {
    case DIRECTION::dir_up:
        return DIRECTION::dir_down;
    case DIRECTION::dir_right:
        return DIRECTION::dir_left;
    case DIRECTION::dir_left:
        return DIRECTION::dir_right;
    case DIRECTION::dir_down:
        return DIRECTION::dir_up;
    case DIRECTION::dir_none:
    default:
        return DIRECTION::dir_none;
        break;
    }
}

pair<int, int> generatePosition(int pos_x, int pos_y, DIRECTION dir)
{
    switch (dir)
    {
    case DIRECTION::dir_up:
        ++pos_y;
        break;
    case DIRECTION::dir_right:
        ++pos_x;
        break;
    case DIRECTION::dir_left:
        --pos_x;
        break;
    case DIRECTION::dir_down:
        --pos_y;
        break;
    case DIRECTION::dir_none:
        break;
    default:
        break;
    }

    return make_pair(pos_x, pos_y);
}

int solution(vector<vector<int>> rectangle, int characterX, int characterY, int itemX, int itemY)
{
    int max_x_pos = INT32_MIN;
    int max_y_pos = INT32_MIN;

    for (auto &rect : rectangle)
    {
        max_x_pos = std::max(max_x_pos, rect[0]);
        max_x_pos = std::max(max_x_pos, rect[2]);

        max_y_pos = std::max(max_y_pos, rect[1]);
        max_y_pos = std::max(max_y_pos, rect[3]);
    }

    // make grid
    const size_t rowSize = max_y_pos * 2 + 1;
    const size_t columnSize = max_x_pos * 2 + 1;

    // memory allocation
    vector<vector<bool>> grid;
    for (size_t i = 0; i < rowSize + 3; ++i)
    {
        grid.push_back(vector<bool>(columnSize + 3, false));
    }

    // main code here

    // 1. fill the grid
    for (auto &rect : rectangle)
    {
        int rectWidth = (rect[2] - rect[0]) * 2;
        int rectHeight = (rect[3] - rect[1]) * 2;

        int rowPos = rect[1] * 2;
        int colPos = rect[0] * 2;

        for (int i = 0; i <= rectHeight; ++i)
        {
            for (int j = 0; j <= rectWidth; ++j)
            {
                grid[rowPos + i][colPos + j] = true;
            }
        }
    }

    // 2.
    DIRECTION prevDirection = DIRECTION::dir_none;
    queue<pair<DIRECTION, pair<int, int>>> candidates;
    int moveCount = 0;

    auto nextPossibleDir = calculateNextPossibleDir(grid, characterX * 2, characterY * 2);
    for (auto &nextDir : nextPossibleDir)
    {
        candidates.push(make_pair(nextDir,
                                  generatePosition(characterX * 2, characterY * 2, nextDir)));
    }

    int minimumMoveCount = INT32_MAX;
    while (!candidates.empty())
    {
        auto candidate = candidates.front();
        candidates.pop();

        moveCount = 1;
        prevDirection = getReverseDirection(candidate.first);
        auto currentPos = candidate.second;
        while (!(currentPos.first == itemX * 2 && currentPos.second == itemY * 2))
        {
            auto nextPossibleDirections = calculateNextPossibleDir(grid, currentPos.first, currentPos.second);

            for (auto &nextPD : nextPossibleDirections)
            {
                if (nextPD == prevDirection)
                {
                    continue;
                }
                else
                {
                    currentPos = generatePosition(currentPos.first, currentPos.second, nextPD);
                    prevDirection = getReverseDirection(nextPD);
                    ++moveCount;
                    break;
                }
            }
        }
        minimumMoveCount = min(moveCount / 2, minimumMoveCount);
    }

END:
    return minimumMoveCount;
}

struct TEST_CASE
{
    vector<vector<int>> rectangle;
    int characterX;
    int characterY;
    int itemX;
    int itemY;
};

#include <iostream>
int main(int argc, char **argv)
{
    /*
    rectangle	characterX	characterY	itemX	itemY	result
    [[1,1,7,4],[3,2,5,5],[4,3,6,9],[2,6,8,8]]	1	3	7	8	17
    [[1,1,8,4],[2,2,4,9],[3,6,9,8],[6,3,7,7]]	9	7	6	1	11
    [[1,1,5,7]]	1	1	4	7	9
    [[2,1,7,5],[6,4,10,10]]	3	1	7	10	15
    [[2,2,5,5],[1,3,6,4],[3,1,4,6]]	1	4	6	3	10
    */
#if 0
    TEST_CASE t1;
    vector<int> tempV;
    tempV.clear();
    tempV.push_back(1);
    tempV.push_back(1);
    tempV.push_back(7);
    tempV.push_back(4);
    t1.rectangle.push_back(tempV);
    tempV.clear();
    tempV.push_back(3);
    tempV.push_back(2);
    tempV.push_back(5);
    tempV.push_back(5);
    t1.rectangle.push_back(tempV);
    tempV.clear();
    tempV.push_back(4);
    tempV.push_back(3);
    tempV.push_back(6);
    tempV.push_back(9);
    t1.rectangle.push_back(tempV);
    tempV.clear();
    tempV.push_back(2);
    tempV.push_back(6);
    tempV.push_back(8);
    tempV.push_back(8);
    t1.rectangle.push_back(tempV);
    t1.characterX = 1;
    t1.characterY = 3;
    t1.itemX = 7;
    t1.itemY = 8;
#else
    TEST_CASE t1{
        .rectangle = {
            {1, 1, 7, 4},
            {3, 2, 5, 5},
            {4, 3, 6, 9},
            {2, 6, 8, 8},
        },
        .characterX = 1,
        .characterY = 3,
        .itemX = 7,
        .itemY = 8};
#endif

    cout << "Result : " << solution(t1.rectangle, t1.characterX, t1.characterY, t1.itemX, t1.itemY) << endl;

    return 0;
}