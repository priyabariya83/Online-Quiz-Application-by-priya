#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

struct Question {
    string text;
    string a, b, c, d;
    char correct;
};

bool login(string &username) {
    string user, pass, inputUser, inputPass;
    cout << "Enter username: ";
    cin >> inputUser;
    cout << "Enter password: ";
    cin >> inputPass;

    ifstream infile("users.txt");
    while (infile >> user >> pass) {
        if (inputUser == user && inputPass == pass) {
            username = user;
            return true;
        }
    }
    return false;
}

void registerUser() {
    string user, pass;
    cout << "Choose username: ";
    cin >> user;
    cout << "Choose password: ";
    cin >> pass;

    ofstream outfile("users.txt", ios::app);
    outfile << user << " " << pass << endl;
    cout << "✅ Registration successful!\n";
}

int loadQuestions(Question qList[], int maxQ) {
    ifstream file("questions.txt");
    int count = 0;
    while (count < maxQ && getline(file, qList[count].text)) {
        getline(file, qList[count].a);
        getline(file, qList[count].b);
        getline(file, qList[count].c);
        getline(file, qList[count].d);
        file >> qList[count].correct;
        file.ignore(); // skip newline
        count++;
    }
    return count;
}

void startQuiz(string username) {
    const int MAX_QUESTIONS = 50;
    Question questions[MAX_QUESTIONS];
    int total = loadQuestions(questions, MAX_QUESTIONS);
    int score = 0;
    char answer;

    cout << "\n=== Quiz Started ===\n";
    for (int i = 0; i < total; i++) {
        cout << "\nQ" << i + 1 << ": " << questions[i].text << endl;
        cout << questions[i].a << endl;
        cout << questions[i].b << endl;
        cout << questions[i].c << endl;
        cout << questions[i].d << endl;
        cout << "Your answer (A/B/C/D): ";
        cin >> answer;
        answer = toupper(answer);
        if (answer == questions[i].correct) {
            cout << "✅ Correct!\n";
            score++;
        } else {
            cout << "❌ Wrong! Correct: " << questions[i].correct << "\n";
        }
    }

    cout << "\n🎯 Score: " << score << "/" << total << endl;

    // Save result
    ofstream resultFile("results.txt", ios::app);
    resultFile << username << " scored " << score << " out of " << total << endl;
}

int main() {
    int choice;
    string username;

    do {
        cout << "\n=== Online Quiz System ===\n";
        cout << "1. Register\n";
        cout << "2. Login and Start Quiz\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (login(username)) {
                    cout << "✅ Login successful! Welcome, " << username << "!\n";
                    startQuiz(username);
                } else {
                    cout << "❌ Login failed.\n";
                }
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "❌ Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
