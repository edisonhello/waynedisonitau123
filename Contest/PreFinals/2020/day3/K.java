import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

public class K {
    static Scanner in = new Scanner(System.in);
    public static void main(String[] args) throws Exception {
        List<BigInteger> a = new ArrayList<BigInteger>(), 
                         b = new ArrayList<BigInteger>(), 
                         c = new ArrayList<BigInteger>();
        int na, nb, nc;

        BigInteger L = BigInteger.ONE;
        
        na = in.nextInt();
        while (a.size() < na) a.add(BigInteger.ZERO);
        for (int i = 0; i < na; ++i) {
            BigInteger v = in.nextBigInteger();
            a.set(na - 1 - i, v);
            L = L.max(v);
        }
        nb = in.nextInt();
        while (b.size() < nb) b.add(BigInteger.ZERO);
        for (int i = 0; i < nb; ++i) {
            BigInteger v = in.nextBigInteger();
            b.set(nb - 1 - i, v);
            L = L.max(v);
        }
        nc = in.nextInt();
        while (c.size() < nc) c.add(BigInteger.ZERO);
        for (int i = 0; i < nc; ++i) {
            BigInteger v = in.nextBigInteger();
            c.set(nc - 1 - i, v);
            L = L.max(v);
        }

        // System.out.println(a);
        // System.out.println(b);
        // System.out.println(c);

        List<BigInteger> ab = new ArrayList<BigInteger>();
        while (ab.size() < na + nb) ab.add(BigInteger.ZERO);

        for (int i = 0; i < na; ++i) 
            for (int j = 0; j < nb; ++j) 
                ab.set(i + j, ab.get(i + j).add(a.get(i).multiply(b.get(j))));

        L = L.add(BigInteger.ONE);
        BigInteger R = BigInteger.valueOf(1l << 61).multiply(BigInteger.valueOf(1000));

        while (L.compareTo(R) != 1) {
            BigInteger base = L.add(R).divide(BigInteger.valueOf(2));
            
            // System.out.println("L base R");
            // System.out.println(L);
            // System.out.println(base);
            // System.out.println(R);

            List<BigInteger> cc = new ArrayList<BigInteger>(ab);
            for (int i = 0; i < cc.size(); ++i) {
                BigInteger z = cc.get(i).divide(base);
                cc.set(i, cc.get(i).mod(base));

                // System.out.println("i = " + i);
                // System.out.println(z);

                if (i == cc.size() - 1) {
                    if (z.compareTo(BigInteger.ZERO) != 0) 
                        cc.add(z);
                } else cc.set(i + 1, cc.get(i + 1).add(z));
            }

            // System.out.println(cc);

            while (cc.size() < c.size()) cc.add(BigInteger.ZERO);
            while (c.size() < cc.size()) c.add(BigInteger.ZERO);


            boolean ok = true;
            for (int i = cc.size() - 1; i >= 0; --i) {
                if (cc.get(i).compareTo(c.get(i)) == -1) {
                    R = base.subtract(BigInteger.ONE);
                    ok = false;
                    break;
                } else if (cc.get(i).compareTo(c.get(i)) == 1) {
                    L = base.add(BigInteger.ONE);
                    ok = false;
                    break;
                }
            }

            if (ok) {
                System.out.println(base);
                return;
            }
        }

        System.out.println("impossible");
    }
}

