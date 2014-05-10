#!/usr/bin/env ruby
system "ruby test.rb 'eval-5.ru' './rube eval_prog inputs/eval-5.ru'"
if $? != 0 then puts "eval-5.ru FAILED"; exit(1) else puts "eval-5.ru PASSED" end
