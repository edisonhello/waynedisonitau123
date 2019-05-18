import java.io.*;
import java.util.*;
import java.math.*;
import java.lang.*;

public class C3{
    static Scanner in = new Scanner(System.in);
    static BigInteger[] dp1;
    static BigInteger[] dp2;
    static BigInteger[][] dp;
    public static BigInteger cnk(BigInteger n, int k) {
        BigInteger res = BigInteger.valueOf(1);
        for (int i = 0; i < k; ++i) res = res.multiply(n.subtract(BigInteger.valueOf(i)));
        for (int i = 0; i < k; ++i) res = res.divide(BigInteger.valueOf(k - i));
        return res;
    }
    public static BigInteger calc(BigInteger n, int k) {
        return cnk(n.add(BigInteger.valueOf(k - 1)), k);
    }
    public static void precalc() {
        dp1 = new BigInteger[61];
        dp2 = new BigInteger[61];
        dp = new BigInteger[61][61];
        dp1[0] = BigInteger.valueOf(1);
        dp2[0] = BigInteger.valueOf(1);
        dp1[1] = BigInteger.valueOf(1);
        for (int i = 1; i <= 60; ++i) {
            for (int j = 0; j <= 60; ++j) for (int k = 0; k <= 60; ++k) dp[j][k] = BigInteger.valueOf(0);
            dp[0][0] = BigInteger.valueOf(1);
            for (int j = 0; j <= i; ++j) {
                for (int k = 1; k <= i; ++k) {
                    for (int p = 0; p * k <= j; ++p) {
                        dp[j][k] = dp[j][k].add(dp[j - p * k][k - 1].multiply(calc(dp1[k], p)));
                    }
                }
            }
            dp2[i] = dp[i][i];
            if (i + 1 <= 60) {
                for (int j = 0; j <= 60; ++j) for (int k = 0; k <= 60; ++k) dp[j][k] = BigInteger.valueOf(0);
                dp[0][0] = BigInteger.valueOf(1);
                for (int j = 0; j <= i; ++j) {
                    for (int k = 1; k <= i; ++k) {
                        for (int p = 0; p * k <= j; ++p) {
                            dp[j][k] = dp[j][k].add(dp[j - p * k][k - 1].multiply(calc(dp2[k], p)));
                        }
                    }
                }
                dp1[i + 1] = dp[i][i];
            }
        }
    }
    public static void main(String[] args) {
        precalc();
        while (true) {
            int n = in.nextInt();
            if (n == 0) break;
            System.out.println(dp2[n]);
        }
    }
}
