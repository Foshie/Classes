#!/usr/bin/env ruby
system "ruby test.rb 'public_prod' 'ocaml public_prod.ml'"
if $? != 0 then puts "public_prod FAILED"; exit(1) else puts "public_prod PASSED" end
