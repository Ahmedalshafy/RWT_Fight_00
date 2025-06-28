#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string analyzeSentimentWithGroq(const std::string& sentence) {
    CURL* curl = curl_easy_init();
    std::string response;
    
    if (!curl) {
        return "Error: Could not initialize CURL";
    }
    json request_data;
    request_data["model"] = "llama3-8b-8192";
    request_data["messages"][0]["role"] = "user";
    request_data["messages"][0]["content"] = "Analyze the sentiment of this sentence and respond with only one word: 'Positive', 'Negative', or 'Neutral'. Sentence: " + sentence;
    request_data["temperature"] = 0.1;
    request_data["max_tokens"] = 10;
    std::string json_payload = request_data.dump();
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.groq.com/openai/v1/chat/completions");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "Authorization: Bearer YOUR_API_KEY"); // Replace with your actual API key
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    if (res != CURLE_OK) {
        return "Error: Failed to make API request";
    }
    try {
        json response_json = json::parse(response);
        
        if (response_json.contains("choices") && 
            response_json["choices"].size() > 0 && 
            response_json["choices"][0].contains("message") &&
            response_json["choices"][0]["message"].contains("content")) {
            
            std::string sentiment = response_json["choices"][0]["message"]["content"];
            
            // Clean up the response (remove quotes, extra spaces, etc.)
            sentiment.erase(std::remove(sentiment.begin(), sentiment.end(), '"'), sentiment.end());
            sentiment.erase(std::remove(sentiment.begin(), sentiment.end(), '\n'), sentiment.end());
            sentiment.erase(std::remove(sentiment.begin(), sentiment.end(), '\r'), sentiment.end());
            sentiment.erase(0, sentiment.find_first_not_of(" \t"));
            sentiment.erase(sentiment.find_last_not_of(" \t") + 1);
            std::transform(sentiment.begin(), sentiment.end(), sentiment.begin(), ::tolower);
            if (sentiment.find("positive") != std::string::npos) {
                return "Positive 😊 (AI analyzed)";
            } else if (sentiment.find("negative") != std::string::npos) {
                return "Negative 🙁 (AI analyzed)";
            } else if (sentiment.find("neutral") != std::string::npos) {
                return "Neutral 😐 (AI analyzed)";
            } else {
                return "Unknown sentiment: " + sentiment;
            }
        } else {
            return "Error: Invalid API response format";
        }
    } catch (const std::exception& e) {
        return "Error: Failed to parse API response";
    }
}
int main() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    std::string sentence;
    std::cout << "Enter a sentence to analyze: ";
    std::getline(std::cin, sentence);
    std::cout << analyzeSentimentWithGroq(sentence) << std::endl;
    curl_global_cleanup();
    return 0;
}