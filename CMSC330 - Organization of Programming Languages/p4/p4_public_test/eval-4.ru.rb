#!/usr/bin/env ruby
system "ruby test.rb 'eval-4.ru' './rube eval_prog inputs/eval-4.ru'"
if $? != 0 then puts "eval-4.ru FAILED"; exit(1) else puts "eval-4.ru PASSED" end
