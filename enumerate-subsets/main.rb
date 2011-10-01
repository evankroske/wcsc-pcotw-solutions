$finished = false

def check_solution (a, n)
	a.length >= n
end

def process_solution (a)
	print "{ "
	a.each_with_index do |e, i|
		print "#{i} " if e
	end
	puts "}"
end

def gen_candidates (a, n)
	return [true, false]
end

def backtrack (a, n)
	if check_solution(a, n)
		process_solution(a)
		return
	end
	candidates = gen_candidates(a, n)
	candidates.each do |c|
		backtrack(a + [c], n)
		return if $finished
	end
end

n = ARGV[0].to_i
backtrack([], n)
