require "re.rb"

class Parser
  def cur
    if @str[@pos] then @str[@pos].chr else nil end
  end
  def adv
    @pos = @pos + 1
  end
  def parse_E
    r = nil
    if cur =~ /^[a-zA-Z(]$/
      r = parse_T
      if cur == '|'
        adv
        r2 = parse_E
        r = REUnion.new(r, r2)
      end
    else
      r = REEpsilon.new
    end
    r
  end
  def parse_T
    r = parse_S
    if cur =~ /^[a-zA-Z(]$/
      r2 = parse_T
      r = REConcat.new(r, r2)
    end
    r
  end
  def parse_S
    r = parse_C
    while cur =~ /\*/
      r = REStar.new r
      adv
    end
    r
  end
  def parse_C
    if cur == '('
      adv
      r = parse_E
      fail "Missing )" if cur != ')'
      adv
      r
    elsif cur =~ /^[a-zA-Z]$/
      r = REConst.new cur
      adv
      r
    else
      fail "Unexpected character #{cur}"
    end
  end
  def parse(s)
    @str = s
    @pos = 0
    parse_E
  end
end
