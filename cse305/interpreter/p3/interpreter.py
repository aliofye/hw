import re
import copy

keywords = ["push", "pop", "add", "sub", "mul", "div", "rem", "neg", "swap",
 			"cat", "and", "or", "not", "equal", "lessThan", "bind", "if", "let",
 			"end","fun", "funEnd", "return", "call", "quit"]

class Scope():
	def __init__(self):
		self.stack = list()
		self.dictionary = dict()

class Closure():
	def __init__(self):
		self.scope = Scope()
		self.arg = str()
		self.commands = list()
		self.type = str()


def interpreter(input, output):
	# open files
	input_file = open(input, "r")
	output_file = open(output, "w")
	# get commands
	commands = list()
	for line in input_file:
		commands.append(line)
	# initialize main scope
	scope = Scope()
	scope = parse(scope, commands)
	# output stack
	while not not scope.stack:
		if len(scope.stack) > 1:
			output_file.write(str(scope.stack.pop()[1]) + "\n");
		else:
			output_file.write(str(scope.stack.pop()[1]));
	#close streams
	input_file.close()
	output_file.close()

def parse(scope, commands):
	# reverse commands to pop in the right order
	commands.reverse()
	# while commands is not empty
	while not not commands:
		line = commands.pop()
		command = line.split()[0]
		
		if "push" in command:
			token = push_helper(line)
			scope.stack.append(token)
		elif "pop" in command:
			scope = pop_helper(scope)
		elif "add" in command:
			scope = math_helper(scope, "add")
		elif "sub" in command:
			scope = math_helper(scope, "sub")
		elif "mul" in command:
			scope = math_helper(scope, "mul")
		elif "div" in command:
			scope = math_helper(scope, "div")
		elif "rem" in command:
			scope = math_helper(scope, "rem")
		elif "neg" in command:
			scope = neg_helper(scope)
		elif "swap" in command:
			scope = swap_helper(scope)
		elif "cat" in command:
			scope = cat_helper(scope)
		elif "and" in command:
			scope = bool_helper(scope, "and")
		elif "or" in command:
			scope = bool_helper(scope, "or")
		elif "not" in command:
			scope = not_helper(scope)
		elif "equal" in command:
			scope = math_helper(scope, "equal")
		elif "lessThan" in command:
			scope = math_helper(scope, "lessThan")
		elif "bind" in command:
			scope = bind_helper(scope)
		elif "if" in command:
			scope = if_helper(scope)
		elif "let" in command:
			scope, commands = let_helper(scope, commands)
		elif "end" in command:
			scope.stack = [scope.stack.pop()]
		elif "fun" in command or "inOutFun" in command:
			scope, commands = fun_helper(line, scope, commands)
		elif "return" in command:
			scope.stack = return_helper(scope)
		elif "call" in command:
			scope.stack = call_helper(scope)
		elif "quit" in command:
			print("quit")
		else:
			pair = ("error", ":error:")
			scope.stack.append(pair)
			print(pair)
	print("scope", scope.stack)
	# return scoped stack and dictionary
	return scope

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

def pop_helper(scope):
	if not scope.stack:
		token = ":error:"
		pair = ("error", token)
		scope.stack.append(pair)
		print(pair)
	else:
		scope.stack.pop()
	return scope

def math_helper(scope, op):
	if len(scope.stack) <= 1:
		token = ":error:"
		pair = ("error", token)
		scope.stack.append(pair)
		print(pair)
	else:
		right = scope.stack.pop()
		left = scope.stack.pop()

		try:
			# check if tokens are bound
			lop, rop = binary_binds(scope.dictionary, left, right);
			
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
			scope.stack.append(pair)
			print(pair)
		except ValueError as e:
			print(e)
			scope.stack.append(left)
			scope.stack.append(right)
			token = ":error:"
			pair = ("error", token)
			scope.stack.append(pair)
			print(pair)	
	return scope

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

def return_helper(scope):
	if not scope.stack:
		token = ":error:"
		pair = ("error", token)
		scope.stack.append(pair)
		print(pair)
	else:
		op = scope.stack.pop()
		isClosure = True if type(scope.dictionary[op[1]]) is type(Closure()) else False
		if not isClosure:
			op = unary_binds(scope.dictionary, op)
			scope.stack.append(op)

	return scope.stack

def neg_helper(scope):
	if not scope.stack:
		token = ":error:"
		pair = ("error", token)
		scope.stack.append(pair)
		print(pair)
	else:
		op = scope.stack.pop()
		try:
			# check if token is bound
			token = unary_binds(scope.dictionary, op)
			
			if token[0] != "number":
				raise ValueError('NaN')
			num = int(token[1])
			num = -num
			pair = ("number", num)
			scope.stack.append(pair)
			print(pair)
		except ValueError as e:
			print(e)
			scope.stack.append(op)
			token = ":error:"
			pair = ("error", token)
			scope.stack.append(pair)
			print(pair)
	return scope

def swap_helper(scope):
	if len(scope.stack) <= 1:
		token = ":error:"
		pair = ("error", token)
		scope.stack.append(pair)
		print(pair)
	else:
		rhs = scope.stack.pop()
		lhs = scope.stack.pop()
		# swap
		scope.stack.append(rhs)
		scope.stack.append(lhs)
	return scope

def cat_helper(scope):
	if len(scope.stack) <= 1:
		token = ":error:"
		pair = ("error", token)
		scope.stack.append(pair)
		print(pair)
	else:
		right = scope.stack.pop()
		left = scope.stack.pop()
		
		try:
			# check if operands are bound
			lhs, rhs = binary_binds(scope.dictionary, left, right)
			
			if lhs[0] != "string" or rhs[0] != "string":
				raise ValueError('Not a String')
			token = lhs[1] + rhs[1]
			pair = ("string", token)
			scope.stack.append(pair)
			print(pair)

		except ValueError as e:
			print(e)
			token = ":error:"
			pair = ("error", token)
			scope.stack.append(left)
			scope.stack.append(right)
			scope.stack.append(pair)
			print(pair)

	return scope

def if_helper(scope):
	if len(scope.stack) <= 2:
		token = ":error:"
		pair = ("error", token)
		scope.stack.append(pair)
		print(pair)
	else:
		x = scope.stack.pop()
		y = scope.stack.pop()
		z = scope.stack.pop()
		
		try:
			# check if operands are bound
			n = unary_binds(scope.dictionary, z)
			
			if n[0] != "boolean" or n[0] != "boolean":
				raise ValueError('Not a Boolean')
			
			if n[1] == ":true:":
				scope.stack.append(y)
			else:
				scope.stack.append(x)


		except ValueError as e:
			print(e)
			token = ":error:"
			pair = ("error", token)
			scope.stack.append(z)
			scope.stack.append(y)
			scope.stack.append(x)
			scope.stack.append(pair)
			print(pair)

	return scope

def not_helper(scope):
	if not scope.stack:
		token = ":error:"
		pair = ("error", token)
		scope.stack.append(pair)
		print(pair)
	else:
		operand = scope.stack.pop()

		try:
			# check if operand is bound
			op = unary_binds(scope.dictionary, operand)

			if op[0] != "boolean":
				raise ValueError('Not a Boolean')
			# extract truth value
			boolean = True if "true" in op[1] else False
			# get negation
			boolean = ":false:" if boolean else ":true:"
			pair = ("boolean", boolean)
			scope.stack.append(pair)
			print(pair)
		except ValueError as e:
			print(e)
			error = ":error:"
			pair = ("error", error)
			scope.stack.append(operand)
			scope.stack.append(pair)
			print(pair)
		return scope

def bool_helper(scope, op):
	if len(scope.stack) <= 1:
		token = ":error:"
		pair = ("error", token)
		scope.stack.append(pair)
		print(pair)
	else:
		rhs = scope.stack.pop()
		lhs = scope.stack.pop()
		
		try:
			# check if operands are bound
			lhs, rhs = binary_binds(scope.dictionary, lhs, rhs)
			
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
			scope.stack.append(pair)
			print(pair)

		except ValueError as e:
			print(e)
			token = ":error:"
			pair = ("error", token)
			scope.stack.append(lhs)
			scope.stack.append(rhs)
			scope.stack.append(pair)
			print(pair)

	return scope

def let_helper(scope, commands):
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
	# init local scope
	local_scope = Scope()
	local_scope.stack = list()
	local_scope.dictionary = scope.dictionary.copy()
	local_scope = parse(local_scope, lc)
	print("let")
	print(local_scope.stack)
	print("end")
	pair = local_scope.stack.pop()
	scope.stack.append(pair)
	print(scope.stack)

	return scope, commands

def fun_helper(line, scope, commands):
	tokens = line.split()
	funType = tokens[0]
	funName = tokens[1]
	funArg = tokens[2]
	
	try:
		if funName in keywords:
			raise ValueError(str(funName + " is a reserved keyword"))
		if funArg in keywords:
			raise ValueError(str(funArg + " is a reserved keyword"))
		if funName == funArg:
			raise ValueError('Function and argument names cannot be the same')

		# closure scope
		closure = Closure()
		closure.scope = copy.deepcopy(scope)
		closure.scope.dictionary[funName] = closure
		print("env", closure.scope.dictionary)
		# closure code
		code = commands.pop()
		closure.commands.append(code)
		while "funEnd" not in code and not not commands:
			code = commands.pop()
			if "funEnd" not in code:
				closure.commands.append(code)
		# closure param
		closure.arg = funArg
		# bind function name to closure
		scope.dictionary[funName] = closure
		# check if regular fun or inOutFun
		if "inOutFun" in funType:
			closure.type = "inOutFun"
		else:
			closure.type = "fun"
		# push unit
		pair = ("unit", ":unit:")
		scope.stack.append(pair)
		print(pair)

	except ValueError as e:
		print(e)
		error = ":error:"
		pair = ("error", error)
		scope.stack.append(pair)
		print(pair)

	return scope, commands

def call_helper(scope):
	if len(scope.stack) < 2:
		token = ":error:"
		pair = ("error", token)
		scope.stack.append(pair)
		print(pair)
	else:
		funArg = scope.stack.pop()
		funName = scope.stack.pop()
		formal = funArg[1]

		print(funName, funArg)
		try:
			if funName[0] != "name":
				raise ValueError('Function name can only be of type \"name\".')
			if funArg[0] != "name" and funArg[0] != "number" and funArg[0] != "string" and funArg[0] != "boolean" and funArg[0] != "unit":
				raise ValueError('Function argument is invalid')
			if funName[1] not in scope.dictionary:
				raise ValueError('Function is not defined')
			else:
				closure = scope.dictionary[funName[1]]
				if type(closure) is not type(Closure()):
					raise ValueError('Function name is not bound to a closure')
			if funArg[0] == "name" and funArg[1] not in scope.dictionary:
				raise ValueError('Function argument is not bound')
			if funName[1] == funArg[1] and not scope.dictionary[funArg[1]]:
				raise ValueError('Function name and argument cannot be the same')
			else:
				funArg = unary_binds(scope.dictionary, funArg)
			print("stack", scope.stack)
			# print("debug", funArg)

			# store scope
			# init local scope
			fun_scope = Scope()
			fun_scope.dictionary = closure.scope.dictionary.copy()
			fun_scope.dictionary[closure.arg] = funArg
			lc = closure.commands
			print("fun_env", fun_scope.dictionary)
			print("fun_cmd", lc)

			fun_scope = parse(fun_scope, lc)
			# bind if inOutFun
			if "inOutFun" in closure.type:
				print("scope", scope.dictionary)
				print("fun_scope", fun_scope.dictionary)
				scope.dictionary[formal] = fun_scope.dictionary[closure.arg]
			
			if fun_scope.stack:
				pair = fun_scope.stack.pop()
				scope.stack.append(pair)

		except ValueError as e:
			print(e)
			error = ":error:"
			pair = ("error", error)
			scope.stack.append(funName)
			scope.stack.append(funArg)
			scope.stack.append(pair)
			print(pair)
	return scope.stack

def bind_helper(scope):
	if len(scope.stack) <= 1:
		token = ":error:"
		pair = ("error", token)
		scope.stack.append(pair)
		print(pair)
	else:
		rhs = scope.stack.pop()
		lhs = scope.stack.pop()
		
		try:
			if lhs[0] != "name":
				raise ValueError('Not a Name')
			if rhs[0] != "number" and rhs[0] != "string" and rhs[0] != "boolean" and rhs[0] != "unit" and rhs[0] != "name":
				raise ValueError('Not a Valid Value')
			if rhs[0] == "name" and rhs[1] not in scope.dictionary:
				raise ValueError('Name is Unbound')
			elif rhs[0] == "name" and rhs[1] in scope.dictionary:
				value = scope.dictionary[rhs[1]]
				scope.dictionary[lhs[1]] = value 				
				token = ":unit:"
				pair = ("unit", token)
				scope.stack.append(pair)
				print(pair)
			else:
				scope.dictionary[lhs[1]] = rhs 				
				token = ":unit:"
				pair = ("unit", token)
				scope.stack.append(pair)
				print(pair)			

		except ValueError as e:
			print(e)
			token = ":error:"
			pair = ("error", token)
			scope.stack.append(lhs)
			scope.stack.append(rhs)
			scope.stack.append(pair)
			print(pair)

	return scope

interpreter("./input.txt", "./output.txt")