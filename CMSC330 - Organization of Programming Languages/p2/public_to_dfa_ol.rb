#!/usr/bin/env ruby

test_name = "to_dfa-ol-2"

print "test to_dfa on ol-2 "

command = "ruby tester.rb to_dfa inputs/nfa-ol-2 inputs/str-ol-2"

cmd_line = "ruby test.rb " + test_name + " \"#{command}\""
system(cmd_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

test_name = "to_dfa-ol-3"

print "test to_dfa on ol-3 "

command = "ruby tester.rb to_dfa inputs/nfa-ol-3 inputs/str-ol-3"

cmd_line = "ruby test.rb " + test_name + " \"#{command}\""
system(cmd_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

