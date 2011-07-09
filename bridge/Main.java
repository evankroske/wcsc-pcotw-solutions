import java.io.*;
import java.util.List;
import java.util.LinkedList;
import java.util.ArrayDeque;
import java.util.Collections;

class Main {
	private PrintStream o;
	private BufferedReader i;

	private boolean handleCase () throws IOException {
		LinkedList<Integer> crossingTimes = new LinkedList<Integer>();
		String l;
		i.readLine();
		for (l = i.readLine(); l != null && !l.isEmpty(); l = i.readLine()) {
			crossingTimes.add(new Integer(l.trim()));
		}
		Collections.sort(crossingTimes);
		System.out.println(crossingTimes);
		if (l != null) {
			return true;
		} else {
			return false;
		}
	}

	public Main() throws IOException {
		i = new BufferedReader(new InputStreamReader(System.in));
		o = System.out;

		i.readLine();
		i.readLine();
		while (handleCase());
	}

	public static void main (String[] args) {
		try { new Main(); } catch (IOException e) {;};
	}
}
