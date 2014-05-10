#!/usr/bin/env ruby

test_name = "check-re-ol-2"

print "test check on re-ol-2 "

command = "ruby tester.rb check inputs/re-ol-2"

cmd_line = "ruby test.rb " + test_name + " \"#{command}\""
system(cmd_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

test_name = "check-re-ol-3"

print "test check on re-ol-3 "

command = "ruby tester.rb check inputs/re-ol-3"

cmd_line = "ruby test.rb " + test_name + " \"#{command}\""
system(cmd_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

