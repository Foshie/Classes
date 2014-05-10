#!/usr/bin/env ruby
system "ruby test.rb 'public_unzip' 'ocaml public_unzip.ml'"
if $? != 0 then puts "public_unzip FAILED"; exit(1) else puts "public_unzip PASSED" end
