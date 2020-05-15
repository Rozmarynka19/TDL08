#include "S2BS.h"

using namespace std;

vector<vector<unsigned int>> matrixMultiplicationWithModulo(vector<vector<unsigned int>> A, vector<vector<unsigned int>> B)
{
	if (A[0].size() != B.size())
	{
		cout << "Number of A's columns are not equal number of B's rows" << endl;
		return vector<vector<unsigned int>>(1,vector<unsigned int>(0,-1));
	}

	vector<vector<unsigned int>> result(A.size(), vector<unsigned int>(B[0].size(), -1));
	unsigned int temp = 0;

	for (size_t r = 0; r < A.size(); r++)
	{
		for (size_t c = 0; c < B[r].size(); c++)
		{
			temp = 0;
			for (size_t i = 0; i < A[r].size(); i++)				
				temp = temp + A[r][i] * B[i][c];				
			result[r][c] = temp % 2;
		}
	}

	return result;
}

int main()
{
    vector<char> charTab{ 'z' };
    vector<bitset<bits>> bitsetArray = S2BS(charTab, false);
	vector<bool> bitsetArrayRewrite;
    
	//Rewriting 2d bitsetArray to 1d bitsetArrayRewrite
	for (size_t i = 0; i < bitsetArray.size(); i++)
	{
		for (size_t j = 0; j < bits; j++)
			bitsetArrayRewrite.push_back(bitsetArray[i][j]);
	}

	//{{20,15},{14,10}} w/o modulo
	/*vector<vector<unsigned int>> A{ {2,3,4},{1,2,3} }, B{ {1,2},{2,1},{3,2} };
	vector<vector<unsigned int>> result = matrixMultiplication(A, B);*/

	//{{1,2},{1,0}} w/o modulo
	//vector<vector<unsigned int>> A{ {1,0,1},{0,1,0} }, B{ {0,1},{1,0},{1,1} };
	//vector<vector<unsigned int>> result = matrixMultiplication(A, B);

	//{{2,2},{1,2}} w/o modulo
	/*vector<vector<unsigned int>> A{ {1,1,1},{1,0,1} }, B{ {1,1},{1,0},{0,1} };
	vector<vector<unsigned int>> result = matrixMultiplicationWithModulo(A, B);*/

	//{{3},{3},{1}} w/o modulo
	vector<vector<unsigned int>> A{ {1,1,1,1},{1,0,1,1},{0,1,1,0} }, B{ {1},{0},{1},{1} };
	vector<vector<unsigned int>> result = matrixMultiplicationWithModulo(A, B);
	
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
