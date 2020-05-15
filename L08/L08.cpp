#include "S2BS.h"

using namespace std;

int main()
{
    vector<char> charTab{ 'z' };
    vector<bitset<bits>> bitsetArray = S2BS(charTab, false);
	vector<bool> bitsetArrayRewrite;
    
	//Rewriting 2d bitsetArray to 1d bitsetArrayRewrite
	for (int i = 0; i < bitsetArray.size(); i++)
	{
		for (int j = 0; j < bits; j++)
			bitsetArrayRewrite.push_back(bitsetArray[i][j]);
	}
}

//Plan dzialania:
//1. Napisac funkcje do wykonywania mnozenia macierzowego
//X2. Wydzielic S2BS i dostoswac do projektu
//3. Zaimplementowac funkcje kodujaca kodem Hamming(7,4)
//4. Napisac funkcje wprowadzajaca bit bledu (negujaca wskazany nr bitu)
//5. Napisac dekoder kodu Hamminga(7,4)
//6. Zmodyfikowac powyzej napisany koder i dekoder, by obslugiwal kod SECDED (z dodatkowym bitem parzystosci)
//    - ten punkt realizowac rownolegle z powyzszymi - dodac przelaczniki
