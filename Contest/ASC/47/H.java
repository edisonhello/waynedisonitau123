import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

public class H {
    static BigInteger[][] get_mat(int n) {
        BigInteger[][] res = new BigInteger[n][n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) res[i][j] = BigInteger.ZERO;
        }
        return res;
    }
    static BigInteger[][] get_Imat(int n) {
        BigInteger[][] res = new BigInteger[n][n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) res[i][j] = BigInteger.ZERO;
            res[i][i] = BigInteger.ONE;
        }
        return res;
    }
    static BigInteger[][] mult(BigInteger[][] a, BigInteger[][] b, int n) {
        BigInteger[][] res = new BigInteger[n][n];
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) res[i][j] = BigInteger.ZERO;
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) for (int k = 0; k < n; ++k) {
            res[i][j] = res[i][j].add(a[i][k].multiply(b[k][j]));
        }
        return res;
    }
    public static int n;
    public static BigInteger[][] L, iL, R, iR, A;
    static void row_op(int from, int to, BigInteger tms) {
        BigInteger op[][] = get_Imat(n);
        op[to][from] = tms;
        L = mult(op, L, n);
        A = mult(op, A, n);
        op[to][from] = tms.multiply(BigInteger.valueOf(-1));
        iL = mult(iL, op, n);
    }
    static void col_op(int from, int to, BigInteger tms) {
        BigInteger op[][] = get_Imat(n);
        op[from][to] = tms;
        R = mult(R, op, n);
        A = mult(A, op, n);
        op[from][to] = tms.multiply(BigInteger.valueOf(-1));
        iR = mult(op, iR, n);
    }
    static void swap_row(int u, int v) {
        BigInteger op[][] = get_Imat(n);
        op[u][u] = op[v][v] = BigInteger.ZERO;
        op[u][v] = op[v][u] = BigInteger.ONE;
        L = mult(op, L, n);
        A = mult(op, A, n);
        iL = mult(iL, op, n);
    }
    static void swap_col(int u, int v) {
        BigInteger op[][] = get_Imat(n);
        op[u][u] = op[v][v] = BigInteger.ZERO;
        op[u][v] = op[v][u] = BigInteger.ONE;
        R = mult(R, op, n);
        A = mult(A, op, n);
        iR = mult(op, iR, n);
    }
    static boolean right_and_down(int z) {
        for (int y = z + 1; y < n; ++y) if (A[z][y].compareTo(BigInteger.ZERO) != 0 || A[y][z].compareTo(BigInteger.ZERO) != 0) return true;
        return false;
    }
    static void clear_row_and_column(int z) {
        while (right_and_down(z)) {
            for (int y = z + 1; y < n; ++y) {
                if (A[y][z].compareTo(BigInteger.ZERO) == 0) continue;
                while (A[y][z].mod(A[z][z].abs()).compareTo(BigInteger.ZERO) != 0) {
                    if (A[y][z].abs().compareTo(A[z][z].abs()) > 0) {
                        BigInteger tms = A[y][z].divide(A[z][z]);
                        row_op(z, y, tms.multiply(BigInteger.valueOf(-1)));
                    } else {
                        BigInteger tms = A[z][z].divide(A[y][z]);
                        if (A[y][z].multiply(tms).compareTo(A[z][z]) == 0) tms = tms.subtract(BigInteger.valueOf(1));
                        row_op(y, z, tms.multiply(BigInteger.valueOf(-1)));
                    }
                }
                row_op(z, y, A[y][z].divide(A[z][z]).multiply(BigInteger.valueOf(-1)));
            }
            for (int y = z + 1; y < n; ++y) {
                if (A[z][y].compareTo(BigInteger.ZERO) == 0) continue;
                while (A[z][y].mod(A[z][z].abs()).compareTo(BigInteger.ZERO) != 0) {
                    if (A[z][y].abs().compareTo(A[z][z].abs()) > 0) {
                        BigInteger tms = A[z][y].divide(A[z][z]);
                        col_op(z, y, tms.multiply(BigInteger.valueOf(-1)));
                    } else {
                        BigInteger tms = A[z][z].divide(A[z][y]);
                        if (A[z][y].multiply(tms).compareTo(A[z][z]) == 0) tms = tms.subtract(BigInteger.valueOf(1));
                        col_op(y, z, tms.multiply(BigInteger.valueOf(-1)));
                    }
                }
                col_op(z, y, A[z][y].divide(A[z][z]).multiply(BigInteger.valueOf(-1)));
            }
        }
    }
    public static void main(String[] args) {
        try {
            System.setIn(new FileInputStream(new File("higher.in")));
            System.setOut(new PrintStream(new File("higher.out")));
        } catch (Exception e) {

        }
        Scanner in = new Scanner(System.in);
        boolean first = true;
        while (in.hasNext()) {
            n = in.nextInt();
            if (n == 0) break;
            L = get_Imat(n);
            iL = get_Imat(n);
            R = get_Imat(n);
            iR = get_Imat(n);
            A = get_mat(n);
            for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) A[i][j] = in.nextBigInteger();
            for (int z = 0; z < n - 1; ++z) {
                for (int i = z; i < n; ++i) for (int j = z; j < n; ++j) if (A[i][j].compareTo(BigInteger.ZERO) != 0) {
                    swap_row(i, z); swap_col(j, z);
                }

                if (A[z][z].compareTo(BigInteger.ZERO) == 0) break;
                // skip let A[i][j] be min part

                clear_row_and_column(z);
                while (true) {
                    boolean change = false;
                    for (int i = z + 1; i < n; ++i) for (int j = z + 1; j < n; ++j) {
                        if (A[i][j].mod(A[z][z].abs()).compareTo(BigInteger.ZERO) > 0) {
                            row_op(i, z, BigInteger.ONE);
                            clear_row_and_column(z);
                            change = true;
                        }
                    }
                    if (change == false) break;
                }
            }
            if (!first) System.out.println("");
            first = false;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    System.out.print(L[i][j] + " ");
                }
                System.out.println("");
            }
            System.out.println("");
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    System.out.print(iL[i][j] + " ");
                }
                System.out.println("");
            }
            System.out.println("");
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    System.out.print(R[i][j] + " ");
                }
                System.out.println("");
            }
            System.out.println("");
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    System.out.print(iR[i][j] + " ");
                }
                System.out.println("");
            }
        }
    }
}
