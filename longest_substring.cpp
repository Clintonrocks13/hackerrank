//https://leetcode.com/problems/longest-substring-without-repeating-characters/submissions/

#include <vector>
#include<algorithm>
#include<map>
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.length() == 1){
            return 1;
        }
        //s = "abccabcdbb";
        int ans = 0;
        map<int,int> arr_last_index;
        vector<int> last_index(1,0);
        for(int i=1;i<=s.length();i++){
            //character ascii value to store index in hash map 
            int index_ = s.at(i-1);
            
            if(arr_last_index.find(index_) == arr_last_index.end()){
                //first-time ocurrance of the character in the string 
                arr_last_index[index_] = i; // store the current index of the string 
                
            }
            //load previous index in last_index 
            last_index.push_back(arr_last_index[index_]);
            //set current visited index as new last knows location for that character 
            arr_last_index[index_] = i;
        }
        //lets print tocheck the last index of character 
        for(int ind : last_index){
            cout<<ind<<" ";
        }
        
        
        //process data and find the max count 
        int last_valid_start_index = 1,
            max_count = 0;
        int current_sub_string_length = 0;
        cout<<endl;
        for(int i = last_valid_start_index;i<last_index.size();i++ ){
            cout<<s.at(i-1)<<" ";
            if(last_index[i] == i // if it's the first occurrance 
              || last_index[i] < last_valid_start_index){
                current_sub_string_length++;
                
            }else{
                //before stripping process, record max unique substring length till now
                cout<<" recording new max : "<<current_sub_string_length<<endl;
                max_count = max(max_count,current_sub_string_length);
               //substring is braking because of releating character 
                //subtract score from current substring score 
                //because you are stripping out a part of string 
                                           //new valid start index - old valid start index  
                current_sub_string_length-=(last_index[i]+1 - last_valid_start_index);
                
                last_valid_start_index =  last_index[i]+1; // start from the repeated character
                //add 1 to current_sub_string_length because you have added new character 
                current_sub_string_length++;
            }
            
        }
        max_count = max(max_count,current_sub_string_length);
        ans = max_count;
        return ans;
    }
};
