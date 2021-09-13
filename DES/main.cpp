#include<iostream>
#include<string>
#include <sstream>
#include <cmath>
#include <cstdlib>

using namespace std;


//---------------------------------------------------------
//-------------------Potrzebne Tabele----------------------
//---------------------------------------------------------

int IpMessage[64] = {
 58,  50,  42,  34,  26,  18,  10,  2,
 60,  52,  44,  36,  28,  20,  12,  4,
 62,  54,  46,  38,  30,  22,  14,  6,
 64,  56,  48,  40,  32,  24,  16,  8,
 57,  49,  41,  33,  25,  17,   9,  1,
 59,  51,  43,  35,  27,  19,  11,  3,
 61,  53,  45,  37,  29,  21,  13,  5,
 63,  55,  47,  39,  31,  23,  15,  7
};

int IpKey[56] = {
57,  49,  41,  33,  25,  17,   9,
1,   58,  50,  42,  34,  26,  18,
10,   2,  59,  51,  43,  35,  27,
19,  11,   3,  60,  52,  44,  36,
63,  55,  47,  39,  31,  23,  15,
7 ,  62,  54,  46,  38,  30,  22,
14,   6,  61,  53,  45,  37,  29,
21,  13,   5,  28,  20,  12,   4
};

int IpKey2[48] = {
14,  17,  11,  24,   1,   5,
3,  28,  15,   6,  21,  10,
23,  19,  12,   4,  26,   8,
16,   7,  27,  20,  13,   2,
41,  52,  31,  37,  47,  55,
30,  40,  51,  45,  33,  48,
44,  49,  39,  56,  34,  53,
46,  42,  50,  36,  29,  32
};

int E[48] = {
32,   1,   2,   3,   4,   5,
4,   5,   6,   7,   8,   9,
8,   9,  10,  11,  12,  13,
12,  13,  14,  15,  16,  17,
16,  17,  18,  19,  20,  21,
20,  21,  22,  23,  24,  25,
24,  25,  26,  27,  28,  29,
28,  29,  30,  31,  32,   1
};

int IpFunF[32] = {
16,   7,  20,  21,
29,  12,  28,  17,
1 ,  15,  23,  26,
5 ,  18,  31,  10,
2 ,   8,  24,  14,
32,  27,   3,   9,
19,  13,  30,   6,
22,  11,   4,  25
};

int ipFinal[64] = {
40,  8,  48,  16,  56,  24,  64,  32,
39,  7,  47,  15,  55,  23,  63,  31,
38,  6,  46,  14,  54,  22,  62,  30,
37,  5,  45,  13,  53,  21,  61,  29,
36,  4,  44,  12,  52,  20,  60,  28,
35,  3,  43,  11,  51,  19,  59,  27,
34,  2,  42,  10,  50,  18,  58,  26,
33,  1,  41,   9,  49,  17,  57,  25
};

int sBox[8][4][16]=
	{{
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
    },
    {
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
    },
    {
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
    },
    {
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
    },
    {
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
    },
    {
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
    },
    {
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
    },
    {
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
    }};

string numbersFour[16] = {
"0000", "0001", "0010", "0011",
"0100", "0101", "0110", "0111",
"1000", "1001", "1010", "1011",
"1100", "1101", "1110", "1111"
};

string numbersTwo[4] = {
"00", "01", "10", "11"
};

string hexNumbers[16] = {
"0","1","2","3",
"4","5","6","7",
"8","9","a","b",
"c","d","e","f"
};

string keyRound;

//---------------------------------------------------------
//------------------Zamiana Bin na Hex---------------------
//---------------------------------------------------------
string binToHex(string binData)
{
    string temp;
    string hex;
    int j=0;
    int i=0;


    for(i=0; i<binData.size(); i=i+4)
        {

        temp = {binData[i],binData[i+1],binData[i+2],binData[i+3]};

           for(j=0;j<16;j++)
           {
               if(numbersFour[j] == temp)
                {

                   hex = hex + hexNumbers[j];
                }
           }

        }
    return hex;
}


//---------------------------------------------------------
//------------------Zamiana Dec na Bin---------------------
//---------------------------------------------------------
int decToBin(int dec)
{
    long long binaryNumber = 0;
    int rest, i = 1, step = 1;

    while (dec!=0)
    {
        rest = dec%2;
        dec /= 2;
        binaryNumber += rest*i;
        i *= 10;
    }
    return binaryNumber;
}


//---------------------------------------------------------
//----------------Zamiana Int na String--------------------
//---------------------------------------------------------
string intToString(int data)
{
    string word;
    ostringstream decToString;
    decToString << data;
    word = decToString.str();
    return word;
}


//---------------------------------------------------------
//------------Pierwsza Permutacja Wiadomosci---------------
//---------------------------------------------------------
string firstPerm(string data)
{
    string returnString;

    for(int i=0; i<64; i++)
        {
            returnString = returnString + data[IpMessage[i]-1];
        }

        return returnString;
}


//---------------------------------------------------------
//-----------Ostateczna Permutacja Wiadomosci--------------
//---------------------------------------------------------
string finalPerm(string data)
{
    string returnString;

    for(int i=0; i<64; i++)
        {
            returnString = returnString + data[ipFinal[i]-1];
        }

        return returnString;
}


//---------------------------------------------------------
//----------------Permutacja w Funkcji F-------------------
//---------------------------------------------------------
string permFunF(string data)
{
    string returnString;

    for(int i=0; i<32; i++)
        {
            returnString = returnString + data[IpFunF[i]-1];
        }

        return returnString;
}


//---------------------------------------------------------
//--------------Pierwsza Permutacja Klucza-----------------
//---------------------------------------------------------
string keyPerm(string data)
{
    string returnString;

    for(int i=0; i<56; i++)
        {
            returnString = returnString + data[IpKey[i]-1];
        }

        return returnString;
}


//---------------------------------------------------------
//--------------Ostatnia Permutacja Klucza-----------------
//---------------------------------------------------------
string keyPerm2(string data)
{
    string returnString;

    for(int i=0; i<48; i++)
        {
            returnString = returnString + data[IpKey2[i]-1];
        }

        return returnString;
}


//---------------------------------------------------------
//----------------------Ekspansja--------------------------
//---------------------------------------------------------
string expansion(string data)
{
        string returnString;

    for(int i=0; i<48; i++)
        {
            returnString = returnString + data[E[i]-1];
        }

        return returnString;
}


//---------------------------------------------------------
//---------------------Funkcja XOR-------------------------
//---------------------------------------------------------
string Xor(string a, string b){
	string result = "";
	int size = b.size();
	for(int i = 0; i < size; i++){
		if(a[i] != b[i]){
			result += "1";
		}
		else{
			result += "0";
		}
	}
	return result;
}


//---------------------------------------------------------
//---------------------Funkcja sBOX------------------------
//---------------------------------------------------------
string xBoxFun(string box, int which)
{

int two = 0;
int four = 0;
int numberFromBox = 0;
string temp;

temp = {box[0],box[5]};

    for(int i=0; i<4;i++)
        {
            if(numbersTwo[i] == temp)
                two = i;
        }

temp = {box[1],box[2],box[3],box[4]};

    for(int i=0; i<16;i++)
        {
            if(numbersFour[i] == temp)
                four = i;
        }

    numberFromBox = sBox[which][two][four];
    box = numbersFour[numberFromBox];

    return box;
}


//---------------------------------------------------------
//-----------------Przetwarzanie Klucza--------------------
//---------------------------------------------------------
string keyGenerator(string mainKey, int round)
{
    string leftKey;         //Lewy Klucz
    string rigthKey;        //Prawy Klucz
    string shiftRigth;      //Przesuniecie w Prawo
    string shiftLeft;       //Przesuniecie w Prawo


    for(int i=0; i<28; i++)
    leftKey = leftKey + mainKey[i];

    for(int i=28; i<56; i++)
    rigthKey = rigthKey + mainKey[i];

    shiftLeft = leftKey;
    shiftRigth = rigthKey;

    leftKey.clear();
    rigthKey.clear();

    if(round == 0 || round == 1 || round == 8 || round == 15)
    {
            for(int i=0; i<27; i++)
        {
            leftKey = leftKey + shiftLeft[i+1];
            rigthKey = rigthKey + shiftRigth[i+1];
        }

        leftKey = leftKey + shiftLeft[0];
        rigthKey = rigthKey + shiftRigth[0];
    }

    else
    {
            for(int i=0; i<26; i++)
        {
            leftKey = leftKey + shiftLeft[i+2];
            rigthKey = rigthKey + shiftRigth[i+2];
        }

        leftKey = leftKey + shiftLeft[0] + shiftLeft[1];
        rigthKey = rigthKey + shiftRigth[0] + shiftRigth[1];

    }

    mainKey = leftKey + rigthKey;


    return mainKey;

}


//---------------------------------------------------------
//---------------Przetwarzanie Danych cz2------------------
//---------------------------------------------------------
string dataGenerator(string mainMessage, string mainKey, int round)
{

    string leftData;        //Lewe Dane
    string rigthData;       //Prawe Dane
    string functionData;    //Klucz Xor Dane
    string s1,s2,s3,s4,s5,s6,s7,s8;
    string copyRigthData;
    string leftKey;         //Lewy Klucz
    string rigthKey;        //Prawy Klucz


    for(int i=0; i<32; i++)
    leftData = leftData + mainMessage[i];

    for(int i=32; i<64; i++)
    rigthData = rigthData + mainMessage[i];


    copyRigthData = rigthData;
    rigthData = expansion(rigthData);


    functionData = Xor(mainKey,rigthData);

    for(int i=0; i<6; i++)
    {
      s1 = s1 + functionData[i];
      s2 = s2 + functionData[i+6];
      s3 = s3 + functionData[i+12];
      s4 = s4 + functionData[i+18];
      s5 = s5 + functionData[i+24];
      s6 = s6 + functionData[i+30];
      s7 = s7 + functionData[i+36];
      s8 = s8 + functionData[i+42];
    }

    s1 = xBoxFun(s1,0);
    s2 = xBoxFun(s2,1);
    s3 = xBoxFun(s3,2);
    s4 = xBoxFun(s4,3);
    s5 = xBoxFun(s5,4);
    s6 = xBoxFun(s6,5);
    s7 = xBoxFun(s7,6);
    s8 = xBoxFun(s8,7);

    functionData = s1 + s2 + s3 + s4 + s5 + s6 + s7 + s8;
    functionData = permFunF(functionData);


    rigthData = Xor(leftData,functionData);
    leftData = copyRigthData;

    return (leftData+rigthData);

}


//---------------------------------------------------------
//---------------Przetwarzanie Danych cz1------------------
//---------------------------------------------------------
string prepareData(string data, int dataSize)
{
    int dataTab[64];
    string dataBin[64];
    string dataMSG;

    for(int i=0; i< dataSize; i++)
    {
        dataTab[i] = decToBin(data[i]);
    }

 for(int i=0; i< dataSize; i++)
    {
        dataBin[i] = intToString(dataTab[i]);


        if(dataBin[i].size() == 6)
             dataBin[i] = "00" + dataBin[i];

        else if(dataBin[i].size() == 7)
            dataBin[i] = "0" + dataBin[i];

        dataMSG = dataMSG + dataBin[i];
    }

    return dataMSG;
}

//---------------------------------------------------------
//-------------------------Main----------------------------
//---------------------------------------------------------

int main()
{
//---------------------------------------------------------
//-----------------------Zmienne---------------------------
//---------------------------------------------------------
int keyTab[64];         //Tablica Asci
int sizeOfMessage;      //Dlugosc Wiadomosci
int sizeOfKey;          //Dlugosc Klucza
int licznik;            //Ilosc paczek danych
string keyBin[64];      //Dane Asci Binarne
string mainMessage;     //Uzyteczny Ciag Binarny
string mainKey;         //Uzyteczny Ciag Binarny
string roundData;       //Dane do ka¿dej paczki
string leftRoundData;   //Lewa Czesc danych
string rigthRoundData;  //Prawa Czesc danych
string keyToFun;        //Klucz do Funkcji
string endMessage;      //Koncowa wiadomosc z kazdej rundy
string roundMessage;    //Poczatkowa wiadomosc w kazdej rundzie
string wholeEndMessage; //Koncowa Wartosc zakodowanej wiadomosci
string message;         //Wiadomosc
string key;             //Klucz


//---------------------------------------------------------
//-----------------Wprowadzenie danych---------------------
//---------------------------------------------------------
cout<<"==============================================================="<<endl;
cout<<"Wiadomosc do Zakodowania"<<endl;
cout<<endl;
cout<<"   Podaj Wiadomosc:          "; cin>>message;
cout<<"   Podaj Klucz:              "; cin>>key;
          while(key.size() > 8)
          {
              cout<<"   Klucz jest za dlugi!"<<endl;
              cout<<"   Podaj Klucz:                    "; cin>>key;
          }
cout<<"==============================================================="<<endl;
cout<<endl;


//---------------------------------------------------------
//-----------------Uzupe³nianie Danych---------------------
//---------------------------------------------------------
 sizeOfMessage = message.size();
 sizeOfKey = key.size();

 mainMessage = prepareData(message,sizeOfMessage);
 mainKey = prepareData(key,sizeOfKey);

 licznik = mainKey.size() % 64;
    if(licznik != 0)
    {
        for(int i=0;i<64-licznik;i++)
        mainKey = mainKey + "0";
    }

    licznik = mainMessage.size() % 64;
    if(licznik != 0)
    {
        for(int i=0;i<64-licznik;i++)
        mainMessage = mainMessage + "0";
    }


//---------------------------------------------------------
//----------------G³owna Czesc Algorytmu-------------------
//---------------------------------------------------------
    keyRound = mainKey;
    for(int howMuchMsg=0; howMuchMsg<(mainMessage.size()/64); howMuchMsg++)
    {
            roundMessage.clear();
            leftRoundData.clear();
            rigthRoundData.clear();
            endMessage.clear();

            for(int letters=0; letters<64;letters++)
              roundMessage = roundMessage + mainMessage[(letters+(64*howMuchMsg))];

            mainKey = keyRound;
            mainKey = keyPerm(mainKey);
            roundMessage = firstPerm(roundMessage);

            for(int i=0; i<16; i++)
                {
                    mainKey = keyGenerator(mainKey,i);
                    keyToFun = keyPerm2(mainKey);
                    roundMessage = dataGenerator(roundMessage, keyToFun,i);
                }

            for(int i=0; i<32;i++)
                {
                    leftRoundData = leftRoundData + roundMessage[i];
                    rigthRoundData = rigthRoundData + roundMessage[i+32];
                }

           endMessage = rigthRoundData + leftRoundData;
           endMessage = finalPerm(endMessage);
           wholeEndMessage = wholeEndMessage + endMessage;
    }


   cout<<"==============================================================="<<endl;
   cout<<"Wiadomosc Po Zakodowaniu"<<endl;
   cout<<endl;
   cout<<"   BIN: "<<wholeEndMessage<<endl;
   cout<<"   HEX: "<<binToHex(wholeEndMessage)<<endl;
   cout<<"==============================================================="<<endl;
}
