class Foo < Object
begin
  def mymethod(x)
    if x then 1 else 2 end
  end
end

(new Foo).mymethod(nil)
