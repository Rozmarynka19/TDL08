#include "S2BS.h"

using namespace std;

vector<vector<bool>> matrixMultiplicationWithModulo(vector<vector<bool>> A, vector<vector<bool>> B)
{
	if (A[0].size() != B.size())
	{
		cout << "Number of A's columns are not equal number of B's rows" << endl;
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

vector<vector<bool>> Hamming74Coder(vector<vector<bool>> data)
{
	vector<vector<bool>> G{ {1,1,0,1},
							{1,0,1,1},
							{1,0,0,0},
							{0,1,1,1},
							{0,1,0,0},
							{0,0,1,0},
							{0,0,0,1} };
	return matrixMultiplicationWithModulo(G, data);
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

	vector<vector<bool>> result = Hamming74Coder(bitsetArrayRewrite);
	for (size_t r = 0; r < result.size(); r++)
	{
		for (size_t c = 0; c < result[r].size(); c++)
			cout << result[r][c] << " ";
		cout << endl;
	}

}

//Plan dzialania:
//x1. Napisac funkcje do wykonywania mnozenia macierzowego
//X2. Wydzielic S2BS i dostoswac do projektu
//3. Zaimplementowac funkcje kodujaca kodem Hamming(7,4)
//4. Napisac funkcje wprowadzajaca bit bledu (negujaca wskazany nr bitu)
//5. Napisac dekoder kodu Hamminga(7,4)
//6. Zmodyfikowac powyzej napisany koder i dekoder, by obslugiwal kod SECDED (z dodatkowym bitem parzystosci)
//    - ten punkt realizowac rownolegle z powyzszymi - dodac przelaczniki
