#!/usr/bin/env ruby
system "ruby test.rb 'public_eval' 'ocaml public_eval.ml'"
if $? != 0 then puts "public_eval FAILED"; exit(1) else puts "public_eval PASSED" end
