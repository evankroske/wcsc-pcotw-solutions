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

HAND_CMP_METHODS = [
	:straight_flush,
	:four_of_a_kind,
	:full_house,
	:flush,
	:straight,
	:three_of_a_kind,
	:pairs,
	:high_cards,
]

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

	def straight_flush ()
		straight = self.straight
		flush = self.flush
		if not straight.empty? and not flush.empty?
			straight
		else
			[]
		end
	end

	def four_of_a_kind ()
		n_of_a_kind 4
	end

	def full_house ()
		triples_and_pairs = n_of_a_kind(3) + n_of_a_kind(2)
		if triples_and_pairs.length == 2
			triples_and_pairs
		else
			[]
		end
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

	def three_of_a_kind ()
		n_of_a_kind(3) + n_of_a_kind(2)
	end

	def pairs ()
		n_of_a_kind 2
	end

	def high_cards ()
		@cards.reverse
	end

	def n_of_a_kind (n)
		n_tuple_values = []
		@numbers.each do |k, v|
			n_tuple_values << v[0] if v.length == n
		end
		n_tuple_values.sort.reverse
	end

	def cards_cmp (a, b)
		i = 0
		loop do
			return 0 if not a[i] and not b[i]
			return -1 if not a[i]
			return 1 if not b[i]
			return a[i] <=> b[i] unless a[i] == b[i]
			i += 1
		end
	end

	def <=> (other)
		HAND_CMP_METHODS.each do |m_name|
			a, b = self.method(m_name), other.method(m_name)
			if not a.call.empty? or not b.call.empty?
				p m_name
				return cards_cmp(a.call, b.call)
			end
		end
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

responses = {
	:"-1" => "White wins",
	:"0" => "Tie",
	:"1" => "Black wins",
}

while l = ARGF.gets
	cards = l.split(" ")
	black_hand = hand_from_array(cards[0, 5])
	white_hand = hand_from_array(cards[5, 5])
	puts responses[:"#{black_hand <=> white_hand}"]
end
