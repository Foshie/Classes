#!/usr/bin/env ruby
system "ruby test.rb 'public_exec_gcd' 'ocaml public_exec_gcd.ml'"
ret = $?
if ret != 0 then puts "public_exec_gcd FAILED"; exit(1) else puts "public_exec_gcd PASSED" end
