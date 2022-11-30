#include "utilities.h"
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

const char WORDFILENAME[] = "/Users/sophiasharif/Desktop/projects/CS 31/project-5/words.txt";

const int MAXWORDS = 9000;
const int NWORDS = 7000;
const int MAXPROBELEN = 100;

int playOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum);
bool containsWord (const char wordArray[][MAXWORDLEN+1], const int nWords, const char word[MAXWORDLEN+1]);
bool isLowercaseWord (const char word[MAXWORDLEN + 1]);


int main()
{
    cout.setf(ios::fixed);
    cout.precision(2);
    
    char w[MAXWORDS][MAXWORDLEN+1];
    int n = getWords(w, NWORDS, WORDFILENAME);
    
    // confirm words were loaded
    if (n < 1) {
        cout << "No words were loaded, so I can't play the game." << endl;
        return -1;
    }
    
    // get number of rounds
    int totalRounds;
    cout << "How many rounds do you want to play? ";
    cin >> totalRounds;
    cin.ignore(10000, '\n');
    
    if (totalRounds < 1) {
        cout << "The number of rounds must be positive." << endl;
        return -1;
    }
    
    // game info
    int totalScore, minScore, maxScore;
    
    for (int currentRound=1; currentRound<=totalRounds; currentRound++) {
        
        // game set up
        cout << endl << "Round " << currentRound << endl;
        int wordnum = randInt(0, n-1);
        cout << "The hidden word is " << strlen(w[wordnum]) << " letters long." << endl;
        
        // play one round
        int numGuesses = playOneRound(w, n, wordnum);
        
        // score output
        if (numGuesses == 1)
            cout << "You got it in 1 try." << endl;
        else
            cout << "You got it in " << numGuesses << " tries." << endl;
        
        // calculate stats
        if (currentRound == 1) {
            totalScore = numGuesses;
            minScore = numGuesses;
            maxScore = numGuesses;
        } else {
            minScore = min(numGuesses, minScore);
            maxScore = max(numGuesses, maxScore);
            totalScore += numGuesses;
        }
        
        // stat output
        cout << "Average: " << static_cast<double>(totalScore)/currentRound << ", minimum: " << minScore << ", maximum: " << maxScore << endl;
    }
    return 0;
}

int playOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum){
    
    if (nWords <= 0 || wordnum < 0 || wordnum >= nWords)
        return -1;
    
    // get hidden word
    char hiddenWord[MAXWORDLEN+1];
    strcpy(hiddenWord, words[wordnum]);
    int numGuesses = 0;
    
    for (;;) {
        
        char probeWord[MAXPROBELEN];
        // ask for another probe word
        cout << "Probe word: ";
        cin.getline(probeWord, MAXPROBELEN);
        
        // check if guess is correct
        if (strcmp(probeWord, hiddenWord) == 0)
            return numGuesses + 1;
        
        // check if probeWord is valid
        if (strlen(probeWord) < MINWORDLEN || strlen(probeWord) > MAXWORDLEN || !isLowercaseWord(probeWord)) {
            cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
            continue;
        } else if (!containsWord(words, nWords, probeWord)) {
            cout << "I don't know that word." << endl;
            continue;
        }
        
        // calculate golds & silvers
        int golds = 0;
        int silvers = 0;
        char hiddenWordCopy[MAXWORDLEN+1]; // create copy of hidden word so we can edit it
        strcpy(hiddenWordCopy, hiddenWord);
        
        // loop through and count golds.
        for (int i=0; i < strlen(probeWord); i++) {
            // if exact match, count as gold
            if (probeWord[i] == hiddenWordCopy[i]) {
                golds += 1;
                hiddenWordCopy[i] = '-'; // change chars to prevent double counting
                probeWord[i] = '*';
            }
        }
        
        // loop through and count silvers
        for (int i=0; i < strlen(probeWord); i++) {
            char* firstInstance = strchr(hiddenWordCopy, probeWord[i]);
            if (firstInstance != nullptr) {
                silvers += 1;
                *firstInstance = '-'; // change chars to prevent double counting
                probeWord[i] = '*';
            }
        }
        
        numGuesses++;
        cout << "Golds: " << golds << ", Silvers: " << silvers << endl;
    }
    
    return numGuesses;
}

bool containsWord (const char wordArray[][MAXWORDLEN+1], const int nWords, const char word[MAXWORDLEN+1]) {
    for (int i = 0; i < nWords; i++) {
        if (strcmp(wordArray[i], word) == 0) {
            return true;
        }
    }
    return false;
}

bool isLowercaseWord (const char word[MAXWORDLEN + 1]) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (!islower(word[i])) {
            return false;
        }
    }
    return true;
}

