#!/usr/bin/env ruby
system "ruby test.rb 'eval-6.ru' './rube eval_prog inputs/eval-6.ru'"
if $? != 0 then puts "eval-6.ru FAILED"; exit(1) else puts "eval-6.ru PASSED" end
