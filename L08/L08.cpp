#include "S2BS.h"
#define verboseMode
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
	//=========== parity check ==============
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
	
	//=========== error correction =============
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

	//============= data bits extraction =================
	vector<vector<bool>> decodedData(bits, vector<bool>(1));
	vector<unsigned int> dataBitsPosition{ 2,4,5,6 };

	for (size_t i = 0; i < bits; i++)
		decodedData[i][0] = codedData[dataBitsPosition[i]][0];

	return decodedData;
}

int main()
{
	vector<char> charTab{ 'z' };
	vector<bitset<bits>> bitsetArray = S2BS(charTab, false);
	vector<vector<bool>> bitsetArrayRewrite(bits, vector<bool>(1));

	//Rewriting 2d bitsetArray to 1d bitsetArrayRewrite - already transposed -> vertical vector
	for (size_t j = 0; j < bits; j++)
	{
		for (size_t i = 0; i < bitsetArray.size(); i++)
			bitsetArrayRewrite[j][i] = bitsetArray[i][j];
	}

	vector<vector<bool>> HammingCode = Hamming74Coder(bitsetArrayRewrite, true);
#ifdef verboseMode
	cout << "After coding:\n";
	for (size_t r = 0; r < HammingCode.size(); r++)
	{
		for (size_t c = 0; c < HammingCode[r].size(); c++)
			cout << HammingCode[r][c] << " ";
		cout << endl;
	}
#endif // verboseMode
	vector<vector<bool>> corruptedHammingCode = bitNegator(HammingCode, 4);
#ifdef verboseMode
	cout << "After negation:\n";
	for (size_t r = 0; r < corruptedHammingCode.size(); r++)
	{
		for (size_t c = 0; c < corruptedHammingCode[r].size(); c++)
			cout << corruptedHammingCode[r][c] << " ";
		cout << endl;
	}
#endif // verboseMode	
	vector<vector<bool>> decodedData = Hamming74Decoder(corruptedHammingCode, true);
#ifdef verboseMode
	cout << "After decoding:\n";
	for (size_t r = 0; r < decodedData.size(); r++)
	{
		for (size_t c = 0; c < decodedData[r].size(); c++)
			cout << decodedData[r][c] << " ";
		cout << endl;
	}
#endif // verboseMode
}