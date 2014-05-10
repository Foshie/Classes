#!/usr/bin/env ruby
system "ruby test.rb 'public_subst' 'ocaml public_subst.ml'"
if $? != 0 then puts "public_subst FAILED"; exit(1) else puts "public_subst PASSED" end
