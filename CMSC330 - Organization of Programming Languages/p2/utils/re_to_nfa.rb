#!/usr/bin/env ruby
require "parser.rb"
require "re.rb"
require "fa.rb"

def gen_re(file)
  p = Parser.new
  f = File.new(file,"r")
  rep = Array.new
  f.each { |line|
    rep << (p.parse line)
  }
  rep
end

def re_to_nfa(rep)
  s = ""
  rep.each { |r|
    nfa = NFA.of_re(r)
    ns = nfa.to_s
    f = ""
    ns.each { |line|
      if line =~ /Start/
        e = line.scan(/Start state: (\S+)/)
        s << "start #{e[0][0]}\n"
      elsif line =~ /Final/
        e = line.scan(/Final states: (\S+)/)
        f << "final #{e[0][0]}\n\n"
      else
        e = line.scan(/(\S+) -->(\w) (\S+)/)
        s << "trans #{e[0][0]} #{e[0][1]} #{e[0][2]}\n"
      end
    }
    s << f
  }
  s
end

ARGV[0..-1].each do |input_file_name|
  input_file_name = File.basename(input_file_name)
  re = "inputs/re-"
  re << input_file_name
  nfa = "inputs/nfa-"
  nfa << input_file_name
  rep = gen_re(re)
  nfa_f = nil
  nfa_f = open("#{nfa}","w")
  nfa_f.write(re_to_nfa(rep))
  nfa_f.close
end
