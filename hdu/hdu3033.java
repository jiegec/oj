

import java.util.ArrayList;
import java.util.Scanner;

public class Main{
	private static int max(int a, int b) {
		return a > b ? a : b;
	}
	public static void main(String args[]) {
		Scanner s = new Scanner(System.in);
		int n, m, k;
		while(s.hasNext()) {
			n = s.nextInt();
			m = s.nextInt();
			k = s.nextInt();
			ArrayList<Integer> price = new ArrayList<Integer>();
			ArrayList<Integer> value = new ArrayList<Integer>();
			ArrayList<ArrayList<Integer>> brands = new ArrayList<ArrayList<Integer>>();
			for(int i = 0;i < k+1;i++) {
				brands.add(new ArrayList<Integer>());
			}
			for(int i = 0;i < n;i++) {
				int a = s.nextInt();
				int b = s.nextInt();
				int c = s.nextInt();
				price.add(b);
				value.add(c);
				brands.get(a).add(i);
			}
			int[][] f = new int[12][10086];
			for(int i = 1;i <= k;i++) {
				for(int j = 0;j <= m;j++) {
					f[i][j] = -1;
				}
			}
			for(int i = 1;i <= k;i++) {
					for(int index : brands.get(i)) {
						for(int j = m;j >= price.get(index);j--) {
							if(f[i][j-price.get(index)] != -1) {
								f[i][j] = max(f[i][j], f[i][j-price.get(index)] + value.get(index));
							}
							if(f[i-1][j-price.get(index)] != -1) {
								f[i][j] = max(f[i][j], f[i-1][j-price.get(index)] + value.get(index));
							}
						}
				}
			}
			if(f[k][m]<0) 
				System.out.println("Impossible");
			else
				System.out.println(f[k][m]);
		}
		s.close();
	}
}