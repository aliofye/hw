def calc_d():
	e = 100 			#enter your own value for e here
	tn = 1729 			#enter your own value for the totient of n (not the n value)
	d = 0
	limit = 10000000 	# you can change this to output more values for d in case the first value of d doesn't satisfy your needs
	m = 0			 	# multiply m by tn and incerement it one by one until the remainder is 0

	for i in range (0, limit):
		r = 1 			#remainder must be initialized as 1 (or any number other than 0) for the while loop to work
		while r != 0:
			r = ((tn * m) + 1) % e # to identify which m, when multiplied by tn, divides e evenly
			if r == 0:
				d = ((tn * m) + 1) / e # to calculate d
			m += 1
		
		print(d)

calc_d() #call function 
