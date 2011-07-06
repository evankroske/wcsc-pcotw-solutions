import java.io.*;

class Main {
	private static Console c = System.console();
	private static PrintWriter o = c.writer();

	private static boolean handleCase () {
		String l;
		for (l = c.readLine(); l != null && !l.equals("\n"); l = c.readLine()) {
			o.println(l);
		}
		if (l.equals("\n")) {
			return true;
		} else {
			return false;
		}
	}

	public static void main (String[] args) {
		c.readLine();
		c.readLine();
		while (handleCase());
	}
}
