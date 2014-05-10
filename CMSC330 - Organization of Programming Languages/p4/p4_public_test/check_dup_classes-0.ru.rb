#!/usr/bin/env ruby
system "ruby test.rb 'check_dup_classes-0.ru' './rube check_dup_classes inputs/check_dup_classes-0.ru '"
if $? != 0 then puts "check_dup_classes-0.ru FAILED"; exit(1) else puts "check_dup_classes-0.ru PASSED" end
