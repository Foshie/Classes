#!/usr/bin/env ruby
system "ruby test.rb 'check_dup_params-1.ru' './rube check_dup_params inputs/check_dup_params-1.ru '"
if $? != 0 then puts "check_dup_params-1.ru FAILED"; exit(1) else puts "check_dup_params-1.ru PASSED" end