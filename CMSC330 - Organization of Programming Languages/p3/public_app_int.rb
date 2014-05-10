#!/usr/bin/env ruby
system "ruby test.rb 'public_app_int' 'ocaml public_app_int.ml'"
if $? != 0 then puts "public_app_int FAILED"; exit(1) else puts "public_app_int PASSED" end
