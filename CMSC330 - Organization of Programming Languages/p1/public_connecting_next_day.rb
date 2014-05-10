#!/usr/bin/env ruby

print "test connecting on multihop-next-day "

test_name = "connecting-ATL-ATL-0-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting ATL ATL 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-ATL-ATL-1-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting ATL ATL 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-ATL-ATL-2-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting ATL ATL 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-ATL-BOS-0-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting ATL BOS 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-ATL-BOS-1-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting ATL BOS 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-ATL-BOS-2-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting ATL BOS 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-ATL-BWI-0-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting ATL BWI 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-ATL-BWI-1-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting ATL BWI 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-ATL-BWI-2-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting ATL BWI 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-ATL-DCA-0-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting ATL DCA 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-ATL-DCA-1-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting ATL DCA 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-ATL-DCA-2-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting ATL DCA 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BOS-ATL-0-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BOS ATL 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BOS-ATL-1-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BOS ATL 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BOS-ATL-2-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BOS ATL 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BOS-BOS-0-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BOS BOS 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BOS-BOS-1-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BOS BOS 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BOS-BOS-2-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BOS BOS 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BOS-BWI-0-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BOS BWI 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BOS-BWI-1-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BOS BWI 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BOS-BWI-2-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BOS BWI 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BOS-DCA-0-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BOS DCA 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BOS-DCA-1-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BOS DCA 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BOS-DCA-2-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BOS DCA 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BWI-ATL-0-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BWI ATL 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BWI-ATL-1-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BWI ATL 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BWI-ATL-2-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BWI ATL 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BWI-BOS-0-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BWI BOS 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BWI-BOS-1-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BWI BOS 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BWI-BOS-2-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BWI BOS 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BWI-BWI-0-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BWI BWI 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BWI-BWI-1-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BWI BWI 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BWI-BWI-2-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BWI BWI 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BWI-DCA-0-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BWI DCA 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BWI-DCA-1-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BWI DCA 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-BWI-DCA-2-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting BWI DCA 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DCA-ATL-0-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting DCA ATL 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DCA-ATL-1-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting DCA ATL 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DCA-ATL-2-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting DCA ATL 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DCA-BOS-0-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting DCA BOS 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DCA-BOS-1-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting DCA BOS 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DCA-BOS-2-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting DCA BOS 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DCA-BWI-0-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting DCA BWI 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DCA-BWI-1-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting DCA BWI 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DCA-BWI-2-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting DCA BWI 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DCA-DCA-0-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting DCA DCA 0"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DCA-DCA-1-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting DCA DCA 1"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

test_name = "connecting-DCA-DCA-2-multihop-next-day"

command = "ruby schedule.rb inputs/multihop-next-day connecting DCA DCA 2"

command_line = "ruby test_multihop.rb " + test_name + " \"#{command}\""
system(command_line)
if $? != 0
  puts "FAILED"
  exit(1)
end

puts "PASSED"

