class NFA
  # A non-deterministic (or deterministic) finite automaton

  # The states of the automaton are arbitrary Ruby objects.  For
  # example, they could be integers, strings, or regular expressions.

  # The automaton is represented by three fields:
  #
  #  @start -- the initial state
  #  @final -- a set of final states (an array)
  #  @delta -- the transition function
  #    In Java notation, @delta has type Hash<State,Hash<Sym,Array<State>>>,
  #    i.e., @delta[state] is itself a hash, and @delta[state][sym]
  #    is an array containing all possible states to transition to
  #    from "state" upon seeing "sym" from the input.
  
  attr_accessor :delta
  attr_accessor :final
  attr_accessor :start
  def initialize
    @delta = Hash.new  # transition function
    @final = []  # final states
    @start = nil   # start state
  end
  def set_start(s)
    @start = s
  end
  def make_final(s)
    @final << s
  end
  def add_trans(s1, sym, s2)  # sym should be a string
    fail "sym must be a single character" if sym.length != 1
    @delta[s1] = Hash.new if not (@delta[s1])
    if (@delta[s1][sym])
      @delta[s1][sym] << s2
    else
      @delta[s1][sym] = [s2]
    end
  end
  def states
    r = [@start] + @final
    @delta.each { |s1, h|
      r << s1
      h.each { |sym, s2s| r += s2s }
    }
    r.uniq
  end
  def to_s
    r = "Start state: #{@start}\n"
    r << "Final states: #{@final.join(" ")}\n"
    @delta.each { |s1, h|
      h.each { |sym, s2s|
        s2s.each { |s2|
          r << "#{s1} -->#{sym} #{s2}\n"
        }
      }
    }
    r
  end
 def accept?(s)
    cur = [@start]
    pos = 0
    while pos < s.length
      res = []
      (cur.map { |state|
         if @delta[state] then
           @delta[state][s[pos].chr]
         else
           []
         end }).each { |move|
        if move then
          res.concat(move)
        end
      }
      cur = res
      pos = pos + 1
    end
	#puts "curr: #{cur.inspect}"
	#puts "final: #{@final.inspect}"
    cur.find { |state|
		@final.include? state }
  end

  ####################################################

  # Return the NFA corresponding to regular expression r
  def NFA.of_re(r)
    # FILL IN
    toReturn = NFA.new
	alph = []
	nStates = [r]
	qStates = [r]
	toReturn.set_start(r) #create initial state
	while nStates.size != 0
		f = nStates.pop 	#pick a state to process, remove it from N
		if f.check then
			toReturn.make_final(f) #@final?????????**********************
		end
		# compute transitions
		f.trans.each{|a, prime|
			if qStates.include?(prime) == false then
				qStates =qStates + [prime]
				nStates = nStates + [prime]
			end
			toReturn.add_trans(f, a, prime)
		}
	end
	return toReturn
  end

  # Return true if self is actually a DFA
  def is_dfa?
    # FILL IN
	self.delta.values.each{|secHash|
		secHash.values.each{|arr|
			if arr.size > 1
				return false
			end
		}
	}
	return true
  end

  # Return a new NFA that accepts the same language as self,
  # but is a DFA.  Self is not modified
  def to_dfa
    # FILL IN
	input = self
    output = NFA.new
	output.set_start([input.start])
	rStates = [output.start]
	marked = []
	# get Sigma
	sigma  = []
	input.delta.values.each{|hash|
		hash.keys.each{|sym|
		sigma << sym
		}
	}
	sigma =sigma.uniq
	r = rStates[0]
	i = 0
	
	while marked.include?(r) == false
		marked.push(r) #mark r
		sigma.each{|a|
			move = []
			if r != nil then
				r.each{|q|
					if input.delta[q] != nil then
						
						if input.delta[q][a] != nil then
							input.delta[q][a].each{|sta|
								move << sta
							}
						end
					end
				}
					if rStates.include?(move) == false then
					rStates << move
				end
				output.add_trans(r, a, move)
			end
		}
		i+=1
		x = 0
		if r != nil then
		r.each{|s|
			if input.final.include?(s) then
				x = 1
			end
		}
		if x == 1 then
			output.make_final(r)
		end
		end
		r = rStates[i]
	end
	return output
  end
  # returns the set of states reachable from p using exactly one transition on a

end