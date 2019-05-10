#include <iostream>
#include <cmath>

using namespace std;

void printBlock(int a[], int n);

int PI[64] = {58, 50, 42, 34, 26, 18, 10, 2,
              60, 52, 44, 36, 28, 20, 12, 4,
              62, 54, 46, 38, 30, 22, 14, 6,
              64, 56, 48, 40, 32, 24, 16, 8,
              57, 49, 41, 33, 25, 17, 9, 1,
              59, 51, 43, 35, 27, 19, 11, 3,
              61, 53, 45, 37, 29, 21, 13, 5,
              63, 55, 47, 39, 31, 23, 15, 7};

int CP_1[56] = {57, 49, 41, 33, 25, 17, 9,
                1, 58, 50, 42, 34, 26, 18,
                10, 2, 59, 51, 43, 35, 27,
                19, 11, 3, 60, 52, 44, 36,
                63, 55, 47, 39, 31, 23, 15,
                7, 62, 54, 46, 38, 30, 22,
                14, 6, 61, 53, 45, 37, 29,
                21, 13, 5, 28, 20, 12, 4};

int *generateBitForm(string s)
{
    int count = 0;
    __int64_t output = 0;

    for (int i = 0; i < s.length(); i++)
    {
        __int64_t tem = s.at(i);
        __int64_t var = tem << (i * 8);
        output |= var;
    }

    int *a = new int[64];
    while (count < 64)
    {
        a[count] = (output & 0x00000001);
        output = output >> 1;
        count++;
    }

    printBlock(a, 64);

    return a;
}

int *generateBlock(string s, int array[], int size)
{
    int *a = generateBitForm(s);

    int *final_out = new int[size];
    for (int i = 0; i < size; i++)
    {
        final_out[i] = a[array[i] - 1];
    }
    return final_out;
}

void printBlock(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i];
        if ((i + 1) % 8 == 0)
            cout << " ";
    }
    cout << endl;
}

int main()
{

    string plaintext;
    string key;
    getline(cin, plaintext);
    getline(cin, key);
    int number_of_blocks = ceil(1.0 * plaintext.length() / 8.0);

    int *blocks[number_of_blocks];

    int *keyBlock = new int[56];
    keyBlock = generateBlock(key, CP_1, 56);

    for (int i = 0; i < number_of_blocks; i++)
    {
        blocks[i] = new int[64];
    }

    for (int i = 0; i < number_of_blocks; i++)
    {
        blocks[i] = generateBlock(plaintext.substr(i * 8, 8), PI, 64);
    }

    return 0;
}