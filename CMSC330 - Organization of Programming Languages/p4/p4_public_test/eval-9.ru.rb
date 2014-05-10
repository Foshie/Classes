#!/usr/bin/env ruby
system "ruby test.rb 'eval-9.ru' './rube eval_prog inputs/eval-9.ru'"
if $? != 0 then puts "eval-9.ru FAILED"; exit(1) else puts "eval-9.ru PASSED" end
