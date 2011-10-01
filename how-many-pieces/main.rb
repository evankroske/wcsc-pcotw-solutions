class PascalTriangle
	def initialize (max_n = 10)
		@max_n
		@triangle = Array.new(max_n + 1)
		(0...max_n+1).each do |row_i|
			@triangle[row_i] = Array.new(row_i+1)
			@triangle[row_i][0] = 1
			@triangle[row_i][row_i] = 1
		end
		(2...max_n+1).each do |n|
			(1...n).each do |k|
				@triangle[n][k] = @triangle[n-1][k-1] + @triangle[n-1][k]
			end
		end
	end

	def choose (n, k)
		return 0 if n < k
		if n > max_n
			extend_triangle(n)
		end
		return @triangle[n][k]
	end

	def extend_triangle (new_max_n)
		old_max_n = @max_n
		@max_n = new_max_n
		(old_max_n + 1...@max_n + 1).each do |row_i|
			@triangle << Array.new(row_i + 1)
			@triangle[row_i][0] = 1
			@triangle[row_i][row_i] = 1
			(1...row_i).each do |k|
				@triangle[n][k] = @triangle[n-1][k-1] + @triangle[n-1][k]
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
