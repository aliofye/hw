import re

def interpreter(input, output):
	# open files
	input_file = open(input, "r")
	output_file = open(output, "w")
	# init stack
	stack = []
	#iterate through lines in file
	for line in input_file:
		if "push" in line:
			token = push_helper(line)
			stack.append(token)
		if "pop" in line:
			stack = pop_handler(stack)
		if "add" in line:
			stack = add_handler(stack)
		if "sub" in line:
			stack = sub_handler(stack)
	# print stack
	for token in stack:
		output_file.write(str(token) + "\n");

	#close streams
	input_file.close()
	output_file.close()

def push_helper(line):
	# sanitize input
	line.replace("push", "")
	# try to match integers
	token = re.findall("\-?\d+", line)[0]
	if token is not None:
		return token
	# try to match strings
	token = re.findall(r'"(.*?)"', line)[0]
	if token is not None:
		return token
	# try to match names
	token = re.findall("[a-zA-Z]+\d*", line)[0]
	if token is not None:
		return token
	# try to match boolean or error literals
	token = re.findall("(:true:|:false:|:error:)", line)[0]
	if token is not None:
		return token
	# not able to match anything
	token = ":error:"
	return token

def pop_handler(stack):
	if not stack:
		stack.append(":error:")
	else:
		stack.pop()
	return stack

def add_handler(stack):
	if len(stack) <= 1:
		stack.append(":error:")
	else:
		lhs = stack.pop()
		rhs = stack.pop()
		try:
			lhs = int(lhs)
			rhs = int(rhs)
			total = lhs + rhs
			stack.append(total)
		except ValueError:
			lhs = str(lhs)
			rhs = str(rhs)
			stack.append(rhs)
			stack.append(lhs)	
	return stack

def sub_handler(stack):
	return stack
	
interpreter("./input/input2.txt", "output.txt")