import java.lang.Math;


class Solution {
    public int maxProfit(int[] prices) {
        int ans = Integer.MIN_VALUE;
        int min = Integer.MAX_VALUE;
        for (int x: prices) {
            min = Math.min(x, min);
            ans = Math.max(ans, x - min);
        }
        return ans;
    }
}
