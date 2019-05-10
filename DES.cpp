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

int CP_2[48] = {14, 17, 11, 24, 1, 5, 3, 28,
                15, 6, 21, 10, 23, 19, 12, 4,
                26, 8, 16, 7, 27, 20, 13, 2,
                41, 52, 31, 37, 47, 55, 30, 40,
                51, 45, 33, 48, 44, 49, 39, 56,
                34, 53, 46, 42, 50, 36, 29, 32};

int E[48] = {32, 1, 2, 3, 4, 5,
             4, 5, 6, 7, 8, 9,
             8, 9, 10, 11, 12, 13,
             12, 13, 14, 15, 16, 17,
             16, 17, 18, 19, 20, 21,
             20, 21, 22, 23, 24, 25,
             24, 25, 26, 27, 28, 29,
             28, 29, 30, 31, 32, 1};

int SHIFT[16] =
    {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

int PI_2[32] = {35, 38, 46, 6, 43, 40, 14, 45,
                33, 19, 26, 15, 23, 8, 22, 10,
                12, 11, 5, 25, 27, 21, 16, 31,
                28, 32, 34, 24, 9, 37, 2, 1};
int P[32] = {16, 7, 20, 21, 29, 12, 28, 17,
             1, 15, 23, 26, 5, 18, 31, 10,
             2, 8, 24, 14, 32, 27, 3, 9,
             19, 13, 30, 6, 22, 11, 4, 25};

int PI_1[64] = {40, 8, 48, 16, 56, 24, 64, 32,
                39, 7, 47, 15, 55, 23, 63, 31,
                38, 6, 46, 14, 54, 22, 62, 30,
                37, 5, 45, 13, 53, 21, 61, 29,
                36, 4, 44, 12, 52, 20, 60, 28,
                35, 3, 43, 11, 51, 19, 59, 27,
                34, 2, 42, 10, 50, 18, 58, 26,
                33, 1, 41, 9, 49, 17, 57, 25};

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

    return a;
}

int *generateBlock(string s, int array[], int size)
{
    //padding
    if (s.length() < 8)
    {
        while (s.length() < 8)
            s += "~";
    }

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

string getCipherText(int block[], int blocksize, int key[], int keysize)
{
    int partition_size = blocksize / 2;
    int L[partition_size];
    int R[partition_size];

    for (int i = 0; i < partition_size; i++)
    {
        L[i] = block[i];
        R[i] = block[partition_size + i];
    }

    //start of iteration
    for (int m = 0; m < 16; m++)
    {
        int keyPartition = keysize / 2;
        int KL[partition_size];
        int KR[partition_size];

        //half of keyblock and shifting
        for (int i = 0; i < keyPartition; i++)
        {
            KL[i] = key[i];
            KR[i] = key[keyPartition + i];
        }

        for (int i = 0; i < m; i++)
        {
            int temp = KL[i], j;
            for (j = 0; j < keyPartition - 1; j++)
                KL[j] = KL[j + 1];

            KL[j] = temp;
        }

        for (int i = 0; i < m; i++)
        {
            int temp = KR[i], j;
            for (j = 0; j < keyPartition - 1; j++)
                KR[j] = KR[j + 1];

            KR[j] = temp;
        }

        int *int_key = new int[56];
        for (int i = 0; i < keyPartition; i++)
        {
            int_key[i] = KL[i];
            int_key[keyPartition + i] = KR[i];
        }

        int *key_round = new int[48];

        //generate 48 bits from 56 bits
        for (int i = 0; i < 48; i++)
        {
            key_round[i] = key[CP_2[i] - 1];
        }

        int *e = new int[48];

        for (int i = 0; i < 48; i++)
        {
            e[i] = R[E[i] - 1];
        }

        int *result_xor = new int[48];

        for (int i = 0; i < 48; i++)
        {
            result_xor[i] = key_round[i] xor e[i];
        }

        int *result = new int[32];

        for (int i = 0; i < 32; i++)
        {
            result[i] = result_xor[PI_2[i] - 1];
        }

        int *final_result = new int[32];

        for (int i = 0; i < 32; i++)
        {
            final_result[i] = result[P[i] - 1];
        }

        for (int i = 0; i < partition_size; i++)
        {
            L[i] = R[i];
            R[i] = final_result[i];
        }
    }

    for (int i = 0; i < partition_size; i++)
    {
        block[i] = R[i];
        block[partition_size + i] = L[i];
    }

    for (int i = 0; i < blocksize; i++)
    {
        block[i] = block[PI_1[i] - 1];
    }

    string output;
    for (int i = 0; i < 8; ++i)
    {
        int c = 0;
        for (int j = i * 8; j < (i + 1) * 8; ++j)
        {
            c = c << 1;
            c += block[j];
        }
        output[i] = (char)c;
    }

    return output;
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
    string cipher_text;
    for (int i = 0; i < number_of_blocks; i++)
    {
        blocks[i] = generateBlock(plaintext.substr(i * 8, 8), PI, 64);
        cipher_text += getCipherText(blocks[i], 64, keyBlock, 56);
    }

    cout << cipher_text << endl;

    return 0;
}