import java.util.HashMap;
import java.util.Map;

class Solution {
    public long beautifulSubarrays(int[] nums) {
        Map<Integer, Integer> cnt = new HashMap<>();
        long ans = 0;
        int mask = 0;
        cnt.put(0, 1);
        for (int x : nums) {
            mask ^= x;
            ans += cnt.getOrDefault(mask, 0);
            cnt.put(mask, cnt.getOrDefault(mask, 0) + 1);
        }
        return ans;
    }

    public static void main(String[] args) {
        int[] nums = { 4, 3, 1, 2, 4 };
        Solution sol = new Solution();

        System.out.println(sol.beautifulSubarrays(nums));
    }
}