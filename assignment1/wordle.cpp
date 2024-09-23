#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>  
#include <algorithm>

using namespace std;



int main(int argc, char* argv[])
{

    string green = "\033[92m";
	string yellow = "\033[93m";
	string off = "\033[0m"; 

    string chosen_word;
    string guess;
    std::vector<string> word_list(12947);
    std::vector<string> board(6); 

    std::ifstream file("wordlist.txt");
    std::string line;
    std::vector<string> color(6);
    bool game_status = true;


    for (int h = 0;  h < 12947 ; h++) 
    {
        getline(file, line);
        stringstream ss(line);
        ss >> word_list[h];
    }

    while(game_status == true)
    {
        cout << "Welcome to Wordle!" << endl;

        srand(time(0)); 
        int random_num = rand() % 12947;
        chosen_word = word_list[random_num];

        cout << chosen_word << endl;

        for (int e = 0; e < 6; e++)
        {
            board[e] = "*****";
            cout << board[e] << endl;
        }
    
        for (int i = 0; i < 6; i++ )
        {
            cout << "Enter your guess: " << endl;
            cin >> guess; 
 
            if (guess == "new") 
            {   
                cout << "" << endl;
                break;
            }

            if (guess == "quit") 
            {
                return 0;
            }

            if (guess.size() != 5) 
            {
                cout << "Unable to parse input, please try again." << endl;
                cout << " " << endl;
                i -= 1;
                continue;
            }  

            auto word_search = std::find(word_list.begin(), word_list.end(), guess);
            
            if (word_search == word_list.end()) 
            {
                game_status = false; 
                cout << "Invalid word, please try again" << endl;
                cout << " " << endl;
                i -= 1;
                continue;
            }
     
            if (guess == chosen_word) 
            {
                board[i] = green + chosen_word; 
                for (int b = 0; b < i + 1; b++)
                {
                    cout << board[b] << endl;
                } 
                game_status = false;
                return 0;          
            }
            
            else 
            {    
                for (int m = 0; m < 5; m++)
                {   
                    for (int s = 0; s < 5; s++)
                    {
                        if (guess[m] == chosen_word[m])
                        {
                            color[m] = green;
                            break;
                        }

                        else if (guess[m] == chosen_word[s])
                        {
                            color[m] = yellow;
                            break;
                        }

                        else 
                        {
                            color[m] = off;
                        }
                    }
                    
                    board[i] = color[0] + guess[0] +
                    color[1] + guess[1] + 
                    color[2] + guess[2] + 
                    color[3] + guess[3] + 
                    color[4] + guess[4] + off;
                    
                } 
                for (int b = 0; b < 6; b++)
                {
                    cout << board[b] << endl;
                } 
                game_status = false;
            }  
        }
        game_status = false; 
        if (guess == "new") {
            game_status = true;
        }          
    }
    return 0;
}
       
         