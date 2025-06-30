#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cmath>
#include <sstream>

using namespace std;

// 1

// Структура для хранения информации о позициях бит
struct HammingPositionInfo {
    int TotalBits;          // Общее количество бит в коде Хемминга (m+r)
    int DataBits;           // Количество информационных бит (m)
    int ControlBits;        // Количество контрольных бит (r)
    vector<int> ControlBitPositions; // Позиции контрольных бит
};

// Рассчитывает необходимое количество контрольных бит
int CalculateHammingControlBits(int DataLength);

// Определяет позиции контрольных бит и общую длину кода
HammingPositionInfo GetHammingPositionInfo(const string& Message);

// Строит код Хемминга для данного сообщения
string BuildHammingCode(const string& Message, const HammingPositionInfo& Info);

// Вычисляет синдром для проверки и исправления ошибки
int CalculateSyndrome(const string& ReceivedCode, const HammingPositionInfo& Info);

// Исправляет одиночную ошибку в коде Хемминга
string CorrectHammingCode(const string& ReceivedCode, const HammingPositionInfo& Info, int ErrorPosition);

// Извлекает исходное сообщение из (исправленного) кода Хемминга
string ExtractMessageFromHamming(const string& CorrectedCode, const HammingPositionInfo& Info);


// 2

// Узел для дерева Хаффмана
struct HuffmanNode {
    char Data;
    unsigned Freq;
    HuffmanNode* Left, * Right;

    HuffmanNode(char Data, unsigned Freq) : Data(Data), Freq(Freq), Left(nullptr), Right(nullptr) {}
};

// Сравнение для priority_queue (min-heap)
struct CompareHuffmanNodes {
    bool operator()(HuffmanNode* L, HuffmanNode* R) {
        return L->Freq > R->Freq;
    }
};

// Основная функция для построения дерева Хаффмана и получения кодов
map<char, string> BuildHuffmanCodes(const string& Text, HuffmanNode*& Root);

// Вспомогательная функция для рекурсивного получения кодов из дерева
void GetHuffmanCodesRecursive(HuffmanNode* Root, string Str, map<char, string>& HuffmanCodeMap);

// Вспомогательная функция для вывода дерева Хаффмана
void PrintHuffmanTree(HuffmanNode* Root, string Indent = "", bool IsLeft = true);

// Функция для кодирования текста с использованием кодов Хаффмана
string EncodeHuffman(const string& Text, const map<char, string>& HuffmanCodes);

// Функция для декодирования текста с использованием дерева Хаффмана
string DecodeHuffman(HuffmanNode* Root, const string& EncodedText);

// Функция для удаления дерева Хаффмана
void DeleteHuffmanTree(HuffmanNode* Node);


// 3

// Шифрование методом столбчатой транспозиции
string ColumnarTranspositionEncrypt(const string& PlainText, const string& Key);

// Дешифрование методом столбчатой транспозиции
string ColumnarTranspositionDecrypt(const string& CipherText, const string& Key);