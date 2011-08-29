def factorial (n)
	return 1 if n < 1
	(1..n).inject {|o, p| o * p}
end

def choose (n, k)
	return 0 if n < k
	factorial(n) / (factorial(k) * factorial(n - k))
end

def count_regions (num_points)
	puts "num_points = #{num_points}"
	num_lines = num_points * (num_points - 1) / 2
	puts "num_lines = #{num_lines}"
	intersections = choose(num_points, 4)
	puts "num_intersections = #{intersections}"
	puts num_lines + intersections + 1
end

STDIN.gets
while l = STDIN.gets
	num_points = l.chomp.to_i
	count_regions(num_points)
end
