#!/usr/bin/env ruby
system "ruby test.rb 'eval-1.ru' './rube eval_prog inputs/eval-1.ru'"
if $? != 0 then puts "eval-1.ru FAILED"; exit(1) else puts "eval-1.ru PASSED" end
