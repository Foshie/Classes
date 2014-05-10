package cmsc420.hextrie;
import java.util.Comparator;

import org.w3c.dom.Document;
import org.w3c.dom.Element;


public abstract class Node<K, V>
{
    protected Comparator<K> comparator;
    protected GuideNode<K, V> parent;
    protected Node<K, V> left, right;

    public Node(Comparator<K> comparator)
    {
        this.comparator = comparator;
    }

    public Comparator<K> getComparator()
    {
        return comparator;
    }
    
    public GuideNode<K, V> getParent()
    {
        return parent;
    }

    public void setParent(GuideNode<K, V> parent)
    {
        this.parent = parent;
    }

    public Node<K, V> getLeft()
    {
        return left;
    }

    public void setLeft(Node<K, V> left)
    {
        this.left = left;
    }

    public Node<K, V> getRight()
    {
        return right;
    }

    public void setRight(Node<K, V> right)
    {
        this.right = right;
    }

    public abstract boolean isFull();
    public abstract boolean isEmpty();
    
    public boolean contains(K key)
    {
        return get(key) != null;
    }

    public abstract void put(K key, V value);

    public abstract V get(K key);

    public abstract V remove(K key);
    
    protected final int cmp(K arg0, K arg1)
    {
        return comparator.compare(arg0, arg1);
    }

	public void addToXmlDoc(Document doc, Element parent)
	{}

	public abstract boolean isMin();
	public abstract void redistribute();
}