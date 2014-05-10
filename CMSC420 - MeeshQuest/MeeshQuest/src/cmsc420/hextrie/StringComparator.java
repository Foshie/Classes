package cmsc420.hextrie;

import java.util.Comparator;

public class StringComparator implements Comparator<String>
    {
    	public StringComparator() {}
    	
        public int compare(String arg0, String arg1)
        {
            String str0 = (String) arg0;
            String str1 = (String) arg1;
            return str0.compareTo(str1);
        }
}