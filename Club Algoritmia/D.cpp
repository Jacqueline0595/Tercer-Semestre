#include <bits/stdc++.h>
using namespace std;

vector<int> get_prefix_count(string &s, char c){
    vector<int> prefix_count(n+1);

    for(int i = 1; i<= n; i++){
        prefix_count[i] = prefix_count[i+1] + (s[i-1] == c);
    }
    return prefix_count;
}

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

    vector<int> prefix_count_t = get_prefix_count(adn, 'T');
    vector<int> prefix_count_a = get_prefix_count(adn, 'A');
    vector<int> prefix_count_g = get_prefix_count(adn, 'G');
    vector<int> prefix_count_c = get_prefix_count(adn, 'C');

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

        freq['A'] = prefix_count_a[end] - prefix_count_a[start-1];
        freq['T'] = prefix_count_t[end] - prefix_count_t[start-1];
        freq['G'] = prefix_count_g[end] - prefix_count_g[start-1];
        freq['C'] = prefix_count_c[end] - prefix_count_c[start-1];

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