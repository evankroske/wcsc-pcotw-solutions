include Math

def is_jj? (nums)
	num_nums = nums.size
	jumper_vals = (1..num_nums - 1).to_a
	c = 0
	while nums[c+1]
		jumper_vals.delete((nums[c] - nums[c+1]).abs)
		c += 1
	end
	return jumper_vals.empty?
end

while l = $stdin.gets
	nums = l.split
	num_nums = nums.shift
	nums.map! {|e| e.to_i}
	if is_jj? nums
		puts "Jolly"
	else
		puts "Not jolly"
	end
end
