import java.util.*;
import java.io.*;
import java.math.*;
import java.lang.*;

public class J {
    static Scanner in = new Scanner(System.in);
    public static void main(String[] args) {
        FileInputStream fin;
        FileOutputStream fout;
        BigInteger a = BigInteger.ZERO, b = BigInteger.ZERO, c = BigInteger.ZERO;
        try {
            fin = new FileInputStream("squares.in");
            fout = new FileOutputStream("squares.out");
            while (true) {
                int z = fin.read();
                if (z >= 48 && z <= 57) a = a.multiply(BigInteger.valueOf(10)).add(BigInteger.valueOf(z - 48));
                else break;
            }
            while (true) {
                int z = fin.read();
                if (z >= 48 && z <= 57) b = b.multiply(BigInteger.valueOf(10)).add(BigInteger.valueOf(z - 48));
                else break;
            }
            while (true) {
                int z = fin.read();
                if (z >= 48 && z <= 57) c = c.multiply(BigInteger.valueOf(10)).add(BigInteger.valueOf(z - 48));
                else break;
            }
            int cnt = 0;
            while (a.mod(BigInteger.valueOf(3)).compareTo(BigInteger.ZERO) == 0 &&
                    b.mod(BigInteger.valueOf(3)).compareTo(BigInteger.ZERO) == 0 &&
                    c.mod(BigInteger.valueOf(3)).compareTo(BigInteger.ZERO) == 0) {
                cnt += 1;
                a = a.divide(BigInteger.valueOf(3));
                b = b.divide(BigInteger.valueOf(3));
                c = c.divide(BigInteger.valueOf(3));
                    }
            for (int i = 0; i < cnt; ++i) {
                if (a.add(b).add(c).mod(BigInteger.valueOf(3)).compareTo(BigInteger.ZERO) != 0) {
                    BigInteger aa = a.multiply(BigInteger.valueOf(2)).add(b.multiply(BigInteger.valueOf(2))).subtract(c).abs();
                    BigInteger bb = a.multiply(BigInteger.valueOf(2)).add(c.multiply(BigInteger.valueOf(2))).subtract(b).abs();
                    BigInteger cc = b.multiply(BigInteger.valueOf(2)).add(c.multiply(BigInteger.valueOf(2))).subtract(a).abs();
                    a = aa;
                    b = bb;
                    c = cc;
                } else {
                    if (b.mod(BigInteger.valueOf(3)).compareTo(BigInteger.ZERO) != 0) {
                        BigInteger z = a;
                        a = b;
                        b = z;
                    }
                    if (c.mod(BigInteger.valueOf(3)).compareTo(BigInteger.ZERO) != 0) {
                        BigInteger z = a;
                        a = c;
                        c = z;
                    }
                    BigInteger aa = a.multiply(BigInteger.valueOf(2)).add(b).subtract(c.multiply(BigInteger.valueOf(2))).abs();
                    BigInteger bb = b.multiply(BigInteger.valueOf(2)).add(c.multiply(BigInteger.valueOf(2))).add(a).abs();
                    BigInteger cc = a.multiply(BigInteger.valueOf(2)).subtract(b.multiply(BigInteger.valueOf(2))).add(c).abs();
                    a = aa;
                    b = bb;
                    c = cc;
                }
            }
            /* BigInteger base = BigInteger.valueOf(10);
               while (a.compareTo(base.multiply(BigInteger.valueOf(10))) == -1) base = base.multiply(BigInteger.valueOf(10));
               do {
               fout.write((int)a.divide(base).toLong() + 48);
               a = a.mod(base);
               base = base.devide(BigInteger.valueOf(10));
               } while (base.compareTo(bigInteger.ZERO) != 0);
               fout.write(32);

               base = BigInteger.valueOf(10);
               while (b.compareTo(base.multiply(BigInteger.valueOf(10))) == -1) base = base.multiply(BigInteger.valueOf(10));
               do {
               fout.write((int)b.divide(base).toLong() + 48);
               b = b.mod(base);
               base = base.devide(BigInteger.valueOf(10));
               } while (base.compareTo(bigInteger.ZERO) != 0);
               fout.write(32);

               base = BigInteger.valueOf(10);
               while (c.compareTo(base.multiply(BigInteger.valueOf(10))) == -1) base = base.multiply(BigInteger.valueOf(10));
               do {
               fout.write((int)c.divide(base).toLong() + 48);
               c = c.mod(base);
               base = base.devide(BigInteger.valueOf(10));
               } while (base.compareTo(bigInteger.ZERO) != 0);
               fout.write(10); */
            String aa = a.toString(10);
            String bb = b.toString(10);
            String cc = c.toString(10);
            for (int i = 0; i < aa.length(); ++i) fout.write(aa.charAt(i));
            fout.write(32);
            for (int i = 0; i < bb.length(); ++i) fout.write(bb.charAt(i));
            fout.write(32);
            for (int i = 0; i < cc.length(); ++i) fout.write(cc.charAt(i));
            fout.write(10);
        } catch (FileNotFoundException e) {

        } catch (IOException e) {

        };
        /* BigInteger a = in.nextBigInteger(),
           b = in.nextBigInteger(),
           c = in.nextBigInteger(); */
    }
}
