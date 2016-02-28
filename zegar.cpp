#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include <windows.h>
#include <unordered_map>

using namespace std;

vector<string> ReturnCharArray(string filename);
void PrintAsciiChar(vector<string> input);
void PrintMultipleChar(vector<string> first, vector<string> second);
void PrintAsciiTime(vector<string> hourfirst, vector<string> hoursecond,
                    vector<string> minutefirst, vector<string> minutesecond,
                    vector<string> secondfirst, vector<string> secondsecond);
//Wszystkie pliki zawieraja tylko X linijek
const int FileLength = 4;

int main()
{

  vector<string> hf;
  vector<string> hs;
  vector<string> mf;
  vector<string> ms;
  vector<string> sf;
  vector<string> ss;
  vector<string> onechar = ReturnCharArray("1.txt");
  vector<string> twochar = ReturnCharArray("2.txt");
  vector<string> threechar = ReturnCharArray("3.txt");
  vector<string> fourchar = ReturnCharArray("4.txt");
  vector<string> fivechar = ReturnCharArray("5.txt");
  vector<string> sixchar = ReturnCharArray("6.txt");
  vector<string> sevenchar = ReturnCharArray("7.txt");
  vector<string> eightchar = ReturnCharArray("8.txt");
  vector<string> ninechar = ReturnCharArray("9.txt");
  vector<string> zerochar = ReturnCharArray("0.txt");
  vector<string> colon = ReturnCharArray("colon.txt");
  unordered_map<char,vector<string>> a ={{'0',zerochar},{'1',onechar},
  										{'2',twochar},{'3',threechar},{'4',fourchar},
										{'5',fivechar},{'6',sixchar},{'7',sevenchar},
										{'8',eightchar},{'9',ninechar}};
  while(true)
  {
  		char buffer[80]; //deklaracja pojemnika na czas
	time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
	timeinfo = localtime(&rawtime);
    strftime(buffer,80,"%H%M%S",timeinfo);
    //sprawic, by buffer odnosil sie jakos to slownika, i potem zdefiniowac wartosci zegara
    hf = a[buffer[0]];
    hs = a[buffer[1]];
    mf = a[buffer[2]];
    ms = a[buffer[3]];
    sf = a[buffer[4]];
    ss = a[buffer[5]];
    PrintAsciiTime(hf,hs,mf,ms,sf,ss);
    buffer[0] = 0;
    Sleep(1000);
    system("cls");
  }
}
/*
Zwraca tablice ze znakami ascii, chyba trzeba dac endl pomiedzy liniami
plik powinien zawierav jeden znak ascii, to jest tylko 1 lub 2 etc.
endl moze przeszkadzac- mialem racje
*/

vector<string> ReturnCharArray(string filename)
{
  fstream file;
  string data;
  vector<string> characters;
  file.open(filename.c_str(),ios::in);
  if (file.good())
  {
    while(!file.eof())
    {
      getline(file,data);
      characters.push_back(data);
      //characters.push_back("\n"); nie potrzebne
    }
  }
  file.close();
  return characters;
}

void PrintAsciiChar(vector<string> input) // dziala dla jednego znaku :)
{
  /* Zakladajac, ze poprzednia funkcja dziala, powinnismy wydrukowac
    poprzez iteracje wartosci tablicy characters, narazie jeden znak
  */
  for(int i = 0; i<FileLength;i++)
  {
    cout << input[i] << endl;
  }
}
void PrintMultipleChar(vector<string> first, vector<string> second)
{
	for (int i = 0; i<FileLength;i++)
	{
		cout << first[i] << " " << second[i] << endl;
	}
}
void PrintAsciiTime(vector<string> hourfirst, vector<string> hoursecond,
                    vector<string> minutefirst, vector<string> minutesecond,
                    vector<string> secondfirst, vector<string> secondsecond)
{
  for (int i = 0; i<FileLength;i++)
  {
    vector<string> colon = ReturnCharArray("colon.txt");
    cout << hourfirst[i] << hoursecond[i] << colon[i]
    << minutefirst[i] << minutesecond[i] << colon[i]
    << secondfirst[i] << secondsecond[i] << endl;

  }

}
