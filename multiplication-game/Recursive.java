import java.io.*;
import java.util.*;

class Recursive {
	public static void main (String[] args) throws Exception {
		if (args.length > 0) {
			new Recursive(true);
		} else {
			new Recursive(false);
		}
	}

	PrintStream out;
	Scanner in;
	boolean list;

	public Recursive (boolean list) {
		out = System.out;
		in = new Scanner(System.in);
		this.list = list;
		play(in.nextInt());
	}

	private void play (int goal) {
		Results results = playRound(goal, 1, true);
		if (!list) {
			String winner = results.stanWins ? "Stan" : "Ollie";
			out.printf("%s wins.\n", winner);
		}
	}
	
	private Results playRound (int goal, int p, boolean stan) {
		if (p >= goal) {
			if (list) {
				out.println(p);
			}
			return new Results(!stan, !stan ? 1 : 0);
		}
		Results resultsIf2 = playRound(goal, p*2, !stan);
		Results resultsIf9 = playRound(goal, p*9, !stan);
		boolean stanWins;
		if (stan) {
			stanWins = resultsIf9.stanWinPercent >= resultsIf2.stanWinPercent ? 
				resultsIf9.stanWins : resultsIf2.stanWins;
		} else {
			stanWins = resultsIf2.stanWinPercent >= resultsIf9.stanWinPercent ? 
				resultsIf9.stanWins : resultsIf2.stanWins;
		}
		double stanWinPercent = (resultsIf2.stanWinPercent + resultsIf9.stanWinPercent) / 2;
		return new Results(stanWins, stanWinPercent);
	}

	private class Results {
		public boolean stanWins;
		public double stanWinPercent;
		public Results (boolean stanWins, double stanWinPercent) {
			this.stanWins = stanWins;
			this.stanWinPercent = stanWinPercent;
		}
	}

}
