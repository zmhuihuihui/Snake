# 基于嵌入式开发的简单的贪吃蛇算法

## 实现功能

* 芯片：LPC1768<br>

开机后进入开机画面，然后等待2s后进入游戏界面，开始游戏。<br>
贪食蛇会按照当前方向前进，控制五项按键可以改变前进方向。<br>
前进中没有碰到食物则继续前进，若碰到食物，贪吃蛇身体长度加一，加分，再随机生成食物。<br>
在前进过程中，若碰到自己的身体或者边界，则游戏结束。<br>
