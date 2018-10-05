import java.io.*;
import java.util.*;
import java.math.*;

public class filename{
    static Scanner in = new Scanner(System.in);
    public static void main(String[] args){
        int a = in.nextInt();
        float b = in.nextFloat();
        String str = in.nextLine(); // full line
        String str2 = in.next(); // without space
        BigInteger bi = in.nextBigInteger(), bj = new BigInteger("7122");
        bi = bi.add(bj);
        bi = bi.and(bj);
        bi = bi.divide(bj);
        bi = bi.gcd(bj);
        bi = bi.max(bj);
        bi = bi.multiply(bj);
        System.out.println("testcase" + a);
        while(in.hasNextInt())a = in.nextInt();
    }
}
