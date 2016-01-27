#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <numeric>
#include <limits>
#include <iterator>
#include <algorithm>
#include <windows.h>

using namespace std;

// problem 59
/*
Each character on a computer is assigned a unique code and the preferred standard is ASCII 
(American Standard Code for Information Interchange). 
For example, uppercase A = 65, asterisk (*) = 42, and lowercase k = 107.

A modern encryption method is to take a text file, convert the bytes to ASCII, then XOR each byte with a given value, 
taken from a secret key. 
The advantage with the XOR function is that using the same encryption key on the cipher text, restores the plain text; 
for example, 65 XOR 42 = 107, then 107 XOR 42 = 65.

For unbreakable encryption, the key is the same length as the plain text message, and the key is made up of random bytes. 
The user would keep the encrypted message and the encryption key in different locations, and without both "halves", 
it is impossible to decrypt the message.

Unfortunately, this method is impractical for most users, so the modified method is to use a password as a key. 
If the password is shorter than the message, which is likely, the key is repeated cyclically throughout the message. 
The balance for this method is using a sufficiently long password key for security, but short enough to be memorable.

Your task has been made easy, as the encryption key consists of three lower case characters. 
Using cipher1.txt (right click and 'Save Link/Target As...'), a file containing the encrypted ASCII codes, 
and the knowledge that the plain text must contain common English words, 
decrypt the message and find the sum of the ASCII values in the original text.
*/
// plain text的第一个字符时(，题目说contain common English words，但没说只含英文单词，所以需要一定的猜测才能解开encryption key

void disp(const vector<int>& v)
{
	for(auto& p: v) cout << p;
}

bool dec_to_bin(int d, vector<int>& bv)
{
	for(int x = d; x > 0; x /= 2)
		bv.insert(bv.begin(), x % 2);
	int l = bv.size();
	for(int i = 0; i < 8 - l; ++i)
		bv.insert(bv.begin(), 0);
	return bv.size() > 8? false: true;
}

int bin_to_dec(const vector<int>& bv)
{
	int d = 0;
	for(int i = bv.size() - 1; i >= 0; --i)
		d += bv[i] * pow(2, bv.size() - i - 1);
	return d;
}

int char_to_ascii(char c)
{
	if(isupper(c)) return c - 'A' + 65;
	if(islower(c)) return c - 'a' + 97;
	return -1;
}

char ascii_to_char(int a)
{
	if(a >= 65 && a <= 90)  return 'A' + a - 65;
	if(a >= 97 && a <= 122) return 'a' + a - 97;
	return '*';
}

int XOR(int b1, int b2)
{
	vector<int> bv1, bv2, bv3;
	dec_to_bin(b1, bv1);
	dec_to_bin(b2, bv2);
	for(int i = 0; i < bv1.size(); ++i)
		if(bv1[i] == 0 && bv2[i] == 0 || bv1[i] == 1 && bv2[i] == 1)
			bv3.push_back(0);
		else
			bv3.push_back(1);
	return bin_to_dec(bv3);
}

int main()
{
	for(char key1 = 'a'; key1 <= 'z'; ++key1)
		for(char key2 = 'a'; key2 <= 'z'; ++key2)
			for(char key3 = 'a'; key3 <= 'z'; ++key3)
			{
				int k1 = char_to_ascii(key1);
				int k2 = char_to_ascii(key2);
				int k3 = char_to_ascii(key3);

				cout << "------------------------------------" << endl;
				cout << key1 << key2 << key3 << " " << k1 << " " << k2 << " " << k3 << endl;

				ifstream f("E:\\document\\programs\\project_euler\\pe_59\\cipher1.txt");

				bool flag = true;
				while(f.good())
				{
					int c1, c2, c3;
					char t;
					f >> c1 >> t >> c2 >> t >> c3 >> t;
					cout << "   " << c1 << " " << c2 << " " << c3 << "   ";

					int m1 = XOR(c1, k1);
					int m2 = XOR(c2, k2);
					int m3 = XOR(c3, k3);
					char message1 = ascii_to_char(m1);
					char message2 = ascii_to_char(m2);
					char message3 = ascii_to_char(m3);
					cout << message1 << message2 << message3 << endl;
					if(message1 == '*' || message2 == '*' || message3 == '*')
					{
						flag = false;
						break;
					}
				}

				f.close();

				cout << "   " << (flag? "yes": "no") << endl;
				if(flag) break;
			}

	return 0;
}