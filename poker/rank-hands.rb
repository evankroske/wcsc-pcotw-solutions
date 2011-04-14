def card (c_str)
	{"number" => c_str[0].chr, "suite" => c_str[1].chr}
end

class Card
	def initialize (card_str)
		@number = card_str[0].chr
		@suite = card_str[1].chr
	end

	def to_s ()
		@number + @suite
	end

	def num()
		@number
	end

	def suite()
		@suite
	end
end

while l = $stdin.gets
	cards = l.split
	blacks_hand = cards[0, 5].map {|c| Card.new(c)}
	whites_hand = cards[5, 5].map {|c| Card.new(c)}
	puts blacks_hand[0].num
	# puts "Black has " + blacks_hand.join(" ")
	# puts "White has " + whites_hand.join(" ")
end
