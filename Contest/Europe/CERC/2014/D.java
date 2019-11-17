import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

public class D {
    static Scanner in = new Scanner(System.in);
    static int n;
    static int[][] g;
    static boolean[] v;
    static BigInteger[][] ans;

    private static boolean connect(int i, int j) {
        long dx = g[i][0] - g[j][0];
        long dy = g[i][1] - g[j][1];
        long r = g[i][2] + g[j][2];
        return dx * dx + dy * dy == r * r;
    }

    private static void dfs(int now, BigInteger nu, BigInteger nd) {
        ans[now][0] = nu; ans[now][1] = nd;
        v[now] = true;

        for (int i = 0; i < n; ++i) if (!v[i] && connect(now, i)) 
            dfs(i, nu.multiply(BigInteger.valueOf(-1)).multiply(BigInteger.valueOf(g[now][2])), nd.multiply(BigInteger.valueOf(g[i][2])));
    }
    
    private static void solve() {
        n = in.nextInt();
        g = new int[n][3];
        ans = new BigInteger[n][2];
        v = new boolean[n];

        for (int i = 0; i < n; ++i) {
            g[i][0] = in.nextInt();
            g[i][1] = in.nextInt();
            g[i][2] = in.nextInt();
            ans[i][0] = ans[i][1] = BigInteger.ZERO;
            v[i] = false;
        }

        dfs(0, BigInteger.ONE, BigInteger.ONE);

        for (int i = 0; i < n; ++i) {
            if (ans[i][0] == BigInteger.ZERO) {
                System.out.println("not moving");
                continue;
            }

            BigInteger z = ans[i][0].gcd(ans[i][1]);
            ans[i][0] = ans[i][0].divide(z);
            ans[i][1] = ans[i][1].divide(z);
            
            if (ans[i][1].compareTo(BigInteger.ONE) == 1) 
                System.out.print(ans[i][0].abs() + "/" + ans[i][1].abs() + " ");
            else 
                System.out.print(ans[i][0].abs() + " ");

            System.out.println(ans[i][0].multiply(ans[i][1]).compareTo(BigInteger.ZERO) == 1 ? "clockwise" : "counterclockwise");
        }
    }
    public static void main(String[] args) {
        int t = in.nextInt();
        while (t > 0) {
            solve();
            --t;
        }
    }
}

