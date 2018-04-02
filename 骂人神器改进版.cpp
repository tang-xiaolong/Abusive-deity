#include<stdio.h>
#include <Windows.h>
int main()
{
	int i;		
	char c;
	HGLOBAL hMen;   
    TCHAR strText[256] ;
	FILE *p;
	printf("温馨（恶意）提示：请将要骂人的话放到F盘下：骂人语句.txt里面。用回车符号隔开。\n\n\n");
	printf("如果想启动该程序，请输入一个非零数，并在4秒内切换到你想要执行程序的页面。如果想退出，请输入0。在此输入：");
	scanf("%d",&i);
	while(i != 0)		
	{
		p = fopen("F:\\骂人语句.txt","r+");
		if(NULL == p)
		{
			printf("打开文件失败！\n");
			return 0;
		}
		Sleep(4000);
		while((c = fgetc(p))!=EOF)	//若没有到文件的结尾，则循环
		{
			fseek(p,-1,SEEK_CUR);	//将文件指针往前移一位
			fgets(strText,300,p);			//读取一行放入strText数组中，strText数组内是保存文本中的一行数据
			if (!OpenClipboard(NULL)|| !EmptyClipboard())    
			{   
				printf("打开或清空剪切板出错！\n");   
				return 0;   
			}   
			
			// 分配全局内存    
			hMen = GlobalAlloc(GMEM_MOVEABLE, ((strlen(strText)+1)*sizeof(TCHAR)));    

			if (!hMen)   
			{   
				printf("分配全局内存出错！\n");    
				// 关闭剪切板    
				CloseClipboard(); 
				return 0;         
			}   

			// 把数据拷贝考全局内存中   
			// 锁住内存区    
			LPSTR lpStr = (LPSTR)GlobalLock(hMen);    

			// 内存复制   
			memcpy(lpStr, strText, ((strlen(strText))*sizeof(TCHAR)));    
			// 字符结束符    
			lpStr[strlen(strText)] = (TCHAR)0;   
			// 释放锁    
			GlobalUnlock(hMen);   

			// 把内存中的数据放到剪切板上   
			SetClipboardData(CF_TEXT, hMen);   
			CloseClipboard();

			keybd_event(0x11,0,0,0);			//0x11是ctrl键  0x0D是enter键		0x56是 V 键。  必须用16进制表示。	第三个参数：0表示按下，2表示松开。
			keybd_event(0x56,0,0,0);			
			keybd_event(0x11,0,2,0);
			keybd_event(0x56,0,2,0);
			keybd_event(0x11,0,0,0);
			keybd_event(0x0D,0,0,0);
			keybd_event(0x11,0,2,0);
			keybd_event(0x0D,0,2,0);
			Sleep(200);			
		}
		system("cls");
		printf("温馨（恶意）提示：请将要骂人的话放到F盘下：骂人语句.txt里面。用回车符号隔开。\n\n\n");
		printf("如果想启动该程序，请输入一个非零数，并在4秒内切换到你想要执行程序的页面。如果想退出，请输入0。在此输入：");
		scanf("%d",&i);
	}
	fclose(p);
}
