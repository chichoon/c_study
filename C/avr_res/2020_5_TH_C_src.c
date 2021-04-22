#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define WIDTHBYTES(bits) (((bits)+31)/32*4) // 비트맵 파일 규격에선, 가로방향 데이터 크기는 4의 배수(바이트단위)로 한다.
// 왜?? -> 이유를 찾아서 레포트에 첨부
#define BYTE unsigned char

FILE *file;// 파일 포인터 선언
int rwsize, rwsize2;// 가로 라인 당 바이트 수
BYTE *lpImg;// 입력 데이터가 저장되는 메모리 주소를 지시하는 포인터
BYTE *lpOutImg;// 출력 데이터가 저장되는 메모리 주소를 지시하는 포인터
RGBQUAD *pRGB;// Lookup Table
BITMAPFILEHEADER hf;// 비트맵 파일 해더
BITMAPINFOHEADER hinfo;// 비트맵 정보 헤더

void bitof24_to_8bit_gray(void);
void egdt(void); // 과제!!
void rgbdis();
void paletteswap();
int crop();
void clearinputbuffer();
// 프로그램 내의 함수에 대한 선언

int main()
{
	//bitof24_to_8bit_gray();
	//rgbdis();
	//crop();
	//paletteswap();
	//egdt();

	return 0;
}

void egdt(void)
{
	//  Make your code at here!
}

void bitof24_to_8bit_gray(void)
{
	int i, j;
	BYTE R, G, B, GRAY;

	BITMAPFILEHEADER ohf; // 출력 파일을 위한 비트맵 파일 헤더
	BITMAPINFOHEADER ohinfo; // 출력 파일을 위한 비트맵 파일 정보 헤더

	printf("RUN bitof24_to_8bit_gray()\n\n");

	file = fopen("ori.bmp", "rb");// 파일을 읽기 모드로 엶

	if (file == NULL)// 파일 열기에 실패하면
	{
		printf("Error At File open!!!\n");
		exit(1);
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file); // 파일을 열어 파일의 BITMAPFILEHEADER만큼을 hf에 저장

	if (hf.bfType != 0x4D42) // 0X4D42 == BM(아스키 코드), 비트맵파일은 맨 처음 시작이 BM이다. 따라서 첫 부분을 읽고, 그 부분을 분석해서 비트맵이 아니면...
	{
		printf("File is NOT BMP\n");
		exit(1);
	}

	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file); // 파일을 열어 파일의 BITMAPINFOHEADER만큼을 hinfo에 저장

	printf("File size : %d\n", hf.bfSize); // 입력받은 비트맵 파일의 크기를 화면에 출력함
	printf("offset : %d\n", hf.bfOffBits); // 입력받은 비트맵 파일에서 실제 데이터가 시작하는 오프셋
	printf("Image Size : (%dX%d)\n", hinfo.biWidth, hinfo.biHeight); // 입력받은 비트맵 파일의 픽셀 개수를 화면에 출력함
	printf("%d BPP \n", hinfo.biBitCount); // 입력받은 비트맵 파일의 픽셀당 비트수를 출력

	ohf = hf; 
	ohinfo = hinfo;
	// 원본 파일과 출력 파일은 거의 유사하므로 헤더파일을 복사해서 사용한다.
	// 단, 일부 값이 바뀌는 것들이 있으므로, 나중에 반드시 수정해줘야 한다.(bfOffBits, biBitCount 등...)

	rwsize = WIDTHBYTES(hinfo.biBitCount*hinfo.biWidth);
	rwsize2 = WIDTHBYTES(8 * ohinfo.biWidth);
	//입력 파일과 출력 파일에서 가로 한 줄당 데이터가 몇비트인지 저장한다
	//이때 입력파일에서 가로폭과(=가로폭에 있는 총 픽셀 갯수)
	//한 픽셀당 바이트 수를 곱하면, 한 줄이 몇 비트를 차지하는지 알 수 있다.
	//rwsize2를 계산할 때는 입력 파일과 출력 파일의 픽셀 사이즈는 동일하기 때문에 입력 파일의 가로폭을 그대로 쓰며
	//8BPP 파일의 픽셀당 비트수는 8비트이므로 8을 곱한다.

	fseek(file, hf.bfOffBits, SEEK_SET);
	//비트맵 파일에서 실제 값들이 저장돼 있는 위치로 포인터를 이동한다

	lpImg = (BYTE*)malloc(rwsize*hinfo.biHeight);
	//입력 받은 파일을 위한 메모리를 할당한다

	fread(lpImg, sizeof(char), rwsize*hinfo.biHeight, file);
	//포인터는 현재 실제 데이터 값이 저장된 곳의 맨 처음으로 이동한 상황이다. 이때 이미지의 세로폭과(=가로폭에 있는 총 픽셀 갯수)
	//한 줄당 비트수를 곱하면, 전체 데이터의 크기가 나온다. fread함수를 이용해 이미지의 데이터를 char변수의 크기만큼
	//나눠서 저장한다.

	fclose(file);
	//파일사용이 완료되었으므로 닫는다.

	lpOutImg = (BYTE*)malloc(rwsize2*ohinfo.biHeight);
	//출력한 파일을 위한 메모리를 할당한다

	for (i = 0; i < hinfo.biHeight; i++)
	{
		for (j = 0; j < hinfo.biWidth; j++)
		{
			B = lpImg[i*rwsize + 3 * j + 0];
			G = lpImg[i*rwsize + 3 * j + 1];
			R = lpImg[i*rwsize + 3 * j + 2];
			//앞서 언급했듯 rwsize는 가로 한줄의 데이터 크기다. 따라서 여기에 i를 곱한다는것은 i+1번째 줄의 데이터를
			//사용함을 의미한다. 한편 컬러에서 한 픽셀당 데이터는 3바이트가 필요하므로 3*j를 해서 j+1번째 픽셀로 이동한다.
			//즉 앞의 과정을 통해  i+1번째 줄의 j+1번째칸의 픽셀의 데이터를 저장한 배열의 값을 확인하게 된다.
			//이때 배열의 위치를 +0,+1,+2를 해서 데이터의 B G R값을 각각 저장한다.

			GRAY = (BYTE)(0.299*R + 0.587*G + 0.114*B);
			//각각 저장한 R,G,B값에 적당한 값을 곱하고 더해서 밝기값을 만든다
			//이 값들은 어떻게 정해진것인가? -> 찾아서 레포트 첨부
			lpOutImg[i*rwsize2 + j] = GRAY;
			//만든 밝기값을 lpOutImg의 i+1번째 줄의 j+1번째칸의 픽셀의 데이터를 저장한 배열에 저장한다.
		}
	}
	ohf.bfOffBits += 1024;
	//bfOffBits는 실제 파일의 화면 데이터가 시작되는 곳의 위치이다.
	//비트맵파일에서 비트수가 낮으면(1 ~ 8BPP)
	//비트수가 높을 때와(8BPP 초과) 달리 ColorTable이 파일의 화면 데이터앞에 있다.
	//따라서 bfOffBits를 1024만큼 뒤로 밀어야 한다.
	//1024는 RGBQUAD의 크기(4바이트) * 256개 팔레트 = 1024다.

	ohinfo.biBitCount = 8;
	//8BPP이니까 8이다.

	pRGB = (RGBQUAD*)malloc(sizeof(RGBQUAD) * 256);
	//앞서 말한 ColorTable을 위한 메모리를 설정한다.

	for (i = 0; i < 256; i++)
	{
		pRGB[i].rgbBlue = i;
		pRGB[i].rgbGreen = i;
		pRGB[i].rgbRed = i;
		pRGB[i].rgbReserved = i;
	}
	//흑백이니까 그냥 0부터 255까지 순차적으로 저장한다.

	file = fopen("BW.bmp", "wb");
	//이제 출력할 파일을 쓰기모드로 연다.

	fwrite(&ohf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&ohinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	fwrite(pRGB, sizeof(RGBQUAD), 256, file);
	//비트맵 파일을 구성하는 BITMAPFILEHEADER, BITMAPINFOHEADER,RGBQUAD를 기록한다.
	fwrite(lpOutImg, sizeof(char), rwsize2*hinfo.biHeight, file);
	//앞서 우리가 만든 출력 데이터를 기록한다.
	fclose(file);
	//파일을 닫는다.

	free(lpImg);
	free(lpOutImg);
	free(pRGB);
	//메모리를 반환한다.

	printf("Check BW.bmp!!\n\n");
}

void rgbdis(void)
{
	int i, j;
	printf("RUN rgbdis()\n\n");
	file = fopen("rgbdis.bmp", "rb");

	if (file == NULL)
	{
		printf("Error At File open!!!\n");
		exit(1);
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file);

	if (hf.bfType != 0x4D42)
	{
		printf("File is NOT BMP\n");
		exit(1);
	}

	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file);

	printf("File size : %d\n", hf.bfSize);
	printf("offset : %d\n", hf.bfOffBits);
	printf("Image Size : (%dX%d)\n", hinfo.biWidth, hinfo.biHeight);
	printf("%d BPP \n", hinfo.biBitCount);

	rwsize = WIDTHBYTES(hinfo.biBitCount*hinfo.biWidth);

	fseek(file, hf.bfOffBits, SEEK_SET);

	lpImg = (BYTE*)malloc(rwsize*hinfo.biHeight);

	fread(lpImg, sizeof(char), rwsize*hinfo.biHeight, file);

	fclose(file);

	lpOutImg = (BYTE*)malloc(rwsize*hinfo.biHeight);

	for (i = 0; i < hinfo.biHeight; i++)
	{
		for (j = 0; j < hinfo.biWidth; j++)
		{
			lpOutImg[i*rwsize + 3 * j + 0] = lpImg[i*rwsize + 3 * j + 0];  // B
			lpOutImg[i*rwsize + 3 * j + 1] = 0;  // G
			lpOutImg[i*rwsize + 3 * j + 2] = 0;  // R
		}
	}

	hinfo.biBitCount = 24;

	file = fopen("blue.bmp", "wb");

	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&hinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	fwrite(lpOutImg, sizeof(char), rwsize*hinfo.biHeight, file);
	fclose(file);

	file = fopen("green.bmp", "wb");
	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&hinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	for (i = 0; i < hinfo.biHeight; i++)
	{
		for (j = 0; j < hinfo.biWidth; j++)
		{
			lpOutImg[i*rwsize + 3 * j + 0] = 0;  // B
			lpOutImg[i*rwsize + 3 * j + 1] = lpImg[i*rwsize + 3 * j + 1];  // G
			lpOutImg[i*rwsize + 3 * j + 2] = 0;  // R
		}
	}
	fwrite(lpOutImg, sizeof(char), rwsize*hinfo.biHeight, file);
	fclose(file);

	file = fopen("red.bmp", "wb");
	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&hinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	for (i = 0; i < hinfo.biHeight; i++)
	{
		for (j = 0; j < hinfo.biWidth; j++)
		{
			lpOutImg[i*rwsize + 3 * j + 0] = 0;  // B
			lpOutImg[i*rwsize + 3 * j + 1] = 0;  // G
			lpOutImg[i*rwsize + 3 * j + 2] = lpImg[i*rwsize + 3 * j + 2];  // R
		}
	}

	fwrite(lpOutImg, sizeof(char), rwsize*hinfo.biHeight, file);

	fclose(file);

	free(lpImg);
	free(lpOutImg);

	printf("Check blue.bmp, green.bmp, red.bmp!!!\n\n");
}

void paletteswap()
{
	int i, j;
	BYTE R, G, B, GRAY;
	RGBQUAD *oripal;
	RGBQUAD *swappal;

	BITMAPFILEHEADER ohf; 
	BITMAPINFOHEADER ohinfo; 

	printf("RUN paletteswap()\n\n");

	file = fopen("logo.bmp", "rb");

	if (file == NULL)
	{
		printf("Error At File open!!!\n");
		exit(1);
	}

	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file); 

	if (hf.bfType != 0x4D42) 
	{
		printf("File is NOT BMP\n");
		exit(1);
	}

	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file); 

	printf("File size : %d\n", hf.bfSize);
	printf("offset : %d\n", hf.bfOffBits);
	printf("Image Size : (%dX%d)\n", hinfo.biWidth, hinfo.biHeight);
	printf("%d BPP \n", hinfo.biBitCount);
	printf("Palette has %d color \n", hinfo.biClrUsed);

	ohf = hf;
	ohinfo = hinfo;

	oripal = (RGBQUAD*)malloc(sizeof(RGBQUAD) * hinfo.biClrUsed);
	fread(oripal, sizeof(RGBQUAD), hinfo.biClrUsed, file);

	for (i = 0; i < hinfo.biClrUsed; i++)
	{
		printf("Original palette %d B : %d\n", i, oripal[i].rgbBlue);
		printf("Original palette %d G : %d\n", i, oripal[i].rgbGreen);
		printf("Original palette %d R : %d\n\n", i, oripal[i].rgbRed);
	}


	rwsize = WIDTHBYTES(hinfo.biBitCount * hinfo.biWidth);
	rwsize2 = WIDTHBYTES(ohinfo.biBitCount * ohinfo.biWidth);

	fseek(file, hf.bfOffBits, SEEK_SET);

	lpImg = (BYTE*)malloc(rwsize*hinfo.biHeight);

	fread(lpImg, sizeof(char), rwsize*hinfo.biHeight, file);

	fclose(file);

	lpOutImg = lpImg;

	swappal = (RGBQUAD*)malloc(sizeof(RGBQUAD) * hinfo.biClrUsed);
	int buf;
	for (i = 0; i < hinfo.biClrUsed; i++)
	{
		printf("input palette %d B : ", i);
		scanf("%d", &buf);
		clearinputbuffer() ;
		swappal[i].rgbBlue = buf>255 ? (unsigned char)255 : buf < 0 ? 0 : (unsigned char)buf;
		printf("input palette %d G : ", i);
		scanf("%d", &buf);
		clearinputbuffer();
		swappal[i].rgbGreen = buf > 255 ? (unsigned char)255 : buf < 0 ? 0 : (unsigned char)buf;
		printf("input palette %d R : ", i);
		scanf("%d", &buf);
		clearinputbuffer() ;
		swappal[i].rgbRed = buf > 255 ? (unsigned char)255 : buf < 0 ? 0 : (unsigned char)buf;
		printf("\n");
	}

	file = fopen("logo_swap.bmp", "wb");

	fwrite(&ohf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&ohinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	fwrite(swappal, sizeof(RGBQUAD), hinfo.biClrUsed, file);
	fwrite(lpOutImg, sizeof(char), rwsize2*hinfo.biHeight, file);
	fclose(file);

	free(lpImg);
	free(oripal);
	free(swappal);
	printf("logo_swap.bmp!!\n\n");
}

void clearinputbuffer() // 입력 버퍼 클리어
{
	while (getchar() != '\n');
}

int crop()
{
	int p1x, p1y, p2x, p2y, fi;
	int i, j;

	BITMAPFILEHEADER ohf;
	BITMAPINFOHEADER ohinfo;

	printf("RUN crop()\n\n");

	file = fopen("ori.bmp", "rb");

	if (file == NULL)
	{
		printf("Error At File open!!!\n");
		exit(1);
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file);

	if (hf.bfType != 0x4D42)
	{
		printf("File is NOT BMP\n");
		exit(1);
	}

	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file);

	printf("File size : %d\n", hf.bfSize);
	printf("offset : %d\n", hf.bfOffBits);
	printf("Image Size : (%dX%d)\n", hinfo.biWidth, hinfo.biHeight);
	printf("%d BPP \n", hinfo.biBitCount);

	printf("P1 x : ");
	scanf("%d", &p1x);
	clearinputbuffer();

	printf("P1 y : ");
	scanf("%d", &p1y);
	clearinputbuffer();

	printf("P2 x : ");
	scanf("%d", &p2x);
	clearinputbuffer();

	printf("P2 y : ");
	scanf("%d", &p2y);
	clearinputbuffer();

	printf("P1 : %4d, %4d\n", p1x, p1y);
	printf("P2 : %4d, %4d\n", p2x, p2y);

	if (p1x<0 || p1x>hinfo.biWidth || p1y<0 || p1y>hinfo.biHeight || p2x<0 || p2x>hinfo.biWidth || p2y<0 || p2y>hinfo.biHeight)
	{
		printf(" check your input!!! \n");
		return -1;
	}

	if (p1x > p2x)
	{
		fi = p1x;
		p1x = p2x;
		p2x = fi;
	}

	if (p1y > p2y)
	{
		fi = p1y;
		p1y = p2y;
		p2y = fi;
	}

	ohf = hf;
	ohinfo = hinfo;

	ohinfo.biWidth = p2x - p1x + 1;
	ohinfo.biHeight = p2y - p1y + 1;

	rwsize = WIDTHBYTES(hinfo.biBitCount*hinfo.biWidth);
	rwsize2 = WIDTHBYTES(ohinfo.biBitCount*ohinfo.biWidth);

	ohf.bfSize = rwsize2 * ohinfo.biHeight + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	fseek(file, hf.bfOffBits, SEEK_SET);
	lpImg = (BYTE*)malloc(rwsize*hinfo.biHeight);
	fread(lpImg, sizeof(char), rwsize*hinfo.biHeight, file);
	fclose(file);

	lpOutImg = (BYTE*)malloc(rwsize2 * ohinfo.biHeight);

	for (i = 0; i < ohinfo.biHeight; i++)
	{
		for (j = 0; j < ohinfo.biWidth; j++)
		{
			lpOutImg[i*rwsize2 + 3 * j + 0] = lpImg[(i + p1y)*rwsize + 3 * (j + p1x) + 0];
			lpOutImg[i*rwsize2 + 3 * j + 1] = lpImg[(i + p1y)*rwsize + 3 * (j + p1x) + 1];
			lpOutImg[i*rwsize2 + 3 * j + 2] = lpImg[(i + p1y)*rwsize + 3 * (j + p1x) + 2];
		}
	}

	file = fopen("crop.bmp", "wb");
	fwrite(&ohf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&ohinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	fwrite(lpOutImg, sizeof(char), rwsize2*ohinfo.biHeight, file);
	fclose(file);
	free(lpImg);
	free(lpOutImg);
	printf("Check crop.bmp!!!\n\n");
}