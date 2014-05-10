#!/usr/bin/env ruby
system "ruby test.rb 'public_no_mult' 'ocaml public_no_mult.ml'"
if $? != 0 then puts "public_no_mult FAILED"; exit(1) else puts "public_no_mult PASSED" end
