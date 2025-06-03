#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>

// �洢ÿ����Ľṹ��
struct Question {
    std::string content;
};

// �ж�һ���Ƿ�Ϊ����Ŀ�ʼ
bool isNewQuestion(const std::string& line) {
    if (line.empty()) return false;

    // ����Ƿ������ֻ��������ֿ�ͷ
    if (isdigit(line[0])) return true;

    // �����������ǰ׺��"1." "һ��" "��һ��" ��
    if (line.find("һ��") == 0 || line.find("����") == 0 ||
        line.find("����") == 0 || line.find("�ġ�") == 0 ||
        line.find("�塢") == 0)
        return true;

    return false;
}

// ���ļ��ж�ȡ��Ŀ������Ŀ����
std::vector<Question> readQuestionsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Question> questions;

    if (file.is_open()) {
        std::string line;
        Question currentQuestion;

        while (getline(file, line)) {
            // ����������⣬������һ��
            if (isNewQuestion(line)) {
                if (!currentQuestion.content.empty()) {
                    questions.push_back(currentQuestion);
                    currentQuestion.content.clear();
                }
            }

            // ��������
            if (!line.empty())
                currentQuestion.content += line + "\n";
        }

        // ������һ��
        if (!currentQuestion.content.empty()) {
            questions.push_back(currentQuestion);
        }

        file.close();
    } else {
        std::cerr << "�޷����ļ�: " << filename << std::endl;
    }

    return questions;
}

// ���ݹؼ���������Ŀ��������
void searchQuestions(const std::vector<Question>& questions, const std::string& keyword) {
    bool found = false;
    for (const auto& q : questions) {
        if (q.content.find(keyword) != std::string::npos) {
            std::cout << "------------------------------\n";
            std::cout << q.content;
            found = true;
        }
    }
    if (!found) {
        std::cout << "δ�ҵ������ùؼ��ʵ���Ŀ��\n";
    }
}

// ���������
int main() {
    std::string filename = "answer.txt";  // �ļ�·��
    std::vector<Question> questions = readQuestionsFromFile(filename);

    std::string keyword;
    while (true) {
        std::cout << "�����������ؼ��ʣ����� q �˳�����";
        std::cin >> keyword;
        if (keyword == "q") break;

        searchQuestions(questions, keyword);
    }

    return 0;
}
