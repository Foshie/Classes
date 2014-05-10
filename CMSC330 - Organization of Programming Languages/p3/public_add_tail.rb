#!/usr/bin/env ruby
system "ruby test.rb 'public_add_tail' 'ocaml public_add_tail.ml'"
if $? != 0 then puts "public_add_tail FAILED"; exit(1) else puts "public_add_tail PASSED" end
