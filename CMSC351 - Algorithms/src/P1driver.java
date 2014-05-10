import java.io.*;
import java.*;
import java.util.Scanner;  //for input
import java.util.Arrays;
import java.util.Random;

public class P1driver {
	private static Scanner scanner = new Scanner( System.in );

	private static boolean VerifyMedian(Comparable[] list, int n, Comparable med) {
	Comparable[] templist = new Comparable[n];
		for (int i=0; i<n; i++) {
			templist[i] = list[i];
		}
		Arrays.sort(templist);
		/* Just in case you need to do a little debugging...
		PrintTheList(templist);
		System.out.println(
			n
			+ " " 
			+ (int)(Math.ceil(n/2.0))
			+ " " 
			+ templist[(int)(Math.ceil(n/2.0))]
		);
		*/
		System.out.println(templist[(int)(Math.ceil(n/2.0)) - 1]);
		return (templist[(int)(Math.ceil(n/2.0)) - 1].compareTo(med)==0);
	}

	private static void PrintTheList(Comparable[] list) {
	int n=list.length;
		for (int i=0; i<n; i++) {
			System.out.print(list[i]);
			if (i!=(n-1)) System.out.print(", ");
		}
		System.out.println();
	}

    public static void main(String [] args) throws Exception {
	Comparable med;
	
	System.out.print("Column size? ");
	int colSize = Integer.parseInt(scanner.nextLine());
	System.out.print("Position in Column? ");
	int colMed = Integer.parseInt(scanner.nextLine());
	int a;
	if(colMed <= colSize/2)
		a= 2*colSize-colMed;
	else
		a = 2*colSize-(colSize-colMed+1);
	int b = 2*colSize;
	
	
	System.out.println("T(n)=T(n/"+colSize+")+T("+a +"n/"+b +")+O(n)");



	System.out.print("How many elements? ");
	int n = Integer.parseInt(scanner.nextLine());

	Integer listToFindMedian[] = new Integer[n];

	for (int i=0; i<n; i++) {
		System.out.print("Enter value #"+(i+1)+": ");
		listToFindMedian[i] = 
			new Integer(Integer.parseInt(scanner.nextLine()));
	}
	/*
	System.out.println("colSize\t\tcolMed\t\tComparisons\n");
	for(int colSize = 3; colSize <= 10; colSize++){
		System.out.println("T(n)=T(n/"+colSize+")+T(3n/4)+O(n)");
		for(int colMed = 1; colMed <= colSize; colMed++){


	int n = 5000;Integer.parseInt(scanner.nextLine());

	Integer listToFindMedian[] = new Integer[n];
	Random generator = new Random(1);
	for (int i=0; i<n; i++) {
		System.out.print("Enter value #"+(i+1)+": ");
		listToFindMedian[i] = 
			new Integer(generator.nextInt(1000000));
	}
	Integer num = new Integer(2);
	VerifyMedian(listToFindMedian, n, num);
	*/
	CMSC351P1 YourSelectionObject = new CMSC351P1();	
	YourSelectionObject.resetComps();
	med = YourSelectionObject.Select(
					listToFindMedian, 
					(int)(Math.ceil(n/2.0)),
					colSize, colMed
	);
	System.out.println(
			"n=" + n + "  " +
			"Comparisons=" +
			YourSelectionObject.getComps()
	);
	if (VerifyMedian(listToFindMedian,n,med)) {
		System.out.println("Median!");
	}
	else {
		System.out.println("You returned: " + med + " which is not the median :(");
	}

	//System.out.println(colSize+"\t\t" + colMed +"\t\t" +YourSelectionObject.getComps());
    }//end main
    
}
