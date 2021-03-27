/*                                                  */
/*  Actividad 3.2 - Programando un DFA              */
/*                                                  */
/*  Luis Alonso Martínez García - A01636255         */
/*  Abraham Mendoza Pérez - A01274857               */
/*  Aldo Alejandro Degollado Padilla - A01638391    */
/*                                                  */

#include <iostream>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <string>
#include <iomanip>

void lexerArithmetic(std::string fileName)
{
    std::string line;
    std::ifstream expressionsFile;
    std::string sigma = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789=+-*/^_().";
    std::string q0 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWZYZ0123456789=+-*/^()";
    std::string q1 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWZYZ0123456789_";
    std::string q2 = "0123456789.";
    std::string q3 = "0123456789eE";
    std::string q4 = "0123456789-";
    std::string numbers = "0123456789"; // q5 and q6
    std::string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWZYZ";
    std::string operators = "+-*^()="; // q7, q8, q9, q10, q11, q12 and q13
    std::string comment = "/"; // q14
    std::string delimiters = " \n\t+-*^()=/";
    std::string toPrint;
    char actual;
    int lineLength = 0;
    int qPosition = 0;
    size_t found;
    bool flag;
    bool invalidChar = false;


    // Open the file to analyze given by user
    expressionsFile.open(fileName, std::ios::in);
    while(expressionsFile.fail())
    {
        std::cout << "Unable to open \"" << fileName << "\", input the name of the file to analyze (include extension): ";
        std::cin >> fileName;
        expressionsFile.open(fileName, std::ios::in);
    }
    
    system("cls");
    std::cout << "\n |-|-|      DFA ANALYSIS      |-|-|" << std::endl;
    std::cout << "By: Aldo Degollado, Abraham Mendoza, and Alonso Martinez\n" << std::endl;

    // Read each line of the file
    while(expressionsFile.is_open() && !expressionsFile.eof())
    {
        std::getline(expressionsFile, line);
        lineLength = line.length();

        // Read each character of the 
        for(int i=0; i < lineLength; i++)
        {
            flag = false;
            actual = line[i];
            if((actual != ' ' && actual != '\n' && actual != '\t') || ((actual == ' ' || actual == '\t') && qPosition == 15 ) || (!invalidChar && qPosition == 1))
            {
                while(!flag)
                {
                    // Select the state of the automata
                    switch(qPosition)
                    {
                        // Checks if the character is valid in the lenguage
                        case 0:
                        {
                            found = q0.find(actual);
                            if(found != std::string::npos)
                            {
                                // Check if we are dragging an error
                                if(invalidChar && (actual != ' ' || actual != '\n' || actual != '\t' || operators.find(actual) == std::string::npos || comment.find(actual) == std::string::npos))
                                {
                                    if(i != lineLength - 1)
                                    {
                                        toPrint = toPrint + actual;
                                        flag = true;
                                    }
                                    else
                                    {
                                        toPrint = toPrint + actual;
                                        std::cout << toPrint << std::setw(30) << "Error" << std::endl;
                                        toPrint.clear();
                                        invalidChar = false;
                                        qPosition = 0;
                                        flag = true;
                                    }
                                }
                                else if(invalidChar && (actual == ' ' || actual == '\n' || actual == '\t'))
                                {
                                    std::cout << toPrint << std::setw(30) << "Error" << std::endl;
                                    toPrint.clear();
                                    qPosition = 0;
                                    invalidChar = false;
                                    flag = true;
                                }
                                else if(invalidChar && (operators.find(actual) != std::string::npos || comment.find(actual) != std::string::npos))
                                {
                                    std::cout << toPrint << std::setw(30) << "Error" << std::endl;
                                    toPrint.clear();
                                    qPosition = 0;
                                    invalidChar = false;
                                }
                                else if(comment.find(q0[found]) != std::string::npos)
                                {
                                    qPosition = 14;
                                }
                                else if(numbers.find(q0[found]) != std::string::npos)
                                {
                                    qPosition = 2;
                                }
                                else if(operators.find(q0[found]) != std::string::npos)
                                {
                                    // The character is an operator, uses switch to determine which
                                    switch(actual)
                                    {
                                        case '+':
                                        {
                                            qPosition = 0;
                                            flag = true;
                                            std::cout << actual << std::setw(30) << "Suma" << std::endl;
                                            break;
                                        }
                                        case '-':
                                        {
                                            qPosition = 0;
                                            flag = true;
                                            std::cout << actual << std::setw(30) << "Resta" << std::endl;
                                            break;
                                        }
                                        case '*':
                                        {
                                            qPosition = 0;
                                            flag = true;
                                            std::cout << actual << std::setw(30) << "Multiplicacion" << std::endl;
                                            break;
                                        }
                                        case '^':
                                        {
                                            qPosition = 0;
                                            flag = true;
                                            std::cout << actual << std::setw(30) << "Potencia" << std::endl;
                                            break;
                                        }
                                        case '(':
                                        {
                                            qPosition = 0;
                                            flag = true;
                                            std::cout << actual << std::setw(30) << "Parentesis de apertura" << std::endl;
                                            break;
                                        }
                                        case ')':
                                        {
                                            qPosition = 0;
                                            flag = true;
                                            std::cout << actual << std::setw(30) << "Parentesis de cierre" << std::endl;
                                            break;
                                        }
                                        case '=':
                                        {
                                            qPosition = 0;
                                            flag = true;
                                            std::cout << actual << std::setw(30) << "Asignacion" << std::endl;
                                            break;
                                        }
                                    }
                                }
                                else
                                {
                                    qPosition = 1;
                                }
                            }
                            else
                            {
                                if(i != lineLength - 1)
                                {
                                    toPrint = toPrint + actual;
                                    flag = true;
                                    invalidChar = true;
                                }
                                else if(i == lineLength - 1)
                                {
                                    toPrint = toPrint + actual;
                                    std::cout << toPrint << std::setw(30) << "Error" << std::endl;
                                    invalidChar = false;
                                    flag = true;
                                    toPrint.clear();
                                }
                            }
                            break;
                        }
                        // The character(s) is(are) a variable
                        case 1:
                        {
                            if(invalidChar && (actual != ' ' || actual != '\n' || actual != '\t' || operators.find(actual) == std::string::npos || comment.find(actual) == std::string::npos))
                            {
                                toPrint = toPrint + actual;
                                flag = true;
                            }
                            else if(invalidChar && (actual == ' ' || actual == '\n' || actual == '\t'))
                            {
                                std::cout << toPrint << std::setw(30) << "Error" << std::endl;
                                toPrint.clear();
                                qPosition = 0;
                                invalidChar = false;
                                flag = true;
                            }
                            else if(invalidChar && (operators.find(actual) != std::string::npos || comment.find(actual) != std::string::npos))
                            {
                                std::cout << toPrint << std::setw(30) << "Error" << std::endl;
                                toPrint.clear();
                                qPosition = 0;
                                invalidChar = false;
                            }
                            else if(!invalidChar && (actual == ' ' || actual == '\n' || actual == '\t'))
                            {
                                std::cout << toPrint << std::setw(30) << "Variable" << std::endl;
                                toPrint.clear();
                                qPosition = 0;
                                flag = true;
                            }
                            else if(!invalidChar && (operators.find(actual) != std::string::npos || comment.find(actual) != std::string::npos))
                            {
                                std::cout << toPrint << std::setw(30) << "Variable" << std::endl;
                                toPrint.clear();
                                qPosition = 0;
                            }
                            else
                            {
                                found = q1.find(actual);
                                if(found != std::string::npos && i != lineLength - 1)
                                {
                                    toPrint = toPrint + actual;
                                    flag = true;
                                }
                                else if(found != std::string::npos && i == lineLength - 1)
                                {
                                    toPrint = toPrint + actual;
                                    std::cout << toPrint << std::setw(30) << "Variable" << std::endl;
                                    qPosition = 0;
                                    flag = true;
                                    toPrint.clear();
                                }
                                else if(i == lineLength - 1)
                                {
                                    toPrint = toPrint + actual;
                                    std::cout << toPrint << std::setw(30) << "Error" << std::endl;
                                    toPrint.clear();
                                    flag = true;
                                    qPosition = 0;
                                }
                                else
                                {
                                    toPrint = toPrint + actual;
                                    invalidChar = true;
                                    flag = true;
                                }
                            }
                            break;
                        }
                        // The character(s) is(are) a integer number
                        case 2:
                        {
                            found = q2.find(actual);
                            if(actual == '.')
                            {
                                toPrint = toPrint + actual;
                                flag = true;
                                qPosition = 3;
                            }
                            else if(found != std::string::npos && i != lineLength - 1)
                            {
                                toPrint = toPrint + actual;
                                flag = true;
                            }
                            else if(found != std::string::npos && i == lineLength - 1)
                            {
                                toPrint = toPrint + actual;
                                std::cout << toPrint << std::setw(30) << "Entero" << std::endl;
                                qPosition = 0;
                                flag = true;
                                toPrint.clear();
                            }
                            else
                            {
                                std::cout << toPrint << std::setw(30) << "Entero" << std::endl;
                                qPosition = 0;
                                toPrint.clear();
                            }
                            break;
                        }
                        // The characters are a floating real number
                        case 3:
                        {
                            if(invalidChar && (actual != ' ' || actual != '\n' || actual != '\t' || operators.find(actual) == std::string::npos || comment.find(actual) == std::string::npos))
                            {
                                if(i != lineLength - 1)
                                {
                                    toPrint = toPrint + actual;
                                    flag = true;
                                }
                                else
                                {
                                    toPrint = toPrint + actual;
                                    std::cout << toPrint << std::setw(30) << "Error" << std::endl;
                                    toPrint.clear();
                                    invalidChar = false;
                                    qPosition = 0;
                                    flag = true;
                                }
                            }
                            else if(invalidChar && (actual == ' ' || actual == '\n' || actual == '\t'))
                            {
                                std::cout << toPrint << std::setw(30) << "Error" << std::endl;
                                toPrint.clear();
                                qPosition = 0;
                                invalidChar = false;
                                flag = true;
                            }
                            else if(invalidChar && (operators.find(actual) != std::string::npos || comment.find(actual) != std::string::npos))
                            {
                                std::cout << toPrint << std::setw(30) << "Error" << std::endl;
                                toPrint.clear();
                                qPosition = 0;
                                invalidChar = false;
                            }
                            else if(!invalidChar && (actual == ' ' || actual == '\n' || actual == '\t'))
                            {
                                std::cout << toPrint << std::setw(30) << "Variable" << std::endl;
                                toPrint.clear();
                                qPosition = 0;
                                flag = true;
                            }
                            else if(!invalidChar && (operators.find(actual) != std::string::npos || comment.find(actual) != std::string::npos))
                            {
                                std::cout << toPrint << std::setw(30) << "Variable" << std::endl;
                                toPrint.clear();
                                qPosition = 0;
                            }
                            else
                            {
                                found = q3.find(actual);
                                if(actual == 'E' || actual == 'e')
                                {
                                    toPrint = toPrint + actual;
                                    flag = true;
                                    qPosition = 4;
                                }
                                else if(found != std::string::npos && i != lineLength - 1)
                                {
                                    toPrint = toPrint + actual;
                                    flag = true;
                                }
                                else if(found != std::string::npos && i == lineLength - 1)
                                {
                                    toPrint = toPrint + actual;
                                    std::cout << toPrint << std::setw(30) << "Real" << std::endl;
                                    qPosition = 0;
                                    flag = true;
                                    toPrint.clear();
                                }
                                else if(actual == '.')
                                {
                                    toPrint = toPrint + actual;
                                    flag = true;
                                    invalidChar = true;
                                }
                                else
                                {
                                    std::cout << toPrint << std::setw(30) << "Real" << std::endl;
                                    qPosition = 0;
                                    toPrint.clear();
                                }
                            }
                            break;
                        }
                        // The characters are a floating real number with exponential
                        case 4:
                        {
                            found = q4.find(actual);
                            if(actual == '-')
                            {
                                toPrint = toPrint + actual;
                                flag = true;
                                qPosition = 5;
                            }
                            else if(found != std::string::npos && i != lineLength - 1)
                            {
                                toPrint = toPrint + actual;
                                flag = true;
                                qPosition = 6;
                            }
                            else if(found != std::string::npos && i == lineLength - 1)
                            {
                                toPrint = toPrint + actual;
                                qPosition = 6;
                                flag = true;
                            }
                            // The floating number has exponential but no number further   
                            else
                            {
                                std::cout << toPrint << std::setw(30) << "Error" << std::endl;
                                qPosition = 0;
                                toPrint.clear();
                            }
                            break;
                        }
                        // The characters are a floating real number with negative exponential
                        case 5:
                        {
                            found = numbers.find(actual);
                            if(found != std::string::npos && i != lineLength - 1)
                            {
                                toPrint = toPrint + actual;
                                flag = true;
                                qPosition = 6;
                            }
                            else if(found != std::string::npos && i == lineLength - 1)
                            {
                                toPrint = toPrint + actual;
                                qPosition = 6;
                                flag = true;
                            }
                            // The floating number has exponential but no number further   
                            else
                            {
                                std::cout << toPrint << std::setw(30) << "Error" << std::endl;
                                qPosition = 0;
                                toPrint.clear();
                            }
                            break;
                        }
                        // The character are a floating real number with exponential
                        case 6:
                        {
                            found = numbers.find(actual);
                            if(found != std::string::npos && i != lineLength - 1)
                            {
                                toPrint = toPrint + actual;
                                flag = true;
                            }
                            else if(found != std::string::npos && i == lineLength - 1)
                            {
                                toPrint = toPrint + actual;
                                std::cout << toPrint << std::setw(30) << "Real" << std::endl;
                                qPosition = 0;
                                flag = true;
                                toPrint.clear();
                            }
                            else
                            {
                                std::cout << toPrint << std::setw(30) << "Real" << std::endl;
                                qPosition = 0;
                                toPrint.clear();
                            }
                            break;
                        }
                        // The character is a division operator (possibly a comment)
                        case 14:
                        {
                            found = comment.find(actual);
                            if(toPrint == "/" && found != std::string::npos && i != lineLength - 1)
                            {
                                toPrint = toPrint + actual;
                                flag = true;
                                qPosition = 15;
                            }
                            else if(found != std::string::npos && i != lineLength - 1)
                            {
                                toPrint = toPrint + actual;
                                flag = true;
                            }
                            else if(found != std::string::npos && i == lineLength - 1)
                            {
                                toPrint = toPrint + actual;
                                std::cout << toPrint << std::setw(30) << "Division" << std::endl;
                                qPosition = 0;
                                flag = true;
                                toPrint.clear();
                            }
                            else
                            {
                                std::cout << toPrint << std::setw(30) << "Division" << std::endl;
                                qPosition = 0;
                                toPrint.clear();
                            }
                            break;
                        }
                        // The characters and the rest of the line are a comment
                        case 15:
                        {
                            if(i != lineLength - 1)
                            {
                                toPrint = toPrint + actual;
                                flag = true;
                            }
                            else if(i == lineLength - 1)
                            {
                                toPrint = toPrint + actual;
                                std::cout << toPrint << std::setw(30) << "Comentario" << std::endl;
                                qPosition = 0;
                                flag = true;
                                toPrint.clear();
                            }
                            break;
                        }
                    }
                }
            }
            else if(invalidChar == true && (actual == ' ' || actual == '\n' || actual == '\t'))
            {
                std::cout << toPrint << std::setw(30) << "Error" << std::endl;
                toPrint.clear();
                invalidChar = false;
                qPosition = 0;
                flag = true;
            }
            else if(invalidChar)
            {
                std::cout << toPrint << std::setw(30) << "Error" << std::endl;
                invalidChar = false;
                toPrint.clear();
                qPosition = 0;
            }
        }
    }
    expressionsFile.close();
}

int main(void)
{
    std::string fileName;
    std::cout << "\n |-|-|      DFA ANALYSIS      |-|-|" << std::endl;
    std::cout << "By: Aldo Degollado, Abraham Mendoza, and Alonso Martinez\n" << std::endl;
    std::cout << "\nInput the name of the file to analyze (with extension): ";
    std::cin >> fileName;

    lexerArithmetic(fileName);

    return 0;
}