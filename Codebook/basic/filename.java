import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

public class filename{
    static Scanner in = new Scanner(System.in);
    public static void main(String[] args) {
        while(in.hasNext()) {
            int a = in.nextInt();
            float b = in.nextFloat();
            String str = in.nextLine(); // getline
            String stu = in.next(); // string
        }
        System.out.println("Case #" + t);
        System.out.printf("%d\n", 7122);
        int c = new int[5];
        int[] e = {5,8,5,8,6,4};
        int[][] d = {{7,1,2,2},{8,7}};
        int g = Integer.parseInt("-123");

        long f = (long)d[0][2];

        Array.sort(e, new cmp());
        for(int i = 0; i < e.length; ++i) {
            System.out.print(e[i]);
        }

        Set<String> s = new HashSet<String>(); // TreeSet
        s.add("jizz");
        System.out.println(s);
        System.out.println(s.contains("jizz"));

        Map<String, Integer> m = new Hashmap<String, Integer>();
        m.put("lol", 7122);
        System.out.println(m);
        for(String key: map.keySet()) {
            System.out.println(key + " : " + map.get(key));
        }
        System.out.println(m.containsKey("lol"));
        System.out.println(m.containsValue(7122));

        System.out.println(Math.PI);
        System.out.println(Math.acos(-1));

        BigInteger bi = in.nextBigInteger(), bj = new BigInteger("-712222222222222"), bk = BigInteger.valueOf(17171);
        bi = bi.add(bj);
        bi = bi.substract(BigInteger.ONE);
        bi = bi.multiply(bj);
        bi = bi.divide(bj);
        bi = bi.and(bj);
        bi = bi.gcd(bj);
        bi = bi.max(bj);
        bi = bi.pow(bj);
        int meow = bi.compareTo(bj);
        String stz = "f5abd69150";
        BigInteger b16 = new Biginteger(stz, 16);
        System.out.println(stz.toString(2));
    }
    static class cmp implements Comparator<Integer> {
        public int compare(Integer a, Integer b) {
            return b - a;
        }
    }
}
