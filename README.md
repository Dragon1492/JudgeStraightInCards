# JudgeStraightInCards
Judge Straight is in the cards and get the max straight in the cards;

#中文说明

##背景介绍
 一副扑克，拥有A,2,3,4,5,6,7,8,9,10,J,Q,K各4张；小王，大王各一张；
 其中，黑桃A~K记作[0,12]，梅花A~K记作[13,25],红桃A~K记作[26,38],方块A~K记作[39,51],小王记作52,大王记作53
 顺子定义：一副牌牌点符合差一的等差数列分布，比如A,2,3,4,5

##功能说明

###bool isShunzi(int nCards[], int nCardNum)

给定一个牌号数组，求该牌组是否是顺子

###bool isShunziWithMagicCard(int nCards[], int nCardNum)

同样给定一个牌号数值，但此时大小王能当万能牌顶替任何牌，求该牌组是否是顺子

###int getMaxShunziInCards(int nCards[], int nCardNum)

在含有万能牌情况下，求最长的顺子长度是多少
