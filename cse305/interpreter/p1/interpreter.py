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
				if len(stack) != 1:
					output_file.write(str(stack.pop()[1]) + "\n");
				else:
					output_file.write(str(stack.pop()[1]));
	

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
		print("literal", token)
		pair = ("literal", token)
		return pair
	# try to match strings
	token = re.match(r'^"(.*?)"$', line)
	if token is not None:
		token = token.group(1)
		print("string", token)
		pair = ("string", token)
		return pair
	# try to match names
	token = re.match(r"^[a-zA-Z]+\d*$", line)
	if token is not None:
		token = token.group()
		print("name", token)
		pair = ("name", token)
		return pair
	# try to match integers
	token = re.match(r"^\-?\d+$", line)
	if token is not None:
		token = token.group()
		if token == "-0":
			token = "0"
		print("number", token)
		pair = ("number", token)
		return pair
	
	# not able to match anything
	token = ":error:"
	pair = ("error", token)
	return pair

def pop_helper(stack):
	if not stack:
		token = ":error:"
		pair = ("error", token)
		stack.append(pair)
	else:
		stack.pop()
	return stack

def math_helper(stack, op):
	if len(stack) <= 1:
		token = ":error:"
		pair = ("error", token)
		stack.append(pair)
	else:
		right = stack.pop()
		left = stack.pop()

		try:
			if right[0] != "number" or left[0] != "number":
				raise ValueError("NaN")

			lhs = int(left[1])
			rhs = int(right[1])
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
					raise ValueError("Division by zero")
				else:
					total = (lhs // rhs)
			elif "rem" in op:
				# divison by zero
				if rhs == 0:
					raise ValueError("Division by zero")
				else:	
					total = (lhs % rhs)
			# append total
			pair = ("number", total)
			stack.append(pair)
		except ValueError as e:
			print(e)
			stack.append(left)
			stack.append(right)
			token = ":error:"
			pair = ("error", token)
			stack.append(pair)	
	return stack

def neg_helper(stack):
	if not stack:
		token = ":error:"
		pair = ("error", token)
		stack.append(pair)
	else:
		token = stack.pop()
		try:
			if token[0] != "number":
				raise ValueError('NaN')
			num = int(token[1])
			num = -num
			pair = ("number", num)
			stack.append(pair)
		except ValueError as e:
			print(e)
			stack.append(token)
			token = ":error:"
			pair = ("error", token)
			stack.append(pair)
	return stack

def swap_helper(stack):
	if len(stack) <= 1:
		token = ":error:"
		pair = ("error", token)
		stack.append(pair)
	else:
		lhs = stack.pop()
		rhs = stack.pop()
		# swap
		stack.append(lhs)
		stack.append(rhs)
	return stack

# interpreter("./input.txt", "./output.txt")