#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

bool vis[40][40];
const char sta[200005] = "10";//前缀
const char zfj[40] = "0123456789abcdefghijklmnopqrstuvwxyz";//字符集（不要改动）
const int stsz = 2;//前缀长度
const int cool = 1500;//防 ban 冷却，建议 3000+
const int save = cool + 1000;//保存内容冷却，最低 1000 + cool
const short op = 1;//op = 1 横推，op = 2 随机撒点

// 移动鼠标到指定坐标
void MoveMouse(int x, int y) {
SetCursorPos(x, y);
return;
}

// 按下并释放左键
void LeftClick() {
mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
Sleep(10);
mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
return;
}

// 按下并释放右键
void RightClick() {
mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
Sleep(10);
mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
return;
}

// 按下并释放指定字母键
void PressKey(char key) {
keybd_event(VkKeyScanA(key), 0, 0, 0);
Sleep(10);
keybd_event(VkKeyScanA(key), 0, KEYEVENTF_KEYUP, 0);
}

// 按下并释放回车键
void PressEnter() {
keybd_event(VK_RETURN, 0, 0, 0);
Sleep(10);
keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
return;
}

// Backspace键函数
void PressBackspace() {
keybd_event(VK_BACK, 0, 0, 0);
Sleep(10);
keybd_event(VK_BACK, 0, KEYEVENTF_KEYUP, 0);
return;
}

// 空格键功能
void PressSpace() {
keybd_event(VK_SPACE, 0, 0, 0);
Sleep(10);
keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
return;
}

// 按下Capslock键
void PressCapslock() {
keybd_event(VK_CAPITAL, 0, 0, 0);
Sleep(10);
keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
return;
}

// 按下CTRL键
void CtrlDown() {
keybd_event(VK_CONTROL, 0, 0, 0);
return;
}

// 释放CTRL键
void CtrlUp() {
keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
return;
}

// 按下并释放主键盘数字键
void PressNum(char num)
{
SHORT vk = VkKeyScanA(num);
keybd_event(LOBYTE(vk), 0, 0, 0);
Sleep(10);
keybd_event(LOBYTE(vk), 0, KEYEVENTF_KEYUP, 0);
return;
}

int main()
{
srand(time(0));
bool BigLetter = 0;
Sleep(5000);
if(op == 1)//平推
{
char i , j;
for(int p = 0 ; p <= 36 ; p++)
{
for(int q = 0 ; q <= 36 ; q++)
{
i = zfj[p];
j = zfj[q];
MoveMouse(500, 50);
LeftClick();
Sleep(10);
LeftClick();
Sleep(20);
PressBackspace();
Sleep(20);
for(int k = 0 ; k < stsz ; k++)
{
if('0' <= sta[k] && sta[k] <= '9')
{
PressNum(sta[k]);
}
else
{
PressKey(sta[k]);
}
Sleep(30);
}
if('0' <= i && i <= '9')
{
PressNum(i);
}
else
{
PressKey(i);
}
Sleep(40);
if('0' <= j && j <= '9')
{
PressNum(j);
}
else
{
PressKey(j);
}
Sleep(15);
PressEnter();
Sleep(cool);
MoveMouse(500, 108);
LeftClick();
Sleep(10);
CtrlDown();
Sleep(40);
PressKey('A');
Sleep(40);
PressKey('V');
Sleep(40);
CtrlUp();
Sleep(max(save - cool - 710 - 30 * stsz , 200));
}
}
}
else//随机撒点
{
int cnt = 0 , i , j;
while(cnt < 46656)
{
if(cnt > 37324)
{
bool flag = 0;
for(int p = 0 ; p < 36 ; p++)
{
for(int q = 0 ; q < 36 ; q++)
{
i = zfj[p];
j = zfj[q];
if(!vis[p][q])
{
vis[p][q] = 1;
flag = 1;
break;
}
}
if(flag)
{
break;
}
}
cnt++;
}
else
{
i = rand() % 36;
j = rand() % 36;
while(vis[i][j])
{
i = rand() % 36;
j = rand() % 36;
}
vis[i][j] = 1;
i = zfj[i];
j = zfj[j];
cnt++;
}
MoveMouse(500, 50);
LeftClick();
Sleep(10);
LeftClick();
Sleep(20);
PressBackspace();
Sleep(20);
for(int k = 0 ; k < stsz ; k++)
{
if('0' <= sta[k] && sta[k] <= '9')
{
PressNum(sta[k]);
}
else
{
PressKey(sta[k]);
}
Sleep(30);
}
if('0' <= i && i <= '9')
{
PressNum(i);
}
else
{
PressKey(i);
}
Sleep(40);
if('0' <= j && j <= '9')
{
PressNum(j);
}
else
{
PressKey(j);
}
Sleep(15);
PressEnter();
Sleep(cool);
MoveMouse(500, 108);
LeftClick();
Sleep(10);
CtrlDown();
Sleep(40);
PressKey('A');
Sleep(40);
PressKey('V');
Sleep(40);
CtrlUp();
Sleep(max(save - cool - 710 - 30 * stsz , 200));
}
}
return 0;
}