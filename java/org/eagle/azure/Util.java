package org.eagle.azure;

import java.io.InputStreamReader;
import java.io.InputStream;
import java.io.BufferedReader;
import java.io.IOException;

public class Util {
	public static String inputstream2string(InputStream inputstream) {
		BufferedReader br = new BufferedReader(
				new InputStreamReader(inputstream));
	 	String str = null;
		StringBuilder sb = new StringBuilder();
		try {
			while ((str = br.readLine()) != null) {
				sb.append(str);
				sb.append("\n");
			}			
		} catch (IOException e) {
			e.printStackTrace();
		}						

		return sb.toString();
	}
}
