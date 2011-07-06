import java.io.*;

public class Main extends Object {
	private static char[] charMap = new char[128];
	static {
		charMap[49] = '`';
		charMap[50] = '1';
		charMap[51] = '2';
		charMap[52] = '3';
		charMap[53] = '4';
		charMap[54] = '5';
		charMap[55] = '6';
		charMap[56] = '7';
		charMap[57] = '8';
		charMap[48] = '9';
		charMap[45] = '0';
		charMap[61] = '-';
		charMap[87] = 'Q';
		charMap[69] = 'W';
		charMap[82] = 'E';
		charMap[84] = 'R';
		charMap[89] = 'T';
		charMap[85] = 'Y';
		charMap[73] = 'U';
		charMap[79] = 'I';
		charMap[80] = 'O';
		charMap[91] = 'P';
		charMap[93] = '[';
		charMap[83] = 'A';
		charMap[68] = 'S';
		charMap[70] = 'D';
		charMap[71] = 'F';
		charMap[72] = 'G';
		charMap[74] = 'H';
		charMap[75] = 'J';
		charMap[76] = 'K';
		charMap[59] = 'L';
		charMap[39] = ';';
		charMap[88] = 'Z';
		charMap[67] = 'X';
		charMap[86] = 'C';
		charMap[66] = 'V';
		charMap[78] = 'B';
		charMap[77] = 'N';
		charMap[44] = 'M';
		charMap[46] = ',';
		charMap[47] = '.';
	}
	public static void run () throws IOException {
		String l = null;
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		while ((l = in.readLine()) != null) {
			for (byte b : l.getBytes()) {
				if (charMap[b] != (char) 0) {
					System.out.print(charMap[b]);
				} else {
					System.out.print((char) b);
				}
			}
			System.out.println();
		}
	}

	public static void main(String[] args) {
		try {
			run();
		} catch (IOException e) {};
	}
}
