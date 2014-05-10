#!/usr/bin/env ruby
system "ruby test.rb 'eval-3.ru' './rube eval_prog inputs/eval-3.ru'"
if $? != 0 then puts "eval-3.ru FAILED"; exit(1) else puts "eval-3.ru PASSED" end
