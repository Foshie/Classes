def compare_files(canonical_file, student_file)
  while (canonical_line = canonical_file.gets) &&
        (student_line = student_file.gets)
    canonical_line.strip!
    student_line.strip!
    if student_line != canonical_line
      return false
    end
  end

  if (canonical_line != nil) && (student_line == nil)
    exit(1)
  end

#  if (canonical_line == nil) && (student_line != nil)
#    puts "FAILED: EOF expected\n"
#    exit(1)
#  end

  return true
end

def do_comparison(canonical_filename, student_filename)
  File.open(canonical_filename) do |canonical_file|
    File.open(student_filename) do |student_file|
      if !compare_files(canonical_file, student_file)
        return false
      end
    end
  end

  return true
end

def do_test(test_name, test_command)
  canonical_output = "outputs/" + test_name + ".out"
  student_output = "student_outputs/" + test_name + ".out"

  command_line = test_command + " > " + student_output

  system(command_line)
  if $? != 0
    exit 1
  end

  if do_comparison(canonical_output, student_output)
    exit(0)
  else
    exit(1)
  end
end

if ARGV.length != 2
  puts "Usage: test.rb <test_name> \"<test_command>\""
  exit(1)
end

test_name = ARGV[0]
test_command = ARGV[1]

do_test(test_name, test_command)
