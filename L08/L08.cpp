#include "S2BS.h"

using namespace std;

vector<vector<bool>> matrixMultiplicationWithModulo(vector<vector<bool>> A, vector<vector<bool>> B)
{
	if (A[0].size() != B.size())
	{
		cout << "[matrixMultiplicationWithModulo]\tNumber of A's columns are not equal number of B's rows" << endl;
		return vector<vector<bool>>(1, vector<bool>(0, 0));
	}

	vector<vector<bool>> result(A.size(), vector<bool>(B[0].size(), 0));
	bool temp = 0;

	for (size_t r = 0; r < A.size(); r++)
	{
		for (size_t c = 0; c < B[0].size(); c++)
		{
			temp = 0;
			for (size_t i = 0; i < A[0].size(); i++)
				temp = temp ^ A[r][i] & B[i][c]; //temp = temp + A[r][i] * B[i][c];		
			result[r][c] = temp;// % 2;
		}
	}

	return result;
}

vector<vector<bool>> Hamming74Coder(vector<vector<bool>> data, bool isSECDED)
{
	vector<vector<bool>> G{ {1,1,0,1},
							{1,0,1,1},
							{1,0,0,0},
							{0,1,1,1},
							{0,1,0,0},
							{0,0,1,0},
							{0,0,0,1} };
	if (isSECDED == false) return matrixMultiplicationWithModulo(G, data);
	else
	{
		vector<vector<bool>> codedData = matrixMultiplicationWithModulo(G, data);
		bool parityBit = 0;

		for (size_t r = 0; r < codedData.size(); r++)
			parityBit = parityBit ^ codedData[r][0];
		codedData.push_back(vector<bool>{parityBit});

		return codedData;
	}
}

//position numbered from 1
//allowed value of position = <1,7>
vector<vector<bool>> bitNegator(vector<vector<bool>> codedData, unsigned int position)
{
	if (position > 7)
	{
		cout << "[bitNegator]\tPosition number out of range! Function will return unchanged vector.\n";
		return codedData;
	}

	codedData[position - 1][0] = !(codedData[position - 1][0]);
	return codedData;
}

//double bit negation
//position1 & position2 numbered from 1
//allowed value of positions = <1,7>
vector<vector<bool>> bitNegator(vector<vector<bool>> codedData, unsigned int position1, unsigned int position2)
{
	if (position1 > 7 || position2 > 7)
	{
		cout << "[bitNegator]\tPosition number out of range! Function will return unchanged vector.\n";
		return codedData;
	}

	codedData[position1 - 1][0] = !(codedData[position1 - 1][0]);
	codedData[position2 - 1][0] = !(codedData[position2 - 1][0]);
	return codedData;
}

vector<vector<bool>> Hamming74Decoder(vector<vector<bool>> codedData, bool isSECDED)
{
	//parity check
	vector<vector<bool>> H{ {1,0,1,0,1,0,1},
							{0,1,1,0,0,1,1},
							{0,0,0,1,1,1,1} };


	//necessary only if isSECDED mode is on
	vector<bool> tmp = codedData.back();
	bool parityBit = tmp.back();
	if (isSECDED) codedData.pop_back();
	//

	vector<vector<bool>> decodedParity = matrixMultiplicationWithModulo(H, codedData);
	unsigned int position = 0;

	for (size_t r = 0; r < decodedParity.size(); r++)
	{
		position = position + (unsigned int)(pow(2, r) * (unsigned int)(decodedParity[r][0]));
	}
	//cout << position << endl;
	//error correction
	if (position != 0)
	{
		cout << "[Hamming74Decoder]\tBit corruption detected at position = " << position << endl;
		codedData[position - 1][0] = !(codedData[position - 1][0]);

		if (isSECDED)
		{
			bool currentParityBit = 0;

			for (size_t r = 0; r < codedData.size(); r++)
				currentParityBit = currentParityBit ^ codedData[r][0];

			if (currentParityBit != parityBit)
			{
				cout << "[Hamming74Decoder]\tDouble bit corruption detected! Retransmission needed. Function will return given coded data.\n";
				codedData[position - 1][0] = !(codedData[position - 1][0]);
				codedData.push_back(tmp);
				return codedData;
			}
		}

	}
	//else if(position==0 && currentParityBit == parityBit

	//data bits extraction
	vector<vector<bool>> decodedData(bits, vector<bool>(1));
	vector<unsigned int> dataBitsPosition{ 2,4,5,6 };

	for (size_t i = 0; i < bits; i++)
		decodedData[i][0] = codedData[dataBitsPosition[i]][0];

	return decodedData;

}

int main()
{
	/*bool a = 1;
	bool b = 1;
	cout << (bool)(a^b) << endl;*/
	vector<char> charTab{ 'z' };
	vector<bitset<bits>> bitsetArray = S2BS(charTab, false);
	vector<vector<bool>> bitsetArrayRewrite(bits, vector<bool>(1));

	//Rewriting 2d bitsetArray to 1d bitsetArrayRewrite
	for (size_t j = 0; j < bits; j++)
	{
		for (size_t i = 0; i < bitsetArray.size(); i++)
			//bitsetArrayRewrite.push_back(bitsetArray[i][j]);
			bitsetArrayRewrite[j][i] = bitsetArray[i][j];
	}

	/*for (size_t r = 0; r < bitsetArrayRewrite.size(); r++)
	{
		for (size_t c = 0; c < bitsetArrayRewrite[r].size(); c++)
			cout << bitsetArrayRewrite[r][c] << " ";
		cout << endl;
	}*/

	//{{20,15},{14,10}} w/o modulo
	/*vector<vector<unsigned int>> A{ {2,3,4},{1,2,3} }, B{ {1,2},{2,1},{3,2} };
	vector<vector<unsigned int>> result = matrixMultiplication(A, B);*/

	//{{1,2},{1,0}} w/o modulo
	/*vector<vector<bool>> A{ {1,0,1},{0,1,0} }, B{ {0,1},{1,0},{1,1} };
	vector<vector<bool>> result = matrixMultiplicationWithModulo(A, B);*/

	//{{2,2},{1,2}} w/o modulo
	/*vector<vector<bool>> A{ {1,1,1},{1,0,1} }, B{ {1,1},{1,0},{0,1} };
	vector<vector<bool>> result = matrixMultiplicationWithModulo(A, B);*/

	//{{3},{3},{1}} w/o modulo
	/*vector<vector<bool>> A{ {1,1,1,1},{1,0,1,1},{0,1,1,0} }, B{ {1},{0},{1},{1} };
	vector<vector<bool>> result = matrixMultiplicationWithModulo(A, B);*/

	vector<vector<bool>> HammingCode = Hamming74Coder(bitsetArrayRewrite, true);
	for (size_t r = 0; r < HammingCode.size(); r++)
	{
		for (size_t c = 0; c < HammingCode[r].size(); c++)
			cout << HammingCode[r][c] << " ";
		cout << endl;
	}
	cout << endl;
	vector<vector<bool>> corruptedHammingCode = bitNegator(HammingCode, 4);
	for (size_t r = 0; r < corruptedHammingCode.size(); r++)
	{
		for (size_t c = 0; c < corruptedHammingCode[r].size(); c++)
			cout << corruptedHammingCode[r][c] << " ";
		cout << endl;
	}
	cout << endl;
	vector<vector<bool>> decodedData = Hamming74Decoder(corruptedHammingCode, true);
	for (size_t r = 0; r < decodedData.size(); r++)
	{
		for (size_t c = 0; c < decodedData[r].size(); c++)
			cout << decodedData[r][c] << " ";
		cout << endl;
	}
}

//Plan dzialania:
//x1. Napisac funkcje do wykonywania mnozenia macierzowego
//X2. Wydzielic S2BS i dostoswac do projektu
//x3. Zaimplementowac funkcje kodujaca kodem Hamming(7,4)
//x4. Napisac funkcje wprowadzajaca bit bledu (negujaca wskazany nr bitu)
//x5. Napisac dekoder kodu Hamminga(7,4)
//6. Zmodyfikowac powyzej napisany koder i dekoder, by obslugiwal kod SECDED (z dodatkowym bitem parzystosci)
//    - ten punkt realizowac rownolegle z powyzszymi - dodac przelaczniki
