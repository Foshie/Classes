#!/usr/bin/env ruby

def exact(n, alphabet)
  if n == 0
    r = [""]
  else
    r = []
    s = exact(n - 1, alphabet)
    s.each do |i|
      alphabet.each do |j|
        r << i + j
      end
    end
  end
  r
end

def upto(n, alphabet)
  res = ""
  (1..n).each do |i|
    exact(i, alphabet).each do |s|
      res << s
      res << "\n"
    end
  end
  res
end

ARGV[0..-1].each do |file_name|
  file_name = File.basename(file_name)
  str = "inputs/str-"
  str << file_name
  e = file_name.scan(/(\w+)-(\d+)/)
  n = e[0][-1].to_i
  alphabet = []
  e[0][0].each_byte { |b|
    alphabet << b.chr
  }
  str_f = nil
  str_f = open("#{str}","w")
  str_f.write(upto(n,alphabet))
  str_f.close
end
