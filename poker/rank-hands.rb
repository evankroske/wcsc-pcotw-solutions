require "set"

CARD_VALUE_HASH = {
	:"2" => 2,
	:"3" => 3,
	:"4" => 4,
	:"5" => 5,
	:"6" => 6,
	:"7" => 7,
	:"8" => 8,
	:"9" => 9,
	:T => 10,
	:J => 11,
	:Q => 12,
	:K => 13,
	:A => 14,
}

CARD_NUM_HASH = CARD_VALUE_HASH.invert

class Card
	include Comparable
	attr_reader :number, :suite

	def initialize (number, suite)
		@number = number
		@suite = suite
	end

	def to_s ()
		@number.to_s + @suite.to_s
	end

	def to_i ()
		CARD_VALUE_HASH[@number]
	end

	def <=> (other)
		self.to_i <=> other.to_i
	end

	def succ ()
		return nil if @number == :A
		next_card_value = CARD_VALUE_HASH[@number] + 1
		next_card_num = CARD_NUM_HASH[next_card_value]
		Card.new(next_card_num, @suite)
	end
end

class Hand
	def initialize ()
		@numbers = {
			:"2" => [],
			:"3" => [],
			:"4" => [],
			:"5" => [],
			:"6" => [],
			:"7" => [],
			:"8" => [],
			:"9" => [],
			:T => [],
			:J => [],
			:Q => [],
			:K => [],
			:A => [],
		}
		@suites = {
			:D => [],
			:H => [],
			:S => [],
			:C => [],
		}
		@cards = []
	end

	def << (card)
		@numbers[card.number] << card
		@suites[card.suite] << card
		@cards << card
		@cards.sort!
	end

	def to_a ()
		@cards
	end

	def to_s ()
		@cards.map{|c| c.to_s}.join(" ")
	end

	def straight ()
		last_card = @cards[0]
		@cards[1..-1].each do |card|
			return [] unless card == last_card.succ
			last_card = card
		end
		[last_card]
	end

	def flush ()
		@suites.each do |k, v|
			return @cards.reverse if v.length == 5
		end
		[]
	end

	def n_of_a_kind (n)
		n_tuple_values
		@numbers.each do |k, v|
			n_tuple_values << v[0] if v.length >= n
		end
		n_tuple_values.sort.reverse
	end

	def four_of_a_kind ()
		n_of_a_kind 4
	end

	def three_of_a_kind ()
		n_of_a_kind(3) + n_of_a_kind(2)
	end

	def two_of_a_kind ()
		n_of_a_kind 2
	end

	def high_cards ()
		@cards.reverse
	end
end

def hand_from_array (cards)
	hand = Hand.new
	cards.each {|c| hand << Card.new(:"#{c[0].chr}", :"#{c[1].chr}")}
	hand
end

def cards_to_s (cards)
	cards.map{|c| c.to_s}.join(" ") if cards
end

while l = ARGF.gets
	cards = l.split(" ")
	black_hand = hand_from_array(cards[0, 5])
	white_hand = hand_from_array(cards[5, 5])
	puts black_hand.to_s
	puts cards_to_s black_hand.straight
	puts cards_to_s black_hand.flush
	puts white_hand.to_s
	puts cards_to_s white_hand.straight
	puts cards_to_s white_hand.flush
end
