def die(msg)
  #puts "FAILED: #{msg}"
  exit 1
end

def compare_files(canonical_file, student_file)
  txt = student_file.read
  ans = []
  if txt != "none\n"
    txt.each do |line|
      ans << line.strip.split("\t")
    end
  end

  if ans.length == 0 and txt != "none\n"
    die "Empty output"
  end

  txt = canonical_file.read
  ref = []
  if txt != "none\n"
    txt.each do |line|
      ref << line.strip.split("\t")
    end
  end

  if ans.sort != ref.sort
    die "Wrong flights"
  end

  (0 ... ans.length - 1).each do |i|
    _,t1,_ = ans[i]
    _,t2,_ = ans[i + 1]
    if t1 > t2
      die "Wrong output order"
    end
  end
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
    die "FAILED: Ruby returned a non-zero value, there are Ruby syntax errors"
  end

  if do_comparison(canonical_output, student_output)
    exit(0)
  else
    die "FAILED\n"
    exit(1)
  end
end

if ARGV.length != 2
  puts "Usage: test_nonstop.rb <test_name> \"<test_command>\""
  exit(1)
end

test_name = ARGV[0]
test_command = ARGV[1]

do_test(test_name, test_command)
