#!/usr/bin/env ruby

def validate
	emptyLine = 0
	i = 0
	while(line = $file.gets)	
		if line =~ /^[\n]/ then
			if emptyLine == 1 then
				return false
			end
		end
		if line =~ (/^([1-9][0-9]{0,3}),([A-Z]{3}),([A-Z]{3}),((([0-1][0-9])|(2[0-3]))[0-5][0-9]),((([0-1][0-9])|(2[0-3]))[0-5][0-9])$/) then
			flightNum = $1
			depart = $2
			arrive = $3
			depTime = $4
			arrTime = $8
			$number[i] = flightNum
			if $flights[flightNum] == nil then
				$flights[flightNum] = Hash.new
			end
			if $flights[flightNum]["numArr"] == nil then
				$flights[flightNum]["numArr"] = Hash.new
				$flights[flightNum]["numArr"] = 0
			end
			if $flights[flightNum]["dep"] == nil then
				$flights[flightNum]["dep"] = Hash.new
			end
			if $flights[flightNum]["arr"] == nil then
				$flights[flightNum]["arr"] = Hash.new
			end
			if $flights[flightNum]["dTime"] == nil then
				$flights[flightNum]["dTime"] = Hash.new
			end
			if $flights[flightNum]["aTime"] == nil then
				$flights[flightNum]["aTime"] = Hash.new
			end
			if depart == arrive then
				return false
			end
			$flights[flightNum]["dep"][$flights[flightNum]["numArr"]] = depart
			$flights[flightNum]["arr"][$flights[flightNum]["numArr"]] = arrive
			$flights[flightNum]["dTime"][$flights[flightNum]["numArr"]] = depTime
			$flights[flightNum]["aTime"][$flights[flightNum]["numArr"]] = arrTime
			
			if $flights[flightNum]["dep"][$flights[flightNum]["numArr"]] !~ (/^(ATL|BOS|BWI|DCA|DEN|DFW|IAD|JFK|LAX|ORD|SEA|SFO)$/) then
				return false
			end
			if $flights[flightNum]["arr"][$flights[flightNum]["numArr"]] !~ (/^(ATL|BOS|BWI|DCA|DEN|DFW|IAD|JFK|LAX|ORD|SEA|SFO)$/) then
				return false
			end
			if ($flights[flightNum]["numArr"] != 0) then
				if(($flights[flightNum]["arr"][0] != depart) && $flights[flightNum]["dep"][0] != arrive) then
					return false
				else
					$number.delete_at(i)
					i-=1
				end
			end
			$flights[flightNum]["numArr"] += 1
			
		else
			return false
		end
		
		emptyLine += 1
		i+=1
	end
	$file.close
end

def nonstop(start, final)
	stops = []
	i = 0
	j = 0
	while i < $number.length
		flag = 0
		second = 0
		if $flights[$number[i].to_s]["numArr"] == 2 then
			if ($flights[$number[i].to_s]["dep"][1] == start) && ($flights[$number[i].to_s]["arr"][1] == final) then
				flag = 1
				second = 1
			end
		end
		if($flights[$number[i].to_s]["dep"][0] == start) && ($flights[$number[i].to_s]["arr"][0] == final) then
			flag = 1
		end
		
		if(flag == 1) then
			stops[j] = Array[$number[i].to_s, $flights[$number[i].to_s]["dep"][second], $flights[$number[i].to_s]["arr"][second], $flights[$number[i].to_s]["dTime"][second], $flights[$number[i].to_s]["aTime"][second]]
			j+=1
			
		end
		i+=1
	end
	if stops.length == 0 then
		puts("none")
		return
	end
	#sort stops
	iPos = 0
	iMin = 0
	i=0

	while iPos < stops.length
		iMin = iPos
		i = iPos+1
		
		while i < stops.length
			if stops[i][3].to_i < stops[iMin][3].to_i then
				iMin = i
			end
			i+=1
		end
		if iMin != iPos then
			stops[iMin], stops[iPos] = stops[iPos], stops[iMin]
		end
		iPos +=1
	end
	
	#print stops
	if ARGV[1] == "nonstop" then
		i = 0
		while i < stops.length
			puts("#{stops[i][0]}\t#{stops[i][3]}\t#{stops[i][4]}")
			i+=1
		end
	end
	i = 0
	fNum = []
	while i < stops.length
		fNum[i] = stops[i][0]
		i+=1
	end
	return fNum

end

def destinations(start)
	dest = Hash.new
	i = 0
	while i < $number.length
		if $flights[$number[i].to_s]["numArr"] == 2 then
			if $flights[$number[i].to_s]["dep"][1] == start then
				if dest[$flights[$number[i].to_s]["arr"][1]] == nil then
					dest[$flights[$number[i].to_s]["arr"][1]] =1
				else
					dest[$flights[$number[i].to_s]["arr"][1]] +=1
				end
			end
		end
		if $flights[$number[i].to_s]["dep"][0] == start then
			
			if dest[$flights[$number[i].to_s]["arr"][0]] == nil then
				dest[$flights[$number[i].to_s]["arr"][0]] =1
			else
				dest[$flights[$number[i].to_s]["arr"][0]] +=1
			end
		end
		i+=1
	end

	# Sort destinations alphabetically in an array
	destArr = dest.keys
	iPos = 0
	iMin = 0
	i=0
	while iPos < destArr.length
		iMin = iPos
		i = iPos+1
		
		while i < destArr.length
			if destArr[i] < destArr[iMin] then
				iMin = i
			end
			i+=1
		end
		if iMin != iPos then
			destArr[iMin], destArr[iPos] = destArr[iPos], destArr[iMin]
		end
		iPos +=1
	end
	# Print out all cities in dest hash
	if ARGV[1] == "destinations" then
		i = 0
		while i < destArr.length
			puts("#{destArr[i]}\t#{dest[destArr[i]]}")
			i+=1
		end
	end
	return destArr
end

def balance
	airports = Hash.new
	i=0
	while i < $number.length
		fnum = $number[i].to_s
		if $flights[fnum]["numArr"] == 2 then
			if airports[$flights[fnum]["dep"][1]] == nil then
				airports[$flights[fnum]["dep"][1]]=0
			end
			if airports[$flights[fnum]["arr"][1]] == nil then
				airports[$flights[fnum]["arr"][1]] = 0
			end
			airports[$flights[fnum]["dep"][1]]-=1
			airports[$flights[fnum]["arr"][1]]+=1
		end
		if airports[$flights[fnum]["dep"][0]] == nil then
			airports[$flights[fnum]["dep"][0]]=0
		end
		if airports[$flights[fnum]["arr"][0]] == nil then
			airports[$flights[fnum]["arr"][0]] = 0
		end
		airports[$flights[fnum]["dep"][0]]-=1
		airports[$flights[fnum]["arr"][0]]+=1
		i+=1
	end
	
	#Sorts and prints
	airArr = airports.keys
	iPos = 0
	iMin = 0
	i=0
	while iPos < airArr.length
		iMin = iPos
		i = iPos+1
		
		while i < airArr.length
			if airArr[i] < airArr[iMin] then
				iMin = i
			end
			i+=1
		end
		if iMin != iPos then
			airArr[iMin], airArr[iPos] = airArr[iPos], airArr[iMin]
		end
		iPos +=1
	end
	# Print out all cities in airports hash with balance
	i = 0
	while i < airArr.length
		puts("#{airArr[i]}\t#{airports[airArr[i]]}")
		i+=1
	end
end

def createTree(start, num, aTime, final)

	# create a list of flight #'s leaving start airport
	i = 0
	d = destinations(start[0])
	if num!= 0 && d.include?(final) == true then
		d.delete(final)
	end

	while i < d.length

		if $visited.include?(d[i]) == false then
			temp = nonstop(start[0], d[i])
			start.concat(temp)
		end

		i+=1
	end
	# f indicates numArr
	# dur indicates flight duration
	# delete all flight numbers that don't fit time criteria
	if !(aTime == nil) then
		thing = String.new(aTime)
		i=1
		minA = aTime[2,2].to_i
		hrA = aTime[0,2].to_i
		
		while i < start.length
		
				deleted = 0
			if $list[$list.length-1][0] != start[i] then
				if $flights[start[i].to_s]["dep"][0] == start[0] then
					nA = 0
				else
					nA = 1
				end
				tempHr = 0
				tempMin = 0
				minD = $flights[start[i]]["dTime"][nA][2,2].to_i
				hrD = $flights[start[i]]["dTime"][nA][0,2].to_i
				if $flights[start[i]]["dTime"][nA].to_i < aTime.to_i then
					#could wrap around midnight
					hrD += 24
					tempHr = hrD - hrA
					tempMin = minD - minA
					if tempMin < 0 then
						tempHr -=1
						tempMin += 60
					end
					if tempHr < 1 || tempHr > 3 then
						if (tempHr == 4 && tempMin == 0) then
						else					
							start.delete_at(i)
							deleted = 1
						end					
					end
				else
					#all other times, find time difference in layover
					tempHr = hrD - hrA
					tempMin = minD - minA
					if tempMin < 0 then
						tempHr -=1
						tempMin += 60
					end
					if tempHr < 1 || tempHr > 3 then
						if !(tempHr == 4 && tempMin == 0) then
							start.delete_at(i)
							deleted = 1
						end					
					end	
				end
			end
			if deleted != 1 then
				i+=1
			end
		end	
	end
	if num > 0 then
		j = 1
		while j < start.length
			f = 0
			if $flights[start[j].to_s]["numArr"] == 2 then
				if $flights[start[j].to_s]["dep"][1] == start[0] then
					arr = $flights[start[j].to_s]["arr"][1]
					arrTime = $flights[start[j].to_s]["aTime"][1]
					f = 1
				else
				arr = $flights[start[j].to_s]["arr"][0]			
				arrTime = $flights[start[j].to_s]["aTime"][0]
				end
			else
				arr = $flights[start[j].to_s]["arr"][0]			
				arrTime = $flights[start[j].to_s]["aTime"][0]
			end
			fNum = start[j].to_s
			start.delete_at(j)
			start.insert(j, Hash.new)
			start[j][fNum] = Array[arr]

			$visited.push(arr)
			#find duration of layover between aTime and flights dTime, add it to flight duration
			dur = duration($flights[fNum]["dTime"][f], $flights[fNum]["aTime"][f])
			if aTime != nil then
				layoverDur = duration(aTime, $flights[fNum]["dTime"][f])
				dur = addTime(dur, layoverDur)
			end
			info = [fNum, f, dur]
			$list.push(info)

			createTree(start[j][fNum], num-1, arrTime, final)
			$list.pop
			$visited.pop
			j+=1
		end
	end
	# base case
	# iterate through all flight numbers
	# if any flight number leaves current airport to correct end  then add list to layover array
	
	if num == 0 then
		count = 1
		while count < start.length
			if $flights[start[count].to_s]["numArr"] == 2 then
				if $flights[start[count].to_s]["arr"][1] == final && $flights[start[count].to_s]["dep"][1] == start[0] then
					dur = duration($flights[start[count].to_s]["dTime"][1], $flights[start[count].to_s]["aTime"][1])
					if aTime != nil then
						layoverDur = duration(aTime, $flights[start[count].to_s]["dTime"][1])
						dur = addTime(dur, layoverDur)
					end
					info = [start[count].to_s, 1, dur]
					$list.push(info)
					index = 0
					$layovers[$layovers.size] = Array.new($list)
					
					$list.pop					
				end
			end
			if $flights[start[count].to_s]["arr"][0] == final && $flights[start[count].to_s]["dep"][0] == start[0] then
				dur = duration($flights[start[count].to_s]["dTime"][0], $flights[start[count].to_s]["aTime"][0])

				if aTime != nil then
					layoverDur = duration(aTime, $flights[start[count].to_s]["dTime"][0])
					dur = addTime(dur, layoverDur)
				end
				info = [start[count].to_s, 0, dur]
				$list.push(info)
				index = 0
				$layovers[$layovers.size] = Array.new($list)
				$list.pop				
			end
			count+=1
		end
	end
end
# adds durations a and b.  returns a string
def addTime(a, b)
	toReturn = String.new
	hrA = a[0,2].to_i
	minA = a[2,2].to_i
	hrB = b[0,2].to_i
	minB = b[2,2].to_i
	tempHr = hrA + hrB
	tempMin = minA + minB
	if tempMin > 59 then
		tempMin -= 60
		tempHr += 1
	end
	if tempHr < 10 then
		toReturn += "0"
	end
	toReturn += tempHr.to_s
	if tempMin < 10 then
		toReturn += "0"
	end
	toReturn += tempMin.to_s
	return toReturn
end
# start and stop both should be string values, calculate values in int, then convert back to string. 
#	returns string(toReturn)
def duration(start, stop)
	toReturn = String.new
	hrL = start[0,2].to_i
	minL = start[2,2].to_i
	hrA = stop[0,2].to_i
	minA = stop[2,2].to_i

	if stop.to_i < start.to_i then
		#could wrap around midnight
		hrA += 24
	end
	tempHr = hrA-hrL
	tempMin = minA-minL
	if tempMin < 0 then
		tempHr -=1
		tempMin += 60
	end
	if tempHr < 10 then
		toReturn += "0"
	end
	toReturn +=tempHr.to_s
	if tempMin < 10 then
		toReturn += "0"
	end
	toReturn += tempMin.to_s
	return toReturn
end
#Main:
$file = File.open(ARGV[0], "r")
$flights = Hash.new
$number = []
$origin = []

if ARGV[1] == "validate" then
	if validate() == false then
		puts("no")
	else
		puts("yes")
	end	
end
if ARGV[1] == "nonstop" then
	if validate() != false then
		nonstop(ARGV[2], ARGV[3])
	end
end
if ARGV[1] == "destinations" then
	if validate() != false then
		destinations(ARGV[2])
	end
end
if ARGV[1] == "balance" then
	if validate() != false then
		balance()
	end
end
if ARGV[1] == "connecting" then
	if validate() != false then
		$origin = [ARGV[2]]
		$layovers = []
		$list = []
		$visited = [ARGV[2]]
		createTree($origin, ARGV[4].to_i, nil, ARGV[3])
		i= 0
		#calculate duration of all itineraries
		while i < $layovers.length
			j = 0
			dur = "0000"
			while j < $layovers[i].length
				dur = addTime(dur, $layovers[i][j][2])
				j+=1
			end
			$layovers[i].insert(0, dur)
			i+=1
		end
		
		i = 0
		iPos = 0
		iMin = 0
		
		#sort list of layovers by duration, use selection sort on rows.
		#Find duration over each row.  Sort rows.
		while iPos < $layovers.length
			iMin = iPos
			i = iPos + 1
			while i < $layovers.length
				if $layovers[i][0].to_i < $layovers[iMin][0].to_i then
					iMin = i
				end
				i+=1
			end
			if iMin != iPos then
				$layovers[iMin], $layovers[iPos] = $layovers[iPos], $layovers[iMin]
			end
			iPos+=1
		end
		
		# Print in pretty format
		i = 0
		if $layovers.length == 0 then
			puts "none\n"
		end
		while i < $layovers.length && i < 5
			j = 1
			while j < $layovers[i].length
				fNum = $layovers[i][j][0].to_s
				f = $layovers[i][j][1].to_i
				print "#{fNum}\t#{$flights[fNum]["dTime"][f]}\t#{$flights[fNum]["aTime"][f]}\t#{$flights[fNum]["arr"][f]}\n"
				j+=1
			end
			puts "Duration #{$layovers[i][0]}"
			puts "\n"
			i+=1
		end
	end
end