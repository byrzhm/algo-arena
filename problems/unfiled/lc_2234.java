import java.util.Arrays;
import java.util.function.Function;
import java.lang.Math;

class Solution {
    public long maximumBeauty(int[] flowers, long newFlowers, int target, int full, int partial) {
        int n = flowers.length;
        Arrays.sort(flowers);
        int idx = lowerBound(flowers, target);
        if (idx == 0) {
            return (long) n * full;
        }
        long leftFlowers = newFlowers - (long) idx * target;
        for (int i = 0; i < idx; i++) {
            leftFlowers += flowers[i];
        }
        if (leftFlowers >= 0) {
            return Math.max((long) n * full, (long) (n - 1) * full + (long) (target - 1) * partial);
        }

        long ans = 0;
        long preSum = 0;
        for (int i = 1, j = 0; i <= idx; i++) {
            leftFlowers += target - flowers[i - 1];
            if (leftFlowers < 0) {
                continue;
            }

            // Invariant: flowers[j - 1] * (j - 1) <= preSum + leftFlowers
            while (j < i && (long) flowers[j] * j <= preSum + leftFlowers) {
                preSum += flowers[j];
                j++;
            }

            long avg = (preSum + leftFlowers) / j;
            long totalBeauty = avg * partial + (long) (n - i) * full;
            ans = Math.max(ans, totalBeauty);
        }

        return ans;
    }

    private int binarySearch(int n, Function<Integer, Boolean> f) {
        // Define: f(-1) == false and f(n) == true
        // Invariant: f(i-1) == false, f(j) == true
        int i = 0;
        int j = n;
        while (i < j) {
            int h = ((j - i) >> 1) + i;
            // l <= h < j
            if (!f.apply(h)) {
                i = h + 1; // preserve f(i - 1) == false
            } else {
                j = h; // preserve f(j) == true
            }

        }
        // i == j, f(i - 1) == false, and f(j) (= f(i)) == true => answer is i.
        return i;
    }

    private int lowerBound(int[] arr, int target) {
        return binarySearch(arr.length, i -> arr[i] >= target);
    }

    public static void main(String[] args) {
        int[] flowers = { 1, 3, 1, 1 };
        int newFlowers = 7;
        int target = 6;
        int full = 12;
        int partial = 1;

        System.out.println((new Solution()).maximumBeauty(flowers, newFlowers, target, full, partial));
    }
}