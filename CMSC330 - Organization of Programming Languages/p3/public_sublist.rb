#!/usr/bin/env ruby
system "ruby test.rb 'public_sublist' 'ocaml public_sublist.ml'"
if $? != 0 then puts "public_sublist FAILED"; exit(1) else puts "public_sublist PASSED" end
