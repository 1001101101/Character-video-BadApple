#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

BITMAPFILEHEADER fileHead;      //�ļ���Ϣͷ
BITMAPINFOHEADER infoHead;      //λͼ��Ϣͷ
RGBQUAD pColorTable[256];       //��ɫ��ָ��
unsigned char *pBmpBuf;         //ͼ������ָ��
int bmpWidth;          //ͼ��Ŀ�
int bmpHeight;        //ͼ��ĸ�
int biBitCount;       //ÿ����λ��
int lineByte;         //ÿ�е��ֽ���
unsigned char a[1000][1000];
unsigned char *Pre = NULL;
char *out;
char info[] = {"$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^` ."};
int len ,reg = 42;
clock_t stime,ftime,ltime,lt;


#define name "frame\\badapple"
#define frame 5216

//������ͨ������Print�����д�ӡ�������Լ����������Ƹ�������
#define clearDegree 2  //����֡��һ��
#define UpdateTime 76 //ÿ�δ�ӡ���߶��
#pragma comment(lib, "WINMM.LIB")



int Read(const char *bmpName);
int Run(const char *bmpName);     /*����ԭ��*/
void Print();
void Pos(int x, int y);



int main(int argc, char *argv[]) 
{
	out = (char *)malloc(sizeof(char) * 40000);
	system("mode con cols=220 lines=150");
	system("color F0");
	
	len = strlen(info) - 1;
	Run(name);
	free(out);
	return 0;
}

int Run(const char *bmpName)
{
	register int i;
	int count = 0,temp = frame;
	char path[30] = "\0";
	char format[15];
	while(temp > 0)
	{
		++count;
		temp /= 10;
	}
	sprintf(format,"%s%dd%s","%s%0",count,"%s");
	//printf("%s\n",format);
	PlaySound("BadApple.wav", NULL, SND_FILENAME | SND_ASYNC);
	stime = lt = clock();
	printf("%ld",stime);
	//Sleep(130);
	for(i = 0;i < frame;)
	{
		if(i % 30 == 0)
		{
			reg = 40;
		}
		ftime = clock();
		if((ftime - stime) >= reg)
		{
			reg = 42;
			path[0] = '\0';
			sprintf(path,format,bmpName,i,".BMP");
			//printf("%s",path);
			++i;
			stime = ftime;
			Read(path);
			Print();
		}
	}
	ltime = clock();

	if(Pre)
		free(Pre);
	system("cls");
	printf("�ܹ��ǻ���%d��\n",(ltime-lt)/CLK_TCK);
	puts("зз����~ ");
	return 1; 
} 
void Print()
{
	int i,j;
	int x = 0;
	Pos(0,0);
	for(i = 17;i < bmpHeight - 17;++i)
	{
		if(i % clearDegree != 0)
			continue;
		for(j = 0;j < bmpWidth;++j)
		{
			//if(j % clearDegree == 0)
				out[x++] = info[(int)(a[i][j]/256.0*len)];
		}
		out[x++] = '\n';	
	}
	out[x] = '\0';
	printf("%s",out);
}
int Read(const char *bmpName)
{
	FILE *fp = fopen(bmpName,"rb");              /*�����ƶ���ʽ��ָ����ͼ���ļ�*/
	register int i,j;
	unsigned char * pix = NULL;
	if(fp==NULL) 
		return 0;
	fread(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);    /*���ļ���Ϣͷ*/
	fread(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);    /*��λͼ��Ϣͷ*/
	bmpWidth=infoHead.biWidth;     /*��ȡͼ����ߣ�ÿ������ռλ������Ϣ */
	bmpHeight=infoHead.biHeight;
	biBitCount=infoHead.biBitCount;
	lineByte=(bmpWidth*biBitCount/8+3)/4*4;    /*����ÿ���ֽ���(������4�ı���)*/

	if(Pre == NULL)
	{
		pix=(unsigned char *)malloc(lineByte+1);
		Pre = pix;
	}
	else
		pix = Pre;
	if(pix == NULL)
		return 0;
	for(i = 0;i < bmpHeight;++i)
	{
		fread(pix,1,lineByte,fp);
		for(j = 0;j < bmpWidth;++j)
		{
			a[bmpHeight-i-1][j] = (int)((unsigned char)(pix[j*3+2] * 0.3 + pix[j*3+1] * 0.59 + pix[j*3] * 0.11));
		}
	}
	fclose(fp);
	return 1; 
} 

void Pos(int x, int y)//���ù��λ��
{//Ҫע�������x��y�����������x��y�Ƿ���
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//���ر�׼�����롢����������豸�ľ����Ҳ���ǻ�����롢���/�������Ļ�������ľ��
	SetConsoleCursorPosition(hOutput, pos);
}