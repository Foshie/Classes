#!/usr/bin/env ruby
for c in ['A', 'B', 'C', 'D', 'Object']
  for m in ['f', 'g', 'h']
    system "ruby test.rb 'lookup-1.ru-#{c}-#{m}' './rube lookup inputs/lookup-1.ru #{c} #{m} '"
    if $? != 0 then puts "lookup-1.ru FAILED"; exit(1) end
  end
end
puts "lookup-1.ru PASSED"
