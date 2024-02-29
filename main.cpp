#include <iostream>
#include <string>
#include <cmath>
using namespace std;
const unsigned int BIT_LENGTH = 8;
// number of bits to repersent an integer number
string convertPositiveIntToBinary(unsigned int X, int len);
string signBit(int X);
string convertToSignMagnitudeForm(int X);
string convertToOneCpmtForm(int X);
string convertToTwoCpmtForm(int X);
char convert4binaryToHexa(string binary);
string convertToHexaForm(int X);
int main()
{
    // input X
    int X = -1;
    cout << "1. Input: ";
    cin >> X;

    cout << "2.\n";
    // Sign-Magitude form
    cout << "Output a(Sign-Magnitude form): ";
    cout << convertToSignMagnitudeForm(X) << "\n";
    // 1's complement form
    cout << "Output b(1's complement form): ";
    cout << convertToOneCpmtForm(X) << "\n";
    // 2's complement form
    string twoCpmt = convertToTwoCpmtForm(X);
    cout << "Output c(2's complement form): ";
    cout << twoCpmt << "\n";
    // hexadecimal (2's complement)
    cout << "3.\n";
    cout << "Hexadecimal: " << convertToHexaForm(X);
}

string convertPositiveIntToBinary(unsigned int X, int len)
{
    string ret(len, '0');
    while (X > 0 && len > 0)
    {
        ret[--len] = X % 2 + '0';
        X /= 2;
    }
    return ret;
}

string signBit(int X)
{
    if (X >= 0)
        return "0";
    else
        return "1";
}

string convertToSignMagnitudeForm(int X)
{
    int minValue = -pow(2, BIT_LENGTH - 1) + 1;
    int maxValue = pow(2, BIT_LENGTH - 1) - 1;
    if (X < minValue || X > maxValue)
        return "overflow";
    string ret;
    string absValue = convertPositiveIntToBinary(abs(X), BIT_LENGTH - 1);
    if (X == 0)
    {
        ret = "0" + absValue + " and 1" + absValue;
    }
    else
        ret = signBit(X) + absValue;
    return ret;
}

string convertToOneCpmtForm(int X)
{
    string ret = convertToSignMagnitudeForm(X);
    if (X < 0)
    {
        for (int i = 1; i < ret.size(); i++)
            if (ret[i] == '1')
                ret[i] = '0';
            else if (ret[i] == '0')
                ret[i] = '1';
    }
    return ret;
}

string convertToTwoCpmtForm(int X)
{
    int minValue = -pow(2, BIT_LENGTH - 1);
    int maxValue = pow(2, BIT_LENGTH - 1) - 1;
    if (X < minValue || X > maxValue)
        return "overflow";
    string ret = signBit(X) + convertPositiveIntToBinary(abs(X), BIT_LENGTH - 1);
    if (X < 0)
    {
        int mem = 1;
        for (int i = ret.size() - 1; i > 0; i--)
        {
            if (ret[i] == '1')
                ret[i] = '0';
            else if (ret[i] == '0')
                ret[i] = '1';
            if (mem == 1)
            {
                if (ret[i] == '1')
                    ret[i] = '0';
                else
                {
                    ret[i] = '1';
                    mem = 0;
                }
            }
        }
    }
    return ret;
}
char convert4binaryToHexa(string binary)
{
    if (binary == "0000")
        return '0';
    if (binary == "0001")
        return '1';
    if (binary == "0010")
        return '2';
    if (binary == "0011")
        return '3';
    if (binary == "0100")
        return '4';
    if (binary == "0101")
        return '5';
    if (binary == "0110")
        return '6';
    if (binary == "0111")
        return '7';
    if (binary == "1000")
        return '8';
    if (binary == "1001")
        return '9';
    if (binary == "1010")
        return 'A';
    if (binary == "1011")
        return 'B';
    if (binary == "1100")
        return 'C';
    if (binary == "1101")
        return 'D';
    if (binary == "1110")
        return 'E';
    if (binary == "1111")
        return 'F';
}
string convertToHexaForm(int X)
{
    string bin = convertToTwoCpmtForm(X);
    if (bin == "overflow")
        return bin;
    while (bin.size() % 4 != 0)
    {
        bin = '0' + bin;
    }
    string hexa;
    for (int i = 0; i < bin.size(); i += 4)
    {
        string temp;
        for (int j = 0; j < 4; j++)
            temp.push_back(bin[i + j]);
        hexa.push_back(convert4binaryToHexa(temp));
    }
    return hexa;
}