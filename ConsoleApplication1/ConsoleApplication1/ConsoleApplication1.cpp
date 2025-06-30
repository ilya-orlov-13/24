#include <iostream>﻿
#include "header.h"
using namespace std;

void SolveTask1() {
    cout << "1)" << endl;
    string message = "0000010101000000111";
    cout << "Исходное сообщение: " << message << endl;

    HammingPositionInfo info = GetHammingPositionInfo(message);
    cout << "Информация о позициях:" << endl;
    cout << "  Всего бит (m+r): " << info.TotalBits << endl;
    cout << "  Информационных бит (m): " << info.DataBits << endl;
    cout << "  Контрольных бит (r): " << info.ControlBits << endl;
    cout << "  Позиции контрольных бит (1-индексация): ";
    for (int pos : info.ControlBitPositions) cout << pos << " ";
    cout << endl;

    string hammingCode = BuildHammingCode(message, info);
    cout << "Построенный код Хемминга: " << hammingCode << endl;

    if (hammingCode.length() > 0) {
        string receivedCodeWithError = hammingCode;
        int errorBitPosition;
        cout << "Введите номер бита с ошибкой: "; cin >> errorBitPosition;
        if (errorBitPosition > 0 && errorBitPosition <= receivedCodeWithError.length()) {
            receivedCodeWithError[errorBitPosition - 1] = (receivedCodeWithError[errorBitPosition - 1] == '0' ? '1' : '0');
            cout << "Код с внесенной ошибкой в позиции " << errorBitPosition << ": " << receivedCodeWithError << endl;

            int syndrome = CalculateSyndrome(receivedCodeWithError, info);
            cout << "Синдром ошибки: " << syndrome << endl;

            if (syndrome != 0) {
                cout << "Ошибка обнаружена в позиции: " << syndrome << endl;
                string correctedCode = CorrectHammingCode(receivedCodeWithError, info, syndrome);
                cout << "Исправленный код: " << correctedCode << endl;
                string extractedMessage = ExtractMessageFromHamming(correctedCode, info);
                cout << "Извлеченное сообщение из исправленного кода: " << extractedMessage << endl;
                if (!(extractedMessage == message)) cout << "Ошибка: Сообщение не восстановлено" << endl;
            }
            else {
                cout << "Ошибок не обнаружено (или синдром равен 0)" << endl;
                string extractedMessage = ExtractMessageFromHamming(receivedCodeWithError, info);
                cout << "Извлеченное сообщение : " << extractedMessage << endl;
            }
        }
        else {
            cout << "Невозможно внести ошибку в позицию " << errorBitPosition << endl;
        }
    }
    cout << endl << endl;
}

void SolveTask2() {
    cout << "2)" << endl;
    string text = "КОШКА КРОШКА НА ОКОШКЕ";
    cout << "Исходный текст: " << text << endl;

    HuffmanNode* huffmanTreeRoot = nullptr;
    map<char, string> huffmanCodes = BuildHuffmanCodes(text, huffmanTreeRoot);

    cout << "Коды Хаффмана для символов:" << endl;
    for (auto pair : huffmanCodes) {
        cout << "'" << pair.first << "' : " << pair.second << endl;
    }

    cout << "\nДерево Хаффмана:" << endl;
    if (huffmanTreeRoot) PrintHuffmanTree(huffmanTreeRoot, "", false);

    string encodedText = EncodeHuffman(text, huffmanCodes);
    cout << "\nЗакодированный текст: " << encodedText << endl;

    string decodedText = DecodeHuffman(huffmanTreeRoot, encodedText);
    cout << "Декодированный текст: " << decodedText << endl;

    if (decodedText == text) {
        cout << "Кодирование и декодирование успешно" << endl;
    }
    else {
        cout << "Ошибка: Декодированный текст не совпадает с исходным." << endl;
    }

    // Вычисление размеров
    int originalBits = text.length() * 8; //8 бит на символ
    int encodedBits = encodedText.length();
    cout << "Размер исходного сообщения (равномерное кодирование): " << originalBits << " бит" << endl;
    cout << "Размер закодированного сообщения (код Хаффмана): " << encodedBits << " бит" << endl;


    DeleteHuffmanTree(huffmanTreeRoot);
    cout << endl << endl;
}

void SolveTask3() {
    cout << "3)" << endl;
    string plainText;
    string key;

    cout << "Введите текст для шифрования: ";
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, plainText);

    cout << "Введите ключ: ";
    cin >> key;

    string cipherText = ColumnarTranspositionEncrypt(plainText, key);
    cout << "Зашифрованный текст: " << cipherText << endl;

    string decryptedText = ColumnarTranspositionDecrypt(cipherText, key);
    cout << "Дешифрованный текст: " << decryptedText << endl;

    if (decryptedText == plainText) {
        cout << "Шифрование и дешифрование успешно" << endl;
    }
    else {
        cout << "Ошибка: Дешифрованный текст не совпадает с исходным." << endl;
    }
    cout << endl << endl;
}


int main() {
    setlocale(LC_ALL, "Russian");

    SolveTask1();
    SolveTask2();
    SolveTask3();

    return 0;
}