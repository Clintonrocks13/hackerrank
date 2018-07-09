#include <bits/stdc++.h>
#include <cmath>
using namespace std;

vector<string> split_string(string);

// Complete the queensAttack function below.
int queensAttack(int n, int k, int r_q, int c_q, vector<vector<int>> obstacles) {
    // cout<<"size : "<<obstacles.size()<<endl;
    long long int total_attack = 0;
    total_attack = (n-1)*2; // rows and columns 
    //diags /
    total_attack+= ((n-c_q) >= (r_q-1))? (r_q-1): (n-c_q);
    total_attack+= ((c_q-1)>= (r_q-1))? (r_q-1): (c_q-1);
                    
    total_attack+= ((n-c_q) >= (n-r_q))? (n-r_q): (n-c_q);
    total_attack+= ((c_q-1)>= (n-r_q))? (n-r_q): (c_q-1);
    cout<<"total attacks : "<<total_attack<<endl;
    //clean data 
    int top,bottom,left,right,d_ltop,d_rtop,d_lbot,d_rbot;
    top = bottom = left = right = d_ltop = d_rtop = d_lbot = d_rbot = 0;
    vector<vector<int> > points(8);
    for(vector< vector<int> >::iterator dta = obstacles.begin(); dta != obstacles.end(); dta+=1){
        vector<int> pair_ = *dta;
        if(pair_[0] == r_q || pair_[1] == c_q || abs( pair_[0] - r_q) == abs(pair_[1] - c_q)){
            int position;
        
            if(pair_[0] < r_q && pair_[1] == c_q ){ // top
                position = 0;
                
            }else if(pair_[0] > r_q && pair_[1] == c_q){ // bottom
                position = 1;
                
            }else if(pair_[1] < c_q && pair_[0] == r_q){ // left
                position = 2;
                
            }else if(pair_[1] > c_q && pair_[0] == r_q){ // right
                position = 3;
            }else if(pair_[1] < c_q && pair_[0] < r_q ){ // diagonal top left
                position = 4;
            }else if(pair_[1] > c_q && pair_[0] < r_q ){ // diagonal top right 
                position = 5;
            }else if(pair_[1] < c_q && pair_[0] > r_q ){ // diagonal top left
                position = 6;
            }else if(pair_[1] > c_q && pair_[0] > r_q ){ // diagonal top right 
                position = 7;
            }
            if(points[position].size() == 0){
                    points[position].resize(2);
                    points[position][0] = pair_[0];
                    points[position][1] = pair_[1];
                    continue;
                }
                int distance = abs(pair_[0] - r_q ) + abs(pair_[1] - c_q );
                if(distance <  (abs(points[position][0] - r_q ) + 
                                abs(points[position][1] - c_q ) ) ){
                    points[position][0] = pair_[0];
                    points[position][1] = pair_[1];
                }
        }
    }
    obstacles.erase(obstacles.begin(),obstacles.end());
    for(vector< vector<int> >::iterator dta = points.begin(); dta != points.end(); dta+=1){
        vector<int> pair_ = *dta;
        if(pair_.size() !=0){
            obstacles.push_back(pair_);
            cout<<" closest "<<pair_[0]<<" "<<pair_[1]<<endl;
        }
    }
    for(vector< vector<int> >::iterator dta = obstacles.begin(); dta != obstacles.end(); dta+=1){
        vector<int> pair_ = *dta;
        bool related = false;
        if(pair_[0] == r_q ){
            related = true; 
            
            if(pair_[1] < c_q){
                total_attack = abs(total_attack -  pair_[1]);
            }else if(pair_[1] > c_q){
                cout<<""<<" - "<<(n - (n - pair_[1] +1))<<endl;
                total_attack = abs(total_attack - ((n - pair_[1] +1)) ); 
            }
        }
        if(pair_[1] == c_q){
            //cout<<"Sub : "<<pair_[0] <<" - "<< r_q<<endl;
            related = true;
            if(pair_[0] < r_q){
                total_attack = abs(total_attack -  pair_[0] );
            }else if(pair_[0] > r_q){
                total_attack = abs(total_attack -  (n - pair_[0] + 1) ); 
            }
        }
        if(abs( pair_[0] - r_q) == abs(pair_[1] - c_q)){
            //cout<<"Sub : "<<pair_[0] <<'-'<< r_q <<endl;
            related = true;
            
                if(pair_[0] < r_q){
                    if(pair_[1] > c_q){
                        long long int topcol_nos = (r_q-1 <= n-c_q )? (r_q-1):  n-c_q;
                        total_attack = abs(total_attack -  ((pair_[0]-(r_q - topcol_nos))+1) );
                    }else if(pair_[1] < c_q){
                        long long int topcol_nos = (r_q-1 <= c_q-1 )? (r_q-1):  c_q -1 ;
                        total_attack= abs(total_attack -  ((pair_[0]-(r_q - topcol_nos))+1) );
                    }
                }else if(pair_[0] > r_q){
                    if(pair_[1] > c_q){
                        cout<<n-r_q<< " <= " << n-c_q << endl;
                        long long int botcol_nos = (n-r_q <=  n-c_q )? (n-r_q):  n-c_q;
                        cout<<" cols bottom : "<<botcol_nos<<endl;
                        cout<<total_attack<<" - "<< '(' << botcol_nos <<" - "<< ((pair_[0]-r_q)-1)<<endl;
                        total_attack = abs(total_attack - ( botcol_nos - ((pair_[0]-r_q)-1)) );
                    }else if(pair_[1] < c_q){
                        long long int botcol_nos = (n-r_q <= c_q-1 )? (n-r_q):  c_q -1 ;
                        total_attack = abs(total_attack - ( botcol_nos - ((pair_[0]-r_q)-1)) );
                    }
                }
        }
        cout<<pair_[0]<< " fodo "<<pair_[1]<<" related : "<<related<<" "<<total_attack<<endl;
    }
    return total_attack;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string r_qC_q_temp;
    getline(cin, r_qC_q_temp);

    vector<string> r_qC_q = split_string(r_qC_q_temp);

    int r_q = stoi(r_qC_q[0]);

    int c_q = stoi(r_qC_q[1]);

    vector< vector<int> > obstacles(k);
    for (int i = 0; i < k; i++) {
        obstacles[i].resize(2);

        for (int j = 0; j < 2; j++) {
            cin >> obstacles[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // cout<<"size : "<<obstacles.size()<<endl;
    int result = queensAttack(n, k, r_q, c_q, obstacles);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}