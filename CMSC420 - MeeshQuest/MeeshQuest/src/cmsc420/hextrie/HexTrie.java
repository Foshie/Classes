package cmsc420.hextrie;


import java.lang.reflect.Array;
import java.util.Collection;
import java.util.Comparator;
import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.Set;
import java.util.SortedMap;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

/**
 *  -
 */
@SuppressWarnings("unchecked")
public class HexTrie<K, V> implements SortedMap<K, V>
{
	private RootNode root;
	private int size = 0;
	private final int cardinality;
	private int height = 1;
	private final boolean bstarMode;

	protected int modCount = Integer.MIN_VALUE;

	public HexTrie(Comparator<K> comparator, int cardinality, boolean bstarMode)
	{
		this.bstarMode = bstarMode;
		root = new RootNode(comparator, cardinality, bstarMode);
		this.cardinality = cardinality;
	}
	public HexTrie(Comparator<K> comparator, int cardinality)
	{

		this.bstarMode = false;
		root = new RootNode(comparator, cardinality, bstarMode);
		this.cardinality = cardinality;
	}
	public Comparator comparator()
	{
		return root.getComparator();
	}

	public K firstKey()
	{
		if (isEmpty())
			throw new NoSuchElementException();

		return root.getFirstLeaf().getKeys().get(0);
	}

	public SortedMap headMap(Object arg0)
	{
		throw new UnsupportedOperationException();
	}

	public K lastKey()
	{
		if (isEmpty())
			throw new NoSuchElementException();

		LeafNode<K, V> l = root.getLastLeaf();
		List<K> keys = l.getKeys();
		return keys.get(keys.size() - 1);
	}

	public SortedMap<K, V> subMap(K arg0, K arg1)
	{
		throw new UnsupportedOperationException();
	}

	public SortedMap<K, V> tailMap(K arg0)
	{
		throw new UnsupportedOperationException();
	}

	public void clear()
	{
		root = new RootNode(root.getComparator(), cardinality, this.bstarMode);
		size = 0;
		modCount++;
	}

	public boolean containsKey(Object key)
	{
		if (key == null)
			throw new NullPointerException();

		return root.contains((K) key);
	}

	public boolean containsValue(Object arg0)
	{
		Iterator it = entrySet().iterator();
		while (it.hasNext())
		{
			if (((Entry) it.next()).getValue().equals(arg0))
				return true;
		}
		return false;
	}

	public Set<Map.Entry<K, V>> entrySet()
	{
		return new EntrySet();
	}

	public V get(Object key)
	{
		if (key == null)
			throw new NullPointerException();

		return root.get((K) key);
	}

	public boolean isEmpty()
	{
		return size == 0;
	}

	public Set keySet()
	{
		throw new UnsupportedOperationException();
	}

	public V put(K key, V value)
	{
		if (key == null)
			throw new NullPointerException();

		V oldVal = get(key);
		if (!root.contains(key) && size != Integer.MAX_VALUE)
			size++;

		root.put(key, value);
		modCount++;
		return oldVal;
	}

	public void putAll(Map<? extends K, ? extends V> entries)
	{
		Iterator<? extends K> it = entries.keySet().iterator();
		K key;
		while (it.hasNext())
		{
			key = it.next();
			put(key, entries.get(key));
		}
	}

	public V remove(Object obj)
	{
		if(obj == null)
			throw new NullPointerException();
		V toReturn = root.remove((K) obj);
		modCount++;
		if(toReturn != null)
			size--;
		return toReturn;
	}

	public int size()
	{
		return size;
	}

	public Collection<V> values()
	{
		throw new UnsupportedOperationException();
	}

	public boolean equals(Object arg0)
	{
		if (arg0 instanceof Map)
		{
			Map m1 = (Map) arg0;
			return m1.entrySet().equals(entrySet());
		}
		return false;
	}

	public int hashCode()
	{
		return entrySet().hashCode();
	}

	private class RootNode extends Node<K, V>
	{
		private Node<K, V> me;
		private EndNode<K, V> first;
		private EndNode<K, V> last;
		private int cardinality;
		private boolean type;
		public RootNode(Comparator<K> comparator, int cardinality, boolean bstarMode)
		{
			super(comparator);
			type = bstarMode;
			this.cardinality = cardinality;
			LeafNode<K, V> tmp = new LeafNode<K, V>(comparator, this.cardinality, bstarMode);
			this.first = new EndNode<K, V>();
			this.last = new EndNode<K, V>();
			this.first.setRight(tmp);
			this.last.setLeft(tmp);
			tmp.setLeft(first);
			tmp.setRight(last);
			this.me = tmp;
		}

		public boolean contains(K key)
		{
			return me.contains(key);
		}

		public V get(K key)
		{
			return me.get(key);
		}

		public V remove(K key)
		{
			V toReturn = me.remove(key);
			if(isSmall()){
				redistribute();
			}
			return toReturn;
		}

		public Comparator<K> getComparator()
		{
			return me.getComparator();
		}

		public GuideNode<K, V> getParent()
		{
			return me.getParent();
		}

		public boolean isFull()
		{
			return me.isFull();
		}

		public boolean isEmpty()
		{
			return me.isEmpty();
		}

		public void put(K key, V value)
		{
			if (isFull())
			{
				// Add a new root node before insertion. If after insertion the new
				// root is not needed (i.e, it has only one kid), delete it.
				GuideNode<K, V> n = new GuideNode<K, V>(me.getComparator(), this.type);
				n.setLeft(new EndNode<K, V>());
				n.setRight(new EndNode<K, V>());
				n.getLeft().setRight(n);
				n.getRight().setLeft(n);
				me.setParent(n);
				me.put(key, value);
				if (!n.isEmpty())
				{
					me = n;
					height++;
				}
				else
					me.setParent(null);
			}
			else
			{
				me.put(key, value);
			}
		}

		public void setParent(GuideNode<K, V> parent)
		{
			me.setParent(parent);
		}

		public LeafNode<K, V> getFirstLeaf()
		{
			return (LeafNode<K, V>) first.getRight();
		}

		public LeafNode<K, V> getLastLeaf()
		{
			return (LeafNode<K, V>) last.getLeft();
		}

		public void addToXmlDoc(Document doc, Element parent) {
			me.addToXmlDoc(doc, parent);
		}

		public boolean isMin() {
			return me.isMin();
		}

		//Collapse root when it only has one child
		public void redistribute() {
			if(me instanceof GuideNode){
				if(isSmall()){
					Node<K,V> node = ((GuideNode<K,V>)me).getKids().get(0);
					node.setParent(null);
					me = node;
				}
			}

		}

		private boolean isSmall() {
			if(me instanceof GuideNode){
				return ((GuideNode<K,V>)me).getKids().size() <2;
			}
			return true;
		}
	}

	private class Entry implements Map.Entry<K, V>
	{
		private K key;

		public Entry(K key)
		{
			this.key = key;
		}

		public K getKey()
		{
			return key;
		}

		public V getValue()
		{
			return get(key);
		}

		public V setValue(V arg0)
		{
			return put(key, arg0);
		}

		public boolean equals(Object arg0)
		{
			if (arg0 instanceof Map.Entry)
			{
				Map.Entry e2 = (Map.Entry) arg0;
				return (key == null ? e2.getKey() == null : key.equals(e2
						.getKey()))
						&& (getValue() == null ? e2.getValue() == null
						: getValue().equals(e2.getValue()));
			}
			return false;
		}

		public int hashCode()
		{
			return (key == null ? 0 : key.hashCode())
					^ (getValue() == null ? 0 : getValue().hashCode());
		}

	}

	private class EntrySet implements Set<Map.Entry<K, V>>
	{
		public boolean add(Map.Entry<K, V> arg0)
		{
			throw new UnsupportedOperationException();
		}

		public boolean addAll(Collection<? extends Map.Entry<K, V>> arg0)
		{
			throw new UnsupportedOperationException();
		}

		public void clear()
		{
			HexTrie.this.clear();
		}

		public boolean contains(Object entry)
		{
			Map.Entry e1 = (Map.Entry) entry;
			Object value = HexTrie.this.get(e1.getKey());
			return e1.getValue() == null ? value == null : e1.getValue()
					.equals(value);
		}

		public boolean containsAll(Collection<?> entries)
		{
			Iterator it = entries.iterator();
			boolean flag = true;
			while (it.hasNext())
			{
				flag = flag && contains(it.next());
			}
			return flag;
		}

		public boolean isEmpty()
		{
			return HexTrie.this.isEmpty();
		}

		public Iterator iterator()
		{
			return new EntryIterator();
		}

		public boolean remove(Object entry)
		{
			if (entry instanceof Map.Entry)
				return HexTrie.this.remove(((Entry) entry).getKey()) != null;
			return false;
		}

		public boolean removeAll(Collection entries)
		{
			Iterator it = entries.iterator();
			boolean flag = false;
			while (it.hasNext())
			{
				flag = remove(it.next()) || flag;
			}
			return flag;
		}

		public boolean retainAll(Collection entries)
		{
			Iterator it = new EntryIterator();
			boolean flag = false;
			while (it.hasNext())
			{
				if (!entries.contains(it.next()))
				{
					it.remove();
					flag = true;
				}
			}
			return flag;
		}

		public int size()
		{
			return HexTrie.this.size();
		}

		public Object[] toArray()
		{
			Object[] arr = new Object[size()];
			Iterator it = new EntryIterator();
			for (int i = 0; it.hasNext(); i++)
			{
				arr[i] = it.next();
			}
			return arr;
		}

		public Object[] toArray(Object[] array)
		{
			if (array.length < size())
				array = (Object[]) Array.newInstance(array.getClass()
						.getComponentType(), size());

			Iterator it = new EntryIterator();
			for (int i = 0; it.hasNext(); i++)
			{
				array[i] = it.next();
			}
			return array;
		}

		public boolean equals(Object arg0)
		{
			if (arg0 instanceof Set)
			{
				Set s1 = (Set) arg0;
				if (s1.size() != size())
					return false;

				Iterator it = s1.iterator();
				while (it.hasNext())
				{
					if (!contains(it.next()))
						return false;
				}
				return true;
			}
			return false;
		}

		public int hashCode()
		{
			Iterator it = iterator();
			int hashCode = 0;
			while (it.hasNext())
			{
				hashCode += it.next().hashCode();
			}
			return hashCode;
		}

		private class EntryIterator implements Iterator<Map.Entry<K, V>>
		{
			private Entry curr, prev;
			private LeafNode<K, V> currNode;
			private Iterator<K> it;
			private int modCount = HexTrie.this.modCount;

			public EntryIterator()
			{
				if (HexTrie.this.isEmpty())
					return;

				this.currNode = root.getFirstLeaf();
				this.it = currNode.keyIterator();

				while (curr == null
						|| HexTrie.this.comparator().compare(curr.getKey(),
								HexTrie.this.firstKey()) < 0)
				{
					if (!it.hasNext())
					{
						if (currNode.getRight() instanceof EndNode)
							return;

						currNode = (LeafNode) currNode.getRight();
						it = currNode.keyIterator();
						continue;
					}

					curr = new Entry(it.next());
				}
			}

			public boolean hasNext()
			{
				return curr != null;
			}

			public Map.Entry<K, V> next()
			{
				if (modCount != HexTrie.this.modCount)
					throw new ConcurrentModificationException();

				if (curr == null)
					throw new NoSuchElementException();

				if (!it.hasNext() && !(currNode.getRight() instanceof EndNode))
				{
					currNode = (LeafNode) currNode.getRight();
					it = currNode.keyIterator();
					return next();
				}

				prev = curr;
				if (it.hasNext() && curr != null && HexTrie.this.lastKey() != null
						&& cmp(curr.getKey(), HexTrie.this.lastKey()) < 0)
					curr = new Entry(it.next());
				else
					curr = null;

				return prev;
			}

			public void remove()
			{
				HexTrie.this.remove(prev.getKey());
			}

			private int cmp(Object o1, Object o2)
			{
				return HexTrie.this.comparator().compare(o1, o2);
			}
		}
	}



	/**
	 * Attaches this tree as xml to the output node in the document results
	 * 
	 * @param outputNode
	 * @param results
	 */
	public void addToXmlDoc(Document doc, Element outputNode) {
		Element trie = doc.createElement("HexTrie");
		trie.setAttribute("cardinality", Integer.toString(size()));
		// TODO: Fix height attribute if we decide we care.
		//		tsTrie.setAttribute("height", Integer.toString(-1));
		//		tsTrie.setAttribute("bpOrder", Integer.toString(order));
		trie.setAttribute("leafOrder", Integer.toString(cardinality));
		String mode;
		if(bstarMode)
			mode = "Bstar";
		else
			mode = "Bplus";
		trie.setAttribute("type", mode);
		root.addToXmlDoc(doc, trie);
		outputNode.appendChild(trie);
	}
}
