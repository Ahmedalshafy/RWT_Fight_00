#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <algorithm>
#include <iostream>

int countWordsThatMakeYouHappy(const std::string& sentence) {
    std::unordered_set<std::string> happyWords = {
        "love", "joy", "peace", "happy", "smile", "grateful", "kind", "hope", "laugh", "sunshine"
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

int main() {
    std::string testSentence = "I love the sunshine and feel happy today!";
    int result = countWordsThatMakeYouHappy(testSentence);
    std::cout << "Found " << result << " happy words in: \"" << testSentence << "\"" << std::endl;
    return 0;
}