#!/usr/bin/env ruby
system "ruby test.rb 'eval-0.ru' './rube eval_prog inputs/eval-0.ru'"
if $? != 0 then puts "eval-0.ru FAILED"; exit(1) else puts "eval-0.ru PASSED" end
