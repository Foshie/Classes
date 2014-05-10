class A < Object begin
  def foo(foo, bar) @foo; @bar end
  def bar(bar, foo) @foo; bar end
  def baz(baz, foo, bar) foo; @bar end
end

class bar < A begin
  def foo(bar) @foo; new bar end
end

nil