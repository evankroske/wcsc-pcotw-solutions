require "set"
class Pairing
	def initialize (decode = Array.new(128, 32), encode = Array.new(128, 32))
		@decode = decode
		@encode = encode
	end
	def add_pair (from, to)
		tmp_decode = @decode.dup
		tmp_encode = @encode.dup
		from.bytes.each_with_index do |b, i|
			if tmp_decode[b] != 32 and tmp_decode[b] != to[i]
				return nil
			end
			if tmp_encode[to[i]] != 32 and tmp_encode[to[i]] != b
				return nil
			end
			tmp_decode[b] = to[i]
			tmp_encode[to[i]] = b
		end
		return Pairing.new(tmp_decode, tmp_encode)
	end
	def decode (from)
		to = ""
		from.bytes.each do |b|
			to << @decode[b].chr
		end
		return to
	end
end

class BadPairing < Pairing
	def initialize ()
		super
		@decode = Array.new(128, 42)
		@decode[32] = 32
	end
end

def gen_pairing (pairing, words)
	from, *remaining = words
	return pairing unless from
	for to in $dict[from.length]
		new_pairing = pairing.add_pair(from, to)
		next unless new_pairing

		result = gen_pairing(new_pairing, remaining)
		return result if result
	end
	return nil
end

def test_pairing
	pairing = Pairing.new
	if pairing.add_pair("cat", "dog")
		puts "1: passed"
	else
		puts "1: failed"
	end
	unless pairing.add_pair("cat", "xxx")
		puts "2: passed"
	else
		puts "2: failed"
	end
	p2 = pairing.add_pair("cat", "dog")
	if p2.decode("cat") == "dog"
		puts "3: passed"
	else
		puts "3: failed"
	end
end

unless ARGV.empty?
	test_pairing
	exit
end

num_words = gets.chomp.to_i
$dict = {}
num_words.times do |i|
	word = gets.chomp
	if not $dict[word.length]
		$dict[word.length] = Set.new
	end
	$dict[word.length] << word
end
line_to_decode = gets.chomp
words_to_decode = line_to_decode.split
words_to_decode_by_num_branches = words_to_decode.uniq.sort do |a, b| 
	$dict[a.length].length <=> $dict[b.length].length
end
p words_to_decode_by_num_branches
pairing = gen_pairing(Pairing.new, words_to_decode_by_num_branches) || 
	BadPairing.new
puts pairing.decode(line_to_decode)

