#!/usr/bin/env ruby
system "ruby test.rb 'eval-2.ru' './rube eval_prog inputs/eval-2.ru'"
if $? != 0 then puts "eval-2.ru FAILED"; exit(1) else puts "eval-2.ru PASSED" end
