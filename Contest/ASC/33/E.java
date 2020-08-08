import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

public class E {
  static Scanner in = new Scanner(System.in);

  public static BigInteger fpow(BigInteger a, BigInteger n) {
    BigInteger res = BigInteger.ONE;
    while (n.compareTo(BigInteger.ZERO) == 1) {
      if (n.mod(BigInteger.valueOf(2)).compareTo(BigInteger.ONE) == 1) {
        res = res.multiply(a);
      }
      a = a.multiply(a);
      n = n.divide(BigInteger.valueOf(2));
    }
    return res;
  }

  public static void main(String[] args) throws Exception {
    int n = in.nextInt();

    BigInteger[][] dp = new BigInteger[n + 1][];
    for (int i = 0; i <= n; ++i) {
      dp[i] = new BigInteger[n + 1];
      for (int j = 0; j <= n; ++j) 
        dp[i][j] = BigInteger.ZERO;
    }

    BigInteger[][][] dp2 = new BigInteger[n + 1][][];
    for (int i = 0; i <= n; ++i) {
      dp2[i] = new BigInteger[n + 1][];
      for (int j = 0; j <= n; ++j) {
        dp2[i][j] = new BigInteger[n + 1];
        for (int k = 0; k <= n; ++k) 
          dp2[i][j][k] = BigInteger.ZERO;
      }
    }

    for (int i = 0; i <= n; ++i) 
      dp2[i][0][0] = BigInteger.ONE;

    BigInteger[][] tabs = new BigInteger[n + 1][];
    for (int i = 0; i <= n; ++i) {
      tabs[i] = new BigInteger[n + 1];
      for (int j = 0; j <= n; ++j) 
        tabs[i][j] = BigInteger.ZERO;
    }

    BigInteger[][] ways = new BigInteger[n + 1][];
    for (int i = 0; i <= n; ++i) 
      ways[i] = new BigInteger[n + 1];

    BigInteger[] frac = new BigInteger[n + 1];


  }
}
