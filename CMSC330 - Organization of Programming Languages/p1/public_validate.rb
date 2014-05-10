#!/usr/bin/env ruby
test_name = "validate-correct-empty"

print "test validate on correct-empty "

command = "ruby schedule.rb inputs/correct-empty validate"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

test_name = "validate-correct-flights"

print "test validate on correct-flights "

command = "ruby schedule.rb inputs/correct-flights validate"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

test_name = "validate-correct-small"

print "test validate on correct-small "

command = "ruby schedule.rb inputs/correct-small validate"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

test_name = "validate-wrong-empty-line"

print "test validate on wrong-empty-line "

command = "ruby schedule.rb inputs/wrong-empty-line validate"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

