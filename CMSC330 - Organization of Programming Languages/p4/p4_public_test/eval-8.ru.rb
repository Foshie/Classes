#!/usr/bin/env ruby
system "ruby test.rb 'eval-8.ru' './rube eval_prog inputs/eval-8.ru'"
if $? != 0 then puts "eval-8.ru FAILED"; exit(1) else puts "eval-8.ru PASSED" end
