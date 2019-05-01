// Leetcode 005 Longest Palindromic Substring
// 最大回文子串：利用扩展

class Solution {
public:
    string longestPalindrome(string s) {
        if(s.size()<2) return s;
        int max_len = 0, head;
        for(int i=0; i<2*s.size()-1; i++){
            int mid = i/2;
            if(i%2){ //mid = mid
                int j = 1;
                while(mid+j<s.size() && mid-j>=0){
                    if(s[mid+j] != s[mid-j]) break;
                    else j++;
                }
                if(2*j-1 > max_len){
                    head = mid-j+1;
                    max_len = 2*j-1;
                }  
            }
            else{ // mid = mid_left
                int j = 0;
                while(mid+1+j<s.size() && mid-j>=0){
                    if(s[mid+1+j] != s[mid-j]) break;
                    else j++;
                }
                if(2*j > max_len){
                    head = mid-j+1;
                    max_len = 2*j;
                } 
            }
        }
        return s.substr(head, max_len);
    }
};
