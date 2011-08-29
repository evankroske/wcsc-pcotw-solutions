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

	long factorial (long degree) {
		long factor = degree;
		if (degree > 1) {
			long result = 1;
			while (factor > 1) {
				result *= factor;
				factor--;
			}
			if (result < 1) {
				out.printf("degree: %d, result: %d%n", degree, result);
			}
			return result;
		} else {
			return 1;
		}
	}

	long choose (long n, long k) {
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
