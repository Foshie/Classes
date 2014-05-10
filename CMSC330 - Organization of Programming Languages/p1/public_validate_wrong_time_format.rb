#!/usr/bin/env ruby
test_name = "validate-wrong-time-format-1"

print "test validate on wrong-time-format-1 "

command = "ruby schedule.rb inputs/wrong-time-format-1 validate"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

test_name = "validate-wrong-time-format-2"

print "test validate on wrong-time-format-2 "

command = "ruby schedule.rb inputs/wrong-time-format-2 validate"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

test_name = "validate-wrong-time-format-3"

print "test validate on wrong-time-format-3 "

command = "ruby schedule.rb inputs/wrong-time-format-3 validate"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

test_name = "validate-wrong-time-format-4"

print "test validate on wrong-time-format-4 "

command = "ruby schedule.rb inputs/wrong-time-format-4 validate"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

test_name = "validate-wrong-time-format-5"

print "test validate on wrong-time-format-5 "

command = "ruby schedule.rb inputs/wrong-time-format-5 validate"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

test_name = "validate-wrong-time-format-6"

print "test validate on wrong-time-format-6 "

command = "ruby schedule.rb inputs/wrong-time-format-6 validate"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

test_name = "validate-wrong-time-format-7"

print "test validate on wrong-time-format-7 "

command = "ruby schedule.rb inputs/wrong-time-format-7 validate"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

test_name = "validate-wrong-time-format-8"

print "test validate on wrong-time-format-8 "

command = "ruby schedule.rb inputs/wrong-time-format-8 validate"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

test_name = "validate-wrong-time-format-9"

print "test validate on wrong-time-format-9 "

command = "ruby schedule.rb inputs/wrong-time-format-9 validate"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

test_name = "validate-wrong-time-format-10"

print "test validate on wrong-time-format-10 "

command = "ruby schedule.rb inputs/wrong-time-format-10 validate"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

