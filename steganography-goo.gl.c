#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <cstring>

typedef unsigned char byte;

#define BYTELEN 8

typedef struct {
	byte signature[2];
	byte size[4];
	byte reserved[2];
	byte reserved1[2];
	byte offset[4];
	byte sizeBITMAPINFOHEADER[4]; // must be 40
	byte width[4];
	byte height[4];
	byte planes[2];
	byte numofbitsperpixel[2];
	byte compressiontype[4];
	byte imgsize[4]; // includes padding?
	byte horizontalres[4];
	byte verticalres[4];
	byte numofcolors[4];
	byte numofimportantcolors[4]; // 54 bytes
} header;


FILE * fileopen(const char * filename);
void loadheaders(header * head, FILE * file);
void printheader(header * head);
int readonehex(byte * translate);

int main() //////////////////////////////////////////MAIN XD/////////////////////
{
	header * bmphead = NULL;
	//bmphead = (*bmphead) malloc(sizeof(byte) * 54);
	FILE * file = fileopen("CRACKME.bmp");
	//byte XD[1000];
	bmphead = (header *) malloc(sizeof(byte) * 54);
	loadheaders(bmphead, file);
	if (file == NULL) return false;
	//for (int i = 0; i < 1000; i++) fread(&XD[i], sizeof(byte), 1, file);
	/*for (int i = 0; i < 2; i++)
	{
		printf("%hhx ", bmphead->signature[i]);
	}*/
	printheader(bmphead);
	//printf("%i", bmphead->width[0]);// dziala
	int x;// = readonehex(bmphead->height, 4);
	//printf("%i", x);// dziala
	byte hold[BYTELEN], byteholder = NULL; // hold trzyma calego bajta i z niego wyciagamy lsb, a do byteholder ladujemy bity w całość
	//bool flag;
	byte * arr = (byte *)malloc(sizeof(byte) * readonehex(bmphead->height) * readonehex(bmphead->width));// chyba bez 3
	printf("%i\n\n", sizeof(byte) * readonehex(bmphead->height) * readonehex(bmphead->width) * 3);
	int size = sizeof(byte) * readonehex(bmphead->height) * readonehex(bmphead->width) * 3;
	//memset(arr, '\0', size);
	//fread(arr, sizeof(byte), size, file);
	int counter = 0, flag;
	//fread(&hold, sizeof(byte), 1, file);
	//flag = hold & 1;
	//byteholder |= flag << 7;
	for (int i = 0; i < 1024; i=i+BYTELEN, counter++)//bierzemy 8 bajtow, z kazdego najmniejszy bit, jeden bit odpowiada kolorowi b g r i moze padding, 
	{
		fread(&hold, sizeof(byte), BYTELEN, file);
		//if (hold[0] & 1) byteholder[0] |= 1 <<(8-8%i);//XDDDDDDDD co to jest, ustawiamy bit w miejscu najbardziej na lewo, caly czas schodzac, wycaigajac lsb
		//else byteholder[0] |= 0 << (8 - 8 % i); //moze dziala xd, sprawdzimy, nie mozna modulo 0
		//if(hold%2) byteholder |= 1 << (8 - 8 % i);
		//else byteholder |= 0 << (8 - 8 % i);
		//flag = hold & 1;
		//byteholder |= flag << (8 % i);//dla 8 jakies smieci, to 7, w koncu ascii to 7 bit
		#if (BYTELEN==8)
		byteholder |= (hold[0] & 1) << 0;
		byteholder |= (hold[1] & 1) << 1;
		byteholder |= (hold[2] & 1) << 2;
		byteholder |= (hold[3] & 1) << 3;
		byteholder |= (hold[4] & 1) << 4;
		byteholder |= (hold[5] & 1) << 5;
		byteholder |= (hold[6] & 1) << 6;
		byteholder |= (hold[7] & 1) << 7;
		#endif // BYTELEN==8
		#if (BYTELEN == 7)
		byteholder |= (hold[0] & 1) << 6;//tez gowno daje
		byteholder |= (hold[1] & 1) << 5;
		byteholder |= (hold[2] & 1) << 4;
		byteholder |= (hold[3] & 1) << 3;
		byteholder |= (hold[4] & 1) << 2;
		byteholder |= (hold[5] & 1) << 1;
		byteholder |= (hold[6] & 1) << 0;
		#endif
		/*byteholder |= (hold[0] & 1) << 7;
		byteholder |= (hold[1] & 1) << 6;
		byteholder |= (hold[2] & 1) << 5;
		byteholder |= (hold[3] & 1) << 4;
		byteholder |= (hold[4] & 1) << 3;
		byteholder |= (hold[5] & 1) << 2;
		byteholder |= (hold[6] & 1) << 1;
		byteholder |= (hold[7] & 1) << 0;*/
		/*byteholder |= (hold[0] & 1) << 6;//tez gowno daje
		byteholder |= (hold[1] & 1) << 5;
		byteholder |= (hold[2] & 1) << 4;
		byteholder |= (hold[3] & 1) << 3;
		byteholder |= (hold[4] & 1) << 2;
		byteholder |= (hold[5] & 1) << 1;
		byteholder |= (hold[6] & 1) << 0;*/
		arr[counter] = byteholder;
		//memcpy(&arr[counter], &byteholder, sizeof(byteholder));
		byteholder = NULL;
	}
	for (int i = 0; i < 1024/BYTELEN; i++)//reszta to zera?
	{
		printf("%hhx ", arr[i]);
	}

	printf("\n\n");


	for (int i = 0; i < 1024 / BYTELEN; i++)//reszta to zera?
	{
		printf("%c ", arr[i]);
	}
	_getch();
}

FILE * fileopen(const char * filename)
{
	FILE * res = fopen(filename, "rb");
	if (res == NULL) {
		printf("couldnt open file\n");
		return res;
	}
	return res;
}

void loadheaders(header * head, FILE * file)
{
	/*for (int i = 0; i < 2; i++)
	{
		fread(&(head->signature[i]), sizeof(byte), 1, file);
	}*/
	fread(&(head->signature), sizeof(byte), 2, file); //should've defined sizes based upon bitmap header, meaning ifdef etc, just upon testing first flag
	fread(&(head->size), sizeof(byte), 4, file);
	fread(&(head->reserved), sizeof(byte), 2, file);
	fread(&(head->reserved1), sizeof(byte), 2, file);
	fread(&(head->offset), sizeof(byte), 4, file);
	fread(&(head->sizeBITMAPINFOHEADER), sizeof(byte), 4, file);
	fread(&(head->width), sizeof(byte), 4, file);
	fread(&(head->height), sizeof(byte), 4, file);
	fread(&(head->planes), sizeof(byte), 2, file);
	fread(&(head->numofbitsperpixel), sizeof(byte), 2, file);
	fread(&(head->compressiontype), sizeof(byte), 4, file);
	fread(&(head->imgsize), sizeof(byte), 4, file);
	fread(&(head->horizontalres), sizeof(byte), 4, file);
	fread(&(head->verticalres), sizeof(byte), 4, file);
	fread(&(head->numofcolors), sizeof(byte), 4, file);
	fread(&(head->numofimportantcolors), sizeof(byte), 4, file);
	
}

void printheader(header * head)
{
	printf("sign: ");
	for (int i = 0; i < 2; i++) printf("%hhx ", head->signature[i]);
	printf("\nsize: ");
	for (int i = 0; i < 4; i++) printf("%hhx ", head->size[i]);
	printf("\nres: ");
	for (int i = 0; i < 2; i++) printf("%hhx ", head->reserved[i]);
	printf("\nres1: ");
	for (int i = 0; i < 2; i++) printf("%hhx ", head->reserved1[i]);
	printf("\noffset: ");
	for (int i = 0; i < 4; i++) printf("%hhx ", head->offset[i]);
	printf("\nsizebitmap: ");
	for (int i = 0; i < 4; i++) printf("%hhx ", head->sizeBITMAPINFOHEADER[i]);
	printf("\nwidth: ");
	for (int i = 0; i < 4; i++) printf("%hhx ", head->width[i]);
	printf("\nheight: ");
	for (int i = 0; i < 4; i++) printf("%hhx ", head->height[i]);
	printf("\nplanes: ");
	for (int i = 0; i < 2; i++) printf("%hhx ", head->planes[i]);
	printf("\nnobpp: ");
	for (int i = 0; i < 2; i++) printf("%hhx ", head->numofbitsperpixel[i]);
	printf("\ncompres: ");
	for (int i = 0; i < 4; i++) printf("%hhx ", head->compressiontype[i]);
	printf("\nimgsize: ");
	for (int i = 0; i < 4; i++) printf("%hhx ", head->imgsize[i]);
	printf("\nhhres: ");
	for (int i = 0; i < 4; i++) printf("%hhx ", head->horizontalres[i]);
	printf("\nvrres: ");
	for (int i = 0; i < 4; i++) printf("%hhx ", head->verticalres[i]);
	printf("\nnumofcol: ");
	for (int i = 0; i < 4; i++) printf("%hhx ", head->numofcolors[i]);
	printf("\nnumofimprcol: ");
	for (int i = 0; i < 4; i++) printf("%hhx ", head->numofimportantcolors[i]);
}

int readonehex(byte * translate)
{
	/*int res = (int)translate[0];
	
	for (int i = 1; i < size; i++)
	{
		res += (int)translate[i];//ja dodaje pojedyncze bajty, to chyba nie to xD
	}
	return res;
	*/
	/*int res = 0, ressize = 0;
	for (int i = 0; i < size; i++)
	{
		if (translate[i] != 0)ressize++;
	}
	for (int i = 0; i < ressize; i++)
	{
		res += translate[i] * (16 * (ressize - i));
	}*/
	//int res = (translate[0] << 24) + (translate[1] << 16) + (translate[2] << 8) + translate[3];
	int res = translate[0] + (translate[1] << 8) + (translate[2] << 16) + (translate[3] << 24); // dziala little endian

	return res;
}
