package cmsc420.hextrie;


import java.util.Comparator;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import org.w3c.dom.Document;
import org.w3c.dom.Element;


/**
 * GuideNode - //TODO Class summary
 */
public class GuideNode<K, V> extends Node<K, V>
{
	private LinkedList<K> guides;

	private LinkedList<Node<K, V>> kids;
	private boolean type;

	public GuideNode(Comparator<K> comparator, boolean type)
	{
		super(comparator);
		this.type = type;
		this.guides = new LinkedList<K>();
		this.kids = new LinkedList<Node<K, V>>();
	}

	protected GuideNode(Comparator<K> comparator, List<K> guides, List<Node<K, V>> kids, boolean type)
	{
		super(comparator);
		this.type = type;
		this.guides = new LinkedList<K>(guides);
		this.kids = new LinkedList<Node<K, V>>(kids);
	}

	public boolean isFull()
	{
		if(type)
			return kids.size() >= 7;
			return kids.size() >= 6;
	}

	public boolean isEmpty()
	{
		return kids.size() == 0;
	}

	public void put(K key, V value)
	{
		int index = childIndex(key);

		kids.get(index).put(key, value);
	}

	public V get(K key)
	{
		return kids.get(childIndex(key)).get(key);
	}

	public V remove(K key)
	{
		int index = childIndex(key);
		return kids.get(index).remove(key);
	}

	public List<K> getGuides()
	{
		return guides;
	}

	public List<Node<K, V>> getKids()
	{
		return kids;
	}

	protected void split()
	{
		int halfGuides = guides.size() / 2;
		int halfKids = halfGuides + 1;
		GuideNode<K, V> left = new GuideNode<K, V>(comparator, guides.subList(0,
				halfGuides), kids.subList(0, halfKids), type);
		GuideNode<K, V> right = new GuideNode<K, V>(comparator, guides.subList(
				halfGuides + 1, guides.size()), kids.subList(halfKids, kids.size()), type);
		left.setLeft(getLeft());
		left.setRight(right);
		getLeft().setRight(left);
		left.setParent(getParent());
		for (Iterator<Node<K, V>> it = left.getKids().iterator(); it.hasNext();)
		{
			it.next().setParent(left);
		}

		right.setLeft(left);
		right.setRight(getRight());
		getRight().setLeft(right);
		right.setParent(getParent());
		for (Iterator<Node<K, V>> it = right.getKids().iterator(); it.hasNext();)
		{
			it.next().setParent(right);
		}

		parent.insertKey(guides.get(halfGuides), left, right);
	}

	protected void insertKey(K key, Node<K, V> left, Node<K, V> right)
	{
		int index = childIndex(key);
		guides.add(index, key);

		if (kids.isEmpty())
			kids.add(index, left);

		kids.set(index, left);
		kids.add(index + 1, right);

		if (isOverfull())
			split();
	}

	private int childIndex(K key)
	{
		Iterator<K> it = guides.iterator();
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
			return kids.size() > 7;
			return kids.size() > 6;
	}
	private boolean isSmall(){
		if(type)
			return kids.size() < 4;
		return kids.size() < 3;
	}
	@Override
	public void addToXmlDoc(Document doc, Element parent)
	{
		Element thisNode = doc.createElement("guide");
		for (int i = 0; i < guides.size(); ++i) {
			kids.get(i).addToXmlDoc(doc, thisNode);
			Element key = doc.createElement("key");
			key.setAttribute("value", guides.get(i).toString());
			thisNode.appendChild(key);
		}
		// Remember to add the last child.
		kids.getLast().addToXmlDoc(doc, thisNode);
		parent.appendChild(thisNode);
	}
	public void replaceGuide(K oldKey, K newKey){
		Iterator<K> it = guides.iterator();
		int i = 0;
		for (i = 0; it.hasNext(); i++)
		{
			if (comparator.compare(oldKey, it.next()) == 0)
			{
				break;
			}
		}
		if(i == guides.size()){
			if(parent !=null)
				parent.replaceGuide(oldKey, newKey);

		}else
			guides.set(i, newKey);
	}
	//Replaces old guide key with a new guide key
	public void replace(K newK){
		Iterator<K> it = guides.iterator();
		int i = 0;
		for (i = 0; it.hasNext(); i++)
		{
			if (comparator.compare(newK, it.next()) <= 0)
			{
				break;
			}
		}
		this.guides.set(i, newK);

	}
	public void replace(K oldK, K newK){
		Iterator<K> it = guides.iterator();
		int i = 0;
		for (i = 0; it.hasNext(); i++)
		{
			if (comparator.compare(oldK, it.next()) <= 0)
			{
				break;
			}
		}
		this.guides.set(i, newK);

	}
	/******* May Have to change if guideKeys are not updated properly with only existing keys. *****/

	public void delete(K key){
		Iterator<K> it = guides.iterator();
		int i = 0;
		for (i = 0; it.hasNext(); i++)
		{
			if (comparator.compare(key, it.next()) <= 0)
			{
				break;
			}
		}
		this.guides.remove(i);
		this.kids.remove(i+1);		
	}
	public void redistribute(){
		if(isSmall()){
			if(!borrow()){
				merge();
			}
		}		
	}

	private boolean borrow() {
		//Look to right
		GuideNode<K, V> right, left;

		if(this.right == null || this.right instanceof EndNode){
			right = null;
		}else{
			right = (GuideNode<K, V>)this.right;
		}
		if(this.left == null || this.left instanceof EndNode){
			left = null;
		}else{
			left = (GuideNode<K, V>)this.left;
		}
		GuideNode<K, V> parent = null;
		if(this.parent != null)
			parent = (GuideNode<K, V>) this.parent;
		//Borrow from right side
		if(right != null  && right.parent.equals(parent) && right.isMin()){
			int i;
			for(i = 0; i < parent.guides.size(); i++){
				if(comparator.compare(guides.getFirst(), parent.guides.get(i)) < 0)
					break;
			}
			Node<K, V> last = kids.getLast();
			K key = parent.guides.get(i);
			guides.add(key);
			kids.add(right.kids.getFirst());
			right.kids.removeFirst();
			
			//Set pointers
			kids.getLast().setParent(this);
			kids.getLast().setRight(right.kids.getFirst());
			right.kids.getFirst().setLeft(kids.getLast());
			kids.getLast().setLeft(last);
			last.setRight(kids.getLast());
			
			parent.guides.set(i, right.guides.getFirst());
			right.guides.removeFirst();
			return true;
		}else if(left != null && left.parent.equals(parent) && left.isMin()){
			int i;
			for(i = 0; i < parent.guides.size(); i++){
				if(comparator.compare(left.guides.getFirst(), parent.guides.get(i)) < 0)
					break;
			}
			Node<K,V> first = kids.getFirst();
			K key = parent.guides.get(i);
			guides.add(0, key);
			kids.add(0, left.kids.getLast());
			//Sets last guide key in sibling as new parent guide Key between two siblings
			left.kids.removeLast();
			left.kids.getLast().setRight(kids.getFirst());
			kids.getFirst().setLeft(left.kids.getLast());
			kids.getFirst().setRight(first);
			first.setLeft(kids.getFirst());
			kids.getFirst().setParent(this);
			
			parent.guides.set(i, left.guides.getLast());
			left.guides.removeLast();
			return true;
		}

		return false;
	}
	//TODO MUST CHECK IF THIS.RIGHT AND THIS.LEFT ARE ALL LINKED ON SAME LEVEL OR JUST LINKED UNDER THE SAME PARENT
	//Merge 2 siblings together
	private void merge() {
		GuideNode<K, V> right, left;

		if(this.right == null || this.right instanceof EndNode){
			right = null;
		}else{
			right = (GuideNode<K, V>)this.right;
		}
		if(this.left == null || this.left instanceof EndNode){
			left = null;
		}else{
			left = (GuideNode<K, V>)this.left;
		}
		GuideNode<K, V> parent = (GuideNode<K, V>) this.parent;
		int i;
		if(right != null){
			if(right.parent.equals(parent)){
				//Merge right with current node
				//Take parent guide key between two nodes and insert between the two merged guide keys.
				for(i = 0; i < parent.guides.size(); i++){
					if(comparator.compare(guides.getFirst(), parent.guides.get(i)) < 0)
						break;
				}
				guides.add(parent.guides.get(i));

				//add guide keys of sibling into current node
				guides.addAll(right.guides);
				//add left sibling keys and children before parent Key
				for(Node<K,V> kid: right.kids){
					kid.setParent(this);
				}
				//add children of sibling into current node
				kids.addAll(right.kids);
				//change pointers
				right.getRight().setLeft(this);
				this.setRight(right.getRight());

				//Delete parent's child pointer and guide Key for right sibling
				parent.guides.remove(i);
				parent.kids.remove(i+1);	
				if(parent != null)
					parent.redistribute();
				return;
			}
		}

		if(left != null){
			if(left.parent.equals(parent)){
				//merge the left with this node
				//Take parent guide key between two nodes and insert between the two merged guide keys.
				for(i = 0; i < parent.guides.size(); i++){
					if(comparator.compare(left.guides.getFirst(), parent.guides.get(i)) < 0)
						break;
				}
				guides.add(0, parent.guides.get(i));
				//add left sibling keys and children before parent Key
				guides.addAll(0, left.guides);
				for(Node<K,V> kid: left.kids){
					kid.setParent(this);
				}
				kids.addAll(0, left.kids);
				//Set pointers
				left.getLeft().setRight(this);
				this.setLeft(left.getLeft());
				//Set all child pointers to same parent
				
				//Delete parent's child pointer
				parent.guides.remove(i);
				parent.kids.remove(i);

				if(parent != null)
					parent.redistribute();
			}
		}
	}

	@Override
	public boolean isMin() {
		if(type){
			return this.kids.size() > 4;
		}
		else
			return this.kids.size() > 3;
	}
}