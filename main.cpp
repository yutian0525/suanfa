#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>

struct Question {
    std::string content;
};

bool isNewQuestion(const std::string& line) {
    if (line.empty()) return false;

    if (isdigit(line[0])) return true;

    if (line.find("一、") == 0 || line.find("二、") == 0 ||
        line.find("三、") == 0 || line.find("四、") == 0 ||
        line.find("五、") == 0)
        return true;

    return false;
}

std::vector<Question> readQuestionsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Question> questions;

    if (file.is_open()) {
        std::string line;
        Question currentQuestion;

        while (getline(file, line)) {

            if (isNewQuestion(line)) {
                if (!currentQuestion.content.empty()) {
                    questions.push_back(currentQuestion);
                    currentQuestion.content.clear();
                }
            }

            if (!line.empty())
                currentQuestion.content += line + "\n";
        }

        if (!currentQuestion.content.empty()) {
            questions.push_back(currentQuestion);
        }

        file.close();
    } else {
        std::cerr << "无法打开文件: " << filename << std::endl;
    }

    return questions;
}

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
        std::cout << "未找到包含该关键词的题目。\n";
    }
}

int main() {
    std::string filename = "answer.txt";
    std::vector<Question> questions = readQuestionsFromFile(filename);

    std::string keyword;
    while (true) {
        std::cout << "请输入搜索关键词（输入 q 退出）：";
        std::cin >> keyword;
        if (keyword == "q") break;

        searchQuestions(questions, keyword);
    }

    return 0;
}
