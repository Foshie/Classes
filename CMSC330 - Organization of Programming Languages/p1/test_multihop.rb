def die(msg)
  #puts "FAILED: #{msg}"
  exit 1
end

def to_hash(l)
  r = {}
  l.each do |i|
    r[i] = true
  end
  return r
end

def compare_files(canonical_file, student_file)
  txt = student_file.read
  ans = []
  if txt != "none\n"
    ans = txt.strip.split("\n\n")
  end

  if ans.length == 0 and txt != "none\n"
    die "Empty output"
  end

  if ans.length > 5
    die "Too many routes"
  end

  txt = canonical_file.read
  ref = []
  if txt != "none\n"
    ref = txt.strip.split("\n\n")
  end

  if ref.length > 5 and ans.length < 5
    die "Too few routes"
  end

  if ref.length <= 5 and ans.length != ref.length
    die "Wrong number of routes"
  end

  ref_hash = to_hash(ref)

  valid_dur = to_hash(ref[0..4].collect do |i|
                        i.split(' ')[-1]
                      end)

  ans.each do |i|
    if not ref_hash[i]
      die "Wrong route or duration"
    end

    if not valid_dur[i.split(' ')[-1]]
      die "Wrong route or duration"
    end
  end

  (0 ... ans.length - 1).each do |i|
    t1 = ans[i].split(' ')[-1].to_i
    t2 = ans[i + 1].split(' ')[-1].to_i
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
