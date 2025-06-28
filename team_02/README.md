# Groq AI Sentiment Analyzer

This C++ program uses the Groq AI API to analyze the sentiment of sentences instead of using hardcoded word matching.

## Prerequisites

1. **Install libcurl development library:**
   ```bash
   sudo apt-get install libcurl4-openssl-dev
   ```

2. **Install nlohmann/json library:**
   ```bash
   sudo apt-get install nlohmann-json3-dev
   ```

3. **Get a Groq API key:**
   - Sign up at [https://console.groq.com/](https://console.groq.com/)
   - Create an API key in your dashboard
   - Replace `YOUR_GROQ_API_KEY` in the code with your actual API key

## Compilation

```bash
g++ -std=c++17 -Wall -Wextra -o sentiment_analyzer do.cpp -lcurl
```

## Usage

```bash
./sentiment_analyzer
```

The program will prompt you to enter a sentence, then analyze its sentiment using Groq AI and display the result.

## Features

- Uses Groq's Llama3-8b-8192 model for sentiment analysis
- Returns one of three sentiments: Positive, Negative, or Neutral
- Includes emoji indicators for better visualization
- Handles API errors gracefully
- Uses proper HTTP client (libcurl) for API communication

## Example Output

```
Enter a sentence to analyze: I love this amazing day!
Positive 😊 (AI analyzed)

Enter a sentence to analyze: This is terrible and awful
Negative 🙁 (AI analyzed)

Enter a sentence to analyze: The weather is cloudy today
Neutral 😐 (AI analyzed)
```

## Notes

- Make sure you have an active internet connection
- The API key should be kept secure and not shared publicly
- The program uses a low temperature (0.1) for consistent results
- Maximum tokens are limited to 10 for efficiency 