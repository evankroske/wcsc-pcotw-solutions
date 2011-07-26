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
		public boolean stan;
		public boolean stanWins;
		public double stanWinPercent;
		public long p;
		public Turn (boolean stan, boolean stanWins, double stanWinPercent, long p) {
			this.stan = stan;
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
			return String.format("Turn(stan=%b, stanWins=%b, " + 		
				"stanWinPercent=%f, p=%d)", stan, stanWins, stanWinPercent, p);
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
		NavigableMap<Long, Turn> turns = findWinningTurns(goal);

		while (true) {
			Map.Entry<Long, Turn> entry = turns.pollLastEntry();
			Turn turn = entry.getValue();
			if (turn.p == 1) {
				String winner = turn.stanWins ? "Stan" : "Ollie";
				out.printf("%s wins.\n", winner);
				break;
			}
			for (int n : Arrays.asList(2, 9)) {
				if (turn.p % n != 0) {
					continue;
				}
				long p = turn.p / n;
				boolean stan = !turn.stan;
				double stanWinPercent;
				boolean stanWins;

				Turn other = turns.remove(p);
				if (other != null) {
					stanWinPercent = (turn.stanWinPercent + other.
						stanWinPercent) / 2;
					if (stan) {
						stanWins = turn.stanWinPercent > other.stanWinPercent
							? turn.stanWins 
							: other.stanWins;
					} else {
						stanWins = turn.stanWinPercent < other.stanWinPercent
							? turn.stanWins 
							: other.stanWins;
					}
				} else {
					stanWinPercent = turn.stanWinPercent;
					stanWins = turn.stanWins;
				}
				turns.put(p, new Turn(stan, stanWins, stanWinPercent, p));
			}
		}
	}

	private NavigableMap<Long, Turn> findWinningTurns(long goal) {
		NavigableMap<Long, Turn> turns = new TreeMap<Long, Turn>();
		long p = 1, pSteps = 0;
		while (true) {
			long q = p;
			long qSteps = pSteps;
			while (true) {
				q *= 2;
				qSteps++;
				if (q >= goal) {
					boolean stan = qSteps % 2 != 0;
					boolean stanWins = stan;
					double stanWinPercent = stanWins ? 1 : 0;
					turns.put(q, new Turn(stan, stanWins, stanWinPercent, q));
					break;
				}
			}
			p *= 9;
			pSteps++;
			if (p >= goal) {
				boolean stan = pSteps % 2 != 0;
				boolean stanWins = stan;
				double stanWinPercent = stanWins ? 1 : 0;
				turns.put(p, new Turn(stan, stanWins, stanWinPercent, p));
				break;
			}
		}
		return turns;
	}
}
