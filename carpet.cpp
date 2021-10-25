/*
카펫
문제 설명
Leo는 카펫을 사러 갔다가 아래 그림과 같이 중앙에는 노란색으로 칠해져 있고 테두리 1줄은 갈색으로 칠해져 있는 격자 모양 카펫을 봤습니다.

carpet.png

Leo는 집으로 돌아와서 아까 본 카펫의 노란색과 갈색으로 색칠된 격자의 개수는 기억했지만, 전체 카펫의 크기는 기억하지 못했습니다.

Leo가 본 카펫에서 갈색 격자의 수 brown, 노란색 격자의 수 yellow가 매개변수로 주어질 때 카펫의 가로, 세로 크기를 순서대로 배열에 담아 return 하도록 solution 함수를 작성해주세요.

제한사항
갈색 격자의 수 brown은 8 이상 5,000 이하인 자연수입니다.
노란색 격자의 수 yellow는 1 이상 2,000,000 이하인 자연수입니다.
카펫의 가로 길이는 세로 길이와 같거나, 세로 길이보다 깁니다.
입출력 예
brown	yellow	return
10	2	[4, 3]
8	1	[3, 3]
24	24	[8, 6]
출처

※ 공지 - 2020년 2월 3일 테스트케이스가 추가되었습니다.
※ 공지 - 2020년 5월 11일 웹접근성을 고려하여 빨간색을 노란색으로 수정하였습니다.
*/

#include <string>
#include <vector>
#include <iostream>

#include <list>
using namespace std;

bool checkYellowWidthHeight(int brown_grid_count, int yellow_width, int yellow_height)
{
	if (yellow_width >= yellow_height)
	{
		return brown_grid_count == (yellow_width * 2 + yellow_height * 2 + 4) ? true : false;
	}

	return false;
}

list<int> findDivisor(int num)
{
	if(num == 1)
	{
		return list<int>{1};
	}

	list<int> retList;

	int copyNum = num;

	retList.push_back(1);

	for (int i = 2; i < copyNum; ++i)
	{
		if (copyNum % i == 0)
		{
			copyNum = copyNum / i;

			retList.push_back(i);
			i = 1;
		}
	}
	retList.push_back(copyNum);

	return retList;
}


int multiplyAllListElement(list<int>& l)
{
	int sum = 1;
	for(auto& i : l)
	{
		sum *= i;
	}
	return sum;
}

bool targetFound = true;
int m_brown_count;
pair<int,int> result;

void fullSearch(list<int> &choosen, list<int> &choose)
{
	int choosenMultiplyValue = multiplyAllListElement(choosen);
	int chooseMultiplyValue = multiplyAllListElement(choose);
		
	if(choosenMultiplyValue <= chooseMultiplyValue)
	{
		if(checkYellowWidthHeight(m_brown_count,chooseMultiplyValue,choosenMultiplyValue))
		{
			result.first = chooseMultiplyValue + 2;
			result.second = choosenMultiplyValue + 2;
			targetFound = true;
			return;
		}
	}
	else
	{
		return;
	}
	
	size_t sizeOfChoose = choose.size();
	list<int>::iterator it;
	for (size_t i = 0; i < sizeOfChoose && !targetFound; ++i)
	{
		it = choose.begin();
		std::advance(it, i);
		int selectedInteger = *it;

		choosen.push_back(selectedInteger);

		list<int> newChoose(choose.begin(), choose.end());
		auto it2 = newChoose.begin();
		std::advance(it2, i);
		newChoose.erase(it2);

		fullSearch(choosen, newChoose);
		choosen.pop_back();
	}
}

vector<int> solution(int brown, int yellow)
{
	vector<int> answer;

	m_brown_count = brown;
	targetFound = false;
	result.first = 0;
	result.second = 0;

	auto yellowDivisorList = findDivisor(yellow);
	list<int> choosenList;
	fullSearch(choosenList,yellowDivisorList);
	
	if(targetFound)
	{
		 answer.push_back(result.first);
		 answer.push_back(result.second);		 
	}

	return answer;
}

void printList(list<int> &l)
{
	cout << "Print List : ";
	for (auto &i : l)
	{
		cout << i << " ";
	}
	cout << endl;
}

void printVector(vector<int> &v)
{
	cout << "print vector : ";
	for (auto &i : v)
	{
		cout << i << " ";
	}
	cout << endl;
}

#include "mj_timer.h"
int main(void)
{

	vector<std::pair<int, int>> testCases{
		{10, 2},
		{8, 1},
		{24, 24},
	};
	for (auto &testCase : testCases)
	{
		startTimer();
		auto res = solution(testCase.first, testCase.second);
		endTimer();
		printTimeDiff();
		printVector(res);
	}

	return 0;
}