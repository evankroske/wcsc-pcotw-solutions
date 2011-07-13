import java.io.*;
import java.util.Scanner;
import java.util.Arrays;
import java.lang.StringBuilder;

class SoftBoard extends Object {
	private Integer[][] board;
	private int numRows;
	private int numCols;
	public SoftBoard(int n, int m) {
		numRows = n;
		numCols = m;
		board = new Integer[numRows][numCols];
		for (int i = 0; i < numRows; i++) {
			Arrays.fill(board[i], 0);
		}
	}

	public void addMine (int rowIndex, int colIndex) {
		if (board[rowIndex][colIndex] == null) {
			return;
		}
		board[rowIndex][colIndex] = null;

		int lowerRowIndex = (rowIndex - 1 >= 0) ? rowIndex - 1 : 0;
		int upperRowIndex = (rowIndex + 1 < numRows) ? rowIndex + 1 : numRows - 1;
		int lowerColIndex = (colIndex - 1 >= 0) ? colIndex - 1 : 0;
		int upperColIndex = (colIndex + 1 < numCols) ? colIndex + 1 : numCols -1;
		for (int i = lowerRowIndex; i <= upperRowIndex; i++) {
			for (int j = lowerColIndex; j <= upperColIndex; j++) {
				if (board[i][j] != null) {
					board[i][j]++;
				}
			}
		}
	}

	public String toString () {
		StringBuilder out = new StringBuilder();
		for (Integer[] row : board) {
			for (Integer cell : row) {
				if (cell != null) {
					out.append(cell);
				} else {
					out.append("*");
				}
			}
			out.append("\n");
		}
		return out.toString().trim();
	}
}

class Main {
	private PrintStream out;
	private BufferedReader in;

	private int[] readDimensions () throws Exception {
		String l = in.readLine();
		Scanner s = new Scanner(l);
		int n = s.nextInt();
		int m = s.nextInt();
		return new int[]{n, m};
	}

	private void handleBoard (int n, int m, int c) throws Exception {
		SoftBoard board = new SoftBoard(n, m);
		int rowIndex = 0;
		for (int i = 0; i < n; i++) {
			String l = in.readLine();
			for (int j = 0; j < m; j++) {
				if (l.charAt(j) == '*') {
					board.addMine(i, j);
				}
			}
		}
		out.printf("Field #%d:\n", c);
		out.println(board);
	}


	public Main () throws Exception {
		out = System.out;
		in = new BufferedReader(new InputStreamReader(System.in));

		int[] dim = readDimensions();
		int n = dim[0], m = dim[1];
		int c = 1;
		handleBoard(n, m, c);
		while (true) {
			c++;
			dim = readDimensions();
			n = dim[0];
			m = dim[1];
			if (n == 0 || m == 0) {
				break;
			}
			out.println();
			handleBoard(n, m, c);
		}
	}

	public static void main (String[] args) {
		try { new Main(); } catch (Exception e) {}
	}
}
