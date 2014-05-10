#!/usr/bin/env ruby
system "ruby test.rb 'public_rindex' 'ocaml public_rindex.ml'"
if $? != 0 then puts "public_rindex FAILED"; exit(1) else puts "public_rindex PASSED" end
