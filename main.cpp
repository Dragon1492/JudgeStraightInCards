//
//  main.cpp
//  JudgeShunzi
//
//  Created by 叶龙 on 16/6/18.
//  Copyright © 2016年 叶龙. All rights reserved.
//

#include <iostream>
using namespace std;

/*
 一副扑克，拥有A,2,3,4,5,6,7,8,9,10,J,Q,K各4张；小王，大王各一张；
 其中，黑桃A~K记作[0,12]，梅花A~K记作[13,25],红桃A~K记作[26,38],方块A~K记作[39,51],小王记作52,大王记作53
 顺子定义：一副牌牌点符合差一的等差数列分布，比如A,2,3,4,5
 */

//牌点转换方法
void switchSerialToPoint(int nCards[], int nCardNum)
{
    for (int i = 0; i < nCardNum; i++) {
        nCards[i] = nCards[i] % 13;
    }
}

//交换数值方法
void swapNum(int &nNumA, int &nNumB)
{
    int nTempNum = 0;
    
    nTempNum = nNumA;
    
    nNumA = nNumB;
    
    nNumB = nTempNum;
}

//冒泡升序排序
void bubbleSortInAscSort(int nCards[], int nCardNum)
{
    for (int i = 0; i < nCardNum - 1; i++) {
        for (int j = 0; j < nCardNum - 1 - i; j++) {
            if (nCards[j] > nCards[j + 1]) {
                swapNum(nCards[j], nCards[j +1]);
            }
        }
    }
}

void printCards(int nCards[], int nCardNum)
{
    cout<<"cards:";
    
    for (int i = 0; i< nCardNum - 1; i++) {
        cout<<nCards[i]<<",";
    }
    
    cout<<nCards[nCardNum - 1]<<endl;
}

/*
 1.给定一套卡组，是否符合顺子条件
 */
bool isShunzi(int nCards[], int nCardNum)
{
    bool bRet = true;
    
    //检查是否含有大小王，有则不符合顺子条件
    for (int i = 0; i < nCardNum; i++) {
        if (51 == nCards[i] || 52 == nCards[i]) {
            bRet = false;
            
            break;
        }
    }
    
    if (bRet) {
        //转换成原有牌点
        printCards(nCards,nCardNum);
        switchSerialToPoint(nCards, nCardNum);
        printCards(nCards,nCardNum);
        
        //进行升序排序
        bubbleSortInAscSort(nCards, nCardNum);
        printCards(nCards,nCardNum);
        
        //检查是否符合差一等差数列来判断是否是顺子
        for (int i =  0; i < nCardNum - 1; i++) {
            if (1 != nCards[i + 1] - nCards[i]) {
                bRet = false;
                
                break;
            }
        }
    }
    
    return bRet;
}

/*
2.假设小王大王是万能牌，即可以顶替任何卡，求如果有万能牌，是否是顺子
*/
bool isShunziWithMagicCard(int nCards[], int nCardNum)
{
    bool bRet = true;
    
    //万能牌计数
    int nMagicCardCount = 0;
    printCards(nCards,nCardNum);
    
    //检查是否含有大小王，有则放到牌尾
    for (int i = nCardNum - 1; i >= 0; i--) {
        if (i < nCardNum - nMagicCardCount) {
            if (53 == nCards[i] || 52 == nCards[i]) {
                swapNum(nCards[i], nCards[nCardNum - 1 - nMagicCardCount]);
                
                nMagicCardCount++;
            }
        }
    }
    printCards(nCards,nCardNum);
    
    //转换成原有牌点
    printCards(nCards,nCardNum);
    switchSerialToPoint(nCards, nCardNum - nMagicCardCount);
    printCards(nCards,nCardNum);
    
    //进行升序排序
    bubbleSortInAscSort(nCards, nCardNum - nMagicCardCount);
    printCards(nCards,nCardNum);
    
    //检查是否符合差一等差数列，可以消耗万能牌凑数
    int nMagicCardCountCopy = nMagicCardCount;
    
    for (int i = 0; i < nCardNum - 1 - nMagicCardCount; i++) {
        int nGapBetweenCards = nCards[i + 1] - nCards[i];
        
        if (0 == nGapBetweenCards) {
            bRet = false;
            
            break;
        }
        else if (1 < nGapBetweenCards) {
            if (nMagicCardCountCopy >= nGapBetweenCards - 1) {
                nMagicCardCountCopy -= nGapBetweenCards - 1;
            }
            else {
                bRet = false;
                
                break;
            }
        }
    }
    
    return bRet;
}

/*
 3.含有万能牌情况下，给定卡组中最长的顺子是多长
*/
int getMaxShunziInCards(int nCards[], int nCardNum)
{
    int nMaxShunziSize = 0;
    
    //万能牌计数
    int nMagicCardCount = 0;
    
    printCards(nCards,nCardNum);
    //检查是否含有大小王，有则放到牌尾
    for (int i = nCardNum - 1; i >= 0; i--) {
        if (i < nCardNum - nMagicCardCount) {
            if (53 == nCards[i] || 52 == nCards[i]) {
                swapNum(nCards[i], nCards[nCardNum - 1 - nMagicCardCount]);
                
                nMagicCardCount++;
            }
        }
    }
    printCards(nCards,nCardNum);
    
    //转换成原有牌点
    switchSerialToPoint(nCards, nCardNum - nMagicCardCount);
    printCards(nCards,nCardNum);
    
    //进行升序排序
    bubbleSortInAscSort(nCards, nCardNum - nMagicCardCount);
    printCards(nCards,nCardNum);
    
    //从头开始检查差一等差数列能排多长，可以消耗万能牌凑数
    for (int i = 0; i < nCardNum - 1 - nMagicCardCount; i++)
    {
        int nMagicCardCountCopy = nMagicCardCount;
        
        int nCurrentMaxCount = 1;
        
        //计算最长计数能排多长
        for (int j = i; j < nCardNum - 1 - nMagicCardCount; j++) {
            int nGapBetweenCards = nCards[j + 1] - nCards[j];
            
            if (0 == nGapBetweenCards) {
                break;
            }
            else if (1 == nGapBetweenCards)
            {
                nCurrentMaxCount++;
            }
            else//1 < nGapBetweenCards
            {
                //万能牌补齐凑数
                if (nMagicCardCountCopy >= nGapBetweenCards - 1) {
                    nMagicCardCountCopy -= nGapBetweenCards - 1;
                    
                    nCurrentMaxCount += nGapBetweenCards;
                }
                else
                {
                    break;
                }
            }
        }
        
        //万能牌要用光
        nCurrentMaxCount += nMagicCardCountCopy;
        
        if (nCurrentMaxCount > nMaxShunziSize) {
            nMaxShunziSize = nCurrentMaxCount;
        }
    }
    
    return nMaxShunziSize;
}

//对三个方法进行检查
int main(int argc, const char * argv[]) {
    
    int nCards_1[6] = {43,14,3,18,39,28};
    
    int nCards_2[6] = {22,5,17,42,28,33 };
    
    int nCards_3[6] = {53,7,52,30,16,41};
    
    int nCards_4[6] = {22,5,17,42,28,33 };
    
    int nCards_5[6] = {53,7,52,30,16,41};
    
    int nCards_6[8] = {52,4,33,14,11,22,53,44};
    
    int nCards_7[8] = {52,4,33,14,11,22,53,44};
    
    string sIsShunziValue = "";
    
    //期望数值为true
    sIsShunziValue = isShunzi(nCards_1, 6) ? "true" : "false";
    
    cout<<"cards 1 is shunzi:"<<sIsShunziValue<<endl<<endl;
    
    //期望数值为false
    sIsShunziValue = isShunzi(nCards_2, 6) ? "true" : "false";
    
    cout<<"cards 2 is shunzi:"<<sIsShunziValue<<endl<<endl;
    
    //期望数值为false
    sIsShunziValue = isShunzi(nCards_3, 6) ? "true" : "false";
    
    cout<<"cards 3 is shunzi:"<<sIsShunziValue<<endl<<endl;
    
    string sIsShunziWithMagicCardValue = "";
    
    //期望数值为false
    sIsShunziWithMagicCardValue = isShunziWithMagicCard(nCards_4, 6) ? "true" : "false";
    
    cout<<"cards 2 is shunzi with magic card:"<<sIsShunziWithMagicCardValue<<endl<<endl;
    
    //期望数值为true
    sIsShunziWithMagicCardValue = isShunziWithMagicCard(nCards_5, 6) ? "true" : "false";
    
    cout<<"cards 3 is shunzi with magic card:"<<sIsShunziWithMagicCardValue<<endl<<endl;
    
    //期望数值为false
    sIsShunziWithMagicCardValue = isShunziWithMagicCard(nCards_6, 8) ? "true" : "false";
    
    cout<<"cards 4 is shunzi with magic card:"<<sIsShunziWithMagicCardValue<<endl<<endl;
    
    //期望数值为6
    int nMaxShunziInCards = getMaxShunziInCards(nCards_7, 8);
    
    cout<<"max shunzi size in cards 4 is:"<<nMaxShunziInCards<<endl<<endl;
    
    return 0;
}
