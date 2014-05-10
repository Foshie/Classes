#!/usr/bin/env ruby
system "ruby test.rb 'public_trans' 'ocaml public_trans.ml'"
if $? != 0 then puts "public_trans FAILED"; exit(1) else puts "public_trans PASSED" end
