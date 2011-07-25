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

	PrintStream out;
	Scanner in;
	public Main () {
		out = System.out;
		in = new Scanner(System.in);

		while (in.hasNextInt()) {
			play(in.nextInt());
		}
	}

	private void play (int goal) {
		Results results = playRound(goal, 1, true);
		String winner = results.stanWins ? "Stan" : "Ollie";
		out.printf("%s wins.\n", winner);
	}
	
	private Results playRound (int goal, int p, boolean stan) {
		if (p >= goal) {
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
}
