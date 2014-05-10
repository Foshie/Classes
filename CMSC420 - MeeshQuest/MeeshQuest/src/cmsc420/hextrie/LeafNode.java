package cmsc420.hextrie;

import java.util.Comparator;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

/**
 * LeafNode - //TODO Class summary
 */
public class LeafNode<K, V> extends Node<K, V>
{
	private LinkedList<K> keys;

	private LinkedList<V> values;

	private int cardinality;
	private boolean type;

	public LeafNode(Comparator<K> comparator, int cardinality, boolean bstarMode)
	{
		super(comparator);
		this.type = bstarMode;
		this.keys = new LinkedList<K>();
		this.values = new LinkedList<V>();
		this.cardinality = cardinality;
	}

	protected LeafNode(Comparator<K> comparator, int cardinality, List<K> keys,
			List<V> values)
	{
		super(comparator);
		this.keys = new LinkedList<K>(keys);
		this.values = new LinkedList<V>(values);
		this.cardinality = cardinality;
	}

	public boolean isFull()
	{
		if(type && parent == null){
			return keys.size() >= cardinality + Math.floor(cardinality/3.0);
		}
		return keys.size() >= cardinality;
	}
	public boolean isSmall(){
		if(type){
			return keys.size() < Math.floor(2.0*cardinality/3);
		}
		return keys.size() < Math.ceil(cardinality /2.0);
	}
	public boolean isEmpty()
	{
		return keys.size() <= 0;
	}

	public int getCardinality()
	{
		return cardinality;
	}

	public void put(K key, V value)
	{
		int index = valueIndex(key);
		if (keys.contains(key))
		{
			values.set(index - 1, value);
		}
		else
		{
			keys.add(index, key);
			values.add(index, value);
		}

		if (isOverfull()) split();
	}

	public V get(K key)
	{
		if (keys.contains(key)) return values.get(keys.indexOf(key));
		return null;
	}

	public V remove(K key)
	{       
		K kCurr;
		V vCurr , toReturn = null;
		int i = 0;
		while(i < keys.size()){

			kCurr = keys.get(i);
			vCurr = values.get(i);
			if(comparator.compare(key, kCurr) == 0){
				keys.remove(kCurr);
				values.remove(vCurr);
				toReturn = vCurr;

				if(parent != null){
					if(keys.size() > 0){
						if(i == 0){
							//replace parent guide Key
							parent.replaceGuide(kCurr, keys.getFirst());
						}
						redistribute();
					}
				}
				break;
			}else{
				i++;
			}
		}
		return toReturn;
	}

	public List<K> getKeys()
	{
		return keys;
	}

	public List<V> getValues()
	{
		return values;
	}

	protected void split()
	{

		int halfKeys= keys.size() / 2;
		int halfKids = halfKeys;
		LeafNode<K, V> left = new LeafNode<K, V>(comparator, cardinality, keys.subList(0,
				halfKeys), values.subList(0, halfKids));
		LeafNode<K, V> right = new LeafNode<K, V>(comparator, cardinality, keys.subList(
				halfKeys, keys.size()), values.subList(halfKids, values.size()));
		left.setParent(getParent());
		left.setRight(right);
		left.setLeft(getLeft());
		if (getLeft() != null) left.getLeft().setRight(left);
		right.setParent(getParent());
		right.setLeft(left);
		right.setRight(getRight());
		if (getRight() != null) right.getRight().setLeft(right);
		parent.insertKey(right.keys.getFirst(), left, right);
	}

	//redistribute borrowing from sibling(adjacent node with same parent)
	protected boolean borrow(){
		LeafNode<K, V> right, left;

		if(this.right instanceof EndNode){
			right = null;
		}else{
			right = (LeafNode<K, V>)this.right;
		}
		if(this.left instanceof EndNode){
			left = null;
		}else{
			left = (LeafNode<K, V>)this.left;
		}
		GuideNode<K, V> parent = (GuideNode<K, V>)this.parent;
		if(right != null && right.parent.equals(parent) && right.isMin()){
			//borrow from right
			K k = (K) right.keys.get(0);
			V v = (V) right.values.get(0);
			keys.addLast(k);
			values.addLast(v);
			right.keys.removeFirst();
			right.values.removeFirst();
			K newParent = right.keys.getFirst();
			this.parent.replace(k, newParent);
			return true;
		}else if(left != null && left.parent.equals(parent)&& left.isMin()){
			K k = (K) left.keys.getLast();
			V v = (V) left.values.getLast();
			keys.add(0, k);
			values.add(0, v);
			left.keys.removeLast();
			left.values.removeLast();
			this.parent.replace(k);
			return true;
		}else
			return false;
	}
	//if redistribution fails, merge L and sibling
	protected void merge(){
		LeafNode<K, V> right, left;

		if(this.right instanceof EndNode){
			right = null;
		}else{
			right = (LeafNode<K, V>)this.right;
		}
		if(this.left instanceof EndNode){
			left = null;
		}else{
			left = (LeafNode<K, V>)this.left;
		}
		GuideNode<K, V> parent = (GuideNode<K, V>)this.parent;
		//Merge entries to the left
		if(left != null){
			if(this.parent.equals(left.parent)){
				left.keys.addAll(this.keys);
				left.values.addAll(this.values);
				//edit parent key
				K parentKey = (K) this.keys.getFirst();
				this.getRight().setLeft(left);
				left.setRight(getRight());
				//Delete Left child, current parent key
				parent.delete(parentKey);
				parent.redistribute();
				return;
			}
		}
		if(right != null){
			if(this.parent.equals(right.parent)){
				K parentKey = (K) right.keys.getFirst();
				//Merge keys from the right
				this.keys.addAll(right.keys);
				this.values.addAll(right.values);
				setRight(right.getRight());
				right.getRight().setLeft(this);
				//edit parent key
				parent.delete(right.keys.getFirst());
				parent.redistribute();
			}
		}
	}
	public boolean isMin() {
		if(type){
			return this.keys.size() > Math.floor((2.0*cardinality + 1)/3);
		}
		return this.keys.size() > Math.ceil(cardinality/2.0);
	}

	private int valueIndex(K key)
	{
		Iterator<K> it = keys.iterator();
		int i = 0;
		for (i = 0; it.hasNext(); i++)
		{
			if (comparator.compare(key, it.next()) < 0)
			{
				break;
			}
		}
		return i;
	}

	private boolean isOverfull()
	{
		if(type)
			return keys.size() > cardinality + Math.floor(cardinality/3.0);
		return keys.size() > cardinality;
	}

	protected Iterator<K> keyIterator()
	{
		return new KeyIterator();
	}

	private class KeyIterator implements Iterator<K>
	{
		private int entryNum = 0;

		public boolean hasNext()
		{
			return entryNum < keys.size();
		}

		public K next()
		{
			return keys.get(entryNum++);
		}

		public void remove()
		{
		}
	}

	@Override
	public void addToXmlDoc(Document doc, Element parent)
	{
		Element thisNode = doc.createElement("leaf");
		for (int i = 0; i < keys.size(); ++i) {
			Element entry = doc.createElement("entry");
			entry.setAttribute("key", keys.get(i).toString());
			entry.setAttribute("value", values.get(i).toString());
			thisNode.appendChild(entry);
		}
		parent.appendChild(thisNode);
	}

	@Override
	public void redistribute() {
		if(parent != null){
			if(isSmall()){
				if(!borrow()){
					merge();
				}
			}
		}
	}
}
