#!/usr/bin/env ruby

print "test destinations on correct-flights "

test_name = "destinations-ATL-correct-flights"

command = "ruby schedule.rb inputs/correct-flights destinations ATL"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "destinations-BOS-correct-flights"

command = "ruby schedule.rb inputs/correct-flights destinations BOS"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "destinations-BWI-correct-flights"

command = "ruby schedule.rb inputs/correct-flights destinations BWI"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "destinations-DCA-correct-flights"

command = "ruby schedule.rb inputs/correct-flights destinations DCA"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "destinations-DEN-correct-flights"

command = "ruby schedule.rb inputs/correct-flights destinations DEN"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "destinations-DFW-correct-flights"

command = "ruby schedule.rb inputs/correct-flights destinations DFW"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "destinations-IAD-correct-flights"

command = "ruby schedule.rb inputs/correct-flights destinations IAD"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "destinations-JFK-correct-flights"

command = "ruby schedule.rb inputs/correct-flights destinations JFK"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "destinations-LAX-correct-flights"

command = "ruby schedule.rb inputs/correct-flights destinations LAX"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "destinations-ORD-correct-flights"

command = "ruby schedule.rb inputs/correct-flights destinations ORD"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "destinations-SEA-correct-flights"

command = "ruby schedule.rb inputs/correct-flights destinations SEA"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "destinations-SFO-correct-flights"

command = "ruby schedule.rb inputs/correct-flights destinations SFO"

command_line = "ruby test.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"
