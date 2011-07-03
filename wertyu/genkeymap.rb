require "optparse"
OptionParser.new do |o|
	o.on("-n ARRAY_NAME") { |array_name| $array_name = array_name }
	o.parse!
end
$array_name = $array_name || "array"
from = $stdin.gets.chomp
to = $stdin.gets.chomp
# puts from
# puts to
puts "\tprivate static char[] #{$array_name} = new char[128];" 
puts "\tstatic {"
from.chars.each_with_index do |c, i|
	puts "\t\t#{$array_name}[#{c[0].ord}] = '#{to[i].chr}';"
end
puts "\t}"
