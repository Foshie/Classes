require "parser.rb"
require "fa.rb"

# Some sample code showing how fa.rb is used

file = File.open(ARGV[0], "r")
#1. /^Loremipsumdolorsitametconsecteturadipiscingelit$/
#2. /^Integertempusdiamnonorciplaceratquisaliquamliberoporta$/
#3. /^Integerposuereaccumsanbibendum$/
#4. /^Invelquamnequevehicularutrumlibero|VestibulumliberonibhvulputatesedadipiscingeumolestiequislacusNullaquissapieneratidpretiumerat$/
#5. /^Nullamaturpismetusnecblanditlacus|NullamenimodiocondimentumetmollisvelconvallisnonpurusSedpretiumviverraauctor$/
#6. /^Nuncornarevehiculaestinfaucibus$/
#7. /^CrasornareportamiidcommodoMorbiimperdietdolorutenimultricesfeugiat$/
p = Parser.new

r = [p.parse("Loremipsumdolorsitametconsecteturadipiscingelit"), p.parse("Integertempusdiamnonorciplaceratquisaliquamliberoporta"), p.parse("Integerposuereaccumsanbibendum"), p.parse("Invelquamnequevehicularutrumlibero|VestibulumliberonibhvulputatesedadipiscingeumolestiequislacusNullaquissapieneratidpretiumerat"), p.parse("Nullamaturpismetusnecblanditlacus|NullamenimodiocondimentumetmollisvelconvallisnonpurusSedpretiumviverraauctor"), p.parse("Nuncornarevehiculaestinfaucibus"), p.parse("CrasornareportamiidcommodoMorbiimperdietdolorutenimultricesfeugiat")]

str = Array.new
file.each{|line|
	s = line.scan(/(\S+)/)
    str << s[0][0]
}
j=1
r.each { |e|
  nfa = NFA.of_re(e)
  puts "nfa:\n"
  beginning_time = Time.now
	(1..10000).each { |i| i }
  str.each{|s|
	puts s if nfa.accept?(s)
  }
  end_time = Time.now
  puts "Time elapsed #{(end_time - beginning_time)*1000} milliseconds\n"

  puts "dfa:\n"
  
  #accept on nfa
  dfa = nfa.to_dfa
  beginning_time = Time.now
	(1..10000).each { |i| i }
  str.each{|s|
	puts s if dfa.accept?(s)
  }
  end_time = Time.now
  puts "Time elapsed #{(end_time - beginning_time)*1000} milliseconds\n"
  
  puts "Ruby regexp:"
  str.each{|s|
  beginning_time = 0
	case j
	when 1
	
		beginning_time = Time.now
		(1..10000).each { |i| i }
		if s=~ /^Loremipsumdolorsitametconsecteturadipiscingelit$/ then
		end_time = Time.now
		puts "Time elapsed #{(end_time - beginning_time)*1000} milliseconds\n"
		end
	when 2
		beginning_time = Time.now
		(1..10000).each { |i| i }
		if s=~ /^Integertempusdiamnonorciplaceratquisaliquamliberoporta$/ then
		end_time = Time.now
		puts "Time elapsed #{(end_time - beginning_time)*1000} milliseconds\n"
		end
	when 3
		beginning_time = Time.now
		(1..10000).each { |i| i }
		if s=~ /^Integerposuereaccumsanbibendum$/ then
		end_time = Time.now
		puts "Time elapsed #{(end_time - beginning_time)*1000} milliseconds\n"
		end
	when 4
		beginning_time = Time.now
		(1..10000).each { |i| i }
		if s=~ /^Invelquamnequevehicularutrumlibero|VestibulumliberonibhvulputatesedadipiscingeumolestiequislacusNullaquissapieneratidpretiumerat$/ then
	
		end_time = Time.now
		puts "Time elapsed #{(end_time - beginning_time)*1000} milliseconds\n"
		end
	when 5
		beginning_time = Time.now
		(1..10000).each { |i| i }
		if s=~ /^Nullamaturpismetusnecblanditlacus|NullamenimodiocondimentumetmollisvelconvallisnonpurusSedpretiumviverraauctor$/ then
		end_time = Time.now
		puts "Time elapsed #{(end_time - beginning_time)*1000} milliseconds\n"
		end
	when 6
		beginning_time = Time.now
		(1..10000).each { |i| i }
		if s=~ /^Nuncornarevehiculaestinfaucibus$/ then
		end_time = Time.now
		puts "Time elapsed #{(end_time - beginning_time)*1000} milliseconds\n"
		end
	else
		beginning_time = Time.now
		(1..10000).each { |i| i }
		if s=~ /^CrasornareportamiidcommodoMorbiimperdietdolorutenimultricesfeugiat$/ then
		end_time = Time.now
		puts "Time elapsed #{(end_time - beginning_time)*1000} milliseconds\n"
		end
	end
  }
  j+=1
}
