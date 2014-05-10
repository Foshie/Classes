#!/usr/bin/env ruby
system "ruby test.rb 'public_check' 'ocaml public_check.ml'"
if $? != 0 then puts "public_check FAILED"; exit(1) else puts "public_check PASSED" end
