#!/usr/bin/env ruby

print "test connecting on correct-empty "

test_name = "connecting-DEN-DFW-0-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN DFW 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-DFW-1-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN DFW 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-DFW-2-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN DFW 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-IAD-0-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN IAD 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-IAD-1-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN IAD 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-IAD-2-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN IAD 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-JFK-0-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN JFK 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-JFK-1-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN JFK 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-JFK-2-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN JFK 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-LAX-0-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN LAX 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-LAX-1-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN LAX 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-LAX-2-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN LAX 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-ORD-0-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN ORD 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-ORD-1-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN ORD 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-ORD-2-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN ORD 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-SEA-0-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN SEA 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-SEA-1-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN SEA 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-SEA-2-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN SEA 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-SFO-0-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN SFO 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-SFO-1-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN SFO 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-SFO-2-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DEN SFO 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-DFW-0-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW DFW 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-DFW-1-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW DFW 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-DFW-2-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW DFW 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-IAD-0-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW IAD 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-IAD-1-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW IAD 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-IAD-2-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW IAD 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-JFK-0-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW JFK 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-JFK-1-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW JFK 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-JFK-2-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW JFK 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-LAX-0-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW LAX 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-LAX-1-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW LAX 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-LAX-2-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW LAX 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-ORD-0-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW ORD 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-ORD-1-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW ORD 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-ORD-2-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW ORD 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-SEA-0-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW SEA 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-SEA-1-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW SEA 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-SEA-2-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW SEA 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-SFO-0-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW SFO 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-SFO-1-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW SFO 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-SFO-2-correct-empty"

command = "ruby schedule.rb inputs/correct-empty connecting DFW SFO 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

print "test connecting on correct-flights "

test_name = "connecting-DEN-DFW-0-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN DFW 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-DFW-1-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN DFW 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-DFW-2-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN DFW 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-IAD-0-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN IAD 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-IAD-1-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN IAD 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-IAD-2-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN IAD 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-JFK-0-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN JFK 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-JFK-1-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN JFK 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-JFK-2-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN JFK 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-LAX-0-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN LAX 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-LAX-1-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN LAX 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-LAX-2-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN LAX 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-ORD-0-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN ORD 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-ORD-1-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN ORD 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-ORD-2-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN ORD 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-SEA-0-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN SEA 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-SEA-1-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN SEA 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-SEA-2-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN SEA 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-SFO-0-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN SFO 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-SFO-1-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN SFO 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-SFO-2-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DEN SFO 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-DFW-0-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW DFW 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-DFW-1-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW DFW 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-DFW-2-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW DFW 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-IAD-0-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW IAD 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-IAD-1-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW IAD 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-IAD-2-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW IAD 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-JFK-0-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW JFK 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-JFK-1-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW JFK 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-JFK-2-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW JFK 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-LAX-0-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW LAX 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-LAX-1-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW LAX 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-LAX-2-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW LAX 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-ORD-0-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW ORD 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-ORD-1-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW ORD 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-ORD-2-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW ORD 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-SEA-0-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW SEA 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-SEA-1-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW SEA 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-SEA-2-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW SEA 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-SFO-0-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW SFO 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-SFO-1-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW SFO 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-SFO-2-correct-flights"

command = "ruby schedule.rb inputs/correct-flights connecting DFW SFO 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

print "test connecting on correct-small "

test_name = "connecting-DEN-DFW-0-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN DFW 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-DFW-1-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN DFW 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-DFW-2-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN DFW 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-IAD-0-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN IAD 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-IAD-1-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN IAD 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-IAD-2-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN IAD 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-JFK-0-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN JFK 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-JFK-1-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN JFK 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-JFK-2-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN JFK 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-LAX-0-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN LAX 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-LAX-1-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN LAX 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-LAX-2-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN LAX 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-ORD-0-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN ORD 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-ORD-1-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN ORD 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-ORD-2-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN ORD 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-SEA-0-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN SEA 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-SEA-1-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN SEA 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-SEA-2-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN SEA 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-SFO-0-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN SFO 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-SFO-1-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN SFO 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DEN-SFO-2-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DEN SFO 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-DFW-0-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW DFW 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-DFW-1-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW DFW 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-DFW-2-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW DFW 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-IAD-0-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW IAD 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-IAD-1-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW IAD 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-IAD-2-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW IAD 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-JFK-0-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW JFK 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-JFK-1-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW JFK 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-JFK-2-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW JFK 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-LAX-0-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW LAX 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-LAX-1-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW LAX 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-LAX-2-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW LAX 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-ORD-0-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW ORD 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-ORD-1-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW ORD 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-ORD-2-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW ORD 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-SEA-0-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW SEA 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-SEA-1-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW SEA 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-SEA-2-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW SEA 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-SFO-0-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW SFO 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-SFO-1-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW SFO 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DFW-SFO-2-correct-small"

command = "ruby schedule.rb inputs/correct-small connecting DFW SFO 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

