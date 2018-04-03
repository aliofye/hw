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
			stack = pop_helper(stack)
		if "add" in line:
			stack = math_helper(stack, "add")
		if "sub" in line:
			stack = math_helper(stack, "sub")
		if "mul" in line:
			stack = math_helper(stack, "mul")
		if "div" in line:
			stack = math_helper(stack, "div")
		if "rem" in line:
			stack = math_helper(stack, "rem")
		if "neg" in line:
			stack = neg_helper(stack)
		if "swap" in line:
			stack = swap_helper(stack)
		if "quit" in line:
			# print stack
			while len(stack) != 0:
				output_file.write(str(stack.pop()) + "\n");
	

	#close streams
	input_file.close()
	output_file.close()

def push_helper(line):
	# sanitize input
	line = line.replace("push", "")
	line = line.strip()
	# try to match boolean or error literals
	token = re.match(r"^(:true:|:false:|:error:)$", line)
	if token is not None:
		token = token.group()
		print("literals", token)
		return token
	# try to match strings
	token = re.match(r'^"(.*?)"$', line)
	if token is not None:
		token = token.group(1)
		print("strings", token)
		return token
	# try to match names
	token = re.match(r"^[a-zA-Z]+\d*$", line)
	if token is not None:
		token = token.group()
		print("names", token)
		return token
	# try to match integers
	token = re.match(r"^\-?\d+$", line)
	if token is not None:
		token = token.group()
		if token == "-0":
			token = "0"
		print("numbers", token)
		return token
	
	# not able to match anything
	token = ":error:"
	return token

def pop_helper(stack):
	if not stack:
		stack.append(":error:")
	else:
		stack.pop()
	return stack

def math_helper(stack, op):
	if len(stack) <= 1:
		stack.append(":error:")
	else:
		rhs = stack.pop()
		lhs = stack.pop()
		try:
			lhs = int(lhs)
			rhs = int(rhs)
			# switch operations
			if "add" in op:
				total = (lhs + rhs)
			elif "sub" in op:
				total = (lhs - rhs)
			elif "mul" in op:
				total = (lhs * rhs)
			elif "div" in op:
				# divison by zero
				if rhs == 0:
					raise ValueError("division by zero")
				else:
					total = (lhs / rhs)
			elif "rem" in op:
				# divison by zero
				if rhs == 0:
					raise ValueError("division by zero")
				else:	
					total = (lhs % rhs)
			# append total
			stack.append(total)
		except ValueError:
			stack.append(lhs)
			stack.append(rhs)
			stack.append(":error:")	
	return stack

def neg_helper(stack):
	if not stack:
		stack.append(":error:")
	else:
		token = stack.pop()
		try:
			num = int(token)
			num = -num
			stack.append(num)
		except ValueError:
			stack.append(token)
			stack.append(":error:")
	return stack

def swap_helper(stack):
	if len(stack) <= 1:
		stack.append(":error:")
	else:
		lhs = stack.pop()
		rhs = stack.pop()
		# swap
		stack.append(lhs)
		stack.append(rhs)
	return stack

interpreter("./input.txt", "output.txt")