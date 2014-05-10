#!/usr/bin/env ruby
system "ruby test.rb 'public_rotate' 'ocaml public_rotate.ml'"
if $? != 0 then puts "public_rotate FAILED"; exit(1) else puts "public_rotate PASSED" end
