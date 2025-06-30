#include "header.h"

//1)

int CalculateHammingControlBits(int DataLength) {
    int r = 0;
    // 2^r >= m + r + 1
    while (pow(2, r) < DataLength + r + 1) {
        r++;
    }
    return r;
}

HammingPositionInfo GetHammingPositionInfo(const string& Message) {
    HammingPositionInfo info;
    info.DataBits = Message.length();
    info.ControlBits = CalculateHammingControlBits(info.DataBits);
    info.TotalBits = info.DataBits + info.ControlBits;

    for (int i = 0; i < info.ControlBits; ++i) {
        info.ControlBitPositions.push_back(static_cast<int>(pow(2, i)));
    }
    return info;
}

string BuildHammingCode(const string& Message, const HammingPositionInfo& Info) {
    string hammingCode(Info.TotalBits, '0');
    int dataIdx = 0;

    // ����������� �������������� ����
    for (int i = 1; i <= Info.TotalBits; ++i) {
        bool isControlPos = false;
        for (int cp : Info.ControlBitPositions) {
            if (i == cp) {
                isControlPos = true;
                break;
            }
        }
        if (!isControlPos) {
            if (dataIdx < Message.length()) {
                hammingCode[i - 1] = Message[dataIdx];
                dataIdx++;
            }
        }
    }

    // ������������ ����������� ����
    for (int controlPos : Info.ControlBitPositions) {
        int xorSum = 0;
        for (int i = 1; i <= Info.TotalBits; ++i) {
            // ���������, ��������� �� ������ ����������� ��� ������� i
            if ((i & controlPos) != 0) {
                if (hammingCode[i - 1] == '1') {
                    xorSum++;
                }
            }
        }
        // ������������� ����������� ��� (��������)
        hammingCode[controlPos - 1] = (xorSum % 2 == 0) ? '0' : '1';
    }
    return hammingCode;
}

int CalculateSyndrome(const string& ReceivedCode, const HammingPositionInfo& Info) {
    int syndrome = 0;
    for (int controlPos : Info.ControlBitPositions) {
        int xorSum = 0;
        for (int i = 1; i <= Info.TotalBits; ++i) {
            if ((i & controlPos) != 0) { // ������� i ����������� ����������� ����� controlPos
                if (ReceivedCode[i - 1] == '1') {
                    xorSum++;
                }
            }
        }
        if (xorSum % 2 != 0) { // ���� �������� ���������� ������, ���� ����������� ��� "�� ��������"
            syndrome += controlPos;
        }
    }
    return syndrome;
}

string CorrectHammingCode(const string& ReceivedCode, const HammingPositionInfo& Info, int ErrorPosition) {
    if (ErrorPosition == 0 || ErrorPosition > Info.TotalBits) {
        return ReceivedCode; // ��� ������ ��� ������� ��� ���������
    }
    string correctedCode = ReceivedCode;
    correctedCode[ErrorPosition - 1] = (correctedCode[ErrorPosition - 1] == '0') ? '1' : '0';
    return correctedCode;
}

string ExtractMessageFromHamming(const string& CorrectedCode, const HammingPositionInfo& Info) {
    string message = "";
    for (int i = 1; i <= Info.TotalBits; ++i) {
        bool isControlPos = false;
        for (int cp : Info.ControlBitPositions) {
            if (i == cp) {
                isControlPos = true;
                break;
            }
        }
        if (!isControlPos) {
            message += CorrectedCode[i - 1];
        }
    }
    return message;
}


//2)

map<char, string> BuildHuffmanCodes(const string& Text, HuffmanNode*& Root) {
    map<char, unsigned> freqMap;
    for (char c : Text) {
        freqMap[c]++;
    }

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareHuffmanNodes> pq;
    for (auto pair : freqMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        // '$' - ����������� ������ ��� ���������� �����
        HuffmanNode* top = new HuffmanNode('$', left->Freq + right->Freq);
        top->Left = left;
        top->Right = right;
        pq.push(top);
    }
    Root = pq.top(); // ������ ������ ��������

    map<char, string> huffmanCodeMap;
    GetHuffmanCodesRecursive(Root, "", huffmanCodeMap);
    return huffmanCodeMap;
}

void GetHuffmanCodesRecursive(HuffmanNode* RootNode, string Str, map<char, string>& HuffmanCodeMap) {
    if (RootNode == nullptr) return;

    // ���� ��� �������� ���� (�������� ������)
    if (RootNode->Data != '$') {
        HuffmanCodeMap[RootNode->Data] = Str;
    }

    GetHuffmanCodesRecursive(RootNode->Left, Str + "0", HuffmanCodeMap);
    GetHuffmanCodesRecursive(RootNode->Right, Str + "1", HuffmanCodeMap);
}

void PrintHuffmanTree(HuffmanNode* RootNode, string Indent, bool IsLeft) {
    if (RootNode == nullptr) {
        return;
    }
    cout << Indent;
    if (RootNode != nullptr) {
        cout << (IsLeft ? "L-- " : "R-- ");
    }

    if (RootNode->Data != '$') {
        cout << "'" << RootNode->Data << "' (" << RootNode->Freq << ")" << endl;
    }
    else {
        cout << "(" << RootNode->Freq << ")" << endl;
    }

    PrintHuffmanTree(RootNode->Left, Indent + (IsLeft ? "    " : "|   "), true);
    PrintHuffmanTree(RootNode->Right, Indent + (IsLeft ? "    " : "|   "), false);
}

string EncodeHuffman(const string& Text, const map<char, string>& HuffmanCodes) {
    string encodedString = "";
    for (char c : Text) {
        encodedString += HuffmanCodes.at(c);
    }
    return encodedString;
}

string DecodeHuffman(HuffmanNode* RootNode, const string& EncodedText) {
    string decodedString = "";
    HuffmanNode* currentNode = RootNode;
    for (char bit : EncodedText) {
        if (bit == '0') {
            currentNode = currentNode->Left;
        }
        else {
            currentNode = currentNode->Right;
        }

        // ���� �������� ��������� ����
        if (currentNode->Left == nullptr && currentNode->Right == nullptr) {
            decodedString += currentNode->Data;
            currentNode = RootNode; // ������������ � ����� ��� ���������� �������
        }
    }
    return decodedString;
}

void DeleteHuffmanTree(HuffmanNode* Node) {
    if (Node == nullptr) return;
    DeleteHuffmanTree(Node->Left);
    DeleteHuffmanTree(Node->Right);
    delete Node;
}


//3

string ColumnarTranspositionEncrypt(const string& PlainText, const string& Key) {
    int numCols = Key.length();
    int numRows = (PlainText.length() + numCols - 1) / numCols; // ���������� �����
    vector<string> matrix(numRows, string(numCols, ' ')); // ��������� ��������� �� ������ �������� ��������� ������

    int k = 0;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (k < PlainText.length()) {
                matrix[i][j] = PlainText[k++];
            }
        }
    }

    // ������� ���� (������ �����, ������ �������) ��� ����������
    vector<pair<char, int>> sortedKey;
    for (int i = 0; i < numCols; ++i) {
        sortedKey.push_back({ Key[i], i });
    }
    sort(sortedKey.begin(), sortedKey.end());

    string cipherText = "";
    for (const auto& p : sortedKey) {
        int colIndex = p.second;
        for (int i = 0; i < numRows; ++i) {
            cipherText += matrix[i][colIndex];
        }
    }
    return cipherText;
}

string ColumnarTranspositionDecrypt(const string& CipherText, const string& Key) {
    int numCols = Key.length();
    int numRows = CipherText.length() / numCols;

    vector<string> matrix(numRows, string(numCols, ' '));
    vector<pair<char, int>> sortedKey;
    for (int i = 0; i < numCols; ++i) {
        sortedKey.push_back({ Key[i], i });
    }
    sort(sortedKey.begin(), sortedKey.end());

    // ��������������� �������� ������� ��������
    vector<int> originalColOrder(numCols);
    for (int i = 0; i < numCols; ++i) {
        originalColOrder[sortedKey[i].second] = i;
    }


    int k = 0;
    for (const auto& p : sortedKey) { // ������ ������� � ������� ���������������� �����
        int originalColIndexOfThisEncryptedColumn = p.second;
        for (int i = 0; i < numRows; ++i) {
            if (k < CipherText.length()) {
                // ����������� ������� ���������� � ������� � "�������������" ������� ��������
                matrix[i][originalColIndexOfThisEncryptedColumn] = CipherText[k++];
            }
        }
    }

    string plainText = "";
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) { // ������ ������� ���������
            plainText += matrix[i][j];
        }
    }
    // ������� ��������� ������ ������� � �����, ���� ��� ���� ��������� ��� ������������
    size_t lastMeaningfulChar = plainText.find_last_not_of(' ');
    if (string::npos != lastMeaningfulChar) {
        plainText.erase(lastMeaningfulChar + 1);
    }

    return plainText;
}