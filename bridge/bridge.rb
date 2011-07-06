def total_crossing_time_fancy(crossing_times)
	crossing_times.inject(:+)
end

def total_crossing_time_plain(crossing_times)
	total_crossing_time = 0
	crossing_method = ""
	queue = crossing_times.sort
	first =  queue.slice!(0)
	while true
		last = queue.pop
		if not queue.empty?
			crossing_method += "#{first} #{last}\n#{first}\n"
			total_crossing_time += first + last
		else
			crossing_method += "#{first} #{last}\n"
			total_crossing_time += last
			break
		end
	end
	puts total_crossing_time
	puts crossing_method.chomp
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
	puts "Plain:"
	total_crossing_time_plain crossing_times
	puts "Fancy:"
	p total_crossing_time_fancy crossing_times
end
