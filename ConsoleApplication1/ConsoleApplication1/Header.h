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

// ��������� ��� �������� ���������� � �������� ���
struct HammingPositionInfo {
    int TotalBits;          // ����� ���������� ��� � ���� �������� (m+r)
    int DataBits;           // ���������� �������������� ��� (m)
    int ControlBits;        // ���������� ����������� ��� (r)
    vector<int> ControlBitPositions; // ������� ����������� ���
};

// ������������ ����������� ���������� ����������� ���
int CalculateHammingControlBits(int DataLength);

// ���������� ������� ����������� ��� � ����� ����� ����
HammingPositionInfo GetHammingPositionInfo(const string& Message);

// ������ ��� �������� ��� ������� ���������
string BuildHammingCode(const string& Message, const HammingPositionInfo& Info);

// ��������� ������� ��� �������� � ����������� ������
int CalculateSyndrome(const string& ReceivedCode, const HammingPositionInfo& Info);

// ���������� ��������� ������ � ���� ��������
string CorrectHammingCode(const string& ReceivedCode, const HammingPositionInfo& Info, int ErrorPosition);

// ��������� �������� ��������� �� (�������������) ���� ��������
string ExtractMessageFromHamming(const string& CorrectedCode, const HammingPositionInfo& Info);


// 2

// ���� ��� ������ ��������
struct HuffmanNode {
    char Data;
    unsigned Freq;
    HuffmanNode* Left, * Right;

    HuffmanNode(char Data, unsigned Freq) : Data(Data), Freq(Freq), Left(nullptr), Right(nullptr) {}
};

// ��������� ��� priority_queue (min-heap)
struct CompareHuffmanNodes {
    bool operator()(HuffmanNode* L, HuffmanNode* R) {
        return L->Freq > R->Freq;
    }
};

// �������� ������� ��� ���������� ������ �������� � ��������� �����
map<char, string> BuildHuffmanCodes(const string& Text, HuffmanNode*& Root);

// ��������������� ������� ��� ������������ ��������� ����� �� ������
void GetHuffmanCodesRecursive(HuffmanNode* Root, string Str, map<char, string>& HuffmanCodeMap);

// ��������������� ������� ��� ������ ������ ��������
void PrintHuffmanTree(HuffmanNode* Root, string Indent = "", bool IsLeft = true);

// ������� ��� ����������� ������ � �������������� ����� ��������
string EncodeHuffman(const string& Text, const map<char, string>& HuffmanCodes);

// ������� ��� ������������� ������ � �������������� ������ ��������
string DecodeHuffman(HuffmanNode* Root, const string& EncodedText);

// ������� ��� �������� ������ ��������
void DeleteHuffmanTree(HuffmanNode* Node);


// 3

// ���������� ������� ���������� ������������
string ColumnarTranspositionEncrypt(const string& PlainText, const string& Key);

// ������������ ������� ���������� ������������
string ColumnarTranspositionDecrypt(const string& CipherText, const string& Key);