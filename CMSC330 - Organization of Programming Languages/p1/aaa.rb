#!/usr/bin/env ruby

print "test nonstop on correct-empty "


test_name = "nonstop-ATL-DEN-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop ATL DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (1)"
  exit(1)
end


test_name = "nonstop-ATL-DFW-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop ATL DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (2)"
  exit(1)
end


test_name = "nonstop-ATL-IAD-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop ATL IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (3)"
  exit(1)
end


test_name = "nonstop-ATL-JFK-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop ATL JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (4)"
  exit(1)
end


test_name = "nonstop-ATL-LAX-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop ATL LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (5)"
  exit(1)
end


test_name = "nonstop-ATL-ORD-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop ATL ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (6)"
  exit(1)
end


test_name = "nonstop-ATL-SEA-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop ATL SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (7)"
  exit(1)
end


test_name = "nonstop-ATL-SFO-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop ATL SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (8)"
  exit(1)
end


test_name = "nonstop-BOS-DEN-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop BOS DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (9)"
  exit(1)
end


test_name = "nonstop-BOS-DFW-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop BOS DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (10)"
  exit(1)
end


test_name = "nonstop-BOS-IAD-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop BOS IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (11)"
  exit(1)
end


test_name = "nonstop-BOS-JFK-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop BOS JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (12)"
  exit(1)
end


test_name = "nonstop-BOS-LAX-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop BOS LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (13)"
  exit(1)
end


test_name = "nonstop-BOS-ORD-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop BOS ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (14)"
  exit(1)
end


test_name = "nonstop-BOS-SEA-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop BOS SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (15)"
  exit(1)
end


test_name = "nonstop-BOS-SFO-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop BOS SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (16)"
  exit(1)
end


test_name = "nonstop-BWI-DEN-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop BWI DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (17)"
  exit(1)
end


test_name = "nonstop-BWI-DFW-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop BWI DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (18)"
  exit(1)
end


test_name = "nonstop-BWI-IAD-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop BWI IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (19)"
  exit(1)
end


test_name = "nonstop-BWI-JFK-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop BWI JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (20)"
  exit(1)
end


test_name = "nonstop-BWI-LAX-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop BWI LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (21)"
  exit(1)
end


test_name = "nonstop-BWI-ORD-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop BWI ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (22)"
  exit(1)
end


test_name = "nonstop-BWI-SEA-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop BWI SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (23)"
  exit(1)
end


test_name = "nonstop-BWI-SFO-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop BWI SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (24)"
  exit(1)
end


test_name = "nonstop-DCA-DEN-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DCA DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (25)"
  exit(1)
end


test_name = "nonstop-DCA-DFW-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DCA DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (26)"
  exit(1)
end


test_name = "nonstop-DCA-IAD-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DCA IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (27)"
  exit(1)
end


test_name = "nonstop-DCA-JFK-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DCA JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (28)"
  exit(1)
end


test_name = "nonstop-DCA-LAX-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DCA LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (29)"
  exit(1)
end


test_name = "nonstop-DCA-ORD-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DCA ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (30)"
  exit(1)
end


test_name = "nonstop-DCA-SEA-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DCA SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (31)"
  exit(1)
end


test_name = "nonstop-DCA-SFO-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DCA SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (32)"
  exit(1)
end


test_name = "nonstop-DEN-DEN-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DEN DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (33)"
  exit(1)
end


test_name = "nonstop-DEN-DFW-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DEN DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (34)"
  exit(1)
end


test_name = "nonstop-DEN-IAD-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DEN IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (35)"
  exit(1)
end


test_name = "nonstop-DEN-JFK-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DEN JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (36)"
  exit(1)
end


test_name = "nonstop-DEN-LAX-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DEN LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (37)"
  exit(1)
end


test_name = "nonstop-DEN-ORD-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DEN ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (38)"
  exit(1)
end


test_name = "nonstop-DEN-SEA-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DEN SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (39)"
  exit(1)
end


test_name = "nonstop-DEN-SFO-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DEN SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (40)"
  exit(1)
end


test_name = "nonstop-DFW-DEN-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DFW DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (41)"
  exit(1)
end


test_name = "nonstop-DFW-DFW-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DFW DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (42)"
  exit(1)
end


test_name = "nonstop-DFW-IAD-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DFW IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (43)"
  exit(1)
end


test_name = "nonstop-DFW-JFK-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DFW JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (44)"
  exit(1)
end


test_name = "nonstop-DFW-LAX-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DFW LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (45)"
  exit(1)
end


test_name = "nonstop-DFW-ORD-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DFW ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (46)"
  exit(1)
end


test_name = "nonstop-DFW-SEA-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DFW SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (47)"
  exit(1)
end


test_name = "nonstop-DFW-SFO-correct-empty"
command = "ruby schedule.rb inputs/correct-empty nonstop DFW SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (48)"
  exit(1)
end

puts "PASSED"

print "test nonstop on correct-flights "


test_name = "nonstop-ATL-DEN-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop ATL DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (49)"
  exit(1)
end


test_name = "nonstop-ATL-DFW-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop ATL DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (50)"
  exit(1)
end


test_name = "nonstop-ATL-IAD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop ATL IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (51)"
  exit(1)
end


test_name = "nonstop-ATL-JFK-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop ATL JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (52)"
  exit(1)
end


test_name = "nonstop-ATL-LAX-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop ATL LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (53)"
  exit(1)
end


test_name = "nonstop-ATL-ORD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop ATL ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (54)"
  exit(1)
end


test_name = "nonstop-ATL-SEA-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop ATL SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (55)"
  exit(1)
end


test_name = "nonstop-ATL-SFO-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop ATL SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (56)"
  exit(1)
end


test_name = "nonstop-BOS-DEN-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BOS DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (57)"
  exit(1)
end


test_name = "nonstop-BOS-DFW-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BOS DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (58)"
  exit(1)
end


test_name = "nonstop-BOS-IAD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BOS IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (59)"
  exit(1)
end


test_name = "nonstop-BOS-JFK-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BOS JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (60)"
  exit(1)
end


test_name = "nonstop-BOS-LAX-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BOS LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (61)"
  exit(1)
end


test_name = "nonstop-BOS-ORD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BOS ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (62)"
  exit(1)
end


test_name = "nonstop-BOS-SEA-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BOS SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (63)"
  exit(1)
end


test_name = "nonstop-BOS-SFO-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BOS SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (64)"
  exit(1)
end


test_name = "nonstop-BWI-DEN-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BWI DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (65)"
  exit(1)
end


test_name = "nonstop-BWI-DFW-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BWI DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (66)"
  exit(1)
end


test_name = "nonstop-BWI-IAD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BWI IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (67)"
  exit(1)
end


test_name = "nonstop-BWI-JFK-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BWI JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (68)"
  exit(1)
end


test_name = "nonstop-BWI-LAX-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BWI LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (69)"
  exit(1)
end


test_name = "nonstop-BWI-ORD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BWI ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (70)"
  exit(1)
end


test_name = "nonstop-BWI-SEA-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BWI SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (71)"
  exit(1)
end


test_name = "nonstop-BWI-SFO-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop BWI SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (72)"
  exit(1)
end


test_name = "nonstop-DCA-DEN-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DCA DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (73)"
  exit(1)
end


test_name = "nonstop-DCA-DFW-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DCA DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (74)"
  exit(1)
end


test_name = "nonstop-DCA-IAD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DCA IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (75)"
  exit(1)
end


test_name = "nonstop-DCA-JFK-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DCA JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (76)"
  exit(1)
end


test_name = "nonstop-DCA-LAX-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DCA LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (77)"
  exit(1)
end


test_name = "nonstop-DCA-ORD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DCA ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (78)"
  exit(1)
end


test_name = "nonstop-DCA-SEA-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DCA SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (79)"
  exit(1)
end


test_name = "nonstop-DCA-SFO-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DCA SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (80)"
  exit(1)
end


test_name = "nonstop-DEN-DEN-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DEN DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (81)"
  exit(1)
end


test_name = "nonstop-DEN-DFW-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DEN DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (82)"
  exit(1)
end


test_name = "nonstop-DEN-IAD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DEN IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (83)"
  exit(1)
end


test_name = "nonstop-DEN-JFK-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DEN JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (84)"
  exit(1)
end


test_name = "nonstop-DEN-LAX-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DEN LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (85)"
  exit(1)
end


test_name = "nonstop-DEN-ORD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DEN ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (86)"
  exit(1)
end


test_name = "nonstop-DEN-SEA-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DEN SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (87)"
  exit(1)
end


test_name = "nonstop-DEN-SFO-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DEN SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (88)"
  exit(1)
end


test_name = "nonstop-DFW-DEN-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DFW DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (89)"
  exit(1)
end


test_name = "nonstop-DFW-DFW-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DFW DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (90)"
  exit(1)
end


test_name = "nonstop-DFW-IAD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DFW IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (91)"
  exit(1)
end


test_name = "nonstop-DFW-JFK-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DFW JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (92)"
  exit(1)
end


test_name = "nonstop-DFW-LAX-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DFW LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (93)"
  exit(1)
end


test_name = "nonstop-DFW-ORD-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DFW ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (94)"
  exit(1)
end


test_name = "nonstop-DFW-SEA-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DFW SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (95)"
  exit(1)
end


test_name = "nonstop-DFW-SFO-correct-flights"
command = "ruby schedule.rb inputs/correct-flights nonstop DFW SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (96)"
  exit(1)
end

puts "PASSED"

print "test nonstop on correct-small "


test_name = "nonstop-ATL-DEN-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop ATL DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (97)"
  exit(1)
end


test_name = "nonstop-ATL-DFW-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop ATL DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (98)"
  exit(1)
end


test_name = "nonstop-ATL-IAD-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop ATL IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (99)"
  exit(1)
end


test_name = "nonstop-ATL-JFK-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop ATL JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (100)"
  exit(1)
end


test_name = "nonstop-ATL-LAX-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop ATL LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (101)"
  exit(1)
end


test_name = "nonstop-ATL-ORD-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop ATL ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (102)"
  exit(1)
end


test_name = "nonstop-ATL-SEA-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop ATL SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (103)"
  exit(1)
end


test_name = "nonstop-ATL-SFO-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop ATL SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (104)"
  exit(1)
end


test_name = "nonstop-BOS-DEN-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop BOS DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (105)"
  exit(1)
end


test_name = "nonstop-BOS-DFW-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop BOS DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (106)"
  exit(1)
end


test_name = "nonstop-BOS-IAD-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop BOS IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (107)"
  exit(1)
end


test_name = "nonstop-BOS-JFK-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop BOS JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (108)"
  exit(1)
end


test_name = "nonstop-BOS-LAX-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop BOS LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (109)"
  exit(1)
end


test_name = "nonstop-BOS-ORD-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop BOS ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (110)"
  exit(1)
end


test_name = "nonstop-BOS-SEA-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop BOS SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (111)"
  exit(1)
end


test_name = "nonstop-BOS-SFO-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop BOS SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (112)"
  exit(1)
end


test_name = "nonstop-BWI-DEN-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop BWI DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (113)"
  exit(1)
end


test_name = "nonstop-BWI-DFW-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop BWI DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (114)"
  exit(1)
end


test_name = "nonstop-BWI-IAD-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop BWI IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (115)"
  exit(1)
end


test_name = "nonstop-BWI-JFK-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop BWI JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (116)"
  exit(1)
end


test_name = "nonstop-BWI-LAX-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop BWI LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (117)"
  exit(1)
end


test_name = "nonstop-BWI-ORD-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop BWI ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (118)"
  exit(1)
end


test_name = "nonstop-BWI-SEA-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop BWI SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (119)"
  exit(1)
end


test_name = "nonstop-BWI-SFO-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop BWI SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (120)"
  exit(1)
end


test_name = "nonstop-DCA-DEN-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DCA DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (121)"
  exit(1)
end


test_name = "nonstop-DCA-DFW-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DCA DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (122)"
  exit(1)
end


test_name = "nonstop-DCA-IAD-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DCA IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (123)"
  exit(1)
end


test_name = "nonstop-DCA-JFK-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DCA JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (124)"
  exit(1)
end


test_name = "nonstop-DCA-LAX-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DCA LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (125)"
  exit(1)
end


test_name = "nonstop-DCA-ORD-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DCA ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (126)"
  exit(1)
end


test_name = "nonstop-DCA-SEA-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DCA SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (127)"
  exit(1)
end


test_name = "nonstop-DCA-SFO-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DCA SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (128)"
  exit(1)
end


test_name = "nonstop-DEN-DEN-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DEN DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (129)"
  exit(1)
end


test_name = "nonstop-DEN-DFW-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DEN DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (130)"
  exit(1)
end


test_name = "nonstop-DEN-IAD-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DEN IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (131)"
  exit(1)
end


test_name = "nonstop-DEN-JFK-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DEN JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (132)"
  exit(1)
end


test_name = "nonstop-DEN-LAX-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DEN LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (133)"
  exit(1)
end


test_name = "nonstop-DEN-ORD-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DEN ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (134)"
  exit(1)
end


test_name = "nonstop-DEN-SEA-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DEN SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (135)"
  exit(1)
end


test_name = "nonstop-DEN-SFO-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DEN SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (136)"
  exit(1)
end


test_name = "nonstop-DFW-DEN-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DFW DEN"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (137)"
  exit(1)
end


test_name = "nonstop-DFW-DFW-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DFW DFW"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (138)"
  exit(1)
end


test_name = "nonstop-DFW-IAD-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DFW IAD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (139)"
  exit(1)
end


test_name = "nonstop-DFW-JFK-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DFW JFK"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (140)"
  exit(1)
end


test_name = "nonstop-DFW-LAX-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DFW LAX"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (141)"
  exit(1)
end


test_name = "nonstop-DFW-ORD-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DFW ORD"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (142)"
  exit(1)
end


test_name = "nonstop-DFW-SEA-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DFW SEA"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (143)"
  exit(1)
end


test_name = "nonstop-DFW-SFO-correct-small"
command = "ruby schedule.rb inputs/correct-small nonstop DFW SFO"

command_line = "ruby test_nonstop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED (144)"
  exit(1)
end

puts "PASSED"

