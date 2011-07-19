import java.io.*;
import java.util.*;

public class Main {
	public static final int MAX_WORD_LENGTH = 16;

	private PrintStream out;
	private BufferedReader in;
	private Map<Integer,Set<String>> dict;

	public static void main (String[] args) throws Exception {
		new Main();
	}

	public Main () throws Exception {
		out = System.out;
		in = new BufferedReader(new InputStreamReader(System.in));
		dict = new HashMap<Integer,Set<String>>();

		String firstLine = in.readLine();
		int dictLength = new Scanner(firstLine).nextInt();

		for (int i = 0; i < dictLength; i++) {
			String word = in.readLine();
			if (dict.get(word.length()) == null) {
				dict.put(word.length(), new HashSet<String>());
			}
			dict.get(word.length()).add(word);
		}

		String l = in.readLine();
		while (l != null) {
			List<String> encodedWords = new ArrayList(new HashSet<String>(Arrays.asList(l.split(" "))));
			Collections.sort(encodedWords, new NumBranchComparator());

			Iterator<String> it = encodedWords.iterator();
			while (it.hasNext()) {
				out.println(it.next());
			}
			out.println();

			findTranslator(encodedWords, 2);
			l = in.readLine();
		}
	}

	private class NumBranchComparator implements Comparator<String> {
		private int countBranches (String a) {
			Set<String> branches = dict.get(a.length());
			return (branches != null) ? branches.size() : 0;
		}

		public int compare (String a, String b) {
			Integer numABranches = countBranches(a);
			Integer numBBranches = countBranches(b);
			return numABranches.compareTo(numBBranches);
		}
	}

	private class ImmutableTranslator {}

	private ImmutableTranslator findTranslator (List<String> encodedWords, int index) {
		ListIterator<String> it = encodedWords.listIterator(index);
		if (it.hasNext()) {
			System.out.printf("found %s\n", it.next());
		}
		return null;
	}
}

