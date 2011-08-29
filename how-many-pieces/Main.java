import java.io.*;
import java.util.*;

class Main {
	public static void main (String[] args) throws Exception {
		Main main = new Main();
	}

	PrintStream out;
	Scanner in;

	Main () {
		out = System.out;
		in = new Scanner(System.in);
		in.nextInt();
		while (in.hasNextInt()) {
			out.printf("%d%n", countRegions(in.nextInt()));
		}
	}

	long factorial (int degree) {
		int result = 1;
		while (degree > 1) {
			result *= degree;
			degree--;
		}
		return result;
	}

	long choose (int n, int k) {
		if (n >= k) {
			return factorial(n) / (factorial(k) * factorial(n - k));
		} else {
			return 0;
		}
	}

	private long countRegions (int numPoints) {
		long numLines = numPoints * (numPoints - 1) / 2;
		long numIntersections = choose(numPoints, 4);
		return 1 + numLines + numIntersections;
	}
}
