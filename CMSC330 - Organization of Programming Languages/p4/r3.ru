class C < Object
begin
  def m(a, b)
    a.+(b)
  end
end

x = new C;
x.m(1, 2)
