#!/usr/bin/env ruby
system "ruby test.rb 'public_even_elts' 'ocaml public_even_elts.ml'"
if $? != 0 then puts "public_even_elts FAILED"; exit(1) else puts "public_even_elts PASSED" end
