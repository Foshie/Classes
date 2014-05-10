class REEpsilon
  def ==(r)
    r.class == REEpsilon
  end
  alias :eql? :==
  def hash
    42
  end
  def to_s
    "()"
  end
  def check
	true
  end
  def trans
    return []
  end
end

class REConst
  attr_accessor :sym
  def initialize(c)
    @sym = c
  end
  def ==(r)
    r.class == REConst && r.sym == @sym
  end
  alias :eql? :==
  def hash
    @sym[0]
  end
  def to_s
    sym
  end
  def check
    false   # filled in for you
  end
  def trans
    [[@sym, REEpsilon.new]]   # filled in for you
  end
end

class REStar
  attr_accessor :expr
  def initialize(e)
    @expr = e
  end
  def ==(r)
    r.class == REStar && r.expr == @expr
  end
  alias :eql? :==
  def hash
    (@expr.hash * 13 + 2) & 0x7FFFFFFF
  end
  def to_s
    if @expr.class == REUnion or @expr.class == REConcat
      "(#{@expr.to_s})*"
    else
      "#{@expr.to_s}*"
    end
  end
  def check
    true
  end
  
  def trans
    eTrans = @expr.trans
	newTrans = []
	eTrans.each{|str, tr|
		con = REConcat.new(tr, REStar.new(@expr))
		newTrans.push([str, con])
	}
	return newTrans
  end
end

class REUnion
  attr_accessor :expr1
  attr_accessor :expr2
  def initialize(e1, e2)
    @expr1 = e1
    @expr2 = e2
  end
  def ==(r)
    r.class == REUnion && r.expr1 == @expr1 && r.expr2 == @expr2
  end
  alias :eql? :==
  def hash
    (@expr1.hash * 129 + @expr2.hash * 13 + 2) & 0x7FFFFFFF
  end
  def to_s
    "#{expr1}|#{expr2}"
  end
  def check
    if @expr1.check then
		true
	else
		@expr2.check
	end
  end
  def trans
	return (@expr1.trans + @expr2.trans).uniq
  end
end

class REConcat
  attr_accessor :expr1
  attr_accessor :expr2
  def initialize(e1, e2)
    @expr1 = e1
    @expr2 = e2
  end
  def ==(r)
    r.class == REConcat && r.expr1 == @expr1 && r.expr2 == @expr2
  end
  alias :eql? :==
  def hash
    (expr1.hash * 129 + @expr2.hash * 13 + 3) & 0x7FFFFFFF
  end
  def to_s
    if @expr1.class == REUnion
      r = "(#{@expr1})"
    else
      r = "#{@expr1}"
    end
    if @expr2.class == REUnion
      r += "(#{@expr2})"
    else
      r += "#{@expr2}"
    end
  end
  def check
	if @expr1.check then
		return @expr2.check
	else
		return false
	end
  end
  def trans
	if @expr1.check then
		s = @expr2.trans
	else
		s = []
	end
	e1trans = @expr1.trans
	setTrans = []
	e1trans.each{|str, currTrans|	
		con = REConcat.new(currTrans, @expr2)
		setTrans.push([str,con])
	}
	return (setTrans + s)
  end
end