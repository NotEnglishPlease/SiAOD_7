#pragma once
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>
using namespace std;
struct Node {
	int offset;
	int length;
	char next;
};
struct newNode {
	int number;
	char next;
};
struct SF {
	char el;
	double numOfoccurrences;
	string code;
};
class ShannonTree {
public:
	string el;
	int weight;
	string code;
	ShannonTree* left;
	ShannonTree* right;
	void buildTree(ShannonTree* root);
	int getWeight(string s, int i);
	ShannonTree(string el, int weight) {
		this->el = el;
		this->weight = weight;
	}

};
class HuffmanTree {
public:
	string el;
	double probability;
	string code;
	HuffmanTree* left;
	HuffmanTree* right;
	void buildTree(HuffmanTree* root);
	double getProbability(string el);
	HuffmanTree(string el, double probability) {
		this->el = el;
		this->probability = probability;
	}
};
vector <Node> list;
vector <newNode> newList;
vector <string> LZ78dictionary;
vector <SF> ShannonFanoTable;
vector <string> codes;
void RLE(string s);
string compressCheck(string compressed);
void LZ77(string s);
void copyCheck(string s, int wPos, Node& rec);
void LZ78(string s);
int findInDictionary(string el);
void ShannonFano(string s);
void isInTable(char el);
int findInTable(char el);
void ShannonTableSort();
int findWeight();
int find(char el);
void Huffman(string s);