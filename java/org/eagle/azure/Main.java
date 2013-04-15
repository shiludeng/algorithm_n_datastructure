package org.eagle.azure;

import java.io.FileInputStream;
import java.io.FileNotFoundException;

public class Main {
	public static void main(String[] args) {
		System.out.println("hello world!");
		
		try {
			System.out.print(Util.inputstream2string(
					new FileInputStream("../test_data/test.txt")));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
}
