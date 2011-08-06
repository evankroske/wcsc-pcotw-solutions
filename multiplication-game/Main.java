import java.io.*;
import java.util.*;

class Main {
	public static void main (String[] args) throws Exception {
		new Main();
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
			if (turn.isOne()) {
				out.printf("%s wins.\n", turn.winner());
				break;
			}
			for (int n : Arrays.asList(2, 9)) {
				if (turn.p % n != 0) {
					continue;
				}
				long p = turn.p / n;
				Turn parent = turns.get(p);
				if (parent == null) {
					parent = new Turn(p);
					turns.put(p, parent);
				}
				parent.addBranch(n, turn);
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
				q *= 9;
				qSteps++;
				if (q >= goal) {
					boolean stan = qSteps % 2 != 0;
					boolean stanWins = stan;
					double stanWinPercent = stanWins ? 1 : 0;
					turns.put(q, new Turn(stan, stanWins, stanWinPercent, q));
					break;
				}
			}
			p *= 2;
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
	
	private class Turn implements Comparable<Turn> {
		private boolean stan;
		private boolean stanWins;
		private double stanWinPercent;
		private long p;
		private Map<Integer, Turn> branches;

		public Turn(long p) {
			this.p = p;
			this.branches = new HashMap<Integer, Turn>(2);
		}

		public Turn (boolean stan, boolean stanWins, double stanWinPercent, long p) {
			this.stan = stan;
			this.stanWins = stanWins;
			this.stanWinPercent = stanWinPercent;
			this.p = p;
			this.branches = new HashMap<Integer, Turn>(2);
		}

		public boolean isOne () {
			return p == 1;
		}

		public String winner () {
			return stanWins ? "Stan" : "Ollie";
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

		private void init () {
			Turn branch2 = branches.get(2);
			Turn branch9 = branches.get(9);

			stan = !branch2.stan;
			stanWinPercent = (branch2.stanWinPercent + branch9.
				stanWinPercent) / 2;
			if (branch9.stanWinPercent > branch2.stanWinPercent) {
				stanWins = stan ? branch9.stanWins : branch2.stanWins;
			} else if (branch9.stanWinPercent < branch2.stanWinPercent) {
				stanWins = stan ? branch2.stanWins : branch9.stanWins;
			} else {
				stanWins = branch9.stanWins;
			}
		}
		
		public void addBranch (int choice, Turn turn) {
			branches.put(choice, turn);
			if (branches.size() == 2) {
				init();
			}
		}
	}
			

}
