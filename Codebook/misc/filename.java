import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

public class filename{
  static Scanner in = new Scanner(System.in);
  public static void main(String[] args) throws Exception {
    Scanner fin = new Scanner(new File("infile"));
    PrintWriter fout = new PrintWriter("outfile", "UTF-8");
    fout.println(fin.nextLine());
    fout.close(); 
    while (in.hasNext()) {
      String str = in.nextLine(); // getline
      String stu = in.next(); // string
    }
    System.out.println("Case #" + t);
    System.out.printf("%d\n", 7122);
    int[][] d = {{7,1,2,2},{8,7}};
    int g = Integer.parseInt("-123");

    long f = (long)d[0][2];

    List<Integer> l = new ArrayList<>();
    Random rg = new Random();
    for (int i = 9; i >= 0; --i) {
      l.add(Integer.valueOf(rg.nextInt(100) + 1));
      l.add(Integer.valueOf((int)(Math.random() * 100) + 1));
    }
    Collections.sort(l, new Comparator<Integer>() {
      public int compare(Integer a, Integer b) { return a - b; }
    });
    for (int i = 0; i < l.size(); ++i)
      System.out.print(l.get(i));

    Set<String> s = new HashSet<String>(); // TreeSet
    s.add("jizz");
    System.out.println(s);
    System.out.println(s.contains("jizz"));

    Map<String, Integer> m = new HashMap<String, Integer>();
    m.put("lol", 7122);
    System.out.println(m);
    for(String key: m.keySet()) 
      System.out.println(key + " : " + m.get(key));
    System.out.println(m.containsKey("lol"));
    System.out.println(m.containsValue(7122));

    System.out.println(Math.PI);
    System.out.println(Math.acos(-1));

    BigInteger bi = in.nextBigInteger(), bj = new BigInteger("-7122"), bk = BigInteger.valueOf(17171);
    int sgn = bi.signum(); // sign(bi)
    bi = bi.subtract(BigInteger.ONE).multiply(bj).divide(bj).and(bj).gcd(bj).max(bj).pow(87);
    int meow = bi.compareTo(bj); // -1 0 1
    String stz = "f5abd69150";
    BigInteger b16 = new BigInteger(stz, 16);
    System.out.println(b16.toString(2));
  }
}
