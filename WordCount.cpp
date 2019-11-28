#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Word
{
    std::string word;
    int count = 1;
};

std::istream& read_word(std::istream& is, Word& word)
{
    is >> word.word;
    is.clear();
}

bool compare(Word& word1, Word& word2)
{
    return word1.count < word2.count;
}

bool operator== (const Word& word1, const Word& word2) {
    return (word1.word == word2.word);
}

int main()
{
    Word input;
    std::vector<Word> all_words;
    std::cout << "Start entering words:" << std::endl;
    while(read_word(std::cin, input))
    {
        if(input.word == "quit")
        {
            break;
        }
        auto index = std::find(all_words.begin(), all_words.end(), input);
        if(index != all_words.end())
        {
            index->count += 1;
        }
        else
        {
            all_words.push_back(input);
        }
    }
    std::sort(all_words.begin(), all_words.end(), compare);
    std::cout << "Sorted!" << std::endl << std::endl;
    for(auto&& w: all_words)
    {
        std::cout << w.word << " has been seen " << w.count << " times" << std::endl;
    }
    return 0;
}