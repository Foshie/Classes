#!/usr/bin/env ruby
system "ruby test.rb 'public_fill' 'ocaml public_fill.ml'"
if $? != 0 then puts "public_fill FAILED"; exit(1) else puts "public_fill PASSED" end
