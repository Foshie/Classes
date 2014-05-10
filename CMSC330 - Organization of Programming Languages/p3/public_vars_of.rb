#!/usr/bin/env ruby
system "ruby test.rb 'public_vars_of' 'ocaml public_vars_of.ml'"
if $? != 0 then puts "public_vars_of FAILED"; exit(1) else puts "public_vars_of PASSED" end
