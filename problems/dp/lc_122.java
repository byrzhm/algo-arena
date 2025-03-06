import java.lang.Math;

class Solution {
    /**
     * Dynamic Programming
     */
    /*
     * public int maxProfit(int[] prices) {
     * int n = prices.length;
     * int [][] f = new int[n + 1][2];
     * f[0][0] = 0;
     * f[0][1] = Integer.MIN_VALUE;
     * // f[i][0] 第 i 天未持有股票的最大利润
     * // f[i][1] 第 i 天持有股票的最大利润
     * for (int i = 1; i <= n; i++) {
     * f[i][0] = Math.max(f[i - 1][0], f[i - 1][1] + prices[i - 1]);
     * f[i][1] = Math.max(f[i - 1][1], f[i - 1][0] - prices[i - 1]);
     * }
     * return f[n][0];
     * }
     */
    public int maxProfit(int[] prices) {
        int ans = 0;
        int n = prices.length;
        for (int i = 1; i < n; ++i) {
            ans += Math.max(0, prices[i] - prices[i - 1]);
        }
        return ans;
    }
}