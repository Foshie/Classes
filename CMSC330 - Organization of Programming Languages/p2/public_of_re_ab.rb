#!/usr/bin/env ruby

test_name = "of_re-ab-2"

print "test of_re on ab-2 "

command = "ruby tester2.rb of_re inputs/re-ab-2 inputs/str-ab-2"

cmd_line = "ruby test.rb " + test_name + " \"#{command}\""
system(cmd_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

test_name = "of_re-ab-3"

print "test of_re on ab-3 "

command = "ruby tester2.rb of_re inputs/re-ab-3 inputs/str-ab-3"

cmd_line = "ruby test.rb " + test_name + " \"#{command}\""
system(cmd_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

