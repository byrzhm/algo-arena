import java.lang.Math;


class Solution {
    public int jump(int[] nums) {
        int n = nums.length;
        int ans = 0;
        int currRight = 0;
        int nextRight = 0;
        for (int i = 0; i < n - 1; i++) { // 在最后不需要再跳了
            nextRight = Math.max(nextRight, i + nums[i]);
            if (i == currRight) {
                currRight = nextRight;
                ans++;
            }
        }
        return ans;
    }
}