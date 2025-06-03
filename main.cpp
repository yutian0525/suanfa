#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>

// 存储每道题的结构体
struct Question {
    std::string content;
};

// 判断一行是否为新题的开始
bool isNewQuestion(const std::string& line) {
    if (line.empty()) return false;

    // 检查是否以数字或中文数字开头
    if (isdigit(line[0])) return true;

    // 常见中文题号前缀："1." "一、" "（一）" 等
    if (line.find("一、") == 0 || line.find("二、") == 0 ||
        line.find("三、") == 0 || line.find("四、") == 0 ||
        line.find("五、") == 0)
        return true;

    return false;
}

// 从文件中读取题目并按题目分组
std::vector<Question> readQuestionsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Question> questions;

    if (file.is_open()) {
        std::string line;
        Question currentQuestion;

        while (getline(file, line)) {
            // 如果遇到新题，保存上一题
            if (isNewQuestion(line)) {
                if (!currentQuestion.content.empty()) {
                    questions.push_back(currentQuestion);
                    currentQuestion.content.clear();
                }
            }

            // 跳过空行
            if (!line.empty())
                currentQuestion.content += line + "\n";
        }

        // 添加最后一题
        if (!currentQuestion.content.empty()) {
            questions.push_back(currentQuestion);
        }

        file.close();
    } else {
        std::cerr << "无法打开文件: " << filename << std::endl;
    }

    return questions;
}

// 根据关键词搜索题目并输出结果
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

// 主函数入口
int main() {
    std::string filename = "answer.txt";  // 文件路径
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
