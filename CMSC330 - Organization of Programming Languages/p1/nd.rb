#!/usr/bin/env ruby

f = File.new(ARGV[0], "r")
i = 1
f.each { |line|
  fp = line =~ /FAILED/
  if fp != nil
    line.insert(fp + "FAILED".length, " (#{i})")
    i += 1
  end
  puts line
}