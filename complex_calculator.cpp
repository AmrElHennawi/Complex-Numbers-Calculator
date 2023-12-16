// complex calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <regex>

using namespace std;

// global variables
char oeprator;
double firstReal, secondReal, firstImaginary, secondImaginary;
double realPart, imgPart; // using it in multiply and division functions

// prototypes
int check(string text);
void split(string text);
void multiply(double real1, double real2, double img1, double img2);
void division(double real1, double real2, double img1, double img2);
void add(double real1, double real2, double img1, double img2);
void subtract(double real1, double real2, double img1, double img2);

int main()
{
    while (true)
    {
        firstReal = secondReal = firstImaginary = secondImaginary = realPart = imgPart = 0;
        string userInput;
        system("cls");
        cout << "welcom to Complex Number Calculator :)" << endl
             << endl;
        while (true)
        {
            cout << "Please enter a complex number operations in the form (a+bi) (oprator) (c+di) without spaces between real and imaginary parts: ";
            getline(cin, userInput);
            if (check(userInput))
            {
                split(userInput);
                break;
            }
            else
            {
                system("cls");
                cout << "invalid input" << endl
                     << endl;
                cin.clear();
            }
        }

        if (oeprator == '*')
        {
            multiply(firstReal, secondReal, firstImaginary, secondImaginary);
        }
        else if (oeprator == '/')
        {
            division(firstReal, secondReal, firstImaginary, secondImaginary);
        }
        else if (oeprator == '+')
        {
            add(firstReal, secondReal, firstImaginary, secondImaginary);
        }
        else if (oeprator == '-')
        {
            subtract(firstReal, secondReal, firstImaginary, secondImaginary);
        }
        cout << endl
             << "press any thing to continue or 0 to Exit: ";
        getline(cin, userInput);
        if (userInput == "0")
        {
            goto end;
        }
    }

end:
    system("cls");
    cout << "Thanks for using Complex Number Calculator." << endl;
}

void split(string text)
{
    string realNum, realNum2, imaginaryNum, imaginaryNum2;
    int operatorCounter = 0;
    int i = 1;

    // first real number
    // text[0] is always == '('
    for (i; i < text.length(); i++)
    {
        if (text[1] == '-' || text[1] == '+') // if the the first number has sign
        {
            if (text[i] == '-' || text[i] == '+') // stops concatenating the string when find a '+' or '-' sign
            {
                operatorCounter += 1;
            }

            if (operatorCounter >= 2) // stops concatenating the string when find a '+' or '-' sign
            {
                break;
            }
        }
        else if (text[1] != '-' || text[1] != '+') // if the the first number was positive
        {
            if (text[i] == '-' || text[i] == '+')
            {
                break;
            }
        }
        realNum += text[i];
    }

    // first imaginary number
    for (i + 1; i < text.length(); i++)
    {
        if ((text[i] == 'i') && (text[i - 1] == '-' || text[i - 1] == '+')) // if its just 'i' without coefficient
        {
            imaginaryNum += "1";
            break;
        }
        if (text[i] == 'i') // checking for 'i'
        {
            break;
        }
        else
        {
            imaginaryNum += text[i];
        }
    }

    oeprator = text[i + 3]; // taking the operator sign
    operatorCounter = 0;
    int j = i + 6;
    i += 6; // making the counting 'i' starting at the next real number

    // second real number
    for (i; i < text.length(); i++)
    {
        if (text[j] == '-' || text[j] == '+') // if the the first number has sign
        {
            if (text[i] == '-' || text[i] == '+') // stops concatenating the string when find a '+' or '-' sign
            {
                operatorCounter += 1;
            }

            if (operatorCounter >= 2) // stops concatenating the string when find a '+' or '-' sign
            {
                break;
            }
        }
        else if (text[1] != '-' || text[1] != '+') // if the the first number was positive
        {
            if (text[i] == '-' || text[i] == '+')
            {
                break;
            }
        }
        realNum2 += text[i];
    }

    // second imaginary number
    for (i + 1; i < text.length(); i++)
    {
        if ((text[i] == 'i') && (text[i - 1] == '-' || text[i - 1] == '+')) // if its just 'i' without coefficient
        {
            imaginaryNum2 += "1";
            break;
        }
        if (text[i] == 'i') // checking for 'i'
        {
            break;
        }
        else
        {
            imaginaryNum2 += text[i];
        }
    }

    firstReal = stod(realNum);
    secondReal = stod(realNum2);
    firstImaginary = stod(imaginaryNum);
    secondImaginary = stod(imaginaryNum2);

    // cout << firstReal << '\n' << firstImaginary << '\n' << oeprator << '\n' << secondReal << '\n' << secondImaginary;
}

int check(string text)
{
    // checks that the input is on the form: (+- a -+ bi) -+*/ (-+ c -+ di)
    // and returns 1 if its valid and 0 if its not valid
    regex textCheck("\\({1}[-+]?[0-9]+.?[0-9]*[-+]?[0-9]*.?[0-9]*i{1}\\){1} [-+*/] \\({1}[-+]?[0-9]+.?[0-9]*[-+]?[0-9]*.?[0-9]*i{1}\\){1}");
    return regex_match(text, textCheck);
}

void multiply(double real1, double real2, double img1, double img2)
{
    realPart = ((real1 * real2) + ((img1 * img2) * -1));

    imgPart = (real1 * img2) + (real2 * img1);

    if (imgPart >= 0 && oeprator == '*') // to add the '+' sign before the imaganery part
    {
        cout << endl
             << "Answer: " << realPart << '+' << imgPart << 'i' << endl;
    }
    else if (imgPart < 0 && oeprator == '*')
    {
        cout << endl
             << "Answer: " << realPart << imgPart << 'i' << endl;
    }
}

void division(double real1, double real2, double img1, double img2)
{
    double temp;
    multiply(real1, real2, img1, (-img2));

    temp = (real2 * real2) + (img2 * img2); // temp for denominator

    if ((imgPart / temp) >= 0) // to add the '+' sign before the imaganery part
    {
        cout << endl
             << "Answer: " << realPart / temp << '+' << imgPart / temp << 'i' << endl;
    }
    else
    {
        cout << endl
             << "Anser: " << realPart / temp << imgPart / temp << 'i' << endl;
    }
}

void add(double real1, double real2, double img1, double img2)
{
    if ((img1 + img2) >= 0)
    {
        cout << endl
             << "Answer: " << real1 + real2 << '+' << img1 + img2 << 'i' << endl;
    }
    else
    {
        cout << endl
             << "Answer: " << real1 + real2 << img1 + img2 << 'i' << endl;
    }
}

void subtract(double real1, double real2, double img1, double img2)
{
    if ((img1 - img2) >= 0)
    {
        cout << endl
             << "Answer: " << real1 - real2 << '+' << img1 - img2 << 'i' << endl;
    }
    else
    {
        cout << endl
             << "Anwser: " << real1 - real2 << img1 - img2 << 'i' << endl;
    }
}