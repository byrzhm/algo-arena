#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());

        int len = nums.size();
        if (len < 3)
            return ans;

        int maxsum = nums[len - 1] + nums[len - 2] + nums[len - 3];
        int minsum = nums[0] + nums[1] + nums[2];

        if (minsum > 0 || maxsum < 0)
            return ans;

        int first, second, third;
        for (first = 0; first < len - 2; first++) {
            if (nums[first] > 0)
                break;
            if (first > 0 && nums[first] == nums[first - 1]) 
                continue;

            int target = -nums[first];
            second = first + 1;
            third = len - 1;
            while (second < third) {
                int sum = nums[second] + nums[third];
                if (sum > target) third--;
                if (sum < target) second++;
                if (sum == target) {
                    ans.push_back({nums[first], nums[second], nums[third]});
                    while (second < third && nums[second] == nums[second + 1]) second++;
                    while (second < third && nums[third] == nums[third - 1]) third--;
                    second++; third--;
                }
            }
        }
        
        return ans;
    }
};