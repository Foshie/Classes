#!/usr/bin/env ruby
require "parser.rb"
#require "utils/re.rb" # canonical version
require "re.rb"
require "fa.rb"

$rep = Array.new

def gen_re(file)
  p = Parser.new
  f = File.new(file,"r")
  f.each { |line|
    $rep << (p.parse line)
  }
end

def check
  $rep.each { |r|
    puts r.check
  }
end

def print_trans(e1, trans)
  s = trans.sort { |a, b|
    a.to_s <=> b.to_s
  }
  s.uniq.each { |arr|
    a, e2 = arr[0], arr[1]
    puts "#{e1} --#{a}--> #{e2}"
  }
end

def trans
  $rep.each { |r|
    print_trans(r, r.trans)
    puts ""
  }
end

def toBool(n)
  if n
    true
  else
    false
  end
end

def of_re(file)
  str = Array.new
  f = File.new(file,"r")
  f.each { |line|
    s = line.scan(/(\S+)/)
    str << s[0][0]
  }
  $rep.each { |r|
    nfa = NFA.of_re(r)
    str.each { |s|
      puts s if nfa.accept? s
      yours = toBool((nfa.accept? s))
      rubys = toBool(s =~ /^(#{r.to_s})$/)
      fail "\"#{s}\" => #{yours}, #{rubys}" if yours != rubys
    }
    puts ""
  }
end

$nfa = Array.new

def gen_nfa(file)
  f = File.new(file,"r")
  n = nil
  f.each { |line|
    if line =~ /start/
      e = line.scan(/start (\S+)/)
      n = NFA.new
      n.set_start e[0][0] 
    elsif line =~ /trans/
      e = line.scan(/trans (\S+) (\w) (\S+)/)
      n.add_trans(e[0][0],e[0][1],e[0][2])
    elsif line =~ /final/
      e = line.scan(/final (\S+)/)
      n.make_final e[0][0]
      $nfa << n
      n = nil
    end
  }
end

def is_dfa
  $nfa.each { |fa|
    puts fa.is_dfa?
  }
end

def to_dfa(file)
  str = Array.new
  f = File.new(file,"r")
  f.each { |line|
    s = line.scan(/(\S+)/)
    str << s[0][0]
  }
  $nfa.each { |nfa|
    dfa = nfa.to_dfa
    str.each { |s|
      puts s if dfa.accept? s
      before = toBool((nfa.accept? s))
       after = toBool((dfa.accept? s))
      fail "\"#{s}\" => #{before}, #{after}" if before != after
    }
    puts ""
  }
end

# ARGV[0] => def, ARGV[1] => RE file, ARGV[2] => STR file
case ARGV[0]
when "check"
  gen_re(ARGV[1])
  check
when "trans"
  gen_re(ARGV[1])
  trans
when "of_re"
  gen_re(ARGV[1])
  of_re(ARGV[2])
when "is_dfa"
  gen_nfa(ARGV[1])
  is_dfa
when "to_dfa"
  gen_nfa(ARGV[1])
  to_dfa(ARGV[2])
end

