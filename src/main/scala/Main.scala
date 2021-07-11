class BST {

  var size = 0;
  var root:BSTNode = Empty;
  def insert(value: Int, kind: String = "fruit"): Unit = this.root = insert(root,new Node(value, kind, Empty, Empty))
  def insert(node: Node): Unit = this.root = insert(root,node)
  def delete(value: Int): Unit = this.root = delete(root, value)
  def find(value: Int): Option[BSTNode] = find(root,value);
  def min(): Option[BSTNode] = min(root);
  def max(): Option[BSTNode] = max(root);
  def iterate(): Unit = {
    iterate(root).foreach(x => print(x.get.mkString(",") + "  "));
    print("\n")
  }
  def filterByType(kind: String): Unit = {
    iterate(root).filter(x => x.kind.get == kind).foreach(x => print(x.get.mkString(",") + "  "));
    print("\n")
  } 

  def filterByWeight(weight: Int): Unit = {
    iterate(root).filter(x => x.value.get > weight).foreach(x => print(x.get.mkString(",") + "  "));
    print("\n")
  } 

  def magnifyByType(kind: String, weight: Int): Unit = {
    iterate(root).filter(x => x.kind.get == kind).foreach {
      x: BSTNode => 
        // println("before everything")
        // iterate()
        this.root = insert(root, x.value.get + weight, kind)
        // println("after insertion")
        // iterate()
        this.root = delete(root, x.value.get)
        // println("after deletion")
        // iterate()
    }
  }


  def toList(): List[BSTNode] = iterate(root);
  

  // ================== private methods ======================
  private def insert(node: BSTNode, toInsert: Node): BSTNode = node match{
    case Empty => toInsert;
    case n: Node if(toInsert.v > n.v) => new Node(n.v, n.k, n.l, insert(n.r,toInsert) );
    case n: Node if(toInsert.v < n.v) => new Node(n.v, n.k, insert(n.l,toInsert) , n.r);
    case n: Node if(toInsert.v == n.v) => n;
  }

  private def insert(node: BSTNode, value: Int, kind: String): BSTNode = node match{
    case Empty => new Node(value, kind, Empty , Empty);
    case n: Node if(value > n.v) => new Node(n.v, n.k, n.l, insert(n.r,value, kind) );
    case n: Node if(value < n.v) => new Node(n.v, n.k, insert(n.l,value, kind) , n.r);
    case n: Node if(value == n.v) => n;
  }

  private def find(node: BSTNode, value: Int): Option[BSTNode] = node match{
    case Empty => None
    case n: Node => 
      if(n.v > value) find(n.r, value)
      else if(n.v < value) find(n.l, value)
      else Some(n)
  }

  private def min(node: BSTNode): Option[BSTNode] = node match{
    case Empty => None
    case n: Node => 
      if(n.l == Empty) Some(n) 
      else min(n.l)
  }

  private def max(node: BSTNode): Option[BSTNode] = node match{
    case Empty => None
    case n: Node => 
      if(n.r == Empty) Some(n) 
      else max(n.r)
  }

  private def iterate(node: BSTNode): List[BSTNode] = node match{
    case n: Node => iterate(n.left.get) ++  List(n) ++ iterate(n.right.get)
    case Empty => List();
  }

  private def delete(node: BSTNode, weight: Int): BSTNode = node match{
    case Empty => Empty
    case n: Node if(weight > n.v) => new Node(n.v, n.k, n.l, delete(n.r,weight) );
    case n: Node if(weight < n.v) => new Node(n.v, n.k, delete(n.l,weight) , n.r);
    case n: Node if(weight == n.v) => 
      // node is a leaft
      if(n.l == Empty && n.r == Empty)
        Empty

      else if(n.l == Empty)
        n.r
      
      else if(n.r == Empty)
        n.l

      else {
        var temp: BSTNode = min(n.r).get
        val temp2 = delete(n, temp.value.get)
        new Node(temp.value.get, temp.kind.get, temp2.left.get, temp2.right.get)
      }
  }
 
}


  trait BSTNode {
    def value: Option[Int] = this match {
      case n: Node => Some(n.v)
      case Empty  => None
    }

    def kind: Option[String] = this match {
      case n: Node => Some(n.k)
      case Empty  => None
    }

    def left: Option[BSTNode] = this match {
      case n: Node => Some(n.l)
      case Empty  => None
    }

    def right: Option[BSTNode] = this match {
      case n: Node => Some(n.r)
      case Empty  => None
    }
    
    def get: Array[Any] = this match {
      case n: Node => Array(n.v,n.k)
      case Empty  => Array(None,None)
    }
  }

  class Node(val v: Int, val k: String, val l: BSTNode, val r: BSTNode) extends BSTNode  
  class Fruit(override val v: Int, override val k: String,override val l: BSTNode,override val r: BSTNode) extends Node(v,k,l,r)   

  class OvalFruit(override val v: Int, override val k: String,override val l: BSTNode,override val r: BSTNode) extends Fruit(v,k,l,r)   
  class Apple(override val v: Int, override val k: String,override val l: BSTNode,override val r: BSTNode) extends OvalFruit(v,k,l,r)   
  class Avocado(override val v: Int, override val k: String,override val l: BSTNode,override val r: BSTNode) extends OvalFruit(v,k,l,r)   

  class TinyFruit(override val v: Int, override val k: String,override val l: BSTNode,override val r: BSTNode) extends Fruit(v,k,l,r)   
  class Grapes(override val v: Int, override val k: String,override val l: BSTNode,override val r: BSTNode) extends TinyFruit(v,k,l,r)   
  class Berries(override val v: Int, override val k: String,override val l: BSTNode,override val r: BSTNode) extends TinyFruit(v,k,l,r)   
  class BlueBerries(override val v: Int, override val k: String,override val l: BSTNode,override val r: BSTNode) extends Berries(v,k,l,r)   
  class RedBerries(override val v: Int, override val k: String,override val l: BSTNode,override val r: BSTNode) extends Berries(v,k,l,r)   
  
  case object Empty extends BSTNode



object Main extends App {
  println("Hello, World!")
  
  var k = new BST()
  
  k.insert(1, "fruit");
  
  k.insert(10, "nice");
  k.insert(10, "nice");

  k.insert(-5, "fruit");
  k.insert(0, "nice");
  
  
  k.iterate()
  k.filterByWeight(-1)
  k.filterByType("fruit")

  k.iterate()
  k.magnifyByType("fruit", 2)
  k.iterate()
}
