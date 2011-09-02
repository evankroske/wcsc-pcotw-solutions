def choose (n, k)
	return 0 if n < k
	return $p_triangle[n][k]
end

$p_triangle
def generate_binomial_coefficients (max_n)
	$p_triangle = Array.new(max_n+1)
	(0...max_n+1).each do |row_i|
		$p_triangle[row_i] = Array.new(row_i+1)
		$p_triangle[row_i][0] = 1
		$p_triangle[row_i][row_i] = 1
	end
	(2...max_n+1).each do |n|
		(1...n).each do |k|
			$p_triangle[n][k] = $p_triangle[n-1][k-1] + $p_triangle[n-1][k]
		end
	end
end

def count_regions (num_points)
	puts "num_points = #{num_points}"
	num_lines = num_points * (num_points - 1) / 2
	puts "num_lines = #{num_lines}"
	intersections = choose(num_points, 4)
	puts "num_intersections = #{intersections}"
	puts num_lines + intersections + 1
end

def main
	STDIN.gets
	while l = STDIN.gets
		num_points = l.chomp.to_i
		count_regions(num_points)
	end
end
