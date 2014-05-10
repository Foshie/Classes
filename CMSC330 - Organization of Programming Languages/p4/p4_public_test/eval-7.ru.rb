#!/usr/bin/env ruby
system "ruby test.rb 'eval-7.ru' './rube eval_prog inputs/eval-7.ru'"
if $? != 0 then puts "eval-7.ru FAILED"; exit(1) else puts "eval-7.ru PASSED" end
