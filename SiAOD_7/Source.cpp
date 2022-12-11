#include "Header.h"

int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string s;
	short problem;
	bool flag = true;
	while (flag)
	{
		system("cls");
		cout << "Практическая работа №7 ИКБО-06-21 Эрднеева Н.Д. Варинат 10" << "\n\n"
			"Меню\n"
			"1) Алгоритм сжатия RLE.\n"
			"2) Алгоритм сжатия LZ77.\n"
			"3) Алгоритм сжатия LZ78.\n"
			"4) Алгоритм сжатия Шеннона-Фано.\n"
			"5) Алгоритм сжатия Хаффмана.\n\n";
		cout << "Ваш выбор: ";
		cin >> problem;
		switch (problem) {
		case 1:
		{
			cout << "Введите строку: ";
			cin >> s;
			cout << "Результат: ";
			RLE(s);
			system("pause");
			break;
		}
		case 2:
		{
			s = "1110100110110001101";
			cout << "Результат: ";
			LZ77(s);
			system("pause");
			break;
		}
		case 3:
		{
			s = "tertrektekertektrek";
			cout << "Результат: ";
			LZ78(s);
			system("pause");
			break;
		}
		case 4:
		{
			s = "Самолёт-вертолёт! Посади меня в полёт! А в полёте пусто – Выросла капуста.";
			cout << "Результат: ";
			ShannonFano(s);
			system("pause");
			break;
		}
		case 5:
		{
			s = "Эрднеева Надежда Дмитриевна.";
			cout << "Результат: ";
			Huffman(s);
			system("pause");
			break;
		}
		default:
			cout << "Извините, я не совсем понимаю, что вы хотите сделать. Попробуйте в другой раз.\n";
			system("pause");
			break;
		}
	}
	return 0;
}
void RLE(string s) {
	string compressed = "";
	double compressCoefficient, begSize, endSize;
	int repeat = 1;
	char curSymbol = NULL;
	string numOfRepeat = "";
	for (int i = 0; i < s.size(); i++) {
		if (curSymbol == NULL) {
			curSymbol = s[i];
		}
		else {
			if (curSymbol == s[i]) {
				repeat++;
			}
			else {
				numOfRepeat = to_string(repeat);
				compressed += numOfRepeat;
				repeat = 1;
				compressed += curSymbol;
				curSymbol = s[i];
			}
		}
		if (i == s.size() - 1) {
			numOfRepeat = to_string(repeat);
			compressed += numOfRepeat;
			compressed += curSymbol;
		}
	}
	compressed = compressCheck(compressed);
	cout << compressed << '\n';
	begSize = s.size();
	endSize = compressed.size();
	if (begSize > endSize) {
		compressCoefficient = begSize / endSize;
		cout << "Коэффициент сжатия: " << compressCoefficient << '\n';
	}
	else {
		compressCoefficient = endSize / begSize;
		cout << "Строка увеличилась в " << compressCoefficient << " раз" << '\n';
	}
}
string compressCheck(string compressed) {
	string newCompressed = "";
	int oneRepeats = 0;
	string numOfUnic = "";
	for (int i = 0; i < compressed.size(); i += 2) {
		if (compressed[i] == '1') {
			oneRepeats++;
		}
		if ((compressed[i] != '1') || (i == compressed.size() - 2)) {
			if (oneRepeats > 0) {
				numOfUnic = to_string(oneRepeats);
				newCompressed += '-';
				newCompressed += numOfUnic;
				for (int j = 1; j <= oneRepeats; j++) {
					newCompressed += compressed[2 * j - 1];
				}
				oneRepeats = 0;
				if (compressed[i] != '1') {
					i -= 2;
				}
			}
			else {
				newCompressed += compressed[i];
				newCompressed += compressed[i + 1];
			}
		}
	}
	return newCompressed;
}
void LZ77(string s) {
	Node currrent;
	for (int i = 0; i < s.size(); i++) {
		copyCheck(s, i, currrent);
		if (currrent.length == 0) {
			currrent.next = s[i];
		}
		else {
			i += currrent.length;
			if (i >= s.size()) {
				currrent.next = '\0';
			}
			else {
				currrent.next = s[i];
			}
		}
		list.push_back(currrent);
	}
	double k;
	double resultSize = 0;
	for (int i = 0; i < list.size(); i++) {
		cout << "(" << list[i].offset << "|" << list[i].length << "|" << list[i].next << ") ";
		if (list[i].offset != 0)
			resultSize += 3;
		else
			resultSize++;
	}
	double initialString = s.size();
	k = initialString / resultSize;
	cout << "\nКоэффициент сжатия: " << k << '\n';
}
void copyCheck(string s, int wPos, Node& rec) {
	int lenght = 0, offset = 0;
	string dictionary = "";
	for (int i = 5; i > 0; i--) {
		if (wPos >= 5) {
			dictionary += s[wPos - i];
			dictionary.erase(0, 1);
		}
		else if ((wPos < 5) && (wPos > 0)) {
			int pos = 0;
			while (true) {
				dictionary += s[pos];
				pos++;
				if (pos == wPos) {
					break;
				}
			}
			break;
		}
	}
	bool find = false;
	if (dictionary.size() == 0) {
		rec.offset = 0;
		rec.length = 0;
	}
	else {
		int i = 0;
		while (true) {
			if (i >= dictionary.size()) break;
			if (dictionary[i] == s[wPos + i]) {
				if (offset == 0) {
					offset = dictionary.size() - i;
				}
				find = true;
				lenght++;
			}
			if (find) {
				if (dictionary[i] != s[wPos + i]) {
					break;
				}
			}
			i++;
			if ((!find) && (i == dictionary.size())) {
				break;
			}
		}
		if (lenght == dictionary.size()) {
			int j = 0;
			while (true) {
				if (wPos + dictionary.size() + j >= s.size())break;
				if (s[wPos + j] == s[wPos + dictionary.size() + j]) {
					lenght++;
				}
				else break;
			}
		}
	}
	rec.length = lenght;
	rec.offset = offset;
}
void LZ78(string s) {
	newNode current;
	string secondCur = "";
	LZ78dictionary.push_back(secondCur);
	for (int i = 0; i < s.size(); i++) {
		string newRec = "";
		newRec += s[i];
		if (findInDictionary(newRec) == -1) {
			current.number = 0;
			current.next = s[i];
		}
		while (findInDictionary(newRec) != -1) {
			current.number = findInDictionary(newRec);
			if (i < s.size()) {
				i++;
				newRec += s[i];
			}
			else {
				current.next = '\0';
				break;
			}
		}
		current.next = newRec[newRec.size() - 1];
		LZ78dictionary.push_back(newRec);
		newList.push_back(current);
	}
	LZ78dictionary.erase(LZ78dictionary.begin() + (LZ78dictionary.size() - 1));
	string compressed = "";
	for (int i = 0; i < newList.size(); i++) {
		cout << newList[i].number << newList[i].next;
		compressed += newList[i].number;
		compressed += newList[i].next;
	}
	cout << "\nПояснение:";
	for (int i = 0; i < newList.size(); i++) {
		cout << "(" << newList[i].number << "|" << newList[i].next << ") ";
	}
	double k;
	double initialString = s.size();
	double resultSize = compressed.size();
	k = initialString / resultSize;
	cout << "\nКоэффициент сжатия: " << k << '\n';
	cout << "Словарь:";
	for (int i = 0; i < LZ78dictionary.size(); i++) {
		cout << LZ78dictionary[i] << '\n';
	}
	cout << '\n';
}
int findInDictionary(string el) {

	for (int i = 0; i < LZ78dictionary.size(); i++) {
		if (LZ78dictionary[i] == el) {
			return i;
		}
	}
	return -1;
}
void ShannonFano(string s) {
	for (int i = 0; i < s.size(); i++) {
		isInTable(s[i]);
	}
	ShannonTableSort();
	string allEl = "";
	for (int i = 0; i < ShannonFanoTable.size(); i++) {
		allEl += ShannonFanoTable[i].el;
	}
	ShannonTree tree = ShannonTree(allEl, findWeight());
	tree.buildTree(&tree);
	string compressed = "";
	for (int i = 0; i < s.size(); i++) {
		compressed += ShannonFanoTable[find(s[i])].code;
	}
	cout << compressed << '\n';
	double k;
	double begSize = s.size() * 8;
	double endSize = compressed.size();
	k = begSize / endSize;
	cout << "\nКоэффициент сжатия: " << k << '\n';
}
void isInTable(char el) {
	SF x;
	for (int i = 0; i < ShannonFanoTable.size(); i++) {
		if (ShannonFanoTable[i].el == el) {
			ShannonFanoTable[i].numOfoccurrences++;
			return;
		}
	}
	x.el = el;
	x.numOfoccurrences = 1;
	ShannonFanoTable.push_back(x);
}
int findInTable(char el) {
	for (int i = 0; i < ShannonFanoTable.size(); i++) {
		if (ShannonFanoTable[i].el == el) {
			return ShannonFanoTable[i].numOfoccurrences;
		}
	}
}
void ShannonTableSort() {
	int max = 0, newNum;
	for (int i = 0; i < ShannonFanoTable.size(); i++) {
		for (int j = i; j < ShannonFanoTable.size(); j++) {
			if (ShannonFanoTable[j].numOfoccurrences > max) {
				max = ShannonFanoTable[j].numOfoccurrences;
				newNum = j;
			}
		}
		max = 0;
		swap(ShannonFanoTable[i], ShannonFanoTable[newNum]);
	}
}
int findWeight() {
	int weight = 0;
	for (int i = 0; i < ShannonFanoTable.size(); i++) {
		weight += ShannonFanoTable[i].numOfoccurrences;
	}
	return weight;
}
void ShannonTree::buildTree(ShannonTree* root) {
	string leftList = "", rightList = root->el;
	if (root->el.size() > 1) {
		for (int i = 0; i < el.size(); i++) {
			leftList += root->el[i];
			rightList.erase(0, 1);
			if (getWeight(leftList, leftList.size() - 1) >= getWeight(rightList, rightList.size() - 1)) {
				root->left = new ShannonTree(leftList, getWeight(leftList, leftList.size() - 1));
				root->right = new ShannonTree(rightList, getWeight(rightList, rightList.size() - 1));
				root->left->code += root->code;
				root->right->code += root->code;
				root->left->code += '0';
				root->right->code += '1';
				buildTree(root->left);
				buildTree(root->right);
				break;
			}
		}
	}
	else {
		char c = root->el[0];
		ShannonFanoTable[find(c)].code = root->code;
	}
}
int find(char el) {
	for (int i = 0; i < ShannonFanoTable.size(); i++) {
		if (el == ShannonFanoTable[i].el) {
			return i;
		}
	}
}
int ShannonTree::getWeight(string s, int i) {
	int weight = 0;
	for (int j = 0; j <= i; j++) {
		for (int k = 0; k < ShannonFanoTable.size(); k++) {
			if (ShannonFanoTable[k].el == s[j]) {
				weight += ShannonFanoTable[k].numOfoccurrences;
				break;
			}
		}
	}
	return weight;
}
void Huffman(string s) {
	for (int i = 0; i < s.size(); i++) {
		isInTable(s[i]);
	}
	ShannonTableSort();
	string allEl = "";
	for (int i = 0; i < ShannonFanoTable.size(); i++) {
		allEl += ShannonFanoTable[i].el;
	}
	HuffmanTree tree = HuffmanTree(allEl, 1);
	tree.buildTree(&tree);
	string compressed = "";
	for (int i = 0; i < s.size(); i++) {
		compressed += ShannonFanoTable[find(s[i])].code;
	}
	cout << compressed << '\n';
	double k;
	double begSize = s.size() * 8;
	double endSize = compressed.size();
	k = begSize / endSize;
	cout << "\nКоэффициент сжатия: " << k << '\n';
}
void HuffmanTree::buildTree(HuffmanTree* root) {
	string leftList = "", rightList = root->el;
	if (root->el.size() > 1) {
		for (int i = 0; i < el.size(); i++) {
			leftList += root->el[i];
			rightList.erase(0, 1);
			if (getProbability(leftList) >= getProbability(rightList)) {
				root->left = new HuffmanTree(leftList, getProbability(leftList));
				root->right = new HuffmanTree(rightList, getProbability(rightList));
				root->left->code += root->code;
				root->right->code += root->code;
				root->left->code += '0';
				root->right->code += '1';
				buildTree(root->left);
				buildTree(root->right);
				break;
			}
		}
	}
	else {
		char c = root->el[0];
		ShannonFanoTable[find(c)].code = root->code;
	}
}
double HuffmanTree::getProbability(string el) {
	double probability = 0;
	for (int i = 0; i < el.size(); i++) {
		probability += ShannonFanoTable[find(el[i])].numOfoccurrences;
	}
	return probability;
}