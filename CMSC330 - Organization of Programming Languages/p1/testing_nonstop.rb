print "test nonstop on correct-flights "


test_name = "nonstop-ATL-DEN-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop ATL DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)

if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-ATL-DFW-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop ATL DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)

if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-ATL-IAD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop ATL IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-ATL-JFK-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop ATL JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-ATL-LAX-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop ATL LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)

if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-ATL-ORD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop ATL ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-ATL-SEA-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop ATL SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-ATL-SFO-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop ATL SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-BOS-DEN-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BOS DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-BOS-DFW-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BOS DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-BOS-IAD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BOS IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-BOS-JFK-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BOS JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-BOS-LAX-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BOS LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-BOS-ORD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BOS ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-BOS-SEA-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BOS SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-BOS-SFO-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BOS SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-BWI-DEN-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BWI DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-BWI-DFW-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BWI DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-BWI-IAD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BWI IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-BWI-JFK-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BWI JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-BWI-LAX-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BWI LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-BWI-ORD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BWI ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-BWI-SEA-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BWI SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-BWI-SFO-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BWI SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DCA-DEN-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DCA DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DCA-DFW-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DCA DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DCA-IAD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DCA IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DCA-JFK-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DCA JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DCA-LAX-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DCA LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DCA-ORD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DCA ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DCA-SEA-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DCA SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DCA-SFO-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DCA SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DEN-DEN-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DEN DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DEN-DFW-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DEN DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DEN-IAD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DEN IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DEN-JFK-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DEN JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DEN-LAX-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DEN LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DEN-ORD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DEN ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DEN-SEA-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DEN SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DEN-SFO-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DEN SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DFW-DEN-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DFW DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DFW-DFW-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DFW DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DFW-IAD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DFW IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DFW-JFK-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DFW JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DFW-LAX-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DFW LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DFW-ORD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DFW ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)

if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DFW-SEA-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DFW SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)

if $? != 0
  puts "FAILED"
  exit(1)
end


test_name = "nonstop-DFW-SFO-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DFW SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)

if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

print "test nonstop on correct-small "


test_name = "nonstop-ATL-DEN-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop ATL DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end