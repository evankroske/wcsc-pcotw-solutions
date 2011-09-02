def split_cars (ferry_length_m, car_lengths)
	ferry_length = ferry_length_m * 100
	total_lanes_length = ferry_length * 2
	sum = 0
	lengths_of_cars_which_can_board = car_lengths.take_while do |l|
		sum += l
		sum <= total_lanes_length
	end
	p sum
	p lengths_of_cars_which_can_board
	left_lane = []
	right_lane = []
	car_lengths_sorted = car_lengths.sort.reverse
	# car_lengths_sorted.each do |l|
end
		
STDIN.gets
loop do
	break unless STDIN.gets
	ferry_length_m = STDIN.gets.chomp.to_i
	car_lengths_in_order = []
	loop do
		car_length = STDIN.gets.chomp.to_i
		break if car_length == 0
		car_lengths_in_order << car_length
	end
	split_cars(ferry_length_m, car_lengths_in_order)
	car_lengths_sorted = car_lengths_in_order.sort.reverse
	puts "Ferry length: #{ferry_length_m} meters"
	puts "Car lengths: #{car_lengths_sorted.join(",")}"
end
