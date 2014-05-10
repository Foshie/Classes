#!/usr/bin/env ruby

test_name = "is_dfa-nfa-ol-2"

print "test is_dfa on nfa-ol-2 "

command = "ruby tester.rb is_dfa inputs/nfa-ol-2"

cmd_line = "ruby test.rb " + test_name + " \"#{command}\""
system(cmd_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

test_name = "is_dfa-nfa-ol-3"

print "test is_dfa on nfa-ol-3 "

command = "ruby tester.rb is_dfa inputs/nfa-ol-3"

cmd_line = "ruby test.rb " + test_name + " \"#{command}\""
system(cmd_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

