LETTERS_IN_ALPHABET = 26 

def pangram(input, output):
	# open files
	input_file = open(input, "r")
	output_file = open(output, "w")
	#iterate through lines in file
	for line in input_file:
		letters = set();
		#iterate through each character in line stripped from whitespace
		for char in line.strip():
			#if the character is in the alphabet
			if char.isalpha():
				#add to set without duplicates
				letters.add(char) 

		#check if the length of letters is the same as the alphabet's
		if len(letters) == LETTERS_IN_ALPHABET:
			#write true to file
			output_file.write("true\n")
		else:
			#write false to file
			output_file.write("false\n")
			
		
	#close streams
	input_file.close()
	output_file.close()

# pangram("./tests/input/input13.txt", "output.txt")