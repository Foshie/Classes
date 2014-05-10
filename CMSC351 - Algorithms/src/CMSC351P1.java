import java.io.*;
import java.*;
import java.util.*;
import java.util.Arrays;


public class CMSC351P1 {

	private int comps;
	public void resetComps() {comps=0;}
	public int getComps() {return comps;}

	public Comparable Select (Comparable[] TheList, int pos, int colSize, int colMed) {
		if (TheList.length < Math.pow(colSize,2) || colSize ==1){
				TheList = insertionSort(TheList, 0, TheList.length-1);
				return TheList[pos-1];
		}else{
			Comparable pivot = choosePivot(TheList, colSize, colMed);
			TheList = partition(TheList, pivot);
			//find q
			int q=-1;
			int dup = 0;
			for(int ind = 0; ind < TheList.length; ind++){
				if(TheList[ind].compareTo(pivot) ==0){
					comps++;
					if (q==-1)
						q= ind;
					dup++;
				}	
			}
			if (pos-1 >= q && pos-1 < q + dup)
				return pivot;
			else {
				if(pos-1 < q){
					Comparable[] newList = new Comparable[q];
					for(int i =0; i < q; i++){
						newList[i] = TheList[i];
					}
					return Select(newList, pos, colSize, colMed);
				}else{
					Comparable[] newList = new Comparable[TheList.length - q];
					for(int i = 0; i < TheList.length-q; i++)
						newList[i] = TheList[i+q];
					return Select(newList, pos-q, colSize, colMed);
				}
			}
		}	
	}
	
	public Comparable[] partition(Comparable[] arr, Comparable pivot){
		Comparable[] partition = new Comparable[arr.length];
		int i =0, index = 0;
		while (i < arr.length){
			if (arr[i].compareTo(pivot) < 0){
				partition[index] = arr[i];
				index++;
				comps++;
			}
			i++;
		}
		i=0;
		while(i < arr.length){
			if (arr[i].compareTo(pivot)==0){
				partition[index]=arr[i];
				index++;
				comps++;
			}
			i++;
		}
		i = 0;
		while(i < arr.length){
			if(arr[i].compareTo(pivot)>0){
				partition[index] = arr[i];
				index++;
				comps++;
			}
			i++;
		}
		return partition;
	}
	public Comparable[] insertionSort(Comparable[] arr, int start, int end) {
		int i, j;
		Comparable newValue;
		for (i = start +1; i <= end; i++) {
			newValue = arr[i];
			j = i;
			while (j > start && arr[j - 1].compareTo(newValue)> 0) {
            	comps++;
            	arr[j] = arr[j - 1];
                j--;
			}
			arr[j] = newValue;
		}
      return arr;
	}
	public Comparable choosePivot(Comparable[] A, int size, int med){
		int m = (int)Math.ceil((double)A.length/size);
		Comparable[] B = new Comparable[m];
		int start=0, end=size-1;
		//Partition A into columns of colSize
		for(int i = 0; i < m; i++){
			if(i == m-1)
				end = A.length-1;
			B[i] = findMed(A, start, end, med);
			start += size;
			end+= size;
		}
		
		return Select(B, (int)Math.ceil((double)(m)/2), size, med);
	}

	public Comparable findMed(Comparable[] A, int start, int end, int med){
		A = insertionSort(A, start, end);
		if (med-1 + start > end){
			return A[start];
		}
		return A[start + med-1];
	}
	
	
}