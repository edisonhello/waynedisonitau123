import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

public class E {
    static Scanner in = new Scanner(System.in);
    static Set<BigInteger> st = new TreeSet<BigInteger>();
    static List<BigInteger> ans = new ArrayList<BigInteger>();
    static List<BigInteger> que = new ArrayList<BigInteger>();
    static int n, k;
    private static void trans(BigInteger a, BigInteger b, BigInteger c) {
        a = (BigInteger.valueOf(k)).multiply(b.add(c)).subtract(a);
        b = (BigInteger.valueOf(k)).multiply(a.add(c)).subtract(b);
        c = (BigInteger.valueOf(k)).multiply(a.add(b)).subtract(c);
        if (st.contains(a) || st.contains(b) || st.contains(c) || a.compareTo(BigInteger.valueOf(0)) <= 0 || b.compareTo(BigInteger.valueOf(0)) <= 0 || c.compareTo(BigInteger.valueOf(0)) <= 0) {

        } else {
            st.add(a); st.add(b); st.add(c);
            ans.add(a); ans.add(b); ans.add(c);
        }
        que.add(a); que.add(b); que.add(c);
    }
    public static void main(String[] args) {
        k = in.nextInt(); n = in.nextInt();
        que.add(BigInteger.valueOf(0)); que.add(BigInteger.valueOf(0)); que.add(BigInteger.valueOf(1));
        for (int a = 1; a <= 200; ++a) for (int b = a + 1; b <= 200; ++b) for (int c = b + 1; c <= 200; ++c) {
            if (a * a + b * b + c * c == k * (a * b + b * c + c * a) + 1) {
                if (st.contains(BigInteger.valueOf(a)) || st.contains(BigInteger.valueOf(b)) || st.contains(BigInteger.valueOf(c))) {

                } else {
                    st.add(BigInteger.valueOf(a)); st.add(BigInteger.valueOf(b)); st.add(BigInteger.valueOf(c));
                    ans.add(BigInteger.valueOf(a)); ans.add(BigInteger.valueOf(b)); ans.add(BigInteger.valueOf(c));
                }
                que.add(BigInteger.valueOf(a)); que.add(BigInteger.valueOf(b)); que.add(BigInteger.valueOf(c));
            }
        }
        // System.out.println("que size: " + que.size());
        int ptr = 0;
        while (ans.size() < 3 * n) {
            // System.out.println("que size: " + que.size());
            BigInteger a = que.get(ptr); ptr += 1;
            BigInteger b = que.get(ptr); ptr += 1;
            BigInteger c = que.get(ptr); ptr += 1;
            trans(a, b, c);
            trans(b, a, c);
            trans(c, a, b);
        }
        ptr = 0;
        while (ptr < 3 * n) {
            BigInteger a = ans.get(ptr); ptr += 1;
            BigInteger b = ans.get(ptr); ptr += 1;
            BigInteger c = ans.get(ptr); ptr += 1;
            System.out.println(a + " " + b + " " + c);
        }
    }
}
