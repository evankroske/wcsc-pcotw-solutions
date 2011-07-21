while l = gets
	number = l.chomp.to_i
	steps = 0
	while number % 2 == 0
		number /= 2
		steps += 1
	end
	while number % 9 == 0
		number /= 9
		steps += 1
	end
	if steps % 2 == 0
		
