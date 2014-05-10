#!/usr/bin/env ruby


test_name = "balance-correct-flights"

print "test balance on correct-flights "

command = "ruby schedule.rb inputs/correct-flights balance"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"


test_name = "balance-correct-small"

print "test balance on correct-small "

command = "ruby schedule.rb inputs/correct-small balance"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

