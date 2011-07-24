def play (goal)
	stan_wins, stan_win_percent = play_round(goal, 1, true)
	winner = stan_wins ? "Stan" : "Ollie"
	puts "#{winner} wins."
end

def play_round(goal, p, stan)
	if p >= goal
		return !stan, !stan ? 1 : 0
	end
	stan_wins = {}
	stan_win_percent = {}
	stan_wins_if_2, stan_win_percent_if_2 = play_round(goal, p*2, !stan)
	stan_wins_if_9, stan_win_percent_if_9 = play_round(goal, p*9, !stan)
	if stan
		stan_wins = if stan_win_percent_if_2 > stan_win_percent_if_9 then 
			stan_wins_if_2 else stan_wins_if_9 end
	else
		stan_wins = if stan_win_percent_if_2 < stan_win_percent_if_9 then 
			stan_wins_if_2 else stan_wins_if_9 end
	end
	stan_win_percent = (stan_win_percent_if_2 + stan_win_percent_if_9) / 2
	return stan_wins, stan_win_percent
end

while l = gets
	goal = l.chomp.to_i
	play(goal)
end
