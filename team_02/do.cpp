#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <iomanip>


int countWordsThatMakeYouHappy(const std::string& sentence) {
    std::unordered_set<std::string> happyWords = {
        "love", "joy", "peace", "happy", "smile", "grateful", "kind", "hope", "laugh", "sunshine", "happiness"
    };

    std::istringstream iss(sentence);
    std::string word;
    int count = 0;

    while (iss >> word) {
        // convert to lowercase
        for (char& c : word) c = std::tolower(c);
        // remove punctuation
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());

        if (happyWords.count(word)) {
            ++count;
        }
    }
    
    return count;
}
std::string analyzeSentiment(const std::string& sentence) {
    int totalWords = std::count_if(sentence.begin(), sentence.end(), [](char c){ return c == ' '; }) + 1;
    int happyCount = countWordsThatMakeYouHappy(sentence);
    double percentage = (static_cast<double>(happyCount) / totalWords) * 100.0;
    std::ostringstream out;
    out << std::fixed << std::setprecision(0);
    if (percentage >= 30.0) out << "Positive 😊 (" << percentage << "% happy words)";
    else if (percentage >= 10.0) out << "Neutral 😐 (" << percentage << "% happy words)";
    else out << "Negative 🙁 (" << percentage << "% happy words)";
    return out.str();
}

int main() {
    std::string s;
    std::cin >> s;
    std::cout << analyzeSentiment(s) << std::endl;
    return 0;
}