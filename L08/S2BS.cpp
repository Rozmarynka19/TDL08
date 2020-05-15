#include "S2BS.h"

std::vector<std::bitset<bits>> S2BS(std::vector<char> input, bool isLittleEndian)
{
    std::vector<std::bitset<bits>> bitsetArray;

    for (int i = 0; i < input.size(); i++)
    {
        bitsetArray.push_back(input[i]);
        //cout << bitsetArray.at(i) << endl;
    }


    if (isLittleEndian)
    {
        for (int i = 0; i < input.size(); i++)
        {
            for (int j = 0; j < bits; j++)
                std::cout << bitsetArray[i][j];
            std::cout << std::endl;
        }


        return bitsetArray;
    }
    else
    {
        std::vector<std::bitset<bits>> copyOfBitsetArray = bitsetArray;

        for (int i = 0; i < input.size(); i++)
        {
            for (int j = 0, k = bits - 1; k >= 0; j++, k--)
            {
                copyOfBitsetArray[i][j] = bitsetArray[i][k];
            }
        }

        for (int i = 0; i < input.size(); i++)
        {
            for (int j = 0; j < bits; j++)
                std::cout << copyOfBitsetArray[i][j];
            std::cout << std::endl;
        }

        return copyOfBitsetArray;
    }


}