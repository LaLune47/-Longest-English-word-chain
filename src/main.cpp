#include <iostream>
#include <vector>
#include <set>
#include <cstring>
#include <fstream>
#include "WordChainCoreInterface.h"

using namespace std;

int wordNum = 0;

char** readWords(string filePath) {
    ifstream file(filePath);
    set<string> words; // 容器用于存储单词

    if (file.is_open()) { // todo 文件异常处理
        string line;
        while (getline(file, line)) {
            string word;
            for (char c : line) {
                if (isalpha(c)) {
                    word += tolower(c);
                }
                else if (!word.empty()) {
                    words.insert(word);
                    word.clear();
                }
            }
            if (!word.empty()) { // 处理每行结尾可能存在的单词
                words.insert(word);
            }
        }
        file.close(); // 关闭文件
    }

    // 创建一个动态数组，用于存储char*指针
    char** result = new char*[words.size()];
    wordNum = words.size();

    int i = 0;
    for (string word : words) {
        int len = word.length();
        result[i] = new char[len + 1];
        //cout << word << endl;
        strcpy(result[i], word.c_str());
        i++;
    }

    // 返回指向char*数组的指针
    return result;
}

void printWords(char** words) {
    for (int i = 0; words[i] != NULL; i++) {
        cout << words[i] << std::endl;
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    char cal_type = '0';  // n,w,c Functional parameters

    // 存储限定的字母
    char h = '0'; //h
    char t = '0'; //t
    char j = '0'; //j

    bool r = false; //r 是否允许成环

    string filePath;

    // todo 异常处理
    // 处理命令行参数,读文件来读单词列表的问题放在最后
    for (int count = 1; count < argc; count++) {
        if (argv[count][0] == '-') { // 参数解析
            if (argv[count][1] == 'n' || argv[count][1] == 'w' || argv[count][1] == 'c') {
                cal_type = argv[count][1];
            } else if (argv[count][1] == 'h') {
                h = tolower(argv[++count][0]);
            } else if (argv[count][1] == 't') {
                t = tolower(argv[++count][0]);
            } else if (argv[count][1] == 'j') {
                j = tolower(argv[++count][0]);
            } else if (argv[count][1] == 'r') {
                r = true;
            }
        } else { // 文件名解析
            filePath = argv[count];
        }
    }

    char **words = readWords(filePath);
    //printWords(words,wordNum);
    //char **result = nullptr;
    char **result = new char*[wordNum];

    if (cal_type == 'n') {
        core::WordChainCoreInterface::gen_chains_all(words,wordNum,result);
    } else if (cal_type == 'w') {
        core::WordChainCoreInterface::gen_chain_word(words,wordNum,result,h,t,j,r);
    } else if (cal_type == 'c') {
        core::WordChainCoreInterface::gen_chain_char(words,wordNum,result,h,t,j,r);
    }

    printWords(result);

    return 0;
}