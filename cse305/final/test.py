def mystery(a):
	z = 1
	def subFunction1(b):
		z = 2
		subFunction2(z)
	def subFunction2(d):
		print(z)
	z = 3
	subFunction1(z)
	z = 4
mystery(1)
# def f():
# 	global s
# 	print(s)
# 	s = "3"
# 	print(s)
# s = "4"
# f()
# print(s)

# def mystery(a):
# 	z = 1
# 	def subFunction1(b):
# 		z = 2
# 		subFunction2(z)
# 	def subFunction2(d):
# 		print(z)
# 	z = 3
# 	subFunction1(z)
# 	z = 4

# mystery(1)