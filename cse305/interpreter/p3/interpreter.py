import re

def interpreter(input, output):
	# open files
	input_file = open(input, "r")
	output_file = open(output, "w")
	# initialize main scope
	stack = list()
	dictionary = dict()
	# get commands
	commands = list()
	for line in input_file:
		commands.append(line)
	#iterate through lines in file
	stack, dictionary = parse(stack, dictionary, commands)
	# output stack
	while not not stack:
		if len(stack) > 1:
			output_file.write(str(stack.pop()[1]) + "\n");
		else:
			output_file.write(str(stack.pop()[1]));
	#close streams
	input_file.close()
	output_file.close()

def parse(stack, dictionary, commands):
	# reverse commands to pop in the right order
	commands.reverse()
	# while commands is not empty
	while not not commands:
		command = commands.pop()
		if "push" in command:
			token = push_helper(command)
			stack.append(token)
		elif "pop" in command:
			stack = pop_helper(stack)
		elif "add" in command:
			stack = math_helper(stack, dictionary, "add")
		elif "sub" in command:
			stack = math_helper(stack, dictionary, "sub")
		elif "mul" in command:
			stack = math_helper(stack, dictionary, "mul")
		elif "div" in command:
			stack = math_helper(stack, dictionary, "div")
		elif "rem" in command:
			stack = math_helper(stack, dictionary, "rem")
		elif "neg" in command:
			stack = neg_helper(stack, dictionary)
		elif "swap" in command:
			stack = swap_helper(stack)
		elif "cat" in command:
			stack = cat_helper(stack, dictionary)
		elif "and" in command:
			stack = bool_helper(stack, dictionary, "and")
		elif "or" in command:
			stack = bool_helper(stack, dictionary, "or")
		elif "not" in command:
			stack = not_helper(stack, dictionary)
		elif "equal" in command:
			stack = math_helper(stack, dictionary, "equal")
		elif "lessThan" in command:
			stack = math_helper(stack, dictionary, "lessThan")
		elif "bind" in command:
			stack, dictionary = bind_helper(stack, dictionary)
		elif "if" in command:
			stack = if_helper(stack, dictionary)
		elif "let" in command:
			stack, commands = let_helper(stack, dictionary, commands)
		elif "end" in command:
			stack = [stack.pop()]
		elif "quit" in command:
			print("quit")
		else:
			pair = ("error", ":error:")
			stack.append(pair)
			print(pair)
	# return scoped stack and dictionary
	return stack, dictionary

def push_helper(line):
	# sanitize input
	line = line.replace("push", "")
	line = line.strip()
	# try to match error literals
	token = re.match(r"^(:error:)$", line)
	if token is not None:
		token = token.group()
		# print("error", token)
		pair = ("error", token)
		return pair
	# try to match boolean or error literals
	token = re.match(r"^(:true:|:false:)$", line)
	if token is not None:
		token = token.group()
		# print("boolean", token)
		pair = ("boolean", token)
		return pair
	# try to match strings
	token = re.match(r'^"(.*?)"$', line)
	if token is not None:
		token = token.group(1)
		# print("string", token)
		pair = ("string", token)
		return pair
	# try to match names
	token = re.match(r"^[a-zA-Z]+\d*$", line)
	if token is not None:
		token = token.group()
		# print("name", token)
		pair = ("name", token)
		return pair
	# try to match integers
	token = re.match(r"^\-?\d+$", line)
	if token is not None:
		token = token.group()
		if token == "-0":
			token = "0"
		# print("number", token)
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
		print(pair)
	else:
		stack.pop()
	return stack

def math_helper(stack, dictionary, op):
	if len(stack) <= 1:
		token = ":error:"
		pair = ("error", token)
		stack.append(pair)
		print(pair)
	else:
		right = stack.pop()
		left = stack.pop()

		try:
			# check if tokens are bound
			lop, rop = binary_binds(dictionary, left, right);
			
			if lop[0] != "number" or rop[0] != "number":
				raise ValueError("NaN")

			lhs = int(lop[1])
			rhs = int(rop[1])
			# switch operations
			if "add" in op:
				total = (lhs + rhs)
				pair = ("number", total)
			elif "sub" in op:
				total = (lhs - rhs)
				pair = ("number", total)
			elif "mul" in op:
				total = (lhs * rhs)
				pair = ("number", total)
			elif "div" in op:
				# divison by zero
				if rhs == 0:
					raise ValueError("Division by zero")
				else:
					total = (lhs // rhs)
					pair = ("number", total)
			elif "rem" in op:
				# divison by zero
				if rhs == 0:
					raise ValueError("Division by zero")
				else:	
					total = (lhs % rhs)
					pair = ("number", total)
			elif "equal" in op:
				token = ":true:" if lhs == rhs else ":false:"
				pair = ("boolean", token)
			elif "lessThan" in op:
				token = ":true:" if lhs < rhs else ":false:"
				pair = ("boolean", token)
			# append total
			stack.append(pair)
			print(pair)
		except ValueError as e:
			print(e)
			stack.append(left)
			stack.append(right)
			token = ":error:"
			pair = ("error", token)
			stack.append(pair)
			print(pair)	
	return stack

def binary_binds(dictionary, lop, rop):
	if lop[0] == "name" and rop[0] == "name":
		if lop[1] in dictionary:
			lop = dictionary[lop[1]]
		if rop[1] in dictionary:
			rop = dictionary[rop[1]]
	elif lop[0] == "name" and rop[0] != "name":
		if lop[1] in dictionary:
			lop = dictionary[lop[1]]
	elif lop[0] != "name" and rop[0] == "name":
		if rop[1] in dictionary:
			rop = dictionary[rop[1]]
	
	return lop, rop

def unary_binds(dictionary, op):
	if op[0] == "name":
		if op[1] in dictionary:
			op = dictionary[op[1]]
	return op


def neg_helper(stack, dictionary):
	if not stack:
		token = ":error:"
		pair = ("error", token)
		stack.append(pair)
		print(pair)
	else:
		op = stack.pop()
		try:
			# check if token is bound
			token = unary_binds(dictionary, op)
			
			if token[0] != "number":
				raise ValueError('NaN')
			num = int(token[1])
			num = -num
			pair = ("number", num)
			stack.append(pair)
			print(pair)
		except ValueError as e:
			print(e)
			stack.append(op)
			token = ":error:"
			pair = ("error", token)
			stack.append(pair)
			print(pair)
	return stack

def swap_helper(stack):
	if len(stack) <= 1:
		token = ":error:"
		pair = ("error", token)
		stack.append(pair)
		print(pair)
	else:
		rhs = stack.pop()
		lhs = stack.pop()
		# swap
		stack.append(rhs)
		stack.append(lhs)
	return stack

def cat_helper(stack, dictionary):
	if len(stack) <= 1:
		token = ":error:"
		pair = ("error", token)
		stack.append(pair)
		print(pair)
	else:
		right = stack.pop()
		left = stack.pop()
		
		try:
			# check if operands are bound
			lhs, rhs = binary_binds(dictionary, left, right)
			
			if lhs[0] != "string" or rhs[0] != "string":
				raise ValueError('Not a String')
			token = lhs[1] + rhs[1]
			pair = ("string", token)
			stack.append(pair)
			print(pair)

		except ValueError as e:
			print(e)
			token = ":error:"
			pair = ("error", token)
			stack.append(left)
			stack.append(right)
			stack.append(pair)
			print(pair)

	return stack

def if_helper(stack, dictionary):
	if len(stack) <= 2:
		token = ":error:"
		pair = ("error", token)
		stack.append(pair)
		print(pair)
	else:
		x = stack.pop()
		y = stack.pop()
		z = stack.pop()
		
		try:
			# check if operands are bound
			n = unary_binds(dictionary, z)
			
			if n[0] != "boolean" or n[0] != "boolean":
				raise ValueError('Not a Boolean')
			
			if n[1] == ":true:":
				stack.append(y)
			else:
				stack.append(x)


		except ValueError as e:
			print(e)
			token = ":error:"
			pair = ("error", token)
			stack.append(z)
			stack.append(y)
			stack.append(x)
			stack.append(pair)
			print(pair)

	return stack

def not_helper(stack, dictionary):
	if not stack:
		token = ":error:"
		pair = ("error", token)
		stack.append(pair)
		print(pair)
	else:
		operand = stack.pop()

		try:
			# check if operand is bound
			op = unary_binds(dictionary, operand)

			if op[0] != "boolean":
				raise ValueError('Not a Boolean')
			# extract truth value
			boolean = True if "true" in op[1] else False
			# get negation
			boolean = ":false:" if boolean else ":true:"
			pair = ("boolean", boolean)
			stack.append(pair)
			print(pair)
		except ValueError as e:
			print(e)
			error = ":error:"
			pair = ("error", error)
			stack.append(operand)
			stack.append(pair)
			print(pair)
		return stack

def bool_helper(stack, dictionary, op):
	if len(stack) <= 1:
		token = ":error:"
		pair = ("error", token)
		stack.append(pair)
		print(pair)
	else:
		rhs = stack.pop()
		lhs = stack.pop()
		
		try:
			# check if operands are bound
			lhs, rhs = binary_binds(dictionary, lhs, rhs)
			
			if lhs[0] != "boolean" or rhs[0] != "boolean":
				raise ValueError('Not a Boolean')
			# extract truth values
			lop = True if "true" in lhs[1] else False
			rop = True if "true" in rhs[1] else False
			# get truth value
			token = ""
			if "and" in op:
				token = ":true:" if lop and rop else ":false:"
			elif "or" in op:
				token = ":true:" if lop or rop else ":false:"

			pair = ("boolean", token)
			stack.append(pair)
			print(pair)

		except ValueError as e:
			print(e)
			token = ":error:"
			pair = ("error", token)
			stack.append(lhs)
			stack.append(rhs)
			stack.append(pair)
			print(pair)

	return stack
def let_helper(stack, dictionary, commands):
	# init new scope
	ls = list()
	ld = dict()
	lc = list()
	# let counter
	let = 0
	end = 0
	# iterate commands until "end"
	nc = commands.pop()
	lc.append(nc)
	while end <= let and not not commands:
		nc = commands.pop()
		lc.append(nc)
		if "let" in nc:
			let += 1
		if "end" in nc:
			end += 1

	print("commands", lc)

	ld = dictionary.copy()
	ls, ld = parse(ls, ld, lc)
	print("let")
	print(ls)
	print("end")
	pair = ls.pop()
	stack.append(pair)
	print(stack)

	return stack, commands

def bind_helper(stack, dictionary):
	if len(stack) <= 1:
		token = ":error:"
		pair = ("error", token)
		stack.append(pair)
		print(pair)
	else:
		rhs = stack.pop()
		lhs = stack.pop()
		
		try:
			if lhs[0] != "name":
				raise ValueError('Not a Name')
			if rhs[0] != "number" and rhs[0] != "string" and rhs[0] != "boolean" and rhs[0] != "unit" and rhs[0] != "name":
				raise ValueError('Not a Valid Value')
			if rhs[0] == "name" and rhs[1] not in dictionary:
				raise ValueError('Name is Unbound')
			elif rhs[0] == "name" and rhs[1] in dictionary:
				value = dictionary[rhs[1]]
				dictionary[lhs[1]] = value 				
				token = ":unit:"
				pair = ("unit", token)
				stack.append(pair)
				print(pair)
			else:
				dictionary[lhs[1]] = rhs 				
				token = ":unit:"
				pair = ("unit", token)
				stack.append(pair)
				print(pair)			

		except ValueError as e:
			print(e)
			token = ":error:"
			pair = ("error", token)
			stack.append(lhs)
			stack.append(rhs)
			stack.append(pair)
			print(pair)

	return stack, dictionary

interpreter("./input/input15.txt", "./output.txt")