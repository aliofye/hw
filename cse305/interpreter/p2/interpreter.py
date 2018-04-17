import re

def interpreter(input, output):
	# open files
	input_file = open(input, "r")
	output_file = open(output, "w")
	# init stack
	stack = list()
	dictionary = dict()
	#iterate through lines in file
	for line in input_file:
		if "push" in line:
			token = push_helper(line)
			stack.append(token)
		elif "pop" in line:
			stack = pop_helper(stack)
		elif "add" in line:
			stack = math_helper(stack, dictionary, "add")
		elif "sub" in line:
			stack = math_helper(stack, dictionary, "sub")
		elif "mul" in line:
			stack = math_helper(stack, dictionary, "mul")
		elif "div" in line:
			stack = math_helper(stack, dictionary, "div")
		elif "rem" in line:
			stack = math_helper(stack, dictionary, "rem")
		elif "neg" in line:
			stack = neg_helper(stack, dictionary)
		elif "swap" in line:
			stack = swap_helper(stack)
		elif "cat" in line:
			stack = cat_helper(stack, dictionary)
		elif "and" in line:
			stack = bool_helper(stack, dictionary, "and")
		elif "or" in line:
			stack = bool_helper(stack, dictionary, "or")
		elif "equal" in line:
			stack = math_helper(stack, dictionary, "equal")
		elif "lessThan" in line:
			stack = math_helper(stack, dictionary, "lessThan")
		elif "bind" in line:
			stack, dictionary = bind_helper(stack, dictionary)
		elif "if" in line:
			stack = if_helper(stack, dictionary)
		elif "quit" in line:
			# print stack
			while len(stack) != 0:
				if len(stack) != 1:
					output_file.write(str(stack.pop()[1]) + "\n");
				else:
					output_file.write(str(stack.pop()[1]));
		else:
			pair = ("error", ":error:")
			stack.append(pair)

	#close streams
	input_file.close()
	output_file.close()

def push_helper(line):
	# sanitize input
	line = line.replace("push", "")
	line = line.strip()
	# try to match error literals
	token = re.match(r"^(:error:)$", line)
	if token is not None:
		token = token.group()
		print("error", token)
		pair = ("error", token)
		return pair
	# try to match boolean or error literals
	token = re.match(r"^(:true:|:false:)$", line)
	if token is not None:
		token = token.group()
		print("boolean", token)
		pair = ("boolean", token)
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

def math_helper(stack, dictionary, op):
	if len(stack) <= 1:
		token = ":error:"
		pair = ("error", token)
		stack.append(pair)
	else:
		lop = stack.pop()
		rop = stack.pop()

		try:
			# check if tokens are bound
			lop, rop = binary_binds(dictionary, lop, rop);
			
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
		except ValueError as e:
			print(e)
			stack.append(lop)
			stack.append(rop)
			token = ":error:"
			pair = ("error", token)
			stack.append(pair)	
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
	else:
		token = stack.pop()
		try:
			# check if token is bound
			token = unary_binds(dictionary, token)
			
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
	else:
		rhs = stack.pop()
		lhs = stack.pop()
		
		try:
			# check if operands are bound
			lhs, rhs = binary_binds(dictionary, lhs, rhs)
			
			if lhs[0] != "string" or rhs[0] != "string":
				raise ValueError('Not a String')
			token = lhs[1] + ' ' + rhs[1]
			pair = ("string", token)
			stack.append(pair)

		except ValueError as e:
			print(e)
			token = ":error:"
			pair = ("error", token)
			stack.append(lhs)
			stack.append(rhs)
			stack.append(pair)

	return stack

def if_helper(stack, dictionary):
	if len(stack) <= 2:
		token = ":error:"
		pair = ("error", token)
		stack.append(pair)
	else:
		x = stack.pop()
		y = stack.pop()
		z = stack.pop()
		
		try:
			# check if operands are bound
			z = unary_binds(dictionary, z)
			
			if z[0] != "boolean" or z[0] != "boolean":
				raise ValueError('Not a Boolean')
			
			if z[1] == ":true:":
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

	return stack

def bool_helper(stack, dictionary, op):
	if len(stack) <= 1:
		token = ":error:"
		pair = ("error", token)
		stack.append(pair)
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
			else:
				token = ":true:" if lop or rop else ":false:"

			pair = ("boolean", token)
			stack.append(pair)

		except ValueError as e:
			print(e)
			token = ":error:"
			pair = ("error", token)
			stack.append(lhs)
			stack.append(rhs)
			stack.append(pair)

	return stack

def bind_helper(stack, dictionary):
	if len(stack) <= 1:
		token = ":error:"
		pair = ("error", token)
		stack.append(pair)
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
			else:
				dictionary[lhs[1]] = rhs 				
				token = ":unit:"
				pair = ("unit", token)
				stack.append(pair)
				print(dictionary)
			

		except ValueError as e:
			print(e)
			token = ":error:"
			pair = ("error", token)
			stack.append(lhs)
			stack.append(rhs)
			stack.append(pair)

	return stack, dictionary

interpreter("./input.txt", "./output.txt")