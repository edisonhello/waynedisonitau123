import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

public class E {
    static Scanner in = new Scanner(System.in);
    public static void main(String[] args) {
        int t = in.nextInt();
        int[] p = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547};
        while (t-- > 0) {
            BigInteger x = in.nextBigInteger();
            BigInteger now = new BigInteger("1");
            BigInteger u = new BigInteger("1");
            BigInteger d = new BigInteger("1");
            // System.out.println("x = " + x.toString());
            // System.out.println("now = " + now.toString());
            for (int i = 0; i < 100; ++i) {
                // System.out.println(now.compareTo(x));
                if (now.multiply(BigInteger.valueOf(p[i])).compareTo(x) == 1) break;
                // System.out.println("current p: " + p[i]);
                now = now.multiply(BigInteger.valueOf(p[i]));
                u = u.multiply(BigInteger.valueOf(p[i]));
                d = d.multiply(BigInteger.valueOf(p[i]+1));
                // System.out.println("now = " + now.toString());
                // System.out.println("u = " + u.toString());
                // System.out.println("d = " + d.toString());
            }
            BigInteger g = u.gcd(d);
            u = u.divide(g);
            d = d.divide(g);
            System.out.println(u.toString() + "/" + d.toString());
        }
    }
}
