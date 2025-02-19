#include <bits/stdc++.h>
using namespace std;

int main()
{
    string adn;
    cin >> adn; 
    int m;
    cin >> m;

    map<char, int> score = {
        {'A', 4},
        {'T', 3},
        {'G', 2},
        {'C', 1},
        {'#', 0}
    };

    for(int i = 0; i<m; i++)
    {
        int start, end;
        cin >> start >> end;
        //TODO: resolver el problema 

        map<char, int> freq = {
            {'A', 0},
            {'T', 0},
            {'G', 0},
            {'C', 0}
        };

        for(int c=start-1; c<end; c++)
        {
            char letter = adn[c];
            freq[letter] = freq[letter] + 1;
        }

        for(auto &[letter, count] : freq)
        {
            cout << letter << ' ' << count << '\n';
        }

        string answer = "";

        for(int t=0; t<4; t++)
        {
            int max_count = 0;
            char max_count_letter = '#';

            for(auto &[letter, count] : freq)
            {
                if(count > max_count){
                    max_count = count;
                    max_count_letter = letter;
                } else if(count == max_count)
                {
                    if(score[letter] > score[max_count_letter])
                    {
                        max_count_letter = letter;
                    }
                }
            }
            answer += max_count_letter;

        }

        cout << answer << '\n';
    }
    return 0;
}