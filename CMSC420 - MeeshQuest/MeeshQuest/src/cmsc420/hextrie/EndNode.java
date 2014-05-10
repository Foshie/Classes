package cmsc420.hextrie;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

public class EndNode<K, V> extends Node<K, V>
{
    public EndNode()
    {
        super(null);
    }
    
    /* (non-Javadoc)
     * @see Node#isFull()
     */
    public boolean isFull()
    {
        // TODO Auto-generated method stub
        return false;
    }

    /* (non-Javadoc)
     * @see Node#isEmpty()
     */
    public boolean isEmpty()
    {
        // TODO Auto-generated method stub
        return false;
    }

    /* (non-Javadoc)
     * @see Node#size()
     */
    public int size()
    {
        // TODO Auto-generated method stub
        return 0;
    }

    /* (non-Javadoc)
     * @see Node#put(java.lang.Object, java.lang.Object)
     */
    public void put(K key, V value)
    {
    // TODO Auto-generated method stub

    }

    /* (non-Javadoc)
     * @see Node#get(java.lang.Object)
     */
    public V get(K key)
    {
        // TODO Auto-generated method stub
        return null;
    }

    /* (non-Javadoc)
     * @see Node#remove(java.lang.Object)
     */
    public V remove(K key)
    {
        return null;
    }

    /* (non-Javadoc)
     * @see Node#accept(BPTreeVisitor)
     */
//    public void accept(BSTrieVisitor visitor)
//    {
//    // TODO Auto-generated method stub
//
//    }

	@Override
	public void addToXmlDoc(Document doc, Element parent) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public boolean isMin() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void redistribute() {
		// TODO Auto-generated method stub
		
	}

}
