#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>

using namespace std;

vector<pair<string,int>> map_to_vector_reverse(const map<string, int>& a);
bool sortbysec(const pair<string, int>& a, const pair<string, int>& b);


class ReadFile {
	string path;
public:
	ReadFile(string path) : path(path) {}

	void printFile() {
		ifstream in(path);
		string line;
		if (in.is_open()) {
			while (getline(in, line)) {
				cout << line << endl;
			}
		}
		in.close();
	}

	void erase_punctuation(string& word) {
		string punct = "“!@#¹$%^&*()-_/.,?><:;";
		for (int i = 0; i < word.length(); i++) {
			for (int j = 0; j < punct.length(); j++) {
				if (word[i] == punct[j]) {
					word.erase(i, 1);
				}
			}
		}
	}

	map<string,int> file_to_map(){
		ifstream in(path);
		string word;
		map<string, int> words;

		if (in.is_open()) {
			while (in >> word) {

				erase_punctuation(word);

				if (words.find(word) == words.end()) {
					words.emplace(word, 1);
				}
				else {
					words[word]++;
				}
			}
		}

		return words;
	}

	void popular_words() {
		
		map<string, int> words = file_to_map();
		//from map to vector;
		vector<pair<string,int>> words_reverse = map_to_vector_reverse(words);
		for (auto [k, v] : words_reverse) {
			cout << k << " " << v << endl;
		}
	}
};

vector<pair<string,int>> map_to_vector_reverse(const map<string, int> &a) {
	vector<pair<string, int>> b;
	copy(a.begin(), a.end(), back_inserter(b));
	sort(b.begin(), b.end(), sortbysec);
	return b;
}

bool sortbysec(const pair<string, int>& a, const pair<string, int>& b)
{
	return (a.second > b.second);
}

int main() {
	setlocale(LC_ALL, "en_US.UTF-8");
	ReadFile a("text.txt");
	a.popular_words();
}