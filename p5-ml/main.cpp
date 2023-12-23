#include <iostream>
#include <map>
#include <set>
#include <cmath>
#include <fstream>
#include "csvstream.hpp"

using namespace std; 

class Classifier {
    private:
        bool debug;
        // The total number of posts in the entire training set
        int totalNumPosts = 0;
        // The number of unique words in the entire training set. (The vocabulary size.)
        set<string> uniqueWords;
        // For each label C, the number of posts with that label.
        // also contains all possible tags
        map<string, int> labelCount;
        // For each word W, the number of posts in the entire training set that contain W
        map<string, int> wordCount;
        // For each label C and word W, the number of posts with label C that contain W.
        // <label, word>, # of occurences
        map<pair<string, string>, int> wordPostCombo;
        
        double logPrior(string label) {
            // cout << "label count: " << labelCount[label] << endl << "totalNumPosts: " << totalNumPosts << endl;
            // cout << "prereturn answer: " << log(labelCount[label]/(totalNumPosts * 1.0)) << endl;
            return log(labelCount[label]/(totalNumPosts * 1.0));
        }

        // EFFECTS: Return a set of unique whitespace delimited words.x
        set<string> unique_words(const string &str) {
            istringstream source(str);
            set<string> words;
            string word;
            while (source >> word) {
                words.insert(word);
            }
            return words;
        }

        double logLikelihood(pair<string, string> combo) {
            // regular formula: there exists a training post with Label C that contains W
            if (wordPostCombo.find(combo) != wordPostCombo.end()) {
                return log(wordPostCombo[combo]/(labelCount[combo.first] * 1.0));
            }

            // W does not occur in Label C but does occur somewhere in the training set
            else if (wordCount.find(combo.second) != wordCount.end()) {
                return log(wordCount[combo.second] / (totalNumPosts * 1.0));
            }

            // W does not occur anywhere
            else {
                return log(1.0/ (totalNumPosts * 1.0));
            }
        }

        void logProbability(string& predictedLabel, double& predictedScore, set<string> uniqueContent) {
            map<string, double> scoreBook;
            for (const auto& label : labelCount) {
                double result = logPrior(label.first);
                for (string word : uniqueContent) {
                    result += logLikelihood(make_pair(label.first, word));
                }
                scoreBook[label.first] = result;
            }
            bool defaultVal = 1;

            for (const auto &score : scoreBook) {
                if (defaultVal) {
                    predictedLabel = score.first;
                    predictedScore = score.second;
                    defaultVal = 0;
                }
                else {
                    if (score.second > predictedScore) {
                        predictedScore = score.second;
                        predictedLabel = score.first;
                    }
                }
            }
        }

    public:
        Classifier(bool debug_in): debug(debug_in){}

        int trainData(string& fileName) {
            try {
                csvstream csvin(fileName);
                map<string, string> row;
                if (debug) {
                    cout << "training data:" << endl;
                }
                while (csvin >> row) {
                    // The total number of posts in the entire training set.
                    totalNumPosts++;

                    // For each label, the number of posts with that label.
                    string label = row["tag"];
                    labelCount[label]++;

                    // The number of unique words in the entire training set. (The vocabulary size.)
                    set<string> words = unique_words(row["content"]);
                    uniqueWords.insert(words.begin(), words.end());
                    for (const auto& word : words) {
                        // For each word W, the number of posts in the entire training set that contain W
                        wordCount[word]++;

                        // For each label and word W, the number of posts with label that contain W.
                        wordPostCombo[make_pair(label, word)]++;
                    }
                    if (debug == true) {
                        cout << "  label = " << row["tag"] << ", content = " << row["content"] << "\n";
                    }
                }
                if(debug == true){
                  cout << "trained on " << totalNumPosts << " examples\n";
                } else {
                  cout << "trained on " << totalNumPosts << " examples\n\n";
                }
                if (debug == true) {
                    cout << "vocabulary size = " << uniqueWords.size() << "\n\n" << "classes:\n";
                    for (const auto& labelPair : labelCount) {
                        cout << "  " << labelPair.first << ", " << labelPair.second 
                        << " examples, log-prior = " << logPrior(labelPair.first) << "\n";
                    }
                    cout << "classifier parameters:\n";
                    for (const auto& combo : wordPostCombo) {
                        cout << "  " << combo.first.first << ":" << combo.first.second 
                        << ", count = " << wordPostCombo[combo.first] << ", log-likelihood = " 
                        << logLikelihood(combo.first) << "\n"; 
                    }
                    cout << endl;
                }
            }
            catch(const csvstream_exception &e) {
                return -1;
            }
            return 0;
        }

        int predictData(string& fileName) {
            try {
                csvstream csvin(fileName);
                cout << "test data:\n";
                map<string, string> row; 

                int totalPosts = 0;
                int totalCorrect = 0;
                
                while (csvin >> row) {
                    totalPosts++;
                    string predictedLabel;
                    double predictedScore;

                    logProbability(predictedLabel, predictedScore, unique_words(row["content"]));

                    cout << "  correct = " << row["tag"] << ", predicted = " 
                    << predictedLabel << ", log-probability score = " << predictedScore 
                    << endl << "  content = " << row["content"] << endl << endl;

                    if (predictedLabel == row["tag"]) {
                        totalCorrect++;
                    }
                }
                cout << "performance: " << totalCorrect << " / " << totalPosts 
                << " posts predicted correctly" << endl;
            }
            catch(const csvstream_exception &e) {
                return -1;
            }
            return 0;
        }
};

int main(int argc, char* argv[]) {
    cout.precision(3);
    if (argc != 3 && argc != 4) {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return -1;
    }
    if (argc == 4 && string(argv[3]) != "--debug") {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return -1;
    }
    bool toDebugOrNotToDebug = (argc == 4); //for the shakespearan in you

    Classifier royalBee(toDebugOrNotToDebug);
     
    string trainFile = string(argv[1]);
    string testFile = string(argv[2]);
   
    int trainFileOpen = royalBee.trainData(trainFile);
    if (trainFileOpen == -1) {
        cout << "Error opening file: " << trainFile << endl;
        return -1;
    }
    int testFileOpen = royalBee.predictData(testFile);
    if (testFileOpen == -1) {
        cout << "Error opening file: " << testFile << endl;
        return -1;
    }
    return 0;
}