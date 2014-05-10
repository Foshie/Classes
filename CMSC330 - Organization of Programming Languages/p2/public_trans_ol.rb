#!/usr/bin/env ruby

test_name = "trans-re-ol-2"

print "test trans on re-ol-2 "

command = "ruby tester.rb trans inputs/re-ol-2"

cmd_line = "ruby test.rb " + test_name + " \"#{command}\""
system(cmd_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

test_name = "trans-re-ol-3"

print "test trans on re-ol-3 "

command = "ruby tester.rb trans inputs/re-ol-3"

cmd_line = "ruby test.rb " + test_name + " \"#{command}\""
system(cmd_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

