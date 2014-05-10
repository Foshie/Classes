package cmsc420.meeshquest.part3;

import cmsc420.xml.XmlUtility;
import java.io.*;
import javax.xml.parsers.ParserConfigurationException;
import org.w3c.dom.*;
import org.xml.sax.*;

public class TestSuite {
    public static void main(String[] args) {
        //String directory = "C:\\doc\\College\\CMSC420\\Project\\tests\\pm3\\distrib";
    	String directory = "C:\\doc\\College\\CMSC420\\Project\\tests\\part2-testfiles\\btree";
    	//String directory = "C:\\doc\\College\\CMSC420\\Project\\tests\\part2-student";
        int count = 0, passed = 0;
        
        TestSuite ts = new TestSuite();
        File files[] = new File(directory).listFiles();
        try {
            for (int i = 0; i < files.length; ++i) {
                String pattern = ".input.xml";
                if (files[i].getName().toLowerCase().endsWith(pattern)) {
                    String path = files[i].getAbsolutePath();
                    if (ts.compare(path.substring(0, path.length() - pattern.length()))) {
                        ++passed;
                    }
                    ++count;
                }
            }
        }
        catch(SAXParseException e) {
            System.err.println("line=" + e.getLineNumber() + " col=" + e.getColumnNumber() + " pubID=" + e.getPublicId() + " sysid=" + e.getSystemId());
            e.printStackTrace();
        }
        catch(Exception e) {
            e.printStackTrace();
        }

        System.out.println(passed + "/" + count + " passed");
    }
    
    private class ID {
        public int id = -1;
        public String toString() {
            return id == -1 ? "?" : "" + id;
        }
    }
    
    private boolean mismatch(String s, Node n1, Node n2, ID id) {
        System.out.println("mismatch(id=" + id + ", " + s + "): " + n1.getNodeName() + ", " + n2.getNodeName());
        return false;
    }
    
    private boolean compare_nodes(Node n1, Node n2, ID id) {
        if(n1.getNodeName().equals(n2.getNodeName())) {
            // compare attributes
            NamedNodeMap a1 = n1.getAttributes();
            NamedNodeMap a2 = n2.getAttributes();
            if((a1 == null || a2 == null) && a1 != a2)
                return mismatch("one tag has no attributes, the other does", n1, n2, id);
            
            if(a1 != null) {
                if(a1.getLength() != a2.getLength()) {
                    return mismatch("different number of attributes for this tag", n1, n2, id);
                }
                for (int i = 0; i < a1.getLength(); ++i) {
                    if(!a1.item(i).getNodeName().equals(a2.item(i).getNodeName()) ||
                       !a1.item(i).getNodeValue().equals(a2.item(i).getNodeValue()))
                        return mismatch("indexing from zero, the " + i + "th attribute is different", n1, n2, id);
                    
                }
            }
            return true;
        }
        return mismatch("name", n1, n2, id);
    }
    
    private boolean compare_nodes_rec(Node n1, Node n2, ID id) {
        // See if we've reached a command ID
        if(n1 instanceof Element) {
            Element ex = (Element)n1;
            if(ex.hasAttribute("id"))
                id.id = Integer.parseInt(ex.getAttribute("id"));
        }        
        if(!compare_nodes(n1, n2, id))
            return false;
        
        // Compare children
        NodeList nl1 = n1.getChildNodes();
        NodeList nl2 = n2.getChildNodes();
        int len1 = nl1.getLength();
        int len2 = nl2.getLength();
        int len = len1 < len2 ? len1 : len2;
        
        if(len1 != len2)
            return mismatch("different number of child elements", n1, n2, id);
        
        for(int i = 0; i < len; ++i) {
            Node c1 = nl1.item(i);
            Node c2 = nl2.item(i);
            
            if(!compare_nodes_rec(c1, c2, id))
                return mismatch("", n1, n2, id);
        }
        return true;
    }
    
    private boolean compare_xml(File a, File b) throws SAXException, IOException, ParserConfigurationException {
        Document adoc = XmlUtility.parse(a);
        Document bdoc = XmlUtility.parse(b);
        
        return compare_nodes_rec(adoc.getDocumentElement(), bdoc.getDocumentElement(), new ID());
    }
    
    public boolean compare(String prefix) throws FileNotFoundException, IOException, SAXException, ParserConfigurationException {
        File testresults = new File(prefix + ".testresults.xml");
    	testresults.delete();
     	testresults.createNewFile();

        PrintStream ps = new PrintStream(testresults), bakOut = System.out;
        InputStream is = new FileInputStream(prefix + ".input.xml"), bakIn = System.in;
        
        System.out.println("testing " + prefix);
        
        // Output to a tmp file and input from the input file
        System.setOut(ps);
        System.setIn(is);
        
        // Run the main program
        MeeshQuest.main(null);
        
        // Revert stdin/out
        System.setOut(bakOut);
        System.setIn(bakIn);
        
        // Compare the results in the tmp file to the correct output
        boolean res = compare_xml(new File(prefix + ".output.xml"), testresults);
        
        if(res)
            System.out.println("PASSED");
        else
            System.out.println("FAILED");
        
        return res;
    }
}