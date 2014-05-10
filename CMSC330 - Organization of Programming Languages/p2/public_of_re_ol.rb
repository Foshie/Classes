#!/usr/bin/env ruby

test_name = "of_re-ol-2"

print "test of_re on ol-2 "

command = "ruby tester2.rb of_re inputs/re-ol-2 inputs/str-ol-2"

cmd_line = "ruby test.rb " + test_name + " \"#{command}\""
system(cmd_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

test_name = "of_re-ol-3"

print "test of_re on ol-3 "

command = "ruby tester2.rb of_re inputs/re-ol-3 inputs/str-ol-3"

cmd_line = "ruby test.rb " + test_name + " \"#{command}\""
system(cmd_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

