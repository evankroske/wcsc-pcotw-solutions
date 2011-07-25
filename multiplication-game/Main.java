import java.io.*;
import java.util.*;

class Main {
	public static void main (String[] args) throws Exception {
		new Main();
	}

	private class Results {
		public boolean stanWins;
		public double stanWinPercent;
		public Results (boolean stanWins, double stanWinPercent) {
			this.stanWins = stanWins;
			this.stanWinPercent = stanWinPercent;
		}
	}

	private class Turn implements Comparable<Turn> {
		public boolean stanWins;
		public double stanWinPercent;
		public long p;
		public Turn (boolean stanWins, double stanWinPercent, long p) {
			this.stanWins = stanWins;
			this.stanWinPercent = stanWinPercent;
			this.p = p;
		}

		public int compareTo(Turn other) throws NullPointerException {
			if (other == null) {
				throw new NullPointerException();
			}
			if (p < other.p) {
				return -1;
			} else if (p > other.p) {
				return 1;
			} else {
				return 0;
			}
		}

		public String toString () {
			return String.format("Turn(stanWins=%b, stanWinPercent=%f, p=%d)", 
				stanWins, stanWinPercent, p);
		}
	}
			


	PrintStream out;
	Scanner in;
	public Main () {
		out = System.out;
		in = new Scanner(System.in);

		while (in.hasNextLong()) {
			play(in.nextLong());
		}
	}

	private void play (long goal) {
		List<Long> winningTurns = new LinkedList<Long>();
		NavigableMap<Long, Turn> turns = new TreeMap<Long, Turn>();
		long p = 1, pSteps = 0;
		while (true) {
			long q = p;
			long qSteps = pSteps;
			while (true) {
				q *= 2;
				qSteps++;
				if (q >= goal) {
					boolean stanWins = qSteps % 2 != 0;
					double stanWinPercent = stanWins ? 1 : 0;
					turns.put(q, new Turn(stanWins, stanWinPercent, q));
					break;
				}
			}
			p *= 9;
			pSteps++;
			if (p >= goal) {
				boolean stanWins = pSteps % 2 != 0;
				double stanWinPercent = stanWins ? 1 : 0;
				turns.put(p, new Turn(stanWins, stanWinPercent, p));
				break;
			}
		}
		out.printf("Goal: %d\n", goal);
		for (Turn turn : turns.values()) {
			out.println(turn);
		}
	}
}
