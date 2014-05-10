#!/usr/bin/env ruby

test_name = "to_dfa-ab-2"

print "test to_dfa on ab-2 "

command = "ruby tester.rb to_dfa inputs/nfa-ab-2 inputs/str-ab-2"

cmd_line = "ruby test.rb " + test_name + " \"#{command}\""
system(cmd_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

test_name = "to_dfa-ab-3"

print "test to_dfa on ab-3 "

command = "ruby tester.rb to_dfa inputs/nfa-ab-3 inputs/str-ab-3"

cmd_line = "ruby test.rb " + test_name + " \"#{command}\""
system(cmd_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

