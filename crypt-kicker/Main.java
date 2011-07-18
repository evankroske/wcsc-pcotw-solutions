import java.io.*;
import java.util.*;

public class Main {
	public PrintStream out;
	public BufferedReader in;
	public static final int MAX_WORD_LENGTH = 16;

	public static void main (String[] args) throws Exception {
		new Main();
	}

	public Main () throws Exception {
		out = System.out;
		in = new BufferedReader(new InputStreamReader(System.in));
		out.println("I/O initialized");

		String firstLine = in.readLine();
		int dictLength = new Scanner(firstLine).nextInt();

		Map<Integer,Set<String>> dict = new HashMap<Integer,Set<String>>();
		for (int i = 0; i < dictLength; i++) {
			String word = in.readLine();
			out.printf("Word \"%s\" read\n", word);
			if (dict.get(word.length()) == null) {
				dict.put(word.length(), new HashSet<String>());
			}
			dict.get(word.length()).add(word);
		}
		out.println(dict.get(4).size());

		String l = in.readLine();
		while (l != null) {
			List<String> encodedWords = Arrays.asList(l.split(" "));
			Iterator<String> it = encodedWords.iterator();
			findTranslator(encodedWords, 2);
			while (it.hasNext()) {
				out.println(it.next());
			}
			out.println();
			l = in.readLine();
		}
	}

	private class NumBranchComparator implements Comparator<String> {
		public int compare (String a, String b) {
			return 0;
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

