import java.io.*;
import java.util.*;

class SoftBoard extends Object {
	private int[][] rows;
	public SoftBoard(int n, int m) {
		rows = new int[n][m];
		for (int i = 0; i < n; i++) {
			Arrays.fill(rows[i], 0);
		}
		for (int[] row : rows) {
			for (int i : row) {
				System.out.print(i);
			}
			System.out.println();
		}
	}
}

class Main extends Object {
	private PrintStream o;
	private BufferedReader i;

	private boolean handleCase () throws IOException {
		String l = i.readLine();
		Scanner s = new Scanner(l);
		int n = s.nextInt();
		int m = s.nextInt();
		SoftBoard board = new SoftBoard(n, m);
		return true;
	}


	public Main () throws IOException {
		o = System.out;
		i = new BufferedReader(new InputStreamReader(System.in));
		o.println("Running");
		handleCase();
	}

	public static void main (String[] args) {
		try { new Main(); } catch (IOException e) {}
	}
}
