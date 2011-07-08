# invariant: crossing_times is sorted in ascending order
def cross(crossing_times)
	if (l = crossing_times.length) >= 4
		a, b = crossing_times.slice(0, 2)
		c, d = crossing_times.slice(-2, 2)
		if 2 * b <= a + c
			steps = [
				"#{a} #{b}",
				"#{a}", 
				"#{c} #{d}", 
				"#{b}"
			]
			time = 2 * b + a + d
			other_time, other_steps = cross(crossing_times.slice(0, l - 2))
			return time + other_time, steps + other_steps
		else
			time = a + d
			steps = [
				"#{a} #{d}", 
				"#{a}"
			]
			other_time, other_steps = cross(crossing_times.slice(0, l - 1))
			return time + other_time, steps + other_steps
		end
	elsif l == 3
		a, b, c = crossing_times
		time = a + b + c
		steps = [
			"#{a} #{c}",
			"#{a}",
			"#{a} #{b}"
		]
		return time, steps
	elsif l == 2
		a, b = crossing_times
		time = b
		steps = [
			"#{a} #{b}"
		]
		return time, steps
	elsif l == 1
		a = crossing_times[0]
		time = a
		steps = [
			"#{a}"
		]
		return time, steps
	else
		puts "Big problem"
		exit 1
	end
end

def read_crossing_times()
	crossing_times = []
	gets
	while t = gets and not t.chomp!.empty?
		crossing_times << t.to_i
	end
	return crossing_times
end

gets
gets
while not (crossing_times = read_crossing_times).empty?
	total_time, steps = cross(crossing_times.sort)
	puts total_time
	puts steps.join("\n")
	puts
end
